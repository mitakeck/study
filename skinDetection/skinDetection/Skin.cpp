//
//  Skin.cpp
//  skinDetection
//
//  Created by mitake on 2015/08/08.
//  Copyright (c) 2015年 mitake. All rights reserved.
//

#include "Skin.h"
#include "Color.h"
#include "defines.h"

using namespace std;
using namespace cv;

Skin::Skin(){
    this->init();
};

Skin::Skin(const string fname){
    this->imageRead(fname);
    this->init();
};

bool Skin::imageRead(string fname){
    m_input = imread(fname);
    if(m_input.empty()){
        cout << "Fail to read image" << endl;
        return false;
    }
    return true;
}

Mat Skin::setInputImage(const string fname){
    this->imageRead(fname);
    return m_input;
}


void Skin::init(){
    // 顔検出用のカスケードファイルを読み込み
    m_faceCascade.load("haarcascade_frontalface_default.xml");
    
    // ログファイル準備
    time_t timer = time(NULL);
    string logfilePrefix = "log_", logfileSuffix = ".txt", fileName = logfilePrefix;
    
    fileName.append(to_string(timer));
    fileName.append(logfileSuffix);
    
    cout << "loggin at " << fileName << endl;
    m_log.open(fileName, 0x04);
}

Rect Skin::faceDetection(){
    return this->faceDetection(this->m_input);
};

Rect Skin::faceDetection(const Mat input){
    vector<Rect> faces;
    int maxsize = -1, maxindex = 0;

    m_faceCascade.detectMultiScale(input, faces);
    for (int i=0; i<faces.size(); i++) {
        int size = faces[i].width * faces[i].height;
        if(maxsize < size){
            maxsize = size;
            maxindex = i;
        }
    }
    return faces[maxindex];
};

Mat Skin::detection(){
    return this->detection(this->m_input);
}

Mat Skin::detection(const Mat input){
    
    Mat grabcut, bg, fg, mask;
    // 顔領域推定
    Rect face_rect = this->faceDetection(input);
    grabCut(input, grabcut, face_rect, bg, fg, 1, GC_INIT_WITH_RECT);
    compare(grabcut, GC_PR_FGD, mask, CMP_EQ);
    input.copyTo(grabcut, mask);
    
    imshow("input", input);
    imshow("grab cut", grabcut);
    bitwise_not(mask, mask);
    imshow("mask", mask);
    
    // 肌色リスト作成
    Color skinColorCount[256];
    Mat dist;
    cvtColor(grabcut, dist, CV_BGR2HSV);
    
    for (int i=0; i<255; i++) {
        skinColorCount[i].setCode(i);
    }
    for(int y=face_rect.y; y<face_rect.y+face_rect.height; y++){
        for(int x=face_rect.x; x<face_rect.x+face_rect.width; x++){
            skinColorCount[(int)dist.at<Vec3b>(y, x)[HSV_H]]++;
        }
    }
    sort(&skinColorCount[1], &skinColorCount[255], [](Color& lcolor, Color& rcolor){ return lcolor > rcolor; });
    
    for (int i=1; i<255; i++) {
        cout << skinColorCount[i].getCode() << "\t" << skinColorCount[i].getCount() << endl;
        m_log << skinColorCount[i].getCode() << "\t" << skinColorCount[i].getCount() << endl;
    }
    cvtColor(input, dist, CV_BGR2HSV);

    int t = 5;
    Mat_<Vec3b> output = Mat::zeros(input.size(), CV_8U);
    string outputFile = "v_";
    outputFile.append(to_string(t));
    outputFile.append(".jpg");
    
    for (int y=0; y<input.rows; y++) {
        for (int x=0; x<input.cols; x++) {
            int s = dist.at<Vec3b>(y, x)[HSV_H];
            if(s == t){
                output.at<Vec3b>(y, x) = (Vec3b)(input.at<Vec3b>(y, x));
            }
        }
    }
    // 肌色領域拡大
    
    imshow("output", output);
    imwrite(outputFile, output);

    
    return output;
}
