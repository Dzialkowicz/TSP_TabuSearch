//
//  myClock.cpp
//  PEA_Proj
//
//  Created by Jakub Sanecki on 3.11.2017.
//  Copyright © 2017 Jakub Sanecki. All rights reserved.
//

#include "myClock.h"

MyClock::MyClock(){
    
}

void MyClock::start(){
    showTime = 0;
    startTClock = clock();
}

void MyClock::stop(){
    stopTClock = clock();
    showTime = ((double)(stopTClock - startTClock))/CLOCKS_PER_SEC;
}

double MyClock::getTime(){
    return  showTime;
}


