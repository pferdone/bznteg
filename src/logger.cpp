/*
 * logger.cpp
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#include "logger.h"

Logger *Logger::_instance = 0;

//--------------------------------------------------------------------------------
Logger::Logger()
{

}

//--------------------------------------------------------------------------------
Logger::~Logger()
{

}

//--------------------------------------------------------------------------------
Logger& Logger::getInstance()
{
  if (_instance==0) {
    _instance = new Logger();
  }

  return *_instance;
}

//--------------------------------------------------------------------------------
void Logger::destroy()
{
  delete _instance;
  _instance = 0;
}

//--------------------------------------------------------------------------------
void Logger::log(const std::string &msg, uint8_t level)
{
  std::cout << (int)level << " " << msg << std::endl;
}
