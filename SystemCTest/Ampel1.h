//
//  Ampel1.h
//  SystemCTest
//
//  Created by Christian Haake on 1/16/13.
//  Copyright (c) 2013 baroos. All rights reserved.
//

#ifndef SystemCTest_Ampel1_h
#define SystemCTest_Ampel1_h

#include "defines.h"

SC_MODULE (ampel1) {
    
    sc_in<bool> clk_in;
    //sc_in<bool> sig_start;
    sc_in<bool> sig_global_start;
    
    sc_out<int> trigger_tandem;
    //sc_out<bool> cycle_complete; //wird gesendet wenn ampel auf rot springt
    
    enum state color;
    
    int internal_ticks;
    bool haveglobalstartsig;
    
    void tick()
    {        
        if(internal_ticks >= 0)
        {
            if(internal_ticks >= WAIT_ROTGELB_A1A3
               && color == rot)
            {
                color = rotgelb;
                printf("%s: switched to: rotgelb after %d seconds\n",sc_time_stamp().to_string().c_str(), internal_ticks);
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A1A3
               + DURATION_ROTGELB
               && color == rotgelb)
            {
                color = gruen;
                printf("%s: switched to: gruen after %d seconds\n",sc_time_stamp().to_string().c_str(),internal_ticks);

            }
            
            if(internal_ticks >= WAIT_ROTGELB_A1A3
               + DURATION_ROTGELB
               + DURATION_GRUEN
               && color == gruen)
            {
                color = gelb;
                printf("%s: switched to: gelb after %d seconds\n",sc_time_stamp().to_string().c_str(),internal_ticks);
                
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A1A3
               + DURATION_ROTGELB
               + DURATION_GRUEN
               + DURATION_GELB
               && color == gelb)
            {
                color = rot;
                printf("%s: switched to: rot after %d seconds\n",sc_time_stamp().to_string().c_str(),internal_ticks);

                internal_ticks = -2;
                //cycle_complete.write(true);
            }
            
            //send current color to ampel3
            trigger_tandem.write(color);
            ++internal_ticks;
        }
        
    }
    
    //when ever this method is called the other light just switched to red
    void received_ext_signal()
    {
        //set internal_ticks to 0 to start cycle
        //bool sigistrue = ;
//        if (sig_start.read() && haveglobalstartsig) {
//            internal_ticks = 0;
//        }
        
    }
    
    //this methods purpose is to trigger the very first start
    void received_global_start_signal()
    {
        //set internal_ticks to 0 to start cycle
        //bool sigistrue = ;
        if (sig_global_start.read() && !haveglobalstartsig) {
            internal_ticks = 0;
            haveglobalstartsig = true;
        }
    }
    
    SC_CTOR (ampel1) {
        internal_ticks = -1;
        color = rot;
        haveglobalstartsig = false;
        
        SC_METHOD(received_global_start_signal);
        sensitive << sig_global_start;
        
        SC_METHOD(received_ext_signal);
       // sensitive << sig_start;
        
        SC_METHOD(tick);
        sensitive << clk_in.pos();
    }
};

#endif