#ifndef ESP01_DEV_H
#define ESP01_DEV_H

#include <string>
#include <vector>
#include "Exception.hpp"

#define ESP_OKAY 1
#define ESP_CREATE_GPIO_CONFLICT 2
#define ESP_DEVICE_NOT_FOUND 3
#define ESP_UNKNOWN_ERROR 4
#define ESP_NOT_IMPLEMENTED 

#define ESP_NOT_NEEDED 0

#define RETURN return returnStatus
  
/*
 * Holds the data of GPIO (ID, GPIO, Status)
 * i: ID
 * g: GPIO
 * s: Status
 */  
struct tGPIO
{
   int id,
       gpio,
       status;   
   tGPIO(int i, int g, int s):id(i),gpio(g),status(s){}    
};

/*
 * Holds the data of GPIO (ID, GPIO, Status)
 * i: ID
 * g: GPIO
 * s: Status
 */  
struct tDevInfo
{
   std::string devname;   
   int id,
       type;   
   tDevInfo(std::string n, int i, int t):devname(n),id(i),type(t){}    
};


class ESP01Dev{
    public:      
            ESP01Dev(std::string url){
                  m_Url = url;
            }
          
           ESP01Dev(){}

            ~ESP01Dev();

            tDevInfo connect();
            void createInput(tGPIO gpio);
            void createOutput(tGPIO gpio);

            tGPIO getStatus(tGPIO gpio);
            void setStatus(tGPIO status); 


            std::vector<int> getCreatedGPOI();
            

      private:
            std::vector<int> GPIO;
            std::string m_Url;
            virtual bool validDateGPIO(tGPIO g)=0;
             


};



#endif