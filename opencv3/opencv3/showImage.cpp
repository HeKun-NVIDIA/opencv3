//
//  showImage.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/29.
//  Copyright (c) 2017年 何琨. All rights reserved.
//
//
#include "showImage.h"

int showImage()
{
    //以下3行代码用于完成图像的载入和显示
    cv::String position = "/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";
    Mat namei = imread(position+"namei.jpg");
    namedWindow("namei");
    imshow(position+"/namei", namei);
    waitKey(0);
    //初级图像混合
    //载入图片
    Mat image = imread(position+"dota2.jpg");
    Mat logo = imread(position+"logo.jpg");
    //载入后先显示图片
    namedWindow("原画图");
    imshow("原画图", image);
    waitKey(0);
    namedWindow("logo");
    imshow("logo", logo);
    waitKey(0);
    
    //定义一个mat类，用于存放，图像ROI
    Mat imageROI;
    //方法1
    imageROI = image(Rect(800,300,logo.cols,logo.rows));
    //方法2
    imageROI = image(Range(image.rows-300,image.rows-300+logo.rows),Range(image.cols-300, image.cols-300+logo.cols));
    //将logo加到原图上
    addWeighted(imageROI, 0.5, logo, 0.3, 0, imageROI);
    //显示结果
    namedWindow("原图＋logo");
    imshow("原图＋logo", image);
    imwrite("有imwrite生成的原图加logo.jpg", image);
    waitKey();
    return 0;
}