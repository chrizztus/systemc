//
//  Ampel3.h
//  SystemCTest
//
//  Created by Christian Haake on 1/18/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
//

#ifndef SystemCTest_Ampel3_h
#define SystemCTest_Ampel3_h

#include "defines.h"

SC_MODULE (ampel3) {
    
    sc_in<state_light> color_trigger;

    //int color;
    enum state_light color;

    void received_trigger()
    {
        color = color_trigger.read();
        
        PRNT(colors[color]);
    }

    SC_CTOR (ampel3) {
        
        color = eRot;
        SC_METHOD(received_trigger);
        sensitive << color_trigger;
    }
};

#endif
