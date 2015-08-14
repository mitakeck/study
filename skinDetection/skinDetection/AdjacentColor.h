//
//  AdjacentColor.h
//  skinDetection
//
//  Created by mitake on 2015/08/14.
//  Copyright (c) 2015年 mitake. All rights reserved.
//

#ifndef __skinDetection__AdjacentColor__
#define __skinDetection__AdjacentColor__

#include <stdio.h>

using namespace std;

class AdjacentColor{
private:
    int m_count;
    int m_pixelCount[256][256];
    
public:
    AdjacentColor();
    int countUp(int prevHue, int currentHue);
    float prob(int hue);
};

#endif /* defined(__skinDetection__AdjacentColor__) */
