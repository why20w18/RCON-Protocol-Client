#include "../../include/login_frame.hpp"
#include <functional> 

login_frame::login_frame(int pGenislik , int pYukseklik , const char *pAd)
:pencere_frame(pGenislik,pYukseklik,pAd)
{
    DEBUG_LOG("--->LOGIN_FRAME_INITALIZE\n");
    this->client = nullptr;
    this->main_frame_window = nullptr;

    this->lockWindowSize(LWP_LOCK_MAX100);

    wxTextCtrl *txtc_serverHostIP = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_SERVER_HOST_IP,"25.18.57.15");
    wxTextCtrl *txtc_serverPort = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_SERVER_HOST_PORT,"25565");
    
    wxTextCtrl *txtc_serverRconPort = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_SERVER_RCON_PORT,"25575");
    wxTextCtrl *txtc_serverRconPassword = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_SERVER_RCON_PASSWORD,"rcon_pass",
    wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
    
    componentPositioner(txtc_serverHostIP,GENISLEYEN_SATIR);
    componentPositioner(txtc_serverPort,GENISLEYEN_SATIR);
    componentPositioner(txtc_serverRconPort,GENISLEYEN_SATIR);
    componentPositioner(txtc_serverRconPassword,GENISLEYEN_SATIR);

    wxButton *btn_girisGonder = new wxButton(this,BUTTONSF_LOGIN_BILGILERI_GONDER,"Giris");
    componentPositioner(btn_girisGonder,GENISLEYEN_SATIRSUTUN);
    


    //SLOT BAGLAMA//
    btn_girisGonder->Bind(wxEVT_BUTTON,[this,txtc_serverHostIP,txtc_serverPort,
                                        txtc_serverRconPort,txtc_serverRconPassword](wxCommandEvent &e){

        uint32_t serverPort = 0;
        uint32_t rconPort = 0;
        txtc_serverPort->GetValue().ToUInt(&serverPort);
        txtc_serverRconPort->GetValue().ToUInt(&rconPort);

        this->slot_rconAuthValidate(e,
            txtc_serverHostIP->GetValue().ToStdString(),
            rconPort,
            txtc_serverRconPassword->GetValue().ToStdString(), 
            serverPort
        );
    });

}

login_frame::~login_frame(){

}

//SLOTLAR//
void login_frame::slot_exit(wxCloseEvent &e){
    if(main_frame_window != nullptr)
        delete main_frame_window;

    this->Destroy();
}



void login_frame::slot_rconAuthValidate(wxCommandEvent &e,const std::string &hostIP,uint32_t rconPort , 
                                        const std::string &rconPass , uint32_t hostPort){
  
    client = new remoteControl(hostIP,hostPort,rconPass,rconPort);

    if(client->isRconAuthSuccess()){
        //yeni pencere gecis
        
        //client->rconServerInfo();

        config_parser *config = new config_parser("settings.cfg");
        config->updateConfig(CONFIG_SETTINGS_SERVER_IP,hostIP);
        config->updateConfig(CONFIG_SETTINGS_SERVER_PORT,std::to_string(hostPort));
        config->updateConfig(CONFIG_SETTINGS_RCON_PASSWORD,rconPass);
        config->updateConfig(CONFIG_SETTINGS_RCON_SERVER_PORT,std::to_string(rconPort));
        config->writeConfig();
        

        main_frame_window = new main_frame(600,450,MAIN_FRAME_NAME,client,this);
        main_frame_window->Show(true);
        
    }
    else{
        this->warnMSG("BU ADRES VE PORTTA BIR SERVER BULUNAMADI !","BAGLANTI HATASI");
        delete client;
    }
    
}

