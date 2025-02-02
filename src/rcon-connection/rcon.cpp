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
            
        DEBUG_LOG("RCON BAGLANTISI BASARIYLA SAGLANDI !");
        rconAuthSuccess = true;

    }
    catch(exception &ex){
        DEBUG_LOG("REMOTE CONTROL CONSTRUCTOR ERR : " << ex.what());
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
        DEBUG_LOG("SEND_PACKET_RCON ERR : " << ex.what());
        return false;
    }
}

bool remoteControl::recvPacket_RCON(char *response){
    try{
        //paket boyutunu okuma
        uint32_t lengthSection;
        boost::asio::read(*socket,boost::asio::buffer(&lengthSection,4));
        DEBUG_LOG("GELEN PAKET BOYUTU : " << lengthSection);

////
        boost::asio::read(*socket,boost::asio::buffer(response+4,lengthSection));
        *reinterpret_cast<uint32_t*>(response) = lengthSection;
        
        return true;

    }
    catch(exception &ex){
        DEBUG_LOG("RECV_PACKET_RCON ERR : " << ex.what());
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
        DEBUG_LOG("HATA KOMUT ISLENEMEDI : " << er.what());
        return "";
    }
}

void remoteControl::rconServerInfo() const{
        cout << "Server IP   : " << this->server_ip << endl;
        cout << "Server Port : " << this->server_port << endl;
        cout << "RCON Port   : " << this->rcon_port << endl;
        cout << "RCON Auth   : " << ((this->rconAuthSuccess) ? "Oturum Yetkilendirildi" : "Oturum Yetkilendirilmedi !") << endl;
}

std::string remoteControl::rconServerInfoStr(){
    string temp_s_servip = "Server IP: "+server_ip;
    string temp_s_servPort = "Server Port: "+to_string(server_port);
    string temp_s_rconPort = "RCON Port: "+to_string(rcon_port);
    string temp_s_rconPass = "RCON Pass: "+rcon_pass;
    string temp_s_auth = ((rconAuthSuccess) ? "Giris: Basarili" : "Giris: Basarisiz");
    

    return std::string("[RCON-SERVER-INFO]\n"+temp_s_servip+"\n"+temp_s_servPort+"\n"+
    temp_s_rconPort+"\n"+temp_s_rconPass+"\n"+temp_s_auth+"\n");    
}


