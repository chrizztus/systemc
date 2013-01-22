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
    
    sc_fifo_out<train> fifo_train;
    sc_out<bool> start_work;

    int internal_ticks,train_number;
    
    sc_int<8> gen_rand(int min,int max)
    {
        sc_int<8> num;
        while (num < min) 
        {
            num = random() % (max+1);
        }
        return num;
    }
    
    void tick()
    {
        internal_ticks++;
        
        if(internal_ticks == 0)
            start_work.write(true);
        
        if (internal_ticks == 303) {
            train t(internal_ticks,gen_rand(10,20),gen_rand(3,8));

            fifo_train.write(t);
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
