//
//  contrastAndBright.cpp
//  opencv3
//
//  Created by 何琨 on 17/2/3.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "contrastAndBright.h"
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";

static void on_ContrastAndBright(int, void*);
int g_nContrastValue;
int g_nBrightValue;
Mat g_srcImage;
Mat g_ndstImage;

int contrastAndBright()
{
    g_srcImage = imread(position+"namei.jpg");
    if( !g_srcImage.data)
    {
        printf("读取图片错误，请确定目录下面时候有imread函数指定的图片");
        return -1;
    }
    g_ndstImage = Mat::zeros(g_srcImage.rows, g_srcImage.cols, g_srcImage.type());
    g_nContrastValue = 80;
    g_nBrightValue =80;
    namedWindow("123",1);
        
    createTrackbar("bright", "123", &g_nBrightValue, 300,on_ContrastAndBright);
    createTrackbar("contrast", "123", &g_nContrastValue, 200,on_ContrastAndBright);
    while(char(waitKey(1)) != 'q');
    return 0;
}
static void on_ContrastAndBright(int, void*)
{
    namedWindow("123",1);
    for( int y=0; y<g_srcImage.rows;y++)
    {
        for(int x=0; x<g_srcImage.cols;x++)
        {
            for(int c = 0; c<g_srcImage.channels();c++)
            {
                g_ndstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c])+g_nBrightValue);
            }
        }
    }
    
    imshow("1234", g_srcImage);
    imshow("123", g_ndstImage);
}