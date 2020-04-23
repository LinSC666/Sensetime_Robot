#include "utils.h"

static const float kMean[3] = { 0.485f, 0.456f, 0.406f };
static const float kStdDev[3] = { 0.229f, 0.224f, 0.225f };

float* Normalize(cv::Mat &img,float* data){
    for (int c = 0; c < 3; ++c){
        for (int i = 0; i < img.rows; ++i){
            cv::Vec3b *p1 = img.ptr<cv::Vec3b>(i);
            for (int j = 0; j < img.cols; ++j){
                data[c * img.cols * img.rows + i * img.cols + j]
                    = (p1[j][c] / 255.0f - kMean[c]) / kStdDev[c];
            }
        }
    }
}

void ImagePreprocess(cv::Mat& inputImage, int inputWidth, int inputHeight,
        float* inputImageFloat){
    if (inputImage.empty()){
        gLogError << "The input image is empty"<<endl;
    }
    //padding image
    float hw_ratio = (float)inputHeight / (float)inputWidth;
    int origin_h = inputImage.rows;
    int origin_w = inputImage.cols;
    int crop_w = origin_w;
    int crop_h = origin_h;
    if ((float)origin_h / (float)origin_w >= hw_ratio) {
        crop_w = (int)std::round((float)origin_h / hw_ratio);
    } else {
        crop_h = (int)std::round(origin_w * hw_ratio);
    }
    int pad_h = std::max(crop_h, 0) - origin_h;
    int pad_w = std::max(crop_w, 0) - origin_w;
    int pad_h_half = (int)std::round(pad_h / 2);
    int pad_w_half = (int)std::round(pad_w / 2);
    if (pad_h > 0 || pad_w > 0) {
    cv::Scalar padding_value(0, 0, 0);
    cv::copyMakeBorder(inputImage, inputImage, pad_h_half, pad_h - pad_h_half, pad_w_half,
                        pad_w - pad_w_half, cv::BORDER_CONSTANT, padding_value);
    }
    cv::Mat scaledImage = cv::Mat(inputHeight,inputWidth,CV_8UC3,cv::Scalar(0,0,0));
    cv::resize(inputImage,scaledImage,scaledImage.size(),0,0,cv::INTER_CUBIC);
    cv::cvtColor(scaledImage, scaledImage, cv::COLOR_BGR2RGB);
    Normalize(scaledImage,inputImageFloat);
}

void copy2Mat(float* outputFlow, cv::Mat& outputMat){
    float *tmp = outputFlow;
    for (int i = 0; i < outputMat.rows; ++i){
        float *p = outputMat.ptr<float>(i);
        for (int j = 0; j < outputMat.cols; ++j){
        *p = *tmp;
        p++;
        tmp++;
        }
    }
}

std::vector<std::string> split(const std::string& str, const std::string& delim){
   std::vector<std::string> tokens;
   size_t prev = 0, pos = 0;
   do{
       pos = str.find(delim, prev);
       if (pos == std::string::npos) pos = str.length();
       std::string token = str.substr(prev, pos-prev);
       if (!token.empty()) tokens.push_back(token);
       prev = pos + delim.length();
   }
   while (pos < str.length() && prev < str.length());
   return tokens;
}

void parse_image_name(std::string& line, std::string& image_name){
    std::vector<std::string> tmp_v;
    tmp_v = split(line, " ");
    tmp_v = split(tmp_v[0], "/");
    image_name =  tmp_v[2];
}

int* get_top_k_indices(float* ptr, int k, int len){
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>,
                        std::greater <std::pair<float, int>> > q;
    for(int i = 0; i < len; i++){
        if(q.size() < k){
            q.push(std::pair<float, int>(ptr[i], i));
        }
        else if(ptr[i] > q.top().first){
            q.pop();
            q.push(std::pair<float, int>(ptr[i], i));
        }
    }

    int* output = new int[k];
    k = q.size();
    for(int i = 0; i < k; i++){
        output[k - i - 1] = q.top().second;
        q.pop();
    }
    return output;
}

void store_image(cv::Mat& inputImage, string image_name, string path){
    printf("write image : %s \n", image_name.c_str());
    cv::imwrite(path+image_name, inputImage);
}

void store_result(int x1, int y1, int x2, int y2, float score, int cls,string image_name,string path){
    std::vector<std::string> tmp_v;
    tmp_v = split(image_name, ".");
    image_name = tmp_v[0];
    std::ofstream output_file;
    std::string filename = path + image_name + ".txt";
    output_file.open(filename, std::ios::app);
    output_file << x1 << "\n";
    output_file << y1 << "\n";
    output_file << x2 << "\n";
    output_file << y2 << "\n";
    output_file << score << "\n";
    output_file << cls << "\n";
    output_file << "\n";
    output_file.close();
}

void draw_rectangle(cv::Mat& img, int up_left_x, int up_left_y,
                       int bottom_right_x, int bottom_right_y, int cls){
    cv::Point up_left(up_left_x, up_left_y);
    cv::Point bottom_right(bottom_right_x, bottom_right_y);
    if(cls == 1){
        rectangle(img, up_left, bottom_right, cv::Scalar(255, 0, 0), 1);
    }
    else if(cls == 2){
        rectangle(img, up_left, bottom_right, cv::Scalar(0, 255, 0), 1);
    }
}
