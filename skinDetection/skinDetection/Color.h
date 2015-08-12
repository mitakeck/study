//
//  Color.h
//  skinDetection
//
//  Created by mitake on 2015/08/08.
//  Copyright (c) 2015年 mitake. All rights reserved.
//

#ifndef __skinDetection__Color__
#define __skinDetection__Color__

#include <stdio.h>

class Color{
private:
    int m_code;
    int m_count;

public:
    Color(){
        m_code = 0;
        m_count = 0;
    }
    void setCode(int code){
        m_code = code;
    }
    void operator++(int){
        m_count++;
    }
    bool operator<(const Color &rColor){
        return m_count < rColor.m_count;
    }
    bool operator>(const Color &lColor){
        return m_count > lColor.m_count;
    }
    int getCode(void){
        return m_code;
    }
    int getCount(void){
        return m_count;
    }
};

#endif /* defined(__skinDetection__Color__) */
