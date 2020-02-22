#ifndef CONFIG_HANDLER_HPP
#define CONFIG_HANDLER_HPP
#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <Poco/StringTokenizer.h>

class ConfigHandler
{
    public:
        ConfigHandler(std::string fn)
        {
            filename = fn;
            getStringFromFile();
            
        }
        std::string getLine(){
            return content;
        }

        std::vector<std::string> getLines(){
            getLinesFromFile();
            return contentList;
        }
    private:
        std::string filename;
        std::string content;
        std::vector<std::string> contentList;
    
        void getStringFromFile()
        {
            std::ifstream fileStream;
            
            fileStream.open(filename,std::ios::binary | std::ios::in);
            if (!fileStream)
            {

            std::cout << "\nDatei " << filename
                    << " konnte nicht geoeffnet werden!" << std::endl;
                
                fileStream.close();
                content = "no content";
            }
            else
            {
                #ifdef DEBUG
                    std::cout << "\nDatei " << filename
                        << " konnte  geoeffnet werden!" << std::endl;
                #endif
                content = std::string ( (std::istreambuf_iterator<char>(fileStream) ),
                            (std::istreambuf_iterator<char>()    ) );

                fileStream.close();            
            }
        }

        void getLinesFromFile()
        {
            Poco::StringTokenizer list (content, "\n",Poco::StringTokenizer::TOK_TRIM);
            for(int i=0;i<list.count();i++){
                #ifdef DEBUG
                    std::cout<<"line "<<i<<": "<<list[i]<<std::endl;
                #endif
                contentList.push_back((std::string)list[i]);
            }
        }


};
#endif