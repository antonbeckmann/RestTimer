#ifndef ESP01_RELAY_H
#define ESP01_RELAY_H

#include "Exception.hpp"
#include "ESP01Dev.hpp"
#include <string>

class ESP01Relay : public ESP01Dev
{
    public:
            ESP01Relay(std::string url):ESP01Dev(url)
            {
                m_Url = url;
            }
            ~ESP01Relay(){};

            

    private:
        std::string m_Url;        
        bool validDateGPIO(tGPIO g);


};

#endif