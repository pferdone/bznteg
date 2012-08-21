/*
 * logger.h
 *
 *  Created on: Aug 21, 2012
 *      Author: pferdone
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <string>
#include <stdint.h>

/** Logging class. **/
class Logger
{
  public:
    /** Destructor. **/
    ~Logger();

    /** Get logger instance. **/
    static Logger& getInstance();
    /** Destroy current instance. **/
    void destroy();

    /** Log message. **/
    void log(const std::string &msg, uint8_t level=0);

  private:
    /** Constructor. **/
    Logger();

    static Logger *_instance;
};


#endif /* LOGGER_H_ */
