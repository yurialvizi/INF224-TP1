/**
 * @file tcpserver.hh
 * @brief TCP/IP INET Server.
 *
 * This file contains the declaration of the TCPServer class, which represents a
 * TCP/IP IPv4 server. The server supports TCP/IP AF_INET IPv4 connections with
 * multiple clients. One thread is used per client.
 *
 * @author Eric Lecolinet
 * @date 2016
 * @see http://www.telecom-paristech.fr/~elc
 */

#ifndef __tcpserver__
#define __tcpserver__

#include <functional>
#include <memory>
#include <string>

#include "ccsocket.hh"

class TCPConnection;
class TCPLock;

/**
 * @brief TCP/IP IPv4 server.
 *
 * The TCPServer class represents a TCP/IP IPv4 server.
 * It supports TCP/IP AF_INET IPv4 connections with multiple clients.
 * One thread is used per client.
 */
class TCPServer {
   public:
    using Callback =
        std::function<bool(std::string const& request, std::string& response)>;

    /**
     * @brief Initializes the server.
     *
     * The callback function will be called each time the server receives a
     * request from a client.
     * - _request_ contains the data sent by the client.
     * - _response_ will be sent to the client as a response.
     * The connection with the client is closed if the callback returns false.
     *
     * @param callback The callback function to be called for each client
     * request.
     */
    TCPServer(Callback const& callback);

    /**
     * @brief Destructor.
     */
    virtual ~TCPServer();

    /**
     * @brief Starts the server.
     *
     * Binds an internal ServerSocket to _port_ then starts an infinite loop
     * that processes connection requests from clients.
     *
     * @param port The port number to bind the server socket to.
     * @return 0 on normal termination, or a negative value if the ServerSocket
     * could not be bound (value is then one of Socket::Errors).
     */
    virtual int run(int port);

   private:
    friend class TCPLock;
    friend class SocketCnx;

    TCPServer(TCPServer const&) = delete;
    TCPServer& operator=(TCPServer const&) = delete;

    /**
     * @brief Handles an error.
     *
     * @param msg The error message.
     */
    void error(std::string const& msg);

    ServerSocket servsock_;
    Callback callback_{};
};

#endif
