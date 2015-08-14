//
//  AdjacentColor.cpp
//  skinDetection
//
//  Created by mitake on 2015/08/14.
//  Copyright (c) 2015年 mitake. All rights reserved.
//

#include "AdjacentColor.h"
#include <string.h>

AdjacentColor::AdjacentColor(){
    // 0 で初期化
    memset(m_pixelCount, 0, sizeof(m_pixelCount));
    m_count = 0;
    
    return;
}

int AdjacentColor::countUp(int prevHue, int currentHue){
    // カウントアップ
    ++m_count;
    return ++m_pixelCount[prevHue][currentHue];
}

float AdjacentColor::prob(int hue){
    return 0.0f;
}