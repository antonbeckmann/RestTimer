cmake_minimum_required(VERSION 2.8.9)
#set (CMAKE_CXX_FLAGS "-g -std=c++0x")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set (CMAKE_CXX g++)

project(app)
#find_package (vsomeip 2.6.0 REQUIRED)
#find_package( Boost 1.55 COMPONENTS system thread log random REQUIRED )
find_package(Poco REQUIRED COMPONENTS Util Net XML JSON Foundation)



SET(Poco_INCLUDE_DIRS "/usr/local/include/Poco")
SET(Json_INCLUDE_DIRS "/nlohmann")
link_directories(/usr/local/lib)
# anton@ThinkPad-X230:~/GIT/curlpp/build/extras$ ./curlpp-config --cflags
# -Iinclude -I/usr/local/include
# anton@ThinkPad-X230:~/GIT/curlpp/build/extras$ ./curlpp-config --libs
# -Llib -L/usr/local/lib -lcurl -lcurlpp

include_directories (
    #${Boost_INCLUDE_DIR}
    ${Poco_INCLUDE_DIRS}
    ${VSOMEIP_INCLUDE_DIRS}
    ${Json_INCLUDE_DIRS}
)

message(${Poco_INCLUDE_DIRS})
#message( ${POCO_LIBRARIES})
#set (CMAKE_CXX_STANDARD 11)
set(PROJEKT "webserver")
#set(PROJEKT "curl")

if(${PROJEKT} STREQUAL "webserver")
    message("webserver is building")
    add_executable(webserver 
                    src/InterfaceServerApp.cpp
                    src/InterfaceServerMain.cpp
                    src/RequestHandlerFactory.cpp
                    src/ESP01Dev.cpp
                    src/ESP01Relay.cpp
                    )
    #add_executable(webserver /home/anton/GIT/webserver/webserver2/webserver.tutotial.cpp)
    target_link_libraries(webserver PUBLIC Poco::Net Poco::Util Poco::JSON  Poco::XML Poco::JSON Poco::Foundation curl curlpp)
    #target_link_libraries(webserver PUBLIC ${Boost_LIBRARIES}   Poco::Net Poco::Util Poco::JSON)
    
else()
    message("webserver is NOT building")
endif()

if(${PROJEKT} STREQUAL "curl")
    message("curl is building")
    add_executable(helloworldcurl 
                    src/helloworldcurl.cpp
                    )
    #add_executable(webserver /home/anton/GIT/webserver/webserver2/webserver.tutotial.cpp)
    target_link_libraries(helloworldcurl PUBLIC curl curlpp)
    #target_link_libraries(webserver PUBLIC ${Boost_LIBRARIES}   Poco::Net Poco::Util Poco::JSON)
    
else()
    message("curl is NOT building")
endif()
