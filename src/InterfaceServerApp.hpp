#include <vector>
#include <Poco/Util/ServerApplication.h>
using namespace Poco::Util;
using namespace std;

class InterfaceServerApp : public ServerApplication
{
protected:
  int main(const vector<string> &);
};