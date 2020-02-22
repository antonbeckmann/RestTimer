#include "RequestHandlerFactory.hpp"
#include "ESP01Relay.hpp"
#include "ESP01Dev.hpp"

void RequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
{
    #ifdef DEBUG
     cout<<"handlerequest"<<endl;
    #endif
    resp.setStatus(HTTPResponse::HTTP_OK);
   
    ostream& out = resp.send();
    out<<getHtmlHeader();

    out<<"<style>\n";
    
    out<<getHtmlStyle();
    
    out<<"</style>\n";
    out<< "</head>\n<body>\n";
   
    //std::vector<std::string> ESPList = getESPIpsFromFile("esp_dev_list.txt");

    // ESPList.push_back("esp-light01");
    // ESPList.push_back("esp-tv");
    // ESPList.push_back("192.168.172.3");
    // ESPList.push_back("192.168.172.4");
    // ESPList.push_back("192.168.172.5");
    for(auto const& value: espIps) {
        std::string ip = Poco::replace(value,".","_");
        
        out<< "<p><a href=\"http://"
           <<req.getHost()<<"/"<<ip
           <<"/on\" class=\"button_on\">"
           << value << "</a>"
           <<"\n";

        out<< "<a href=\"http://"
           <<req.getHost()<<"/"<<ip
           <<"/off\" class=\"button_off\">"
           << value << "</a></p>"
           <<"\n";   
    }

    out<<getHtmlEnd();

    Poco::StringTokenizer requrl (req.getURI(), "/",Poco::StringTokenizer::TOK_TRIM);
    //std::cout<<"url: "<<req.getURI()<<std::endl;
    if (requrl.count() > 2)        
    {        
            std::string ip = Poco::replace(requrl[1],"_",".");
            
            ESP01Relay relay(ip);
            // std::cout<<"url 1"<<requrl[0]<<std::endl;
            // std::cout<<"url 2"<<requrl[1]<<std::endl;
            // std::cout<<"url 3"<<requrl[2]<<std::endl;
            
            try
            {
                tDevInfo info = relay.connect();

                relay.createOutput(tGPIO(1,0,0));
                // std::cout<<"gpio "<<info.devname<<std::endl;
                // std::cout<<"id "<<info.id<<std::endl;
                // std::cout<<"status "<<info.type<<std::endl;
            
                
            
            }
            catch(const Esp01Exception_CouldNotConnect& e)
            {
                std::cerr << e.what() << '\n';
            }  
            catch(const Esp01Exception_CreateFailed& e)
            {
                std::cerr << e.what() << '\n';
            }
            catch(const Esp01Exception_CreateDuplicate& e)
            {
                std::cerr << e.what() << '\n';
            }
            try{
                if(requrl[2] == "on"){   
                    std::cout<<"turn on "<<req.getURI()<<std::endl; 
                    relay.setStatus(tGPIO(1,0,1)); 
                }    
            
                if(requrl[2] == "off"){
                    std::cout<<"turn off "<<req.getURI()<<std::endl; 
                    relay.setStatus(tGPIO(1,0,0));
                }
            }
            catch(const Esp01Exception_SetFailed& e)
            {
                std::cerr << e.what() << '\n';
            }     
    }     
  
}
string RequestHandler::getHtmlHeader()
{
    return     "<!DOCTYPE html> \n <html> \n <head> \n ";    
}

string RequestHandler::getHtmlStyle()
{
    return styleString;
}

string RequestHandler::getHtmlEnd()
{
    return "</body> </html>";
}

