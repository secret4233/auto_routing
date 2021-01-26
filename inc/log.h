#ifndef _LOG_H
#define _LOG_H

#include <log4cplus/log4cplus.h>
#include <time.h>
using namespace std;

class LogOutput{
private:
    log4cplus::Logger logMessage;
public:
    //log4cplus::SharedAppenderPtr LogInitConsole(string name);
    log4cplus::Logger LogInitFile(string name);
    void LogInfo(string formatString);
};




#endif