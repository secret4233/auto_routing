#ifndef _LOG_H
#define _LOG_H

#include <log4cplus/log4cplus.h>
using namespace std;
using namespace log4cplus;


#define PATH_SIZE 1024
//日志封装
#define logDebug(...) LOG4CPLUS_DEBUG_FMT(LogUtils::_logger, __VA_ARGS__)
#define logInfo(...) LOG4CPLUS_INFO_FMT(LogUtils::_logger, __VA_ARGS__)
#define logWarn(...) LOG4CPLUS_WARN_FMT(LogUtils::_logger, __VA_ARGS__)
#define logError(...) LOG4CPLUS_ERROR_FMT(LogUtils::_logger, __VA_ARGS__)

// 日志控制类，全局共用一个日志
class LogUtils{
private:
    //log文件路径及名称
    char _log_path[PATH_SIZE];
    char _log_name[PATH_SIZE << 1];
public:
    LogUtils();
    virtual ~LogUtils();
    bool open_log();

    // 获得日志实例
    static LogUtils& instance();

    static Logger _logger;
};




#endif