/**
* \file
* The most simple example.
* 
*/

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <string> 
#include <sstream>
#include <iostream>

#include <curlpp/Infos.hpp>

using namespace curlpp::options;

int main(int, char **)
{
    /*
	try
	{
		// That's all that is needed to do cleanup of used resources (RAII style).
		curlpp::Cleanup myCleanup;

        cURLpp::Easy easyhandle;    

        cURLpp::Options::Url optUrl("http://example.com/");
        
        std::ostringstream os;
        os << optUrl;
        // Set the URL.
		easyhandle.setOpt(optUrl);
		
        
		easyhandle.perform();

        std::cout<<"~~~~~~~~~~~~~~~~~~~~"<<std::endl;

        std::cout<<os.str().size();
        }        // request.setOpt(new curlpp::options::PostFields(json));
        // request.setOpt(new curlpp::options::PostFieldSize(json.size()));
	{
		std::cout << e.what() << std::endl;
	}

	catch(curlpp::LogicError & e)
	{
		std::cout << e.what() << std::endl;
	}

    std::cout<<"######################################"<<std::endl;
*/
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;       
        cURLpp::Options::Url optUrl("http://esp-light01");

        std::ostringstream respMsg;
        request.setOpt(new curlpp::options::WriteStream(&respMsg));
        request.setOpt(optUrl); 
         
        //request.setOpt(new curlpp::options::Verbose(true)); 
        //request.setOpt(new cURLpp::Options::Port(1080));
        
        std::list<std::string> header; 
        header.push_back("Content-Type: application/json"); 
        
        request.setOpt(new curlpp::options::HttpHeader(header)); 
  
        std::string json = "{    \"id\": 1,    \"gpio\": 0,    \"status\": 1 }";
        // DO POST
        // request.setOpt(new curlpp::options::PostFields(json));
        // request.setOpt(new curlpp::options::PostFieldSize(json.size()));
        
        //DO PUT
        // request.setOpt(new curlpp::options::CustomRequest{"PUT"});
        // request.setOpt(new curlpp::options::PostFields(json));
        // request.setOpt(new curlpp::options::PostFieldSize(json.size()));

        request.perform(); 
        
        std::cout << respMsg.str() << std::endl;

        long http_code = curlpp::infos::ResponseCode::get(request);

        if (http_code == 200) {
            std::cout << "\n\nRequest succeeded, response: " << http_code << std::endl;
        } else {
            std::cout << "\n\nRequest failed, response: " << http_code << std::endl;
        }


        std::cout << respMsg.str() << std::endl;
        // os << request;
        // std::cout<<"\n~~~~~~~~lllllllllllllllll~~~~~~~~~~\n"<<os.str();
    }
    catch ( curlpp::LogicError & e ) {
        std::cout << e.what() << std::endl;
    }
    catch ( curlpp::RuntimeError & e ) {
        std::cout << e.what() << std::endl;
    }
    
  return 0;
}
