#include "log.h"


string getNowTime(){
    time_t setTime;
	time(&setTime);
	tm* ptm = localtime(&setTime);
	std::string time = std::to_string(ptm->tm_year + 1900)
	                   + "."
	                   + std::to_string(ptm->tm_mon + 1)
	                   + "."
	                   + std::to_string(ptm->tm_mday);		
	return time;	
}

// log4cplus::SharedAppenderPtr LogInitConsole(string name){
//     log4cplus::Initializer initializer;
//     log4cplus::SharedAppenderPtr consoleAppender(new log4cplus::ConsoleAppender);

//     //设置Appender的名称和输出格式
//     consoleAppender->setName(LOG4CPLUS_TEXT(name));
//     consoleAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout()));
//     return consoleAppender;
// }

log4cplus::Logger LogOutput::LogInitFile(string name){
    //用Initializer类进行初始化
    log4cplus::Initializer initializer;

    //参数app表示追加到文件后
    string nameOfLog = "./output";
    nameOfLog = nameOfLog + "/" + getNowTime() + ".log";

    log4cplus::SharedAppenderPtr fileAppender(new log4cplus::FileAppender(
                                                  LOG4CPLUS_TEXT(nameOfLog),
                                                  std::ios_base::app
                                                  )
                                              );

    //设置Appender的名称和输出格式                                          
    fileAppender->setName(LOG4CPLUS_TEXT(name));
    log4cplus::tstring pattern = LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S}  %-5p %c - %m [%l]%n");
    fileAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern))); 

    //获得一个logger实例,并设置日志输出等级阈值
    log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT ("test"));
    logger.setLogLevel(log4cplus::ALL_LOG_LEVEL);
 
    //为Logger实例添加FileAppender
    logger.addAppender(fileAppender);
 
    //第5步：使用宏将日志输出
    return logger;
}

void LogOutput::LogInfo(string formatString){
    LOG4CPLUS_INFO(logMessage, LOG4CPLUS_TEXT("Hello world"));
    return;
}

