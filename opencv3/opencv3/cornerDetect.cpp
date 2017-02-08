//
//  cornerDetect.cpp
//  opencv3
//
//  Created by 何琨 on 17/2/8.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "cornerDetect.h"
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";
int pdistance(Point,Point);
int cornerDetect()
{
    Mat c_dstImage,normImage;
    Mat c_srcImage = imread(position+"4.pic.jpg",0);
    imshow("srcaImage",c_srcImage);
    
    Mat cornerStrength;
    cornerHarris(c_srcImage, cornerStrength, 2, 3, 0.01);
    imshow("cornerStrength", cornerStrength);
    waitKey(0);
    Mat harrisCorner;
    threshold(cornerStrength, harrisCorner, 0.0001, 255, THRESH_BINARY);
    imshow("harriscorner", harrisCorner);
    waitKey(0);
    normalize(cornerStrength, normImage,0,255,NORM_MINMAX,CV_32FC1,Mat());
    convertScaleAbs(normImage, c_dstImage);
    for (int j =0 ; j < normImage.rows; j++) {
        for (int i = 0 ; i < normImage.cols; i++) {
            if ((int) normImage.at<float>(j,i)>50) {
                cout << "i , j: "<< i << " , " << j<<endl;
                circle(c_srcImage, Point(i,j), 5, Scalar(0,0,255),2,8,0);
            }
        }
    }
    imshow("c_srcImage1", c_srcImage);
    waitKey(0);
    return 0;
}
int pdistance1(Point a,Point b)
{
    return sqrt(double((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
}