//
//  colorReduce.h
//  opencv3
//
//  Created by 何琨 on 17/1/31.
//  Copyright (c) 2017年 何琨. All rights reserved.
//
//
#ifndef __opencv3__colorReduce__
#define __opencv3__colorReduce__

#include <stdio.h>
#include "include.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#endif /* defined(__opencv3__colorReduce__) */

void colorReduce1(Mat& inputImage, Mat& outputImage, int div);//指针
void colorReduce2(Mat& inputImage, Mat& outputImage, int div);//迭代器
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);
int main1();
//const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";
