//
//  ROI_LinearBlending.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/31.
//  Copyright (c) 2017年 何琨. All rights reserved.
//
//
#include "ROI_LinearBlending.h"
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";
int ROI_LinearBlending()
{
    Mat srcImage = imread(position+"shuidi.jpeg",1);
    Mat logoImage = imread(position+"xiaocao.jpeg");
    Mat imageRoi;
    imageRoi = srcImage(Rect(0,0,logoImage.cols,logoImage.rows));
    //addWeighted参数含义
    //第一个参数和第三个参数分别表示两张要融合的图片
    //第二个参数和第四个参数分别表示两个融合的图片的权重
    //第五个参数表示增加的亮度，最后一个表示融合之后的图片保存的地方
    addWeighted(imageRoi, 0.5, logoImage, 0.3,-100, imageRoi);
    namedWindow("123",WINDOW_NORMAL);
    imshow("123", srcImage);
    waitKey(0);
    return 0;
}