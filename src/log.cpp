#include "log.h"
#include <time.h>
#include <memory>

// 取得当前日期 格式:1900.1.1
string getNowTime(){
    time_t setTime;
	time(&setTime);
	tm* ptm = localtime(&setTime);
	string time = to_string(ptm->tm_year + 1900)
	                + "."
	                + to_string(ptm->tm_mon + 1)
	                + "."
	                + to_string(ptm->tm_mday);		
	return time;	
}


Logger LogUtils::_logger = log4cplus::Logger::getInstance("main_log");

/*
ALL_LOG_LEVEL       (    0) ：开放所有log信息输出
DEBUG_LOG_LEVEL     (10000) ：开放debug信息输出
INFO_LOG_LEVEL      (20000) ：开放info信息输出
WARN_LOG_LEVEL      (30000) ：开放warning信息输出
ERROR_LOG_LEVEL     (40000) ：开放error信息输出
OFF_LOG_LEVEL       (60000) ：关闭所有log信息输出
*/
LogUtils::LogUtils(int logLevel){
    snprintf(logPath,sizeof(logPath),  "%s", "./output");
    snprintf(logName,sizeof(logName),  "%s/%s.%s", logPath, getNowTime().c_str(), "log");
    logInit(logLevel);
}

LogUtils::~LogUtils(){}



//日志初始化操作
bool LogUtils::logInit(int logLevel){

    /* step 1: Instantiate an appender object */
    SharedAppenderPtr _append(new FileAppender(logName,ios_base::app));
    _append->setName("file log");

    /* step 2: Instantiate a layout object */
    string pattern = "[%p] [%D{%y-%m-%d %H:%M:%S}] [%l] - %m%n";

    /* step 3: Attach the layout object to the appender */
    _append->setLayout(unique_ptr<Layout>(new PatternLayout(pattern))); 

    /* step 5: Attach the appender object to the logger  */
    LogUtils::_logger.addAppender(_append);

    /* step 6: Set a priority for the logger  */
    LogUtils::_logger.setLogLevel(logLevel);
    return true;
}

// 设置日志等级
void LogUtils::SetLogLevel(int logLevel){
    _logger.setLogLevel(logLevel);
    return;
}



