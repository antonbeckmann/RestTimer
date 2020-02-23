#include "RestTimer.hpp"

#include <Poco/DateTimeParser.h>
#include "ESP01Relay.hpp"
#include <chrono>

using namespace Poco::Util;
using Poco::AutoPtr;
using Poco::Util::XMLConfiguration;
int RestTimer::main(const std::vector<std::string> &args)
{
    Poco::DateTime ld;
    int timeZone = 0;
    std::string debugdate;

    std::cout<<ld.hour()<<":"<<ld.minute()<<std::endl;
//    std::cout<<turnOffList.at(0).hour()<<":"<<turnOffList.at(0).minute()<<std::endl;

    ESP01Relay relay(url);

    do
    {
        ld = Poco::DateTime();
        /* Sleep for 5 seconds */
        std::this_thread::sleep_for(std::chrono::seconds(30));
        try
        {

            tDevInfo info = relay.connect();
            relay.createOutput(tGPIO(1, 0, 0));
        }
        catch (const Esp01Exception_CouldNotConnect &e)
        {
            std::cerr << e.what() << '\n';
        }
        catch (const Esp01Exception_CreateFailed &e)
        {
            std::cerr << e.what() << '\n';
        }
        catch (const Esp01Exception_CreateDuplicate &e)
        {
            std::cerr << e.what() << '\n';
        }

        try
        {

            //debugdate = std::string("2005-01-01 02:08:50");
            //ld = Poco::DateTimeParser::parse(debugdate, timeZone);
    
            for (Poco::DateTime fileDT : turnOnList)
            {
                if (fileDT.hour() == ld.hour() &&
                    fileDT.minute() == ld.minute() &&
                    fileDT.second() == ld.second())
                {
                    std::cout<<"turn on"<<std::endl;
                    relay.setStatus(tGPIO(1, 0, 1));
                }
            }

            //std::this_thread::sleep_for(std::chrono::seconds(5));

            //debugdate = std::string("2005-01-01 02:08:55");
            //ld = Poco::DateTimeParser::parse(debugdate, timeZone);
    
            for (Poco::DateTime fileDT : turnOffList)
            {
                if (fileDT.hour() == ld.hour() &&
                    fileDT.minute() == ld.minute() &&
                    fileDT.second() == ld.second())
                {
                    std::cout<<"turn off"<<std::endl;
                    relay.setStatus(tGPIO(1, 0, 0));
                }
            }
            //std::this_thread::sleep_for(std::chrono::seconds(5));

        }
        catch (const Esp01Exception_SetFailed &e)
        {
            std::cerr << e.what() << '\n';
        }

    } while (!quit);

    return Application::EXIT_OK;
}

void RestTimer::defineOptions(Poco::Util::OptionSet &options)
{
    Application::defineOptions(options);

    options.addOption(
        Option("help", "h", "display help information")
            .required(false)
            .repeatable(false)
            .callback(OptionCallback<RestTimer>(this, &RestTimer::handleHelp)));

    options.addOption(
        Option("config-file", "f", "load configuration data from a file")
            .required(false)
            .repeatable(true)
            .argument("file")
            .callback(OptionCallback<RestTimer>(this, &RestTimer::handleConfig)));
    /*
        options.addOption(        
            Option("bind", "b", "bind option value to test.property")
                        .required(false)            
                        .argument("value")            
                        .validator(new IntValidator(0, 100))            
                        .binding("test.property"));
        */
}

void RestTimer::handleConfig(const std::string &name, const std::string &value)
{
    configFile = Poco::File(value);
    if (!configFile.exists())
    {
        std::cerr << "this is file but no file" << std::endl;
        return;
    }
    else
    {
        std::cout << "file foutn" << std::endl;
        try
        {
            AutoPtr<XMLConfiguration> pConf(new XMLConfiguration(value));

            std::string turnOn = pConf->getString("turnOn");
            std::string turnOff = pConf->getString("turnOff");
            url = pConf->getString("url");

            std::cout << turnOn << std::endl;
            std::cout << turnOff << std::endl;
            std::cout << url << std::endl;

            int timeZone = 0;
            turnOffList.push_back(Poco::DateTimeParser::parse(turnOff, timeZone));
            turnOnList.push_back(Poco::DateTimeParser::parse(turnOn, timeZone));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}