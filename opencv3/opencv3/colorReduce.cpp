//
//  colorReduce.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/31.
//  Copyright (c) 2017年 何琨. All rights reserved.
//
//
#include "colorReduce.h"
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";

int main1()
{
    Mat srcImage = imread(position+"namei.jpg");
    if (!srcImage.data) {
        cout<< "原始图像加载失败" <<endl;
        return -1;
    }
    imshow("srcImage", srcImage);
    Mat dstImage;
    dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());
    double time0 = static_cast<double>(getTickCount());
    colorReduce1(srcImage, dstImage, 128);
    time0 = ((double)getTickCount()-time0)/getTickFrequency();
    cout <<"指针操作像素运行时间为："<<time0<<"秒"<<endl;
    imshow("dstImage1", dstImage);
    time0 = static_cast<double>(getTickCount());
    colorReduce2(srcImage, dstImage, 128);
    time0 = ((double)getTickCount()-time0)/getTickFrequency();
    cout <<"迭代器操作像素运行时间为："<<time0<<"秒"<<endl;
    imshow("dstImage2", dstImage);
    time0 = static_cast<double>(getTickCount());
    colorReduce3(srcImage, dstImage, 128);
    time0 = ((double)getTickCount()-time0)/getTickFrequency();
    cout <<"动态地址操作像素运行时间为："<<time0<<"秒"<<endl;
    imshow("dstImage3", dstImage);
    waitKey(0);
    return 0;
}
//用指针操作像素
void colorReduce1(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols;
    //双重循环，遍历所有像素值
    for (int i = 0; i<rowNumber; i++) {
        uchar* data = outputImage.ptr<uchar>(i);
        for (int j =0; j<colNumber*outputImage.channels(); j++) {
            data[j] = data[j]/div*div+div/2;
        }
    }
}
  //用迭代器操作像素
void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
    //参数准备
    outputImage = inputImage.clone();
    Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();
    Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();
    for (; it != itend; ++it) {
        (*it)[0] = (*it)[0]/div*div +div/2;
        (*it)[1] = (*it)[1]/div*div +div/2;
        (*it)[2] = (*it)[2]/div*div+div/2;
    }
}

//用动态地址运算配合at
void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
    outputImage = inputImage.clone();
    int rowNumber = outputImage.rows;
    int colNumber = outputImage.cols;
    
    for (int i = 0;  i<rowNumber; i++) {
        for (int j = 0;  j<colNumber; j++) {
            for (int x = 0; x<outputImage.channels(); x++) {
                outputImage.at<Vec3b>(i,j)[x] = outputImage.at<Vec3b>(i, j)[x]/div*div+div/2;
            }
        }
    }
}
    
    
