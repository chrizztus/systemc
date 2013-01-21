//
//  Environment.h
//  SystemCTest
//
//  Created by Christian Haake on 1/21/13.
//  Copyright (c) 2013 baroos. All rights reserved.
//

#ifndef SystemCTest_Environment_h
#define SystemCTest_Environment_h

#include "defines.h"

SC_MODULE (env) {
    
    sc_in<bool> clk_in;

    int internal_ticks;
    
    void received_tick()
    {

    }
    
    SC_CTOR (env) {
        
        
        
        SC_METHOD(tick);
        sensitive << clk_in;
    }
};


#endif
