//https://minecraft.wiki/w/RCON//
#ifndef __REMOTE_CONTROL_CLIENT__
#define __REMOTE_CONTROL_CLIENT__

#include "funcEnums.hpp"
#include "debug.hpp"
#include <iostream>
#include <string>
#include <boost/asio.hpp>

#define RCON_PACKET_FIELD_LENGTH 4
#define RCON_PACKET_FIELD_REQUEST_ID 4
#define RCON_PACKET_FIELD_TYPE 4
    #define RCON_PACKET_FIELD_TYPE_LOGIN 3
    #define RCON_PACKET_FIELD_TYPE_RUN_COMMAND 2
#define RCON_PACKET_FIELD_PAD 1

using namespace std;
using namespace boost::asio;


class remoteControl{
private:
    std::string server_ip;
    uint32_t server_port;
    std::string rcon_pass;
    uint32_t rcon_port;

    bool rconAuthSuccess;

    //kalici baglanti icin SMART POINTERLAR//
    unique_ptr<boost::asio::io_context> io_context;
    unique_ptr<ip::tcp::socket> socket;
    unique_ptr<ip::tcp::resolver> resolver;

    void createPacket_RCON(char *packet,int requestID,const std::string &payload,bool isAuthRequest);
    bool sendPacket_RCON(const char *packet,uint32_t packetSize);
    bool recvPacket_RCON(char *response);


public:
    
    remoteControl(const std::string &server_ip , uint32_t server_port, 
                  const std::string &rcon_pass , uint32_t rcon_port);

    std::string runCommand(const std::string &command);
    bool isRconAuthSuccess();

    void rconServerInfo() const;
    std::string rconServerInfoStr();
};

#endif 

/*
Field name	    Field type	    Notes
Length	        int32	        Length of remainder of packet
Request ID	    int32	        Client-generated ID
Type	        int32	        3 for login, 2 to run a command, 0 for a multi-packet response
Payload	        byte[]	        NULL-terminated ASCII text
1-byte pad	    byte	        NULL
*/