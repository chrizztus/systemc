//
//  Tramsignal.h
//  SystemCTest
//
//  Created by Christian Haake on 1/22/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
//

#ifndef SystemCTest_Tramsignal_h
#define SystemCTest_Tramsignal_h

#include "defines.h"

SC_MODULE (tram) {
    
    sc_in<state_tramsignal> trigger;
    
    uint32_t current;
    int color;
    enum state_tramsignal sig_tram;
    
    void received_trigger()
    {
        sig_tram = trigger.read();
        
        current = (uint32_t) sc_time_stamp().to_seconds();
        if(current > 0) // to prevent debug out when system started
            PRNT(sig_tram==eF0?"F0":"F1");
    }
    
    SC_CTOR (tram) {
        
        sig_tram = eF0;
        SC_METHOD(received_trigger);
        sensitive << trigger;
    }
};

#endif
