//
//  imageROI.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/31.
//  Copyright (c) 2017年 何琨. All rights reserved.
//
//
#include "imageROI.h"
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";
int imageRoi()
{
    Mat srcImage = imread(position+"dota2.jpg");
    Mat logoImage = imread(position+"logo.jpg");
    if (!srcImage.data) {
        printf("读取srcImage 失败 ～！");
    }
    if (!logoImage.data) {
        printf("读取logoImage 失败～！");
    }
    //利用rect方法建立image ROI
    Mat imageROI = srcImage(Rect(200,300,logoImage.cols,logoImage.rows));
    //利用range方法建立image ROI
    Mat imageROI1 = srcImage(Range(200, 200+logoImage.rows),Range(300, 300+logoImage.cols));
    Mat mask = imread(position+"logo.jpg",cv::IMREAD_GRAYSCALE);
    logoImage.copyTo(imageROI, logoImage);
    imshow("123", srcImage);
    waitKey(0);
    return 0;
}