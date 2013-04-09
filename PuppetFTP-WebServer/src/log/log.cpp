/*
 * log.cpp
 *
 *  Created on: 3 oct. 2012
 *      Author: laplace
 */

#include <iostream>
#include <QDateTime>
#include "log.h"

void logMessage(QtMsgType type, const char* msg) {
    std::cout << "[" << QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss").toStdString() << "]";
    switch (type) {
    case QtDebugMsg:
        std::cout << "[INFO    ]    " << msg;
        break;
    case QtWarningMsg:
        std::cout << "[WARNING ]    " << msg;
        break;
    case QtCriticalMsg:
        std::cout << "[ERROR   ]    " << msg;
        break;
    case QtFatalMsg:
        std::cout << "[CRITICAL]    " << msg;
        break;
    }
    std::cout << std::endl;
 }
