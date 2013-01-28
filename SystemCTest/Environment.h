//
//  Environment.h
//  SystemCTest
//
//  Created by Christian Haake on 1/21/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
//

#ifndef SystemCTest_Environment_h
#define SystemCTest_Environment_h

#include <iostream>
#include <fstream>

#include "defines.h"

#define PLOT(a) printf("%s: [%s] - %s\n",sc_time_stamp().to_string().c_str(),name(),a);

//http://stackoverflow.com/questions/8058190/gnuplot-insert-custom-xtic-label-amidst-otherwise-regular-tic-intervals
SC_MODULE (env) {
    
    sc_in<bool> clk_in;
    sc_fifo_in<int> fifo_train_passed_signal;//time when train passed
    
    sc_fifo_out<int> fifo_train_in;
    sc_fifo_out<int> fifo_train_out;
    sc_out<bool> start_work;

    //plot functionality
    enum state_light light1;
    enum state_light light2;
    enum state_tramsignal tram;
    enum state_arrow arrow;
    sc_in<state_light> light1_in;
    sc_in<state_light> light2_in;
    sc_in<state_tramsignal> tram_in;
    sc_in<state_arrow> arrow_in;
    
    ofstream plotfile;
    
    int trigger_time;
    uint32_t current_time;
    double current_time_ms;
    int testcase;
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
    
    void testcase1()
    {
        
        if(current_time == 0)
            start_work.write(true);
        
        if (current_time == 40) {
            t = new train(current_time,gen_rand(10,20),gen_rand(3,8));
            char foo[64];
            sprintf(foo, "Train> Arrival: %d Time1: %d Time2: %d",t->arrival,t->time1,t->time2);
            PRNT(foo);
            fifo_train_in.write(t->time1);
        }
        
        if (current_time == 342) {
            t = new train(current_time,gen_rand(10,20),gen_rand(3,8));
            char foo[64];
            sprintf(foo, "Train> Arrival: %d Time1: %d Time2: %d",t->arrival,t->time1,t->time2);
            PRNT(foo);
            fifo_train_in.write(t->time1);
            //delete t;
        }
        
        if(current_time == trigger_time)
        {
            fifo_train_out.write(current_time);
            delete t;
            t=NULL;
        }
    }
    
    void plot(bool rising)
    {
        if(rising)
            plotfile << current_time_ms << " 1 " << light1 << " " << light2 << " " << tram << " " << arrow << "\n";
        else
            plotfile << current_time_ms << " 0 " << light1 << " " << light2 << " " << tram << " " << arrow << "\n";
    }
    
    void tick()
    {
        
        current_time_ms = sc_time_stamp().to_double()/10e+11;
        current_time = (uint32_t) current_time_ms;
        
        plot(true);
        
        switch (testcase) {
            case 1:
                testcase1();
                break;
                
            default:
                break;
        }
    }
    
    void tack()
    {
        current_time_ms = sc_time_stamp().to_double()/10e+11;
        plot(false);
        //cout << "time: " << std::scientific << current_time_ms << endl;
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
    
    void update_signals()
    {
        light1 = light1_in.read();
        light2 = light2_in.read();
        tram = tram_in.read();
        arrow = arrow_in.read();
    }
    
    SC_CTOR (env) {
        
        plotfile.open ("gnuplot.dat");
        SC_METHOD(update_signals);
        sensitive << light1_in << light2_in << tram_in << arrow_in;
        
        testcase = 1;
        trigger_time = -1;
        
        SC_THREAD(train_passed_signal_event);
        
        SC_METHOD(tick);
        sensitive << clk_in.pos();
        
        SC_METHOD(tack);
        sensitive << clk_in.neg();
    }
    
    // Destructor
    ~env() {      
        plotfile.close();
        cout << "Environment destructor called..." << endl;
    } 
};


#endif
