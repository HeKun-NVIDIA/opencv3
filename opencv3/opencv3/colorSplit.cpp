//
//  colorSplit.cpp
//  opencv3
//
//  Created by 何琨 on 17/2/1.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "colorSplit.h"
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";

int colorSplit()
{
    Mat srcImage;
    Mat imageROI;
    Mat logoImage;
    vector<Mat> channels;
    Mat srcBlueChannel;
    srcImage = imread( position+"dota2.jpg");
    logoImage = imread(position+"logo.jpg",0);
    split(srcImage, channels);
    //利用split函数分离三个channels，0－》蓝色 ，1－》绿色，2－》红色
    srcBlueChannel = channels.at(0);
    imageROI = channels.at(0)(Rect(200,300,logoImage.cols,logoImage.rows));
    addWeighted(imageROI,0, logoImage, 0.5, 0, imageROI);
    merge(channels, srcImage);
    imshow("123", srcImage);
    waitKey(0);
    return 0;
}