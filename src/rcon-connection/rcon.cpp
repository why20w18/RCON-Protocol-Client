#include "../../include/rcon.hpp"

remoteControl::remoteControl(const std::string &server_ip , uint32_t server_port , const std::string &rcon_pass , uint32_t rcon_port)
: server_ip(server_ip) , server_port(server_port) , rcon_pass(rcon_pass) , rcon_port(rcon_port){
    rconAuthSuccess = false;

    try{
        //KALICI BAGLANTIYI SAGLAMA//
        this->io_context = make_unique<boost::asio::io_context>();
        this->socket = make_unique<ip::tcp::socket>(*io_context);
        this->resolver = make_unique<ip::tcp::resolver>(*io_context);
        

        auto endpoint = resolver->resolve(server_ip,std::to_string(rcon_port));
        boost::asio::connect(*socket,endpoint);

        const int packetSize = 12 + (rcon_pass.length()+1) + 1;
        std::vector<char> loginPacket(packetSize);

        createPacket_RCON(loginPacket.data(),1,rcon_pass,true);
        sendPacket_RCON(loginPacket.data(),packetSize);

        std::vector<char> response(4096);
        if(!recvPacket_RCON(response.data())){
            throw std::runtime_error("RCON DOGRULAMASI HATALI BASARISIZ !");
        }

        uint32_t requestID = *reinterpret_cast<uint32_t*>(response.data()+4); //4.bytedan itibaren request id 4-8
        if(requestID == -1){
            throw std::runtime_error("GECERSIZ RCON PAROLASI");
        }
            

        cout << "RCON BAGLANTISI BASARIYLA SAGLANDI !\n";
        rconAuthSuccess = true;

    }
    catch(exception &ex){
        cerr << "REMOTE CONTROL CONSTRUCTOR ERR : " << ex.what() << endl;
        rconAuthSuccess = false;
    }
}

void remoteControl::createPacket_RCON(char *packet,int requestID,const std::string &payload,bool isAuthRequest){
    
    int lengthByte = RCON_PACKET_FIELD_REQUEST_ID + RCON_PACKET_FIELD_TYPE + (payload.length()+1) + RCON_PACKET_FIELD_PAD;
    //4+4+(payload+1)+1


    *reinterpret_cast<uint32_t*>(packet) = lengthByte;                                      //LENGTH// 
    *reinterpret_cast<uint32_t*>(packet+4) = requestID;                                     //REQUEST-ID//
    *reinterpret_cast<uint32_t*>(packet+8) = isAuthRequest ? RCON_PACKET_FIELD_TYPE_LOGIN   //TYPE//
                                                           : RCON_PACKET_FIELD_TYPE_RUN_COMMAND;

    //PAYLOAD//
    memcpy((packet+12),payload.c_str(),payload.length());
    packet[12 + payload.length()] = '\0';

    //PAD//
    packet[12 + payload.length()+1] = '\0';

}


bool remoteControl::sendPacket_RCON(const char *packet,uint32_t packetSize){

    try{
            if(!socket->is_open()){
                throw std::runtime_error("[ERROR] SOKET KAPALIDIR PAKET GONDERILEMEZ");
            }

            boost::asio::write(*socket,boost::asio::buffer(packet,packetSize));
            return true;
        }
    catch(exception &ex){
        cerr << "SEND_PACKET_RCON ERR : " << ex.what() << endl;
        return false;
    }
}

bool remoteControl::recvPacket_RCON(char *response){
    try{
        //paket boyutunu okuma
        uint32_t lengthSection;
        boost::asio::read(*socket,boost::asio::buffer(&lengthSection,4));
        cout << "GELEN PAKET BOYUTU : " << lengthSection << endl;

////
        boost::asio::read(*socket,boost::asio::buffer(response+4,lengthSection));
        *reinterpret_cast<uint32_t*>(response) = lengthSection;
        
        return true;

    }
    catch(exception &ex){
        cerr << "RECV_PACKET_RCON ERR : " << ex.what() << endl;
        return false;
    }

}

bool remoteControl::isRconAuthSuccess(){
    return this->rconAuthSuccess;
}

std::string remoteControl::runCommand(const std::string &command){
    try{
        static int requestID = 2;
    
        const uint32_t packetSize = 12 + (command.length()+1) +1;
        std::vector<char> packet(packetSize);

        createPacket_RCON(packet.data(),requestID,command,false);

        if(!sendPacket_RCON(packet.data(),packetSize)){
            throw std::runtime_error("RUN_COMMAND : PAKET GONDERILEMEDI");
        }

        std::vector<char> response(4096);

        if(!recvPacket_RCON(response.data())){
            throw std::runtime_error("RUN_COMMAND : PAKET ICERIGI ALINAMADI");
        }

        return std::string(response.data()+12);
    }
    catch(exception &er){
        cerr << "HATA KOMUT ISLENEMEDI : " << er.what() << endl;
        return "";
    }
}
