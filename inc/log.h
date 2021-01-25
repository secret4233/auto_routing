#ifndef _LOG_H
#define _LOG_H

#include <log4cplus/log4cplus.h>
using namespace std;

log4cplus::SharedAppenderPtr LogInitConsole(string name);
log4cplus::SharedAppenderPtr LogInitFile(string name);


#endif