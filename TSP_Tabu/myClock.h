//
//  myClock.hpp
//  PEA_Proj
//
//  Created by Jakub Sanecki on 3.11.2017.
//  Copyright © 2017 Jakub Sanecki. All rights reserved.
//
#ifndef MYCLOCK_H
#define MYCLOCK_H


#include <stdio.h>
#include <ctime>

class MyClock{
public:
    MyClock();
    void start();
    void stop();
    double showTime;
    double getTime();
    clock_t startTClock;
    clock_t stopTClock;
};

#endif
