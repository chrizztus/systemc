//
//  Ampel2.h
//  SystemCTest
//
//  Created by Christian Haake on 1/19/13.
//  Copyright (c) 2013 baroos. All rights reserved.
//

#ifndef SystemCTest_Ampel2_h
#define SystemCTest_Ampel2_h

#include "defines.h"

SC_MODULE (ampel2) {
    
    sc_in<bool> clk_in;
    sc_in<bool> sig_start;
    
    sc_out<int> trigger_tandem;
    //sc_out<bool> cycle_complete; //wird gesendet wenn ampel auf rot springt
    
    enum state color;
    
    int internal_ticks;
    
    
    void tick()
    {
        if(internal_ticks >= 0)
        {
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               && color == rot)
            {
                color = rotgelb;
                printf("%s: switched to: rotgelb after %d seconds\n",sc_time_stamp().to_string().c_str(), internal_ticks);
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               && color == rotgelb)
            {
                color = gruen;
                printf("%s: switched to: gruen after %d seconds\n",sc_time_stamp().to_string().c_str(),internal_ticks);
                
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               + DURATION_GRUEN
               && color == gruen)
            {
                color = gelb;
                printf("%s: switched to: gelb after %d seconds\n",sc_time_stamp().to_string().c_str(),internal_ticks);
                
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               + DURATION_GRUEN
               + DURATION_GELB
               && color == gelb)
            {
                color = rot;
                printf("%s: switched to: rot after %d seconds\n",sc_time_stamp().to_string().c_str(),internal_ticks);
                
                internal_ticks = -1; //will be set on next sig_start
            }
            
            //send current color to ampel4
            trigger_tandem.write(color);
            ++internal_ticks;
        }
        
    }
    
    void received_ext_signal()
    {
        //set internal_ticks to 0 to start cycle
        //bool sigistrue = ;
        if (sig_start.read()) {
            internal_ticks = 0;
        }
        
    }
    
    SC_CTOR (ampel2) {
        internal_ticks = -1;
        color = rot;
        
        SC_METHOD(received_ext_signal);
        sensitive << sig_start;
        
        SC_METHOD(tick);
        sensitive << clk_in.pos();
    }
};


#endif
