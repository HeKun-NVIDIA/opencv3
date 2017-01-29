//
//  main.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/29.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "createAlphaMat.h"
using namespace std;
using namespace cv;
int main(int argc, const char * argv[]) {
    Mat mat(480,640, CV_8UC4);
    createAlphaMat(mat);
    
    vector<int>compression_params;
    compression_params.push_back(IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(9);
    try {
        imwrite("透明Alpha值图.png", mat,compression_params);
        imshow("透明Alpha值图.png", mat);
        fprintf(stdout, "png图片文件的alpha数据保存完毕～\n可以在工程目录下查看有imwrite函数生成的图片\n");
        waitKey(0);
    } catch (runtime_error& ex) {
        fprintf(stderr, "图像转成png格式发生错误：%s\n", ex.what());
        return 1;
    }
    return 0;
}
