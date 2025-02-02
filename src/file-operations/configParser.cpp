#include "../../include/configParser.hpp"


config_parser::config_parser(const char *configPath){
    this->configPath = new std::string(configPath);
   
    //constructorla beraber MAP baslatildi tum config file icinde tutuluyor
    readConfig();


}

config_parser::~config_parser(){
    delete this->configPath;
}

    
void config_parser::setConfigSyntax(std::string &value){
    //bastaki ve sondaki bosluklari kaldirma [)
    value.erase(0,value.find_first_not_of(' '));
    value.erase(value.find_last_not_of(' ')+1);

    //tum harfleri kucuk harfe cevirme
    std::transform(value.begin(),value.end(),value.begin(),::tolower);
}

void config_parser::addConfigContentMap(const std::string key,const std::string &value){
    if(key == "SERVER_IP")
        this->configContent[CONFIG_SETTINGS_SERVER_IP] = value;
    
    else if(key == "SERVER_PORT")
        this->configContent[CONFIG_SETTINGS_SERVER_PORT] = value;

    else if(key == "RCON_SERVER_PORT")
        this->configContent[CONFIG_SETTINGS_RCON_SERVER_PORT] = value;

    else if(key == "RCON_PASSWORD")
        this->configContent[CONFIG_SETTINGS_RCON_PASSWORD] = value;

}
    


void config_parser::getCommentLine(){

}

int config_parser::getRecordCount(){

}

//initalize configContent
void config_parser::readConfig(){
    std::string satir;
    std::fstream read_file(*configPath,std::ios::in);

    while(getline(read_file,satir)){
        int equalIndex = satir.find('=');

        //yorum satirlarini atla
        if(satir.at(0) == '#')
            continue;
    
        //eger = karakterini bulduysa    
        else if(equalIndex != std::string::npos){
            std::string key = satir.substr(0,equalIndex);   //0'dan = 'e kadar
            std::string value = satir.substr(equalIndex+1); //='in 1 adim ilerisinden sona kadar
            
            setConfigSyntax(value);
            addConfigContentMap(key,value);

            DEBUG_LOG("key : " << key << "  value : " << value);
        }
        else{
            DEBUG_LOG("GECERSIZ CONFIG SYNTAX !");
        }
            
    }

    read_file.close();
}

void config_parser::writeConfig(){
    //mapin son halini write eder
    //tum mapi gezip tek tek write edecegiz
    std::string key;
    std::fstream write_file(*configPath,std::ios::out);
    
    for(const auto &mapRecord : configContent){
        switch(mapRecord.first){
            case CONFIG_SETTINGS_SERVER_IP: key = "SERVER_IP"; break;
            case CONFIG_SETTINGS_SERVER_PORT: key = "SERVER_PORT"; break;
            case CONFIG_SETTINGS_RCON_SERVER_PORT: key = "RCON_SERVER_PORT"; break;
            case CONFIG_SETTINGS_RCON_PASSWORD: key = "RCON_PASSWORD"; break;
        }

        write_file << key << "=" << mapRecord.second << std::endl;
    }

    write_file.close();
}

void config_parser::updateConfig(CONFIG_SETTINGS settings , const std::string &newValue){
    this->configContent[settings] = newValue;
}
