#include "log.h"
#include <time.h>
#include <memory>

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

LogUtils::LogUtils(){
    snprintf(_log_path,sizeof(_log_path),  "%s", "./output");
    snprintf(_log_name,sizeof(_log_name),  "%s/%s.%s", _log_path, getNowTime().c_str(), "log");
}

LogUtils::~LogUtils(){}

LogUtils& LogUtils::instance(){
    static LogUtils log;
    return log;
}

bool LogUtils::open_log(){
    int Log_level = 0;

    /* step 1: Instantiate an appender object */
    SharedAppenderPtr _append(new FileAppender(_log_name,ios_base::app));
    _append->setName("file log test");

    /* step 2: Instantiate a layout object */
    string pattern = "[%p] [%d{%m/%d/%y %H:%M:%S}] [%l] - %m%n";

    /* step 3: Attach the layout object to the appender */
    _append->setLayout(unique_ptr<Layout>(new PatternLayout(pattern))); 

    /* step 5: Attach the appender object to the logger  */
    LogUtils::_logger.addAppender(_append);

    /* step 6: Set a priority for the logger  */
    LogUtils::_logger.setLogLevel(Log_level);
    return true;
}

// Logger LogInitFile(string name){
//     //用Initializer类进行初始化
//     Initializer initializer;

//     //参数app表示追加到文件后
//     string nameOfLog = "./output";
//     nameOfLog = nameOfLog + "/" + getNowTime() + ".log";

//     SharedAppenderPtr fileAppender(new FileAppender(LOG4CPLUS_TEXT(nameOfLog),std::ios_base::app));

//     //设置Appender的名称和输出格式                                          
//     fileAppender->setName(LOG4CPLUS_TEXT(name));
//     tstring pattern = LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S}  - %m [%l]%n");
//     fileAppender->setLayout(std::unique_ptr<Layout>(new PatternLayout(pattern))); 

//     //获得一个logger实例,并设置日志输出等级阈值
//     logger = Logger::getInstance(LOG4CPLUS_TEXT ("file_logger"));
//     logger.setLogLevel(ALL_LOG_LEVEL);
 
//     //为Logger实例添加FileAppender
//     logger.addAppender(fileAppender);
//     LOG4CPLUS_INFO(logger,"why" << 233 << "error");
//     LOG4CPLUS_DEBUG(logger,LOG4CPLUS_TEXT("fuck!!"));

//     return logger;
// }


