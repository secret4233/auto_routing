#ifndef _LOG_H
#define _LOG_H

#include <log4cplus/log4cplus.h>
using namespace std;
using namespace log4cplus;


// TODO 1.日志颜色封装; 2.日志等级封装

#define PATH_SIZE 1024
//日志封装
#define LogDebug(...) LOG4CPLUS_DEBUG_FMT(LogUtils::_logger, __VA_ARGS__)
#define LogInfo(...) LOG4CPLUS_INFO_FMT(LogUtils::_logger, __VA_ARGS__)
#define LogWarn(...) LOG4CPLUS_WARN_FMT(LogUtils::_logger, __VA_ARGS__)
#define LogError(...) LOG4CPLUS_ERROR_FMT(LogUtils::_logger, __VA_ARGS__)


// 日志控制类，全局共用一个日志
class LogUtils{
private:
    //log文件路径及名称
    char logPath[PATH_SIZE];
    char logName[PATH_SIZE << 1];
    bool logInit(int);
public:
    LogUtils(int);
    virtual ~LogUtils();
    void SetLogLevel(int);

    // 日志实例
    static Logger _logger;
};




#endif