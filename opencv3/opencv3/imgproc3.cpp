//
//  imgproc3.cpp
//  opencv3
//
//  Created by 何琨 on 17/2/5.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "imgproc3.h"

const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";
//分别声明原始图，目标图，灰度图，掩模图
Mat g_6_2srcImage, g_6_2dstImage, g_6_2grayImage, g_6_2maskImage;

int g_nFillMode = 1;//漫水填充模式
int g_nLowDifference = 20;//负差最大值
int g_nUpDifference = 20;//正差最大值
int g_nConnectivity =4;//表示flootFill函数标识符底八位的联通值
int g_bIsColor = true; //是否为彩色图的标识符
bool g_bUseMask = false;//是否显示掩模窗口的布尔值
int g_nNewMaskVal =255;//新的重新绘制的像素值

static void onMouse(int event, int x, int y, int, void*)
{
    //若鼠标没有按下，便返回
    if (event != EVENT_LBUTTONDOWN) {
        return;
    }
    //调用floodFill函数之前的参数准备部分
    Point seed = Point(x,y);
    int LowDifference = g_nFillMode == 0? 0:g_nLowDifference;
    int UpDifference = g_nFillMode == 0? 0:g_nUpDifference;
    //标识符的0～7位为g_nConnectivity，8～15位为g_nNewMaskVal左移8位的值，16～23位为CV_FLOODFILL_FIXED_RANGE或者0
    int flags = g_nConnectivity+(g_nNewMaskVal <<8)+(g_nFillMode==1?FLOODFILL_FIXED_RANGE:0);
    //随机生成bgr值
    int b = (unsigned)theRNG()&255;
    int g = (unsigned)theRNG()&255;
    int r = (unsigned)theRNG()&255;
    Rect ccomp;//定义重绘区域的最小边界矩型框
    Scalar newVal = g_bIsColor ? Scalar(b,g,r): Scalar(r*0.299+g*0.587+b*0.114);
    //重绘区域的新像素值，若是彩色图模式，取scalar(b,g,r),若是灰度图模式，取scalar(r*0.299+g*0.587+b*0.114)
    Mat dst = g_bIsColor? g_6_2dstImage:g_6_2grayImage;
    int area;
    if (g_bUseMask) {
        threshold(g_6_2maskImage, g_6_2maskImage, 1, 128, THRESH_BINARY);
        area = floodFill(dst, g_6_2maskImage, seed, newVal,&ccomp,Scalar(LowDifference,LowDifference,LowDifference),flags);
        imshow("mask", g_6_2maskImage);
    }
    else
    {
        area = floodFill(dst, seed, newVal,&ccomp,Scalar(LowDifference,LowDifference,LowDifference),Scalar(UpDifference,UpDifference,UpDifference),flags);
    }
    imshow("dst", dst);
    cout << area << "个像素被重绘\n";
}

int imgproc3()
{
    g_6_2srcImage = imread(position+"namei.jpg");
    if (!g_6_2srcImage.data) {
        printf("读取图片错误，请确认imread的取的图片在目录下");
        return false;
    }
    g_6_2srcImage.copyTo(g_6_2dstImage);
    cvtColor(g_6_2srcImage, g_6_2grayImage, COLOR_BGR2GRAY);
    g_6_2maskImage.create(g_6_2srcImage.rows+2, g_6_2srcImage.cols+2, CV_8UC1);
    namedWindow("dst",WINDOW_AUTOSIZE);
    createTrackbar("lowDifference", "dst", &g_nLowDifference, 255,0);
    createTrackbar("upDifference", "dst", &g_nUpDifference, 255,0);
    setMouseCallback("dst", onMouse,0);
    while (1) {
        imshow("dst", g_bIsColor ? g_6_2dstImage : g_6_2grayImage);
        int c = waitKey(0);
        if ((c&255) == 27) {
            cout << "程序退出................\n";
            break;
        }
        switch ((char)c) {
            case '1':
                if (g_bIsColor) {
                    cout<<"键盘“1”被按下，切换彩色灰度模式，当前操作为将彩色模式切换为灰度模式\n";
                    cvtColor(g_6_2srcImage, g_6_2grayImage, COLOR_BGR2GRAY);
                    g_6_2maskImage = Scalar::all(0);
                    g_bIsColor = false;
                }
                else
                {
                    cout << "键盘“1”被按下，切换彩色灰度模式，当前操作为将彩色模式切换为灰度模式\n";
                    g_6_2srcImage.copyTo(g_6_2dstImage);
                    g_6_2maskImage = Scalar::all(0);
                    g_bIsColor = true;
                }
                break;
            case '2':
                if (g_bUseMask) {
                    destroyWindow("mask");
                    g_bUseMask = false;
                }
                else
                {
                    namedWindow("mask",0);
                    g_6_2maskImage = Scalar::all(0);
                    imshow("mask", g_6_2maskImage);
                    g_bUseMask =true;
                }
                break;
            case '3':
                cout << "按键“3”被按下，恢复原始图像\n";
                g_6_2srcImage.copyTo(g_6_2dstImage);
                cvtColor(g_6_2dstImage, g_6_2grayImage, COLOR_BGR2GRAY);
                g_6_2maskImage = Scalar::all(0);
                break;
            case '4':
                cout << "按键“4”被按下，使用空范围的漫水填充\n";
                g_nFillMode =0;
                break;
            case '5':
                cout <<"按键“5”被按下，使用渐变、固定范围的漫水填充\n";
                g_nFillMode =1;
                break;
            case '6':
                cout << "按键“6”被按下，使用渐变、浮动范围的漫水填充\n";
                g_nFillMode = 2;
                break;
            case 7:
                cout << "按键“7”被按下，操作标志符的低八位使用4位链接模式\n";
                g_nConnectivity = 4;
                break;
            case '8':
                cout << "按键“8”被按下，操作标志符的底八位使用8位链接模式\n";
                g_nConnectivity = 8;
                break;
        }
    }
    return 0;
}








