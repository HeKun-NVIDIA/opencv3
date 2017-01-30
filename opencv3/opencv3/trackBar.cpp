//
//  trackBar.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/30.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "trackBar.h"

//全局变量声明
const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider;//滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

//声明存储图像变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

//响应滑动条的回调函数

void on_Trackbar( int, void*)
{
    g_dAlphaValue = (double) g_nAlphaValueSlider/g_nMaxAlphaValue;
    g_dBetaValue = (1.0-g_dAlphaValue);
    //根据alpha和beta值进行线性混合
    addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
    imshow(WINDOW_NAME, g_dstImage);
}

int trackBar()
{
    g_srcImage1 = imread(position+"qiaodan1.jpeg");
    g_srcImage2 = imread(position+"qiaodan2.jpg");
    if (!g_srcImage1.data) {
        cout << "读取第一幅图片出现错误，请确认当前目录下存在该图片"<<endl;
        return -1;
    }
    if (!g_srcImage2.data) {
        cout << "读取第二幅图片出现错误，请确认当前目录下存在该图片"<<endl;
        return -1;
    }
    //设置滑动条初始值为70
    g_nAlphaValueSlider = 70;
    //创建窗体
    namedWindow(WINDOW_NAME,1);
    //在创建的窗体中创建一个滑动条控件
    char TrackbarName[50];
    sprintf(TrackbarName, "透明值 %d",g_nMaxAlphaValue);
    createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue,on_Trackbar);
    on_Trackbar(g_nAlphaValueSlider, 0);
    waitKey(0);
    
    return 0;
}