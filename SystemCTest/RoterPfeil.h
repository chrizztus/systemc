//
//  RoterPfeil.h
//  SystemCTest
//
//  Created by Christian Haake on 1/22/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
//

#ifndef SystemCTest_RoterPfeil_h
#define SystemCTest_RoterPfeil_h

#include "defines.h"

SC_MODULE (arrow) {
    
    sc_in<state_arrow> trigger;
    
    sc_time current;

    enum state_arrow sig_arrow;
    
    void received_trigger()
    {
        sig_arrow = trigger.read();
        
        current = sc_time_stamp();
        if(current.value() > 0) // to prevent debug out when system started
            PRNT(sig_arrow==eOff?"Pfeil aus":"Pfeil an");
    }
    
    SC_CTOR (arrow) {
        
        sig_arrow = eOff;
        SC_METHOD(received_trigger);
        sensitive << trigger;
    }
};

#endif
