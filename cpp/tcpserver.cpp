/**
 * @file tcpserver.cpp
 * @brief Implementation file for the tcpserver class.
 *
 * This file contains the implementation of the tcpserver class, which
 * represents a TCP/IP INET server. It provides functionality to establish
 * connections with clients and process incoming requests.
 *
 * @author Eric Lecolinet
 * @date 2016
 * @see http://www.telecom-paristech.fr/~elc
 */

#include "tcpserver.hh"

#include <csignal>
#include <iostream>
#include <thread>
using namespace std;

/// Connection with a given client. Each SocketCnx uses a different thread.
class SocketCnx {
   public:
    /**
     * @brief Constructs a SocketCnx object.
     * @param server The TCPServer object.
     * @param socket The Socket object representing the client connection.
     */
    SocketCnx(TCPServer&, Socket*);

    /**
     * @brief Destroys the SocketCnx object.
     */
    ~SocketCnx();

    /**
     * @brief Processes incoming requests on the client connection.
     */
    void processRequests();

    TCPServer& server_;  ///< Reference to the TCPServer object.
    Socket* sock_;  ///< Pointer to the Socket object representing the client
                    ///< connection.
    SocketBuffer* sockbuf_;  ///< Pointer to the SocketBuffer object for
                             ///< reading/writing data.
    std::thread thread_;     ///< Thread for processing requests.
};

SocketCnx::SocketCnx(TCPServer& server, Socket* socket)
    : server_(server),
      sock_(socket),
      sockbuf_(new SocketBuffer(sock_)),
      thread_(std::thread([this] { processRequests(); })) {
    thread_.detach();
}

SocketCnx::~SocketCnx() {
    sock_->close();
    delete sockbuf_;
    delete sock_;
}

void SocketCnx::processRequests() {
    while (true) {
        std::string request, response;

        auto received = sockbuf_->readLine(request);

        if (received < 0) {
            server_.error("Read error");
            break;
        }

        if (received == 0) {
            server_.error("Connection closed by client");
            break;
        }

        if (!server_.callback_) {
            response = "OK";
        } else if (!server_.callback_(request, response)) {
            server_.error("Closing connection with client");
            break;
        }

        response += "|";
        auto sent = sockbuf_->writeLine(response);

        if (sent < 0) {
            server_.error("Write error");
            break;
        }

        if (sent == 0) {
            server_.error("Connection closed by client");
            break;
        }
    }

    delete this;
}

TCPServer::TCPServer(Callback const& callback) : callback_(callback) {}

TCPServer::~TCPServer() {}

int TCPServer::run(int port) {
    int status = servsock_.bind(port);

    if (status < 0) {
        error("Can't bind on port: " + to_string(port));
        return status;
    }

    while (true) {
        if (auto* socket = servsock_.accept()) {
            new SocketCnx(*this, socket);
        } else
            error("input connection failed");
    }
    return 0;
}

void TCPServer::error(const string& msg) {
    std::cerr << "TCPServer: " << msg << std::endl;
}
