#include <bits/stdc++.h>
#include <log4cplus/log4cplus.h> 
#include "inc/pso.h"
#include "inc/grap.h"
#include "inc/log.h"



using namespace std;    

int main(){
    log4cplus::SharedAppenderPtr consoleAppender = LogInitConsole("console");

    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT ("test"));
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);
 
    //第4步：为Logger实例添加ConsoleAppender和FileAppender
    logger.addAppender(consoleAppender);
    //logger.addAppender(fileAppender);
 
    //第5步：使用宏将日志输出
    LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("Hello world"));
}