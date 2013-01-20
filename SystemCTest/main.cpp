// All systemc modules should include systemc.h header file
#include <systemc.h>

#include "Ampel1.h"
#include "Ampel3.h"
//#include "Ampel2.h"
#include "Randomizer.h"
//#include "defines.h"

// sc_main in top level function like in C++ main
int sc_main(int argc, char* argv[]) {
    
    /*
     * Signals
     */
    sc_signal<bool> global_start;
    //sc_signal<bool> red2;
    sc_signal<bool> sw; //used for initial signal
    sc_signal<int> connect1_3;
    
    sc_clock clock("clock", 1, SC_SEC);
    
    
    ampel3 ampel3("Ampel3");
    //ampel2 ampel2("Ampel2");
    
    randomizer random("Randomizer");
    random.clk_in(clock);

    ampel1 ampel1("Ampel1");
    ampel1.clk_in(clock);
    
    ampel1.sig_global_start(global_start);
    random.start_work(global_start);
    
    //connections
    ampel3.color_trigger(connect1_3);
    ampel1.trigger_tandem(connect1_3);
    
//    ampel1.cycle_complete(red1);
//    ampel2.sig_red(red1);
//    ampel2.cycle_complete(red2);
//    ampel1.sig_red(red2);
    
    sc_start(60, SC_SEC);
    
    return(EXIT_SUCCESS);
}