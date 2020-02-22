#include "nlohmann/json.hpp"

#include <time.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>


#include "ESP01Dev.hpp"
#include "Exception.hpp"
#include "RestCallHandler.hpp"
#include <sstream>
#include <iostream>

using namespace curlpp::options;

ESP01Dev::~ESP01Dev()
{

}
void ESP01Dev::createInput(tGPIO gpio)
{
    throw Esp01Exception_NotImplemented();

    /*
    200 (OK) or 204 (No Content). Use 404 (Not Found), if ID not found or invalid.
     */
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;
        cURLpp::Options::Url optUrl(m_Url);
        request.setOpt(optUrl); 
        request.setOpt(new curlpp::options::Verbose(true)); 
        
        std::list<std::string> header; 
        header.push_back("Content-Type: application/json"); 
        
        request.setOpt(new curlpp::options::HttpHeader(header)); 
        
        std::string json = "{    \"id\": 1,    \"gpio\": 0,    \"status\": 1 }";
        request.setOpt(new curlpp::options::PostFields(json));
        request.setOpt(new curlpp::options::PostFieldSize(json.size()));
       
        std::ostringstream os;
        os << optUrl;
        request.perform(); 
    }
    catch ( curlpp::LogicError & e ) {
        std::cout << e.what() << std::endl;
    }
    catch ( curlpp::RuntimeError & e ) {
        std::cout << e.what() << std::endl;
    }
}


tDevInfo ESP01Dev::connect()
{
    std::ostringstream respMsg;
    try{
        RestCallHandler rest(m_Url);
        std::string restResponse = rest.performGetRequest();
        //std::cout<<"return of restclass: "<<restResponse<<std::endl;

        int rid=-1,rtype=-1;
        std::string rdevname="zero";

        std::istringstream ifs(restResponse);    
        nlohmann::json j;
        ifs >> j;

        j.at("devname").get_to(rdevname);
        j.at("id").get_to(rid);
        j.at("type").get_to(rtype);

        return tDevInfo(rdevname,rid,rtype);
    }
    catch(curlpp::RuntimeError & e)
    {
        throw Esp01Exception_CouldNotConnect(); 
        std::cout << e.what() << std::endl;
    }
    catch(curlpp::LogicError & e)
    {
        throw Esp01Exception_CouldNotConnect(); 
        std::cout << e.what() << std::endl;
    }


}

void ESP01Dev::createOutput(tGPIO gpio)
{
    //ESP01 hat nur 2 gpios: 
    // 0 und 1
    if(!validDateGPIO(gpio))
        throw Esp01Exception_InvalidGPIO();

    /*
    200 (OK) or 204 (No Content). Use 404 (Not Found), if ID not found or invalid.
     */
           
        std::string json;
        json = "{";
        json += "\"id\": "    + std::to_string(gpio.id) + ","; 
        json += "\"gpio\":"   + std::to_string(gpio.gpio) + ",";
        json += "\"status\":" + std::to_string(gpio.status);
        json += "}";

        RestCallHandler rest(m_Url + "/leds");        
        std::string restResponse = rest.performPostRequest(json);
        
   

    // if(r.status_code != 201)
    //     throw Esp01Exception_CreateFailed();

    // if(r.status_code != 409)
    //     throw Esp01Exception_CreateDuplicate();

    // if(r.status_code != 404)
    //     throw Esp01Exception_ZeroId();    
        
}

tGPIO ESP01Dev::getStatus(tGPIO gpio)
{

    //ESP01 hat nur 2 gpios: 
    // 0 und 1
    if(!validDateGPIO(gpio))
        throw Esp01Exception_InvalidGPIO();


    std::ostringstream respMsg;
    try{
        RestCallHandler rest(m_Url + "/leds");
        std::string restResponse = rest.performGetRequest();
        //std::cout<<"return of restclass: "<<restResponse<<std::endl;

        
        std::istringstream ifs(restResponse);    
        nlohmann::json j;
        ifs >> j;

        int rid=-1,rgpio=-1,rstatus=-1;

        j.at("id").get_to(rid);
        j.at("gpio").get_to(rgpio);
        j.at("status").get_to(rstatus);

        return tGPIO(rid,rgpio,rstatus);
    }
    catch(Esp01Exception_GetFailed & e)
    {
        std::cout << e.what() << std::endl;
        
    }
    catch(curlpp::RuntimeError & e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(curlpp::LogicError & e)
    {
        std::cout << e.what() << std::endl;
    }
}

std::vector<int> ESP01Dev::getCreatedGPOI()
{
    std::cout<<"ESP01Dev::getCreatedGPOI NOT IMPLEMENTED"<<std::endl;
    std::vector<int> createdGpios;
    return createdGpios;
}

void ESP01Dev::setStatus(tGPIO gpio)
{
    //ESP01 hat nur 2 gpios: 
    // 0 und 1
    if(!validDateGPIO(gpio))
        throw Esp01Exception_InvalidGPIO();


    std::ostringstream respMsg;
    try{
        nlohmann::json json;       

        int rid=-1,rgpio=-1,rstatus=-1;

        json["id"]=gpio.id;
        json["gpio"]=gpio.gpio;
        json["status"]=gpio.status;
        //std::cout<<json.dump()<<std::endl;
        RestCallHandler rest(m_Url + "/leds");
        std::string restResponse = rest.performPutRequest(json.dump());

        return;
    }
    catch(Esp01Exception_SetFailed & e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(curlpp::RuntimeError & e)
    {
        std::cout << e.what() << std::endl;
    }
    catch(curlpp::LogicError & e)
    {
        std::cout << e.what() << std::endl;
    }

}