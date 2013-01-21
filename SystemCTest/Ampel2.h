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
    
    /*
     * signals in
     */
    sc_in<bool> clk_in;
    sc_in<bool> sig_start;
    sc_fifo_in<int> fifo_incomingTrain; // x1
    sc_fifo_in<int> fifo_outgoingTrain; // x2
    
    /*
     * signals out
     */
    sc_out<int> trigger_tandem;
    sc_out<bool> cycle_complete; //wird gesendet wenn ampel auf rot springt
    
    /*
     * variables
     */
    enum state_light color;
    enum state_arrow eArrow;
    int internal_ticks;
    int offset;
    bool train_inside;
    
    void tick()
    {
        if(internal_ticks >= 0)
        {
            ++internal_ticks;
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               && color == eRot)
            {
                cycle_complete.write(false);
                color = eRotgelb;
                PRNT(colors[color]);
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               && color == eRotgelb)
            {
                
                color = eGruen;
                PRNT(colors[color]);
                
            }
            
            // handle incoming and outgoing trains
            if(color == eGruen)
            {
                int i;
                if(fifo_incomingTrain.nb_read(i)){ //read w\o wait()
                    PRNT("Incoming train");
                    
                    train_inside = true;
                }
                
                if(fifo_outgoingTrain.nb_read(i))
                {
                    PRNT("Outgoing train");
                    train_inside = false;
                    offset = -1;
                }
                
                if (train_inside) {
                    offset ++;
                }
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               + DURATION_GRUEN
               && color == eGruen)
            {
                color = eGelb;
                PRNT(colors[color]);
                
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               + DURATION_GRUEN
               + DURATION_GELB
               && color == eGelb)
            {
                color = eRot;
                PRNT(colors[color]);
                
                internal_ticks = -1; //will be set on next sig_start
                cycle_complete.write(true);
            }
            
            //send current color to ampel4
            trigger_tandem.write(color);
        }
        
    }
    
    void received_ext_signal()
    {
        //set internal_ticks to 0 to start cycle
        if (sig_start.read()) {
            internal_ticks = 0;
            
            printf("\n\n\n");
            PRNT("started cycle");

//            sc_stop();
        }
    }
    
    
    SC_CTOR (ampel2) {
        internal_ticks = -1;
        color = eRot;
        eArrow = eOff;
        offset = -1;
        
        SC_METHOD(received_ext_signal);
        sensitive << sig_start;
        
        SC_METHOD(tick);
        sensitive << clk_in.pos();
        
    }
};


#endif
