#ifndef __RCON_LINK_HPP__
#define __RCON_LINK_HPP__

#include "funcEnums.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

//RCON CLIENT CLASS SABITLERI//
const int RCON_HEADER_SIZE = 10;
const int RCON_AUTH_COMMAND = 3;
const int RCON_EXEC_COMMAND = 2;
const int RCON_AUTH_SUCCESS = 2;
const int RCON_AUTH_FAILED = 0;

class rconClient{
private:
    tcp::socket rconSocket;
    std::string rconHost;
    short rconPort;

public:
    rconClient(boost::asio::io_service &ioserv, const std::string &rconHost , short rconPort);
    bool rconConnect();
    bool rconValidate(const std::string &password); 
    void rconExecuteCommand(const std::string &sendedCommand);
};

/*
1-rcona baglanilir
2-rcona baglandiktan sonra parola dogrulama kismi gecilmelidir
3-parola dogrulama gecilirse eger o zaman serverda komut yurutulebilir
*/

#endif 