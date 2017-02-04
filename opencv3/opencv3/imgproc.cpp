//
//  imgproc.cpp
//  opencv3
//
//  Created by 何琨 on 17/2/4.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "imgproc.h"
//全局变量声明
Mat g_nsrcImage;
Mat g_ndstImage1,g_ndstImage2,g_ndstImage3,g_ndstImage4,g_ndstImage5;
int g_nBoxFilterValue = 3;
int g_nMeanFilterValue = 3;
int g_nGaussianFilterValue =3;
int g_nMedianBlurValue = 10;
int g_nBilateralFilterValue = 10;
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";

//轨迹条的回调函数
static void on_BoxFilter(int,void*);
static void on_MeanFilter(int,void*);
static void on_GaussianFilter(int,void*);
static void on_MedianBlur(int,void*);
static void on_BilateralFilter(int,void*);
int test()
{
    g_nsrcImage = imread(position+"qiaodan2.jpg");
    if (!g_nsrcImage.data) {
        printf("图片读取错误，请确认imread函数读取的图片存在于目录下");
    }
    g_ndstImage1=g_nsrcImage.clone();
    g_ndstImage2=g_nsrcImage.clone();
    g_ndstImage3=g_nsrcImage.clone();
    g_ndstImage4=g_nsrcImage.clone();
    g_ndstImage5=g_nsrcImage.clone();
    namedWindow("srcImage",1);
    imshow("srcImage", g_nsrcImage);
    //方块滤波
    namedWindow("boxFilter",1);
    createTrackbar("kernal value", "boxFilter", &g_nBoxFilterValue, 40,on_BoxFilter);
    on_BoxFilter(g_nBoxFilterValue, 0);
    imshow("boxFilter", g_ndstImage1);
    
    //均值滤波
    namedWindow("meanFilter",1);
    createTrackbar("kernal value", "meanFilter", &g_nMeanFilterValue, 40,on_MeanFilter);
    on_MeanFilter(g_nMeanFilterValue, 0);
    
    //高斯滤波
    namedWindow("gaussianFilter",1);
    createTrackbar("kernal value", "gaussianFilter", &g_nGaussianFilterValue, 40,on_GaussianFilter);
    on_GaussianFilter(g_nGaussianFilterValue, 0);
    
    //中值滤波
    namedWindow("medianBlur",1);
    createTrackbar("kernal value", "medianBlur", &g_nMedianBlurValue, 40,on_MedianBlur);
    on_MedianBlur(g_nMedianBlurValue, 0);
    
    
    //双边滤波
    namedWindow("bilateralFilter",1);
    createTrackbar("kernal value", "bilateralFilter", &g_nBilateralFilterValue, 40,on_BilateralFilter);
    on_BilateralFilter(g_nBilateralFilterValue, 0);
    while (char (waitKey(1)) !='q') {}
    
    return 0;
}
static void on_BoxFilter(int,void*)
{
    //方框滤波操作
    boxFilter(g_nsrcImage, g_ndstImage1, -1, Size(g_nBoxFilterValue+1,g_nBoxFilterValue+1));
    imshow("boxFilter", g_ndstImage1);
}
static void on_MeanFilter(int,void*)
{
    //均值滤波操作
    blur(g_nsrcImage, g_ndstImage2, Size(g_nMeanFilterValue+1,g_nMeanFilterValue+1),Point(-1,-1));
    imshow("meanFilter", g_ndstImage2);
}
static void on_GaussianFilter(int,void*)
{
    //高斯滤波操作
    GaussianBlur(g_nsrcImage, g_ndstImage3, Size(g_nGaussianFilterValue*2+1,g_nGaussianFilterValue*2+1), 0,0);
    imshow("gaussianFilter", g_ndstImage3);
}
static void on_MedianBlur(int,void*)
{
    //中值滤波
    medianBlur(g_nsrcImage, g_ndstImage4, g_nMedianBlurValue*2+1);
    imshow("medianBlur", g_ndstImage4);
}
static void on_BilateralFilter(int,void*)
{
    //双边滤波
    bilateralFilter(g_nsrcImage, g_ndstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2);
    imshow("bilateralFilter", g_ndstImage5);
}