#include "InterfaceServerApp.hpp"
#include "RequestHandlerFactory.hpp"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <stdexcept>
using namespace Poco::Net;


int InterfaceServerApp::main(const vector<string> &vargs)
{


std::string configFile="esp_dev_list.txt";
if(vargs.size() >0) configFile = vargs.at(0);

std::string styleFile="style.css";
if(vargs.size() >1) styleFile = vargs.at(1);

int port = 9090;
try {
        port = std::stoi (vargs.at(2),nullptr,0);
    }
catch (const std::invalid_argument& ia) {
	  std::cerr << "Invalid argument @ port " << ia.what() << '\n';
      return Application::EXIT_CANTCREAT;
    }

HTTPServer s(new RequestHandlerFactory(configFile,styleFile), ServerSocket(port), new HTTPServerParams);

s.start();
cout << endl << "Server started" << endl;

waitForTerminationRequest();  // wait for CTRL-C or kill

cout << endl << "Shutting down..." << endl;
s.stop();

return Application::EXIT_OK;
}
