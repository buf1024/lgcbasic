////////////////////////////////////////////////////////////////////////////////////////
// 
// Filekeeper Project
//  
//  
// FileName    : log.h
// Purpose     : Simple log4cxx wrapper
//               Use Example: 
//               FileKeeper.properties
//                 log4j.rootLogger=DEBUG, lgc.FileKeeper
//                 log4j.appender.lgc.FileKeeper=org.apache.log4j.FileAppender
//                 log4j.appender.lgc.FileKeeper.File=FileKeeper.log
//                 log4j.appender.lgc.FileKeeper.Append=false
//                 log4j.appender.lgc.FileKeeper.Encoding=UTF-8
//                 log4j.appender.lgc.FileKeeper.layout=org.apache.log4j.PatternLayout
//                 log4j.appender.lgc.FileKeeper.layout.ConversionPattern=%d %-5p %c - %m%n
//               #include <log.h> in stdafx.h
//               LOG(_T("lgc.FileKeeper"), _T("FileKeeper.properties"));
// Version     : 2011-01-04 (22:00) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#if _DEBUG

#include <log4cxx.h>
#include <stl.h>


#define LOG_ROOT(logger) \
    static LoggerPtr __theGlobalRootLogger(Logger::getLogger(##logger))\

class __Config
{
public:
    __Config(Std_String strFile)
    {
        PropertyConfigurator::configure(strFile.c_str());
    }
};

#define LOG_CONF(file) \
    static __Config __theGlobalConfig(##file)\

#define LOG(logger, file) \
    LOG_ROOT(logger); \
    LOG_CONF(file)  \

#define LOG_DEBUG(message)   LOG4CXX_DEBUG(__theGlobalRootLogger, message)
#define LOG_INFO(message)    LOG4CXX_INFO(__theGlobalRootLogger, message)
#define LOG_WARN(message)    LOG4CXX_WARN(__theGlobalRootLogger, message)
#define LOG_ERROR(message)   LOG4CXX_ERROR(__theGlobalRootLogger, message)
#define LOG_FATAL(message)   LOG4CXX_FATAL(__theGlobalRootLogger, message)

#else

#define LOG_ROOT(logger)
#define LOG_CONF(file)
#define LOG(logger, file)

#define LOG_DEBUG(message)
#define LOG_INFO(message)
#define LOG_WARN(message)
#define LOG_ERROR(message)
#define LOG_FATAL(message)

#endif
