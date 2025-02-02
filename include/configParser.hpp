#ifndef __CONFIG_PARSER_HPP__
#define __CONFIG_PARSER_HPP__

#include "funcEnums.hpp"
#include "debug.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>

class config_parser{
private:
    DINAMIK_MEMORY std::string *configPath;
    std::unordered_map<int,std::string> configContent;

    void readConfig();
    void setConfigSyntax(std::string &line);
    void addConfigContentMap(const std::string key,const std::string &value);

public:
    config_parser(const char *configPath);
    ~config_parser();

        
    void getCommentLine();
    int getRecordCount();

    //mape buradan erisecegiz
    void updateConfig(CONFIG_SETTINGS settings , const std::string &newValue);
    //updateConfig() metodundan sonra writeConfig() cagrilarak config dosyasina yeni veriler aktarilir
    void writeConfig();
     
};

#endif 