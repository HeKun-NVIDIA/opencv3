//
//  matFoundation.cpp
//  opencv3
//
//  Created by 何琨 on 17/1/30.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "matFoundation.h"
int matFoundation()
{
    //显示创建Mat对象的几种方法
    //第一种
    Mat M(20,20,CV_8UC3,Scalar(0,125,255));//CV_[the number of bits per item][Signed or Unsigned]C[The channel number]
    cout << "M = " << endl <<" "<< M <<endl;
    //第二种
    int sz[3] = {2,2,2};
    Mat L(3,sz[0],CV_8UC3,Scalar::all(0));
    cout << "L = " << endl <<" "<< L <<endl;
    //第三种
    /*char* file;
    sprintf(file, "%snamei.jpg",position);
    IplImage* img = cvLoadImage(file,1);
    Mat mtx(img);*/
    //二维点和三维点的定义和输出
    Point2f p(6,2);
    Point3f p3f(8,2,0);
    cout<< "二维点 p："<<p<<endl;
    cout<<"三维点 p："<<p3f<<endl;
    //定义和输出基于Mat的std::vector
    vector<float> v;
    v.push_back(3);
    v.push_back(5);
    v.push_back(7);
    cout << "基于Mat的vector shortvec："<<Mat(v)<<";\n"<<endl;
    //定义和输出std::vector point
    vector<Point2f> points(20);
    for (size_t i = 0; i<points.size(); ++i) {
        points[i] = Point2f((float)(i*5),(float)(i%7));
    }
    cout << "二维点向量 points： "<<points<<";";
    return 0;
}