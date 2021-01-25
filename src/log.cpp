#include "log.h"


log4cplus::SharedAppenderPtr LogInitConsole(string name){
    //用Initializer类进行初始化
    log4cplus::Initializer initializer;
    log4cplus::SharedAppenderPtr consoleAppender(new log4cplus::ConsoleAppender);

    //设置Appender的名称和输出格式
    consoleAppender->setName(LOG4CPLUS_TEXT(name));
    consoleAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout()));
    return consoleAppender;
}

log4cplus::SharedAppenderPtr LogInitFile(string name){
    log4cplus::Initializer initializer;

    //参数app表示追加到文件后
    log4cplus::SharedAppenderPtr fileAppender(new log4cplus::FileAppender(
                                                  LOG4CPLUS_TEXT("../output/log.txt"),
                                                  std::ios_base::app
                                                  )
                                              );

    //设置Appender的名称和输出格式                                          
    fileAppender->setName(LOG4CPLUS_TEXT(name));
    log4cplus::tstring pattern = LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S,%Q} [%t] %-5p %c - %m [%l]%n");
    fileAppender->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::PatternLayout(pattern))); 
    return fileAppender;
}