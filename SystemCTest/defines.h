//
//  defines.h
//  SystemCTest
//
//  Created by Christian Haake on 1/16/13.
//  Copyright (c) 2013 baroos. All rights reserved.
//

#ifndef SystemCTest_defines_h
#define SystemCTest_defines_h

#define WAIT_ROTGELB_A1A3   4
#define WAIT_ROTGELB_A2A4   3

#define DURATION_ROTGELB    1
#define DURATION_GRUEN      20
#define DURATION_GELB       2

#define NUM_STATES          4

enum state
{
    rot=0,
    rotgelb,
    gruen,
    gelb,
    count
};

char *colors[NUM_STATES] = {"Rot","Rotgelb","Gruen","Gelb"};

#endif
