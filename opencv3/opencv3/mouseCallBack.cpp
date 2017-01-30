//
//  mouseCallBack.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/30.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "mouseCallBack.h"

#define WINDOW_NAME "程序窗口"

//全局函数声明
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat &img, cv::Rect box);
void ShowHelpText();

//全局变量声明
Rect g_rectangle;
bool g_bDrawingBox = false;//是否进行绘制
RNG g_rng(12345);

//控制台应用程序入口
int mousecallback()
{
    g_rectangle = Rect(-1,-1,0,0);
    Mat srcImage(800,480,CV_8UC3);
    Mat tempImage;
    srcImage.copyTo(tempImage);
    g_rectangle = Rect(-1,-1,0,0);
    srcImage = Scalar::all(0);
    //设置鼠标操作回调函数
    namedWindow(WINDOW_NAME);
    setMouseCallback(WINDOW_NAME, on_MouseHandle,(void*) &srcImage);
    while (1) {
        srcImage.copyTo(tempImage);//复制原图到临时变量
        if (g_bDrawingBox) {
            DrawRectangle(tempImage, g_rectangle);
            //当进行绘制的标识符为真，则进行绘制
        }
        imshow(WINDOW_NAME, tempImage);
        if (waitKey(10) == 27) {
            break;//按下ESC键，退出程序
        }
    }
    return 0;
}

void on_MouseHandle(int event,int x, int y, int flags, void* param)
{
    Mat& image = *(cv::Mat*) param;
    switch (event) {
        //鼠标移动时的响应
        case EVENT_MOUSEMOVE:
        {
            if (g_bDrawingBox) {
                g_rectangle.width=x-g_rectangle.x;
                g_rectangle.height=y-g_rectangle.y;
            }
            break;
        }
        //鼠标左键按下时的响应
        case EVENT_LBUTTONDOWN:
        {
            g_bDrawingBox = true;
            g_rectangle = Rect(x,y,0,0);
        }
            break;
        //鼠标左键弹起时的响应
        case EVENT_LBUTTONUP:
        {
            g_bDrawingBox=false;
            if (g_rectangle.width<0) {
                g_rectangle.x += g_rectangle.width;
                g_rectangle.width *= -1;
            }
            if (g_rectangle.height<0) {
                g_rectangle.y += g_rectangle.height;
                g_rectangle.height *=-1;
            }
            //调用函数进行绘制
            DrawRectangle(image, g_rectangle);
        }
    }
}
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
    
    rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255),g_rng.uniform(0, 255),g_rng.uniform(0, 255)));
}






