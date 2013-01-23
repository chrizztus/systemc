//
//  Ampel2.h
//  SystemCTest
//
//  Created by Christian Haake on 1/19/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
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
    sc_out<state_light> trigger_tandem;
    sc_out<bool> cycle_complete; //wird gesendet wenn ampel auf rot springt
    sc_out<state_tramsignal> tram_out;
    sc_out<state_arrow> arrow_out;
    sc_fifo_out<int> fifo_train_passed_signal;
    
    /*
     * variables
     */
    enum state_light color;
    enum state_arrow eArrow;
    int internal_ticks;
    int offset;
    bool train_inside,train_at_signal;
    train *t;
    int current_time;
    
    void tick()
    {
        if(internal_ticks >= 0)
        {
            
            ++internal_ticks;
            
            if(internal_ticks == 305)
                delete &t;
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               && color == eRot)
            {
                cycle_complete.write(false);
                color = eRotgelb;
                PRNT(colors[color]);
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               + offset
               && color == eRotgelb)
            {
                color = eGruen;
                PRNT(colors[color]);
            }
            
            // handle incoming and outgoing trains
            if(color == eGruen)
            {
                current_time = (int)sc_time_stamp().to_seconds();
                
                tram_out.write(eF1);

                
                if (t) {
                    //calculate train arrival
                    int tmp_time = (t->arrival + t->time1) - current_time;
                    
                    //check if train already reached signal
                    if  (tmp_time <= 0)
                    {
                        fifo_train_passed_signal.write(current_time);
                        t = NULL;
                    }
                    
                    cout << "train will arrive signal in " << tmp_time << " seconds..." << endl;

                    offset ++;
                }
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               + DURATION_GRUEN
               + offset
               && color == eGruen)
            {
                color = eGelb;
                tram_out.write(eF0);
                train_inside = false;
                PRNT(colors[color]);
                
            }
            
            if(internal_ticks >= WAIT_ROTGELB_A2A4
               + DURATION_ROTGELB
               + DURATION_GRUEN
               + DURATION_GELB
               + offset
               && color == eGelb)
            {
                color = eRot;
                PRNT(colors[color]);
                
                internal_ticks = -1; //will be set on next sig_start
                cycle_complete.write(true);
                
                offset = 0;
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
    
    void wait_outgoing_train()
    {
        while (1)
        {
            int foo;
            fifo_outgoingTrain.read(foo);
            //
            //
            wait(SC_ZERO_TIME);
        }
    }
    
    void wait_incoming_train()
    {
        while (!t)
        {
            int time = 0;
            fifo_incomingTrain.read(time);
            t = new train((int)sc_time_stamp().to_seconds(),time,0);
            wait(SC_ZERO_TIME);
        }
    }
    
    SC_CTOR (ampel2) {
        internal_ticks = -1;
        color = eRot;
        eArrow = eOff;
        offset = 0;
        train_inside = false;
        t = NULL;
        
        SC_THREAD(wait_incoming_train);
        SC_THREAD(wait_outgoing_train);
        
        SC_METHOD(received_ext_signal);
        sensitive << sig_start;
        
        SC_METHOD(tick);
        sensitive << clk_in.pos();
        
    }
};


#endif
