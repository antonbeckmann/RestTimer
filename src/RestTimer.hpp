
#ifndef REST_TIMER
#define REST_TIMER

#include <stdio.h>
#include <Poco/File.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionCallback.h>
#include <Poco/Util/XMLConfiguration.h>
#include <Poco/DateTime.h>

#include "ESP01Relay.hpp"

class RestTimer : public Poco::Util::Application
{

public:
    void defineOptions(Poco::Util::OptionSet &options);
    void defineOptions();

    const char *name()
    {
        return "ESPTimer";
    }

protected:
    void initialize(Application &self)
    {
        loadConfiguration(); // load default configuration files, if present
        Application::initialize(self);
        // add your own initialization code here
    }

    void uninitialize()
    {
        // add your own uninitialization code here
        quit = true;
        Application::uninitialize();

    }

    void reinitialize(Application &self)
    {
        Application::reinitialize(self);
        // add your own reinitialization code here
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    void handleHelp(const std::string &name, const std::string &value)
    {
        std::cout << "this is help";
    }

    void handleConfig(const std::string &name, const std::string &value);
   

    int main(const std::vector<std::string> &args);

    private:
        Poco::File configFile;
        std::string url;
        std::vector<Poco::DateTime> turnOnList;
        std::vector<Poco::DateTime> turnOffList;
        bool quit;
};

#endif

POCO_APP_MAIN(RestTimer)