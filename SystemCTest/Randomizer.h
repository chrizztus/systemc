//
//  Randomizer.h
//  SystemCTest
//
//  Created by Christian Haake on 1/17/13.
//  Copyright (c) 2013 baroos. All rights reserved.
//

#ifndef SystemCTest_Randomizer_h
#define SystemCTest_Randomizer_h

#include "defines.h"

SC_MODULE (randomizer) {
    
    sc_in<bool> clk_in;
    sc_out<bool> start_work;
    
    int seconds_passed, random_wait;
    
    void received_tick()
    {
        //printf("[%s] %d seconds passed\n",name());
        if (seconds_passed == 0) {
            random_wait = rand() % 10;
            printf("random wait is %d\n",random_wait);
        }
        
        if (random_wait == seconds_passed) {
            start_work.write(true);
        }
        else if (random_wait > seconds_passed)
        {
            start_work.write(false);
        }
        
        ++seconds_passed;
    }
    
    SC_CTOR (randomizer) {
        seconds_passed = 0;
        
        SC_METHOD(received_tick);
        sensitive << clk_in.pos();
    }
};

#endif
