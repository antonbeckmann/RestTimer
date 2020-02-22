#ifndef RESTCALLHANDLER_HPP
#define RESTCALLHANDLER_HPP

#include<string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include <sstream>
#include <iostream>

#include "Exception.hpp"


class RestCallHandler
{
    public:
    RestCallHandler(std::string apiUrl){
        m_apiUrl = apiUrl;
    }

    std::string performGetRequest(){
        std::string json= "";
        std::ostringstream respMsg;
        curlpp::Cleanup myCleanup;
        curlpp::Easy request;

        
        long http_code = 0;    
     
        // That's all that is needed to do cleanup of used resources (RAII style).
        request.setOpt(new curlpp::options::WriteStream(&respMsg));

        cURLpp::Options::Url optUrl(m_apiUrl);
        request.setOpt(optUrl); 

        std::list<std::string> header; 
        header.push_back("Content-Type: application/json"); 
        request.setOpt(new curlpp::options::HttpHeader(header)); 

        //std::cout<<"\nconnect to:"<<m_apiUrl<<std::endl;
    

        // Send request and get a result.
        // By default the result goes to standard output.
        request.perform();

        //std::cout << respMsg.str() << std::endl;
        http_code = curlpp::infos::ResponseCode::get(request);
        
        checkResponseAndThrow(http_code);
        json = respMsg.str();
        #ifdef DEBUG
        std::cout<<"INFO:RESTHANDLER:performGetRequest: "<<json<<std::endl;
        #endif
        return json;
    }

    std::string performPostRequest(std::string payload){
        std::string json= "";
        std::ostringstream respMsg;
      
        // That's all that is needed to do cleanup of used resources (RAII style).
        curlpp::Cleanup myCleanup;
        curlpp::Easy request;
        
        long http_code = 0;
            

            request.setOpt(new curlpp::options::WriteStream(&respMsg));

            cURLpp::Options::Url optUrl(m_apiUrl);
            request.setOpt(optUrl); 

            std::list<std::string> header; 
            header.push_back("Content-Type: application/json"); 
            request.setOpt(new curlpp::options::HttpHeader(header)); 
 
            // DO POST
            request.setOpt(new curlpp::options::PostFields(payload));
            request.setOpt(new curlpp::options::PostFieldSize(payload.size()));
  
            request.perform(); 
            http_code = curlpp::infos::ResponseCode::get(request);
   

        
        checkResponseAndThrow(http_code);
        json = respMsg.str();
        #ifdef DEBUG
        std::cout<<"INFO:RESTHANDLER:performPosRequest: "<<json<<std::endl;
        #endif
        return json;
    }

    std::string performPutRequest(std::string payload){
       
        std::string json= "";
        std::ostringstream respMsg;
        
        // That's all that is needed to do cleanup of used resources (RAII style).
        curlpp::Cleanup myCleanup;
        curlpp::Easy request;
        
        
        long http_code = 0;

        try{    

            request.setOpt(new curlpp::options::WriteStream(&respMsg));

            cURLpp::Options::Url optUrl(m_apiUrl);
            request.setOpt(optUrl); 

            std::list<std::string> header; 
            header.push_back("Content-Type: application/json"); 
            request.setOpt(new curlpp::options::HttpHeader(header)); 

            //std::cout<<"\nconnect to:"<<m_apiUrl<<std::endl;
           
            // DO Put
            request.setOpt(new curlpp::options::CustomRequest{"PUT"});
            request.setOpt(new curlpp::options::PostFields(payload));
            request.setOpt(new curlpp::options::PostFieldSize(payload.size()));
  
            request.perform();

            //std::cout << respMsg.str() << std::endl;
            http_code = curlpp::infos::ResponseCode::get(request);
            
        }
        catch ( curlpp::LogicError & e ) {
            std::cout << e.what() << std::endl;
        }
        catch ( curlpp::RuntimeError & e ) {
            std::cout << e.what() << std::endl;
        }
        
      
        checkResponseAndThrow(http_code);
        json = respMsg.str();
        #ifdef DEBUG
        std::cout<<"INFO:RESTHANDLER:performPutRequest: "<<json<<std::endl;
        #endif   
        return json;
    }

    void checkResponseAndThrow(int response)
    {
        #ifdef DEBUG
        std::cout<<"INFO:RESTHANDLER:checkResponseAndThrow:"<<response<<std::endl;
        #endif DEBUG
        switch(response)
        {
            case 409:
                throw Esp01Exception_CreateDuplicate();
            break;
            case 404:
                throw Esp01Exception_SetFailed();
            break;
            case 400:
                throw Esp01Exception_JSONError();
            break;
            case 204:
                throw Esp01Exception_GetFailed();
            break;
            
        }


    }

    private:
        std::string m_apiUrl;
};


#endif