//
//  defines.h
//  SystemCTest
//
//  Created by Christian Haake on 1/16/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
//

#ifndef SystemCTest_defines_h
#define SystemCTest_defines_h

#include <systemc.h>

#define WAIT_ROTGELB_A1A3   4
#define WAIT_ROTGELB_A2A4   3

#define DURATION_ROTGELB    1
#define DURATION_GRUEN      20
#define DURATION_GELB       2

#define OFFSET_BASE         (WAIT_ROTGELB_A2A4 + DURATION_ROTGELB + DURATION_GRUEN)

#define OFF                 0
#define ON                  1

#define NUM_STATES          4

#define LIFECYCLE           240

#define TRAIN_ARRIVAL       155

#define WITH_GNUPLOT_OUT    1
#define GNUPLOT_FILE_NAME   "gnuplot.dat"

#define PRNT(a) printf("%s: [%s] - %s\n",sc_time_stamp().to_string().c_str(),name(),a);

        
struct train
{
    int arrival;
    int time1;
    int time2;


    train(int ar, int t1, int t2):arrival(ar),time1(t1),time2(t2)
    {}
};

enum state_light
{
    eRot=0,
    eRotgelb,
    eGruen,
    eGelb,
    count
};

enum state_arrow
{
    eOff=0,
    eOn
};

enum state_tramsignal
{
    eF0=0,  // horizontal
    eF1     // vertical
};



char *colors[NUM_STATES] = {(char*)"Rot",(char*)"Rotgelb",(char*)"Gruen",(char*)"Gelb"};

#endif
