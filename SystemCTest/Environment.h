//
//  Environment.h
//  SystemCTest
//
//  Created by Christian Haake on 1/21/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
//

#ifndef SystemCTest_Environment_h
#define SystemCTest_Environment_h

#include "defines.h"

SC_MODULE (env) {
    
    sc_in<bool> clk_in;
    sc_fifo_in<int> fifo_train_passed_signal;//time when train passed
    
    sc_fifo_out<int> fifo_train_in;
    sc_fifo_out<int> fifo_train_out;
    sc_out<bool> start_work;

    int trigger_time;
    uint32_t current_time;
    train *t;
    
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
        
        current_time = (uint32_t) sc_time_stamp().to_seconds();
        
        if(current_time == 0)
            start_work.write(true);
        
        if (current_time == 289) {
            t = new train(current_time,gen_rand(10,20),gen_rand(3,8));
//            t.arrival = ;
//            t.time1 = );
//            t.time2 = ;
            //train t(internal_ticks,gen_rand(10,20),gen_rand(3,8));
            //delete t;
            fifo_train_in.write(t->time1);
            //PRNT("sending train sig");
        }
        
        if(current_time == trigger_time)
        {
            fifo_train_out.write(current_time);
            delete t;
            t=NULL;
        }

    }
    
    void train_passed_signal_event()
    {
        while(1)
        {
            int tmp_time;
            fifo_train_passed_signal.read(tmp_time);
            trigger_time = tmp_time + t->time2;
            wait(SC_ZERO_TIME);
        }
    }
    
    SC_CTOR (env) {
        
        SC_THREAD(train_passed_signal_event);
        
        SC_METHOD(tick);
        sensitive << clk_in.pos();
    }
};


#endif
