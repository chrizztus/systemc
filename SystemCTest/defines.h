//
//  defines.h
//  SystemCTest
//
//  Created by Christian Haake on 1/16/13.
//  Copyright (c) 2013 baroos. All rights reserved.
//

#ifndef SystemCTest_defines_h
#define SystemCTest_defines_h

#include <systemc.h>

#define WAIT_ROTGELB_A1A3   4
#define WAIT_ROTGELB_A2A4   3

#define DURATION_ROTGELB    1
#define DURATION_GRUEN      20
#define DURATION_GELB       2

#define NUM_STATES          4

#define LIFECYCLE           360

#define PRNT(a) printf("%s: [%s] - %s\n",sc_time_stamp().to_string().c_str(),name(),a);

class train {
    
private:
    
public:
    
    int time1, time2, arrival;
    // constructor
    train()
    {arrival=0;}
    
    train (int ar,int t1, int t2):
        arrival(ar),time1(t1),time2(t2)
    {}
    
    
    //do some neccessary overload
    inline friend ostream& operator << ( ostream& os,  train const & v ) {
        os << "(" << v.arrival << ")";
        return os;
    }
    
    inline bool operator == (const train & t) const {
        return (t.arrival == arrival 
                && t.time1 == time1
                && t.time2 == time2);
    }
    
    operator bool() const
    {
        return (arrival);
    }
};

enum state_light
{
    eRot=0,
    eRotgelb,
    eGruen,
    eGelb,
    count
};

enum state_arrow
{
    eOff=0,
    eOn
};

enum state_tramsignal
{
    eF0=0,  // horizontal
    eF1     // vertical
};



char *colors[NUM_STATES] = {"Rot","Rotgelb","Gruen","Gelb"};

#endif
