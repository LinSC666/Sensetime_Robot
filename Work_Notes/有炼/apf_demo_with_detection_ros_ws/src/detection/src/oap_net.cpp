#include "oap_net.h"
OAPNet::OAPNet(const BaseEngine& baseEngine):batchSize(1),engine(baseEngine.context->getEngine())
{
    avg_infer_time = 0;
    inputIndex = 0;

    Dims inputDims = engine.getBindingDimensions(inputIndex);

    if(IS_CUSTOM_OUTPUT_NAME){
        for(int i = 0; i < OUTPUT_NUM; i++)
            outputIndex[i] = i+1;
    } else {
        outputIndex[0] = engine.getBindingIndex("output");
    }

    Dims outputDims[OUTPUT_NUM];
    for(int i = 0; i < OUTPUT_NUM; i++){
        outputDims[i] = engine.getBindingDimensions(outputIndex[i]);
        //avoid OUTPUTSIZE[i].d == 0
        for(int j = 0; j < 3; j++){
            outputDims[i].d[j] = (outputDims[i].d[j] == 0) ? 1 : outputDims[i].d[j];
        }
    }
    INPUT_C = inputDims.d[0];
    INPUT_H = inputDims.d[1];
    INPUT_W = inputDims.d[2];
    printf("INPUT_SIZE : %d, %d, %d \n", inputDims.d[0], inputDims.d[1], inputDims.d[2]);
    assert(INPUT_C>0&&INPUT_H>0&&INPUT_W>0);

    for(int i = 0; i < OUTPUT_NUM; i++){
        OUTPUT_SIZE[i] = outputDims[i].d[0] * outputDims[i].d[1] * outputDims[i].d[2];
        printf("OUTPUT_SIZE %d : %d, %d, %d \n", i,
            outputDims[i].d[0], outputDims[i].d[1], outputDims[i].d[2]);
        assert(OUTPUT_SIZE[i]>0);
    }
    OUTPUT_HM_W = outputDims[0].d[2];
    OUTPUT_HM_H = outputDims[0].d[1];

    //allocate memory for input and output data
    inputFlow = (float*) malloc(INPUT_C*INPUT_W*INPUT_H*sizeof(float));
    for(int i = 0; i < OUTPUT_NUM; i++)
        outputFlow[i] = (float*) malloc(sizeof(float)*OUTPUT_SIZE[i]);

    //allocate cuda memory and create stream
    CHECK(cudaMalloc(&buffers[inputIndex], batchSize * INPUT_C * INPUT_H * INPUT_W * sizeof(float)));
    for(int i = 0; i < OUTPUT_NUM; i++)
        CHECK(cudaMalloc(&buffers[outputIndex[i]], batchSize * OUTPUT_SIZE[i] * sizeof(float)));

    CHECK(cudaStreamCreate(&cuStream));
}

OAPNet::~OAPNet(){
    free(inputFlow);
    cudaStreamDestroy(cuStream);
    CHECK(cudaFree(buffers[inputIndex]));
    for(int i = 0; i < OUTPUT_NUM; i++){
        CHECK(cudaFree(buffers[outputIndex[i]]));
        free(outputFlow[i]);
    }
}

std::vector<RealWorldCoordinate> OAPNet::Run(cv::Mat& inputImage, string image_name,
                                    const BaseEngine& OAPEngine){
    // std::cout << "Before PreProcess() size = " << inputImage.cols << "X" << inputImage.rows << std::endl;
    PreProcess(inputImage);
    // std::cout << "After PreProcess() size = " << inputImage.cols << "X" << inputImage.rows << std::endl;
    auto start_chrono = chrono::steady_clock::now();
    cudaMemcpyAsync(buffers[inputIndex], inputFlow, batchSize * INPUT_C * INPUT_H * INPUT_W *
                        sizeof(float), cudaMemcpyHostToDevice, cuStream);

    OAPEngine.context->enqueue(batchSize, buffers, cuStream, nullptr);

    for(int i = 0; i < OUTPUT_NUM; i++)
        CHECK(cudaMemcpyAsync(outputFlow[i], buffers[outputIndex[i]], batchSize * OUTPUT_SIZE[i] *
                                sizeof(float), cudaMemcpyDeviceToHost, cuStream));

    cudaStreamSynchronize(cuStream);
    cout << "infer_T: "
         << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()
                            - start_chrono).count() << endl;
    avg_infer_time += chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()
                            - start_chrono).count();

    // std::cout << "Before PostProcess() size = " << inputImage.cols << "X" << inputImage.rows << std::endl;
    return PostProcess(outputFlow[0], outputFlow[1], outputFlow[2],
                        OUTPUT_HM_W, OUTPUT_HM_H, inputImage, image_name);
}

void OAPNet::PreProcess(cv::Mat& inputImage){
    ImagePreprocess(inputImage,INPUT_W,INPUT_H,inputFlow);
}

void OAPNet::getDistanceByHomograph(vector<cv::Point2f> &img_pts, const cv::Mat &homograph_matrix) {
    cv::perspectiveTransform(img_pts, img_pts, homograph_matrix);
}

std::vector<RealWorldCoordinate> OAPNet::PostProcess(
                                    float* hm, float* wh, float* reg,
                                    int input_w, int input_h,
                                    cv::Mat& inputImage, string image_name)
{
    int k = 20;
    int* top_k_indices = get_top_k_indices(hm, k, OUTPUT_SIZE[0]);
    int scale = 4;
    int output_w = scale * input_w;
    int output_h = scale * input_h;
    int threshold = 0.3;
    int obj_num = 0;
    std::vector<DetectObjects> obj;
    cv::Mat outputImage = cv::Mat::ones(cv::Size(INPUT_W, INPUT_H), CV_64F);
    if(STORE_RESULT_IMG){
        cv::resize(inputImage, outputImage, outputImage.size(),0,0,cv::INTER_CUBIC);
    }

    for(int i = 0; i < k; i++){
        if(hm[top_k_indices[i]] < 0.3){
            if(STORE_RESULT_IMG){
                store_image(outputImage, image_name, IMAGE_OUTPUT_PATH);
            }
            break;
        }
        DetectObjects tmp;
        tmp.score = hm[top_k_indices[i]];
        tmp.cls = top_k_indices[i] / (input_w*input_h);
        obj.push_back(tmp);
        top_k_indices[i] = top_k_indices[i] % (input_w*input_h);
        obj_num ++;
    }

    int reg_top_k[obj_num];
        for(int i = 0; i < obj_num; i++){
        reg_top_k[i] = (top_k_indices[i] + reg[top_k_indices[i]] +
                       (int)reg[top_k_indices[i] + input_w*input_h] * input_w);
        if(reg_top_k[i] > scale*input_h*input_w || reg_top_k[i] <0)
            reg_top_k[i] = 0;
    }

    double h[3][3] = {{-1.0921e-03, 4.08185e-04, 4.28306e-01},
                      {3.09506e-06, -6.5860e-04, -7.5276e-01},
                      {-1.2194e-05, -8.2926e-03, 1.0}};

    cv::Mat homograph_matrix = cv::Mat(3, 3, CV_64F, h);
    std::vector<RealWorldCoordinate> output_results;

    for(int i = 0; i < obj_num; i++){
        obj[i].w = scale * wh[reg_top_k[i]];
        obj[i].h = scale * wh[reg_top_k[i] + input_w*input_h];
        obj[i].x = (top_k_indices[i]*scale % output_w) ;
        obj[i].y = (top_k_indices[i]*scale*scale / output_w);

        obj[i].up_left_x      = (int)(obj[i].x - obj[i].w/2);
        obj[i].up_left_y      = (int)(obj[i].y - obj[i].h/2);
        obj[i].bottom_right_x = (int)(obj[i].x + obj[i].w/2);
        obj[i].bottom_right_y = (int)(obj[i].y + obj[i].h/2);
        obj[i].bottom_left_x  = (int)(obj[i].x - obj[i].w/2);
        obj[i].bottom_left_y  = (int)(obj[i].y + obj[i].h/2);

        // resize to undistort size 919*515 and return bottom_right & bottom_left
        // int big_bottom_right_x = obj[i].bottom_right_x / 480.0 * 919.0;
        // int big_bottom_right_y = (obj[i].bottom_right_y-26) / 320.0 * 515.0;
        // int big_bottom_left_x  = obj[i].bottom_left_x  / 480.0 * 919.0;
        // int big_bottom_left_y  = (obj[i].bottom_left_y-26)  / 320.0 * 515.0;

        double ratio = 919.0/480.0;
        int big_bottom_right_x = obj[i].bottom_right_x * ratio;
        int big_bottom_right_y = obj[i].bottom_right_y * ratio - 49;
        int big_bottom_left_x  = obj[i].bottom_left_x  * ratio;
        int big_bottom_left_y  = obj[i].bottom_left_y  * ratio - 49;

        std::vector<cv::Point2f> img_pts;
        img_pts.push_back(cv::Point2f(big_bottom_left_x, big_bottom_left_y));
        img_pts.push_back(cv::Point2f(big_bottom_right_x, big_bottom_right_y));
        getDistanceByHomograph(img_pts, homograph_matrix);
        cv::Point2f output_bottom_left = img_pts[0];
        cv::Point2f output_bottom_right = img_pts[1];

        RealWorldCoordinate tmp;
        tmp.bottom_left = img_pts[0];
        tmp.bottom_right = img_pts[1];
        output_results.push_back(tmp);

        if(STORE_FINAL_RESULT){
            // if (NULL == opendir(RESULT_PATH))
            //     mkdir(RESULT_PATH, 0777);
            store_result(obj[i].up_left_x, obj[i].up_left_y,
                         obj[i].bottom_right_x,obj[i].bottom_right_y,
                         obj[i].score, obj[i].cls,
                         image_name, RESULT_PATH);
        }

        draw_rectangle(inputImage, obj[i].up_left_x*ratio, obj[i].up_left_y*ratio,
                          obj[i].bottom_right_x*ratio, obj[i].bottom_right_y*ratio, obj[i].cls);

        if(STORE_RESULT_IMG){
            draw_rectangle(outputImage, obj[i].up_left_x, obj[i].up_left_y,
                          obj[i].bottom_right_x, obj[i].bottom_right_y, obj[i].cls);
        }
    }

    if(STORE_RESULT_IMG){
        // if (NULL == opendir(IMAGE_OUTPUT_PATH))
        //     mkdir(IMAGE_OUTPUT_PATH, 0777);
        store_image(outputImage, image_name, IMAGE_OUTPUT_PATH);
    }

    // std::cout << "After PostProcess() size = " << inputImage.cols << "X" << inputImage.rows << std::endl;

    return output_results;
 }
