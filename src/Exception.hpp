#ifndef ESP01_EXCEP_H
#define ESP01_EXCEP_H
#include <iostream>
#include <exception>
using namespace std;

class Esp01Exception_CouldNotConnect: public exception
{
  public:  
  virtual const char* what() const throw()
  {
    return "Could not connect to Hardware";
  }
};

class Esp01Exception_CreateFailed: public exception
{
  public:    
  virtual const char* what() const throw()
  {
    return "Could not create GPIO";
  }
};

class Esp01Exception_CreateDuplicate: public exception
{
  public:    
  virtual const char* what() const throw()
  {
    return "Could not create duplicated GPIO";
  }
};

class Esp01Exception_ZeroId: public exception
{
  public:    
  virtual const char* what() const throw()
  {
    return "GPIO with ID ZERO";
  }
};

class Esp01Exception_InvalidGPIO: public exception
{
  public:    
  virtual const char* what() const throw()
  {
    return "GPIO with invalid value";
  }
};

class Esp01Exception_InvalidStatus: public exception
{
  public:    
  virtual const char* what() const throw()
  {
    return "GPIO with invalid value";
  }
};

class Esp01Exception_GetFailed: public exception
{
public:  
  virtual const char* what() const throw()
  {
    return "Could not get status of GPIO";
  }
};

class Esp01Exception_SetFailed: public exception
{
    public:  
  virtual const char* what() const throw()
  {
    return "Could not set Output";
  }
};

class Esp01Exception_Unknown: public exception
{
    public:  
  virtual const char* what() const throw()
  {
    return "Unknown error occured";
  }
};

class Esp01Exception_NotImplemented: public exception
{
    public:  
  virtual const char* what() const throw()
  {
    return "Not implemented yet";
  }
};

class Esp01Exception_JSONError: public exception
{
    public:  
  virtual const char* what() const throw()
  {
    return "Server could not parse JSON";
  }
};
#endif //ESP01_EXCEP_H