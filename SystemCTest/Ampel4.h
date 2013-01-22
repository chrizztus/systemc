//
//  Ampel4.h
//  SystemCTest
//
//  Created by Christian Haake on 1/21/13.
//  Copyright (c) 2013 baroos. All rights reserved.
//

#ifndef SystemCTest_Ampel4_h
#define SystemCTest_Ampel4_h

#include "defines.h"

SC_MODULE (ampel4) {
    
    sc_in<state_light> color_trigger;
    
    //int color;
    enum state_light color;
    
    void received_trigger()
    {
        color = color_trigger.read();
        
        PRNT(colors[color]);
    }
    
    SC_CTOR (ampel4) {
        
        color = eRot;
        
        SC_METHOD(received_trigger);
        sensitive << color_trigger;
    }
};

#endif
