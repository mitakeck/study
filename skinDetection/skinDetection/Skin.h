//
//  Skin.h
//  skinDetection
//
//  Created by mitake on 2015/08/08.
//  Copyright (c) 2015年 mitake. All rights reserved.
//

#ifndef __skinDetection__Skin__
#define __skinDetection__Skin__

#include <stdio.h>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>


using namespace std;
using namespace cv;

class Skin{
private:
    Mat m_input;
    CascadeClassifier m_faceCascade;
    ofstream m_log;
    void init();
    bool imageRead(string fname);

public:
    Skin();
    Skin(const string fname);
    Mat setInputImage(const string fname);
    Rect faceDetection();
    Rect faceDetection(const Mat input);
    Mat detection();
    Mat detection(const Mat input);
    
};

#endif /* defined(__skinDetection__Skin__) */
