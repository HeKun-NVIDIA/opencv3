//
//  houghLinesDetect.cpp
//  opencv3
//
//  Created by 何琨 on 17/2/7.
//  Copyright (c) 2017年 何琨. All rights reserved.
//

#include "houghLinesDetect.h"
#include <math.h>
const cv::String position ="/Users/FEGTT/Documents/opencv3/opencv3/opencv3/";
int pdistance(Point,Point);
int houghLinesDetect()
{
    Mat h_srcImage = imread(position+"3.pic.jpg");
    Mat midImage, h_dstImage,h_gray;
    //cvtColor(h_srcImage, h_gray, COLOR_BGR2GRAY);
    //blur(h_gray, midImage, Size(3,3));
    Canny(h_srcImage, midImage, 100, 250,3);
    cvtColor(midImage, h_dstImage, CV_GRAY2BGR);

    vector<Vec4i> lines;
    vector<Vec4i> lines2;
    HoughLinesP(midImage, lines, 1, CV_PI/180, 80,100,350);
   // HoughLinesP(midImage, lines2, 1, CV_PI/180, 80,100,270);
    
    size_t i =0;
    Point p[4];
    int th333 = 25;//距离点的阈值
    for (; i<lines.size(); i++) {
        Vec4i l = lines[i];
        Point temp[2];
        temp[0].x = l[0];
        temp[0].y = l[1];
        temp[1].x = l[2];
        temp[1].y = l[3];
        //Vec4i l2 = lines2[i];
       /* if ((abs(l[0]-l[2])<230)&&(abs(l[0]-l[2])>100) && (abs(l[1]-l[3])<10)) {
            continue;
        }
        if ((abs(l[1]-l[3])<270)&&(abs(l[1]-l[3])>100) && (abs(l[0]-l[2])<10)) {
            continue;
        }*/
        
        /*float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a =cos(theta), b=sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0+1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));*/
        //line(h_srcImage, pt1, pt2, Scalar(55,100,195),2,LINE_AA);*/
        //cout << l <<endl;
        //cout << pdistance(Point(l[0],l[1]),Point(l[2],l[3]))<<endl;
       /* if (pdistance(pdistance(Point(0,0), Point(l[0],l[1]))<pdistance(Point(0,0), Point(l[2]))?Point(l[0],l[1]):Point(l[2],l[3]),Point(0,0)) < 30) {
            if (temp[0].x) {
                temp[0].x = (temp[0].x+)
            }
        }*/
        cout << "**********************"<<endl;
        cout << temp[0] <<endl;
        cout << "pdistance(temp[0], Point(270,315)): "<<pdistance(temp[0], Point(270,315))<<endl;
        cout << temp[1]<<endl;
        for (int n = 0; n<2; n++) {
            if (pdistance(temp[n], Point(0,0)) < th333) {
                cout << "pdistanc(temp[n], Point(0,0)): "<<pdistance(temp[n], Point(0,0))<<endl;
                if (p[0].x) {
                    p[0].x = (p[n].x+temp[n].x)/2;
                }
                else
                    p[0].x = temp[n].x;
                if (p[0].y) {
                    p[0].y =(p[0].y+temp[n].y)/2;
                }
                else
                    p[0].y = temp[n].y;
                cout << "p0: "<< p[0]<<endl;
            }
            else if (pdistance(temp[n], Point(0,315))<th333)
            {
                if (p[1].x) {
                    p[1].x = (p[1].x+temp[n].x)/2;
                }
                else
                {
                    p[1].x = temp[n].x;
                }
                if (p[1].y) {
                    p[1].y =(p[1].y+temp[n].y)/2;
                }
                else
                    p[1].y = temp[n].y;
                cout << "p1: "<< p[1]<<endl;
            }
            else if (pdistance(temp[n], Point(270,315))<th333)
            {
                cout <<"pdistance(temp[n], Point(270,315)): "<<pdistance(temp[n], Point(270,315)) <<endl;
                if (p[2].x) {
                    p[2].x = (p[2].x+temp[n].x)/2;
                }
                else
                {
                    p[2].x = temp[n].x;
                }
                if (p[2].y) {
                    p[2].y =(p[2].y+temp[n].y)/2;
                }
                else
                    p[2].y = temp[n].y;
                cout << "p2: "<< p[2]<<endl;
            }
            else if (pdistance(temp[n], Point(270,0))<th333)
            {
                if (p[3].x) {
                    p[3].x = (p[3].x+temp[n].x)/2;
                }
                else
                {
                    p[3].x = temp[n].x;
                }
                if (p[3].y) {
                    p[3].y =(p[3].y+temp[n].y)/2;
                }
                else
                    p[3].y = temp[n].y;
                cout << "p3: "<< p[3]<<endl;
            }
            
        }
        //line( h_srcImage , Point(l[0],l[1]),Point(l[2],l[3]),Scalar(3,0,200),2,CV_AA);
       // line( h_srcImage , Point(l2[0],l2[1]),Point(l2[2],l2[3]),Scalar(3,0,200),1,CV_AA);
    }
    for (int i = 0; i<4; i++) {
        cout << p[i] <<endl;
        cout << (i+1)%4<<endl;
        line(h_srcImage, p[i], p[(i+1)%4], Scalar(3,0,200),1,CV_AA);
    }
    imshow("h_dstImage", h_srcImage);
    imshow("mid_dstImage",midImage);
    waitKey(0);
    return 0;
}
int pdistance(Point a,Point b)
{
    return sqrt(double((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
}