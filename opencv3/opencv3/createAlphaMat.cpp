//
//  createAlphaMat.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/29.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "createAlphaMat.h"
void createAlphaMat(Mat &mat)
{
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j<mat.cols; ++j) {
            Vec4b &rgba = mat.at<Vec4b>(i,j);
            rgba[0] = UCHAR_MAX;
            rgba[1] = saturate_cast<uchar>((float (mat.cols-j)) /((float)mat.cols) *UCHAR_MAX);
            rgba[2] = saturate_cast<uchar>((float(mat.rows-i))/((float)mat.rows)*UCHAR_MAX);
            rgba[3] = saturate_cast<uchar>(0.5*(rgba[1]+rgba[2]));
        }
    }
}