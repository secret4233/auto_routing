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


Logger LogInitFile(string name){
    //用Initializer类进行初始化
    Initializer initializer;

    //参数app表示追加到文件后
    string nameOfLog = "./output";
    nameOfLog = nameOfLog + "/" + getNowTime() + ".log";

    SharedAppenderPtr fileAppender(new FileAppender(LOG4CPLUS_TEXT(nameOfLog),std::ios_base::app));

    //设置Appender的名称和输出格式                                          
    fileAppender->setName(LOG4CPLUS_TEXT(name));
    tstring pattern = LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S}  - %m [%l]%n");
    fileAppender->setLayout(std::unique_ptr<Layout>(new PatternLayout(pattern))); 

    //获得一个logger实例,并设置日志输出等级阈值
    logger = Logger::getInstance(LOG4CPLUS_TEXT ("file_logger"));
    logger.setLogLevel(ALL_LOG_LEVEL);
 
    //为Logger实例添加FileAppender
    logger.addAppender(fileAppender);
    LOG4CPLUS_INFO(logger,"why" << 233 << "error");
    LOG4CPLUS_DEBUG(logger,LOG4CPLUS_TEXT("fuck!!"));

    return logger;
}


