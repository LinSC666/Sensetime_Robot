#ifndef BASE_NET_H
#define BASE_NET_H
#include "common.h"
#include "base_engine.h"
#include "utils.h"

const static int OUTPUT_NUM = 3;
//const static string engineFile = "../model/oap_320_add_upsample_1222_05_nms.engine";
const static string engineFile = "../model/oap_mobilenet.engine";
const static bool IS_CUSTOM_OUTPUT_NAME = 1;
const static bool STORE_RESULT_IMG = 0;
const static bool STORE_FINAL_RESULT = 0;

#define IMAGE_OUTPUT_PATH  "../result_img/"
#define RESULT_PATH  "../result_output/"

struct RealWorldCoordinate {
    cv::Point2f bottom_left, bottom_right;
};

class OAPNet{
public:
    OAPNet(const BaseEngine&);
    ~OAPNet();
    std::vector<RealWorldCoordinate>  Run(cv::Mat&, string, const BaseEngine&);
    const ICudaEngine &engine;
    float avg_infer_time;
    void getDistanceByHomograph(vector<cv::Point2f> &img_pts, const cv::Mat &homograph_matrix);

    struct DetectObjects {
    int x, y, h, w, cls;
    int up_left_x, up_left_y, bottom_right_x, bottom_right_y, bottom_left_x, bottom_left_y;
    float score;
    };

private:
    cudaStream_t cuStream;
    void* buffers[OUTPUT_NUM + 1];
    float* inputFlow;
    float* outputFlow[OUTPUT_NUM];
    int OUTPUT_SIZE[OUTPUT_NUM], OUTPUT_HM_W, OUTPUT_HM_H;
    int INPUT_C, INPUT_H, INPUT_W;
    int inputIndex, outputIndex[OUTPUT_NUM], batchSize;

    std::vector<RealWorldCoordinate> PostProcess(float*, float*, float*, int, int, cv::Mat&, string);
    void PreProcess(cv::Mat&);
};
#endif
