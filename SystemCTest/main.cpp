// All systemc modules should include systemc.h header file
#include "defines.h"

#include "Ampel1.h"
#include "Ampel3.h"
#include "Ampel2.h"
#include "Ampel4.h"
#include "Randomizer.h"
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
    sc_signal<int> connect1_3;
    sc_signal<int> connect2_4;
    
    //train signal
    sc_fifo<int> sig_x1;
    sc_fifo<int> sig_x2;
    
    sc_clock clock("clock", 1, SC_SEC);
    
    
    ampel1 ampel1("Ampel1");
    ampel2 ampel2("Ampel2");
    ampel3 ampel3("Ampel3");
    ampel4 ampel4("Ampel4");
    randomizer random("Randomizer");
    
    ampel1.clk_in(clock);
    ampel2.clk_in(clock);
    random.clk_in(clock);
   
    //initial connection
    ampel1.sig_global_start(global_start);
    random.start_work(global_start);
    
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
    ampel2.fifo_outgoingTrain(sig_x2);
    
    sc_start(360, SC_SEC);
    
    return(EXIT_SUCCESS);
}