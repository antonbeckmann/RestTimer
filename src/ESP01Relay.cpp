#include "ESP01Relay.hpp"
#include <iostream>

bool ESP01Relay::validDateGPIO(tGPIO g)
{
    if( g.gpio !=0) 
    {
        std::cout<<"Esp01Exception_InvalidGPIO: "<<g.gpio<<std::endl;
        return false;    
    }
    
    if(g.id < 1)
    {
        std::cout<<"Esp01Exception_ZeroId: "<<g.id<<std::endl;
        return false;
    }

    if(!(g.status == 0 || g.status == 1))
    {
        std::cout<<"Esp01Exception_InvalidStatus: "<<g.status<<std::endl;
        return false;
    }
    return true;
}