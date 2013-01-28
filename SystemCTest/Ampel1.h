//
//  Ampel1.h
//  SystemCTest
//
//  Created by Christian Haake on 1/16/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
//

#ifndef SystemCTest_Ampel1_h
#define SystemCTest_Ampel1_h

#include "defines.h"

SC_MODULE (ampel1) {
    
    sc_in<bool> clk_in;
    sc_in<bool> sig_start;
    sc_in<bool> sig_global_start;
    
    sc_out<state_light> trigger_tandem;
    sc_out<bool> cycle_complete; //send when switched to red
    
    enum state_light color;
    
    int internal_ticks;
    bool haveglobalstartsig;
    
    void tick()
    {        
        if(internal_ticks >= 0)
        {
            ++internal_ticks;
            
            if(internal_ticks >= WAIT_ROTGELB_A1A3
               && color == eRot)
            {
                //write to false to ensure ampel2 will be triggered the next time
                cycle_complete.write(false);
                
                color = eRotgelb;
                PRNT(colors[color]);
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A1A3
               + DURATION_ROTGELB
               && color == eRotgelb)
            {
                color = eGruen;
                PRNT(colors[color]);s
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A1A3
               + DURATION_ROTGELB
               + DURATION_GRUEN
               && color == eGruen)
            {
                color = eGelb;
                PRNT(colors[color]);
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A1A3
               + DURATION_ROTGELB
               + DURATION_GRUEN
               + DURATION_GELB
               && color == eGelb)
            {
                color = eRot;
                PRNT(colors[color]);

                internal_ticks = -1;
                cycle_complete.write(true);
                
            }
            
            //send current color to ampel3
            trigger_tandem.write(color);
            
        }
        
    }
    
    //when ever this method is called the other light just switched to red
    void received_ext_signal()
    {

        if (sig_start.read() && haveglobalstartsig) {
            internal_ticks = 0;
        
            printf("\n\n\n");
            PRNT("started cycle");    
        }
        
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
        color = eRot;
        haveglobalstartsig = false;
        
        SC_METHOD(received_global_start_signal);
        sensitive << sig_global_start;
        
        SC_METHOD(received_ext_signal);
        sensitive << sig_start;
        
        SC_METHOD(tick);
        sensitive << clk_in.pos();
    }
};

#endif
