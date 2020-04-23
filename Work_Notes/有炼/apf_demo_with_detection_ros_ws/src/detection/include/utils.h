#include "common.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <sys/stat.h>


typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<double, std::ratio<1, 1000>> ms;
typedef std::chrono::duration<float> fsec;

std::vector<std::string> split(const std::string&, const std::string&);

void GetFileNames(std::string path, std::vector<std::string>&);

void write_result_file(float**, std::string, const int*);

void parse_image_name(std::string& , std::string&);

void printHelpInfo();

void ImagePreprocess(cv::Mat&, int, int, float*);

float* Normalize(cv::Mat&, float*);

void copy2Mat(float*, cv::Mat&);

int* get_top_k_indices(float*, int, int);

void draw_rectangle(cv::Mat&, int, int, int, int, int);

void store_image(cv::Mat&, string, string);

void store_result(int, int, int, int, float, int, string, string);