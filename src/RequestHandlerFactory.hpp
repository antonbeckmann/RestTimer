#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Util/ServerApplication.h>

#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/IPAddress.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/String.h>
#include <Poco/Net/HTMLForm.h>

#include <Poco/StringTokenizer.h>

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ConfigHandler.hpp"
// take out and try
//#include "ESPDevInfo.hpp"

using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;


class RequestHandler : public HTTPRequestHandler
{

private:
  static int count;
  string getHtmlHeader();
  string getHtmlStyle();
  string getHtmlEnd();
  string getStringFromFile(std::string fileName);
  std::vector<std::string> getLinesFromFile(std::string fileName);
  std::vector<std::string> getESPIpsFromFile(std::string fileName);
  std::vector<std::string> espIps;
  std::string styleString ="";
public:
  RequestHandler(std::string configFile, std::string styleFile)
  {
     espIps      = ConfigHandler(configFile).getLines();
     styleString = ConfigHandler(styleFile).getLine();
  }
  virtual void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp);
    
};

class RequestHandlerFactory : public HTTPRequestHandlerFactory
{

public:
  RequestHandlerFactory(std::string _configFile, std::string _styleFile)
  {
     configFile = _configFile;
     styleFile  = _styleFile;
  }

  virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &)
  {
    return new RequestHandler(configFile,styleFile);
  }
  private:
      std::string styleFile ="";
      std::string configFile ="";
      int serverport = 0;
};

