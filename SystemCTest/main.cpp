//
//  main.cpp
//  SystemCTest
//
//  Created by Christian Haake on 1/16/13.
//  Copyright (c) 2013 barfoos. All rights reserved.
//

#include "defines.h"

#include "Ampel1.h"
#include "Ampel3.h"
#include "Ampel2.h"
#include "Ampel4.h"
#include "Environment.h"
#include "Tramsignal.h"
#include "RoterPfeil.h"
//#include "defines.h"

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {
    
    /*
     * Signals
     */
    sc_signal<bool> global_start;
    sc_signal<bool> trigger12;
    sc_signal<bool> trigger21;
    sc_signal<bool> sw; //used for initial signal
    sc_signal<state_light> connect1_3;
    sc_signal<state_light> connect2_4;
    sc_signal<state_tramsignal> connect2_tram;
    sc_signal<state_arrow> connect2_arrow;
    
    //train signal
    sc_fifo<int> sig_x1(1); //guarantee only one train at a time
    sc_fifo<int> sig_x2(1);
    sc_fifo<int> train_passed;
    
    sc_clock clock("clock", 1, SC_SEC);
    
    
    ampel1 ampel1("Ampel1");
    ampel2 ampel2("Ampel2");
    ampel3 ampel3("Ampel3");
    ampel4 ampel4("Ampel4");
    tram tram("Tramsignal");
    arrow pfeil("RoterPfeil");
    env env("Environment");
    
    ampel1.clk_in(clock);
    ampel2.clk_in(clock);
    env.clk_in(clock);
   
    //initial connection
    ampel1.sig_global_start(global_start);
    env.start_work(global_start);
    
    /*
     * connections
     */
    //color trigger
    ampel3.color_trigger(connect1_3);
    ampel1.trigger_tandem(connect1_3);
    
    ampel4.color_trigger(connect2_4);
    ampel2.trigger_tandem(connect2_4);
    
    //ampel became red notification
    ampel2.sig_start(trigger12);
    ampel1.cycle_complete(trigger12);
    
    ampel1.sig_start(trigger21);
    ampel2.cycle_complete(trigger21);

    ampel2.fifo_incomingTrain(sig_x1);
    env.fifo_train_in(sig_x1);
    ampel2.fifo_outgoingTrain(sig_x2);
    env.fifo_train_out(sig_x2);
    
    env.fifo_train_passed_signal(train_passed);
    ampel2.fifo_train_passed_signal(train_passed);
    
    //ampel2<->tramsignal
    ampel2.tram_out(connect2_tram);
    tram.trigger(connect2_tram);
    
    //ampel2<->red arrow
    ampel2.arrow_out(connect2_arrow);
    pfeil.trigger(connect2_arrow);
    
#if WITH_GNUPLOT_OUT > 0
    //gnuplot connections
    env.light1_in(connect1_3);
    env.light2_in(connect2_4);
    env.arrow_in(connect2_arrow);
    env.tram_in(connect2_tram);
#endif
    
    sc_start(LIFECYCLE, SC_SEC);
    
    return(EXIT_SUCCESS);
}