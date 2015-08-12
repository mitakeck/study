//
//  main.cpp
//  skinDetection
//
//  Created by mitake on 2015/08/08.
//  Copyright (c) 2015年 mitake. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <fstream>

#include "Skin.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    string filename = "1855.jpg";
    Skin *skin = new Skin(filename);
    skin->detection();
    
    waitKey();
    
    return 0;
}
