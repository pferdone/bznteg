/*
 * nntp_connector.h
 *
 *  Created on: Aug 20, 2012
 *      Author: pferdone
 */

#ifndef NNTP_MANAGER_H_
#define NNTP_MANAGER_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>
#include "common/nntp_common.h"

using boost::asio::ip::tcp;
typedef std::vector<uint8_t> Buffer8_t;

/** NNTP manager is used to connect to an nntp server and provide
 *  basic communication methods. */
class NNTPManager
{
  public:
    /** Destructor. **/
    ~NNTPManager();

    /** Returns an instance to the NNTPManager. **/
    static NNTPManager& getInstance(const std::string &host = "", const std::string &port = "");
    /** Destroys the current instance of the NNTPManager. **/
    void destroy();

    /** Connect to server set in the constructor. **/
    void connect();
    /** Close connection to server. **/
    void close();
    /** Send buffer to the server. **/
    void send(const Buffer8_t &buffer);
    void send(const uint8_t *buffer, std::size_t size);
    /** If socket is connected to the server. **/
    bool isConnected() const;
    /** Poll server messages. **/
    bool poll();
    /** Returns the data buffer. **/
    const Buffer8_t& buffer() const;
    /** Returns the response code: 0x20??????.
     * @return Returns 0xffffffff when buffer is not big enough. **/
    uint32_t getResponseCode() const;

  private:
    /** Constructor. **/
    NNTPManager(const std::string &host, const std::string &port);
    /** Handle connection errors. **/
    void handleConnection(const boost::system::error_code& error);
    /** Handle socket read errors. **/
    void handleRead(const boost::system::error_code& error);
    /** Handle socket send errors. **/
    void handleSend(const boost::system::error_code& error);

    static NNTPManager *_instance;
    boost::asio::io_service _ioService;
    tcp::socket _socket;
    tcp::resolver::iterator _resIter;
    Buffer8_t _buffer;
};

#endif /* NNTP_MANAGER_H_ */
