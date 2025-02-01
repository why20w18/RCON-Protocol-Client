#include "../../include/rcon.hpp"

rconClient::rconClient(boost::asio::io_context &ioserv, const std::string &rconHost , short rconPort)
: rconSocket(ioserv) , rconHost(rconHost) , rconPort(rconPort)
{    
    std::cout << "--->RCON CONSTRUCTOR\n";
}

bool rconClient::rconConnect(){
    try{
        tcp::resolver rconResolver(rconSocket.get_executor());
        auto rconEndPointIterator = rconResolver.resolve(rconHost, std::to_string(rconPort));


        for (auto& endpoint : rconEndPointIterator) {
            std::cout << "Trying endpoint: " << endpoint.endpoint() << "\n";
        }

        boost::asio::connect(rconSocket,rconEndPointIterator);

        return true;
    }
    catch(std::exception &e){
        std::cout << "CONNECTION FAILED : " << e.what() << "\n";
        return false;
    }
}

bool rconClient::rconValidate(const std::string &password) {
    const size_t paketSize = RCON_HEADER_SIZE + password.size() + 1;
    std::vector<char> req_ParolaDogrulama(paketSize);

    memset(req_ParolaDogrulama.data(), 0, req_ParolaDogrulama.size());

    req_ParolaDogrulama[0] = 1;                  // req_id
    req_ParolaDogrulama[1] = RCON_AUTH_COMMAND; // command type
    req_ParolaDogrulama[RCON_HEADER_SIZE + password.size()] = '\0'; // Null terminator

    // Paket hazırlanıyor
    memcpy(req_ParolaDogrulama.data() + RCON_HEADER_SIZE, password.c_str(), password.size());

    // Paket gönderiliyor
    boost::asio::write(rconSocket, boost::asio::buffer(req_ParolaDogrulama));

    return true;
}


 void rconClient::rconExecuteCommand(const std::string& command) {
    const size_t paketSize = RCON_HEADER_SIZE+command.size()+1;
    std::vector<char> req_CommandSender(paketSize);
    
    memset(req_CommandSender.data(),0,req_CommandSender.size());
    
        // Başlık (ID, komut tipi, vb.)
        req_CommandSender[0] = 0;                   // Request ID
        req_CommandSender[1] = RCON_EXEC_COMMAND;   // Komut tipi (execute command)
        req_CommandSender[2] = 0;                   // Hata kodu
        req_CommandSender[3] = 0;                   // Hata kodu

        // Komutu ekleme
        std::memcpy(req_CommandSender.data() + RCON_HEADER_SIZE, command.c_str(), command.size());

        // RCON komutunu gönderme
        boost::asio::write(rconSocket, boost::asio::buffer(req_CommandSender));

    }
