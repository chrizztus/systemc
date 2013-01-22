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
    
    sc_fifo_out<int> fifo_train;

    int internal_ticks,train_number;
    
    void tick()
    {
        internal_ticks++;
        
        if (internal_ticks == 303) {
            fifo_train.write(++train_number);
            PRNT("sending train sig");
        }
    }
    
    SC_CTOR (env) {
        
        train_number = 0;
        internal_ticks = -1;
        
        SC_METHOD(tick);
        sensitive << clk_in.pos();
    }
};


#endif
