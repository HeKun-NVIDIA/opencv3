//
//  imgproc2.cpp
//  opencv3
//
//  Created by 何琨 on 17/2/4.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "imgproc2.h"
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";
Mat g_6_1srcImage;
Mat g_6_1dstImage;

int g_nElementShape = cv::MORPH_RECT;
//变量接受的Trackbar位置参数
int g_nMaxIterationNum = 10;
int g_nOpenCloseNum =0;
int g_nErodeDilateNum = 0;
int g_nTopBlackHatNum = 0;
//全局函数声明
static void on_OpenClose(int,void*);
static void on_ErodeDilate(int,void*);
static void on_TopBlackHat(int,void*);

int imgproc2()
{
    g_6_1srcImage = imread(position+"namei.jpg");
    if (!g_6_1srcImage.data) {
        printf("读取srcimage错误，请确认imread读取的图片存在目录下面 ");
    }
    namedWindow("srcImage");
    imshow("srcImage", g_6_1srcImage);
    //创建3个窗口
    namedWindow("openClose",1);
    namedWindow("erodeDilate",1);
    namedWindow("topBlack",1);
    //参数赋值
    g_nOpenCloseNum = 9;
    g_nErodeDilateNum = 9;
    g_nTopBlackHatNum = 2;
    //分别给三个窗口创建滚动条
    createTrackbar("iterator", "openClose", &g_nOpenCloseNum, g_nMaxIterationNum*2+1,on_OpenClose);
    createTrackbar("iterator", "erodeDilate", &g_nErodeDilateNum, g_nMaxIterationNum*2+1,on_ErodeDilate);
    createTrackbar("iterator", "topBlack", &g_nTopBlackHatNum, g_nMaxIterationNum*2+1,on_TopBlackHat);
    //轮询获取案件信息
    while (1) {
        int c;
        //执行回调函数
        on_OpenClose(g_nOpenCloseNum, 0);
        on_ErodeDilate(g_nErodeDilateNum, 0);
        on_TopBlackHat(g_nTopBlackHatNum, 0);
        
        c = waitKey(0);
        if ((char)c == 'q' || (char)c == 27) {
            break;
        }
        if ((char)c==49) {
            g_nElementShape = cv::MORPH_ELLIPSE;
        }else if ((char) c==50)
        {
            g_nElementShape = cv::MORPH_RECT;
        }else if ((char)c==51)
        {
            g_nElementShape = cv::MORPH_CROSS;
        }else if ((char) c==' ')
        {
            g_nElementShape = (g_nElementShape+1)%3;
        }
    }
    return 0;
}
//开运算／闭运算 窗口回调函数
static void on_OpenClose(int,void*)
{
    int offset = g_nOpenCloseNum-g_nMaxIterationNum;//偏移量
    int Absolute_offset;
    Absolute_offset = offset > 0 ? offset : -offset;
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
    //进行操作
    if (offset <0) {
        morphologyEx(g_6_1srcImage, g_6_1dstImage, MORPH_OPEN, element);
    }
    else
    {
        morphologyEx(g_6_1srcImage, g_6_1dstImage, MORPH_CLOSE, element);
    }
    imshow("openClose", g_6_1dstImage);
}

//腐蚀／膨胀窗口回调函数
static void on_ErodeDilate(int,void*)
{
    int offset = g_nErodeDilateNum-g_nMaxIterationNum;
    int Absolute_offset = offset>0? offset : -offset;
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
    if (offset>0) {
        erode(g_6_1srcImage, g_6_1dstImage, element);
    }
    else{
        dilate(g_6_1srcImage, g_6_1dstImage, element);
    }
    imshow("erodeDilate", g_6_1dstImage);
}

//顶帽运算／黑帽运算
static void on_TopBlackHat(int,void*)
{
    int offset = g_nTopBlackHatNum-g_nMaxIterationNum;
    int Absolute_offset = offset > 0? offset : -offset;
    Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
    if (offset > 0) {
        morphologyEx(g_6_1srcImage, g_6_1dstImage, MORPH_TOPHAT, element);
    }
    else
    {
        morphologyEx(g_6_1srcImage, g_6_1dstImage, MORPH_BLACKHAT, element);
    }
    imshow("topBlack", g_6_1dstImage);
}






