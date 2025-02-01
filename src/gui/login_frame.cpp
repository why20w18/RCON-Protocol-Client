#include "../../include/login_frame.hpp"
#include <functional> 

login_frame::login_frame(int pGenislik , int pYukseklik , const char *pAd)
:pencere_frame(pGenislik,pYukseklik,pAd)
{
    std::cout << "--->LOGIN_FRAME_INITALIZE\n";
    this->serverHostIP = "25.18.57.15";
    this->client = nullptr;

    this->lockWindowSize(LWP_LOCK_MAX100);

    wxTextCtrl *txtc_serverHostIP = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_SERVER_HOST_IP,"Server IP");
    wxTextCtrl *txtc_serverPort = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_SERVER_HOST_PORT,"Server PortNo");
    
    wxTextCtrl *txtc_serverRconPort = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_SERVER_RCON_PORT,"RCON PortNo");
    wxTextCtrl *txtc_serverRconPassword = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_SERVER_RCON_PASSWORD,"RCON Password");
    
    componentPositioner(txtc_serverHostIP,GENISLEYEN_SATIR);
    componentPositioner(txtc_serverPort,GENISLEYEN_SATIR);
    componentPositioner(txtc_serverRconPort,GENISLEYEN_SATIR);
    componentPositioner(txtc_serverRconPassword,GENISLEYEN_SATIR);

    wxButton *btn_girisGonder = new wxButton(this,BUTTONSF_LOGIN_BILGILERI_GONDER,"Giris");
    componentPositioner(btn_girisGonder,GENISLEYEN_SATIRSUTUN);

    
    //SLOT BAGLAMA//

}

login_frame::~login_frame(){
    
}


void login_frame::slot_validater(wxTextCtrl *txtcVerisi,std::string rconPass){
    this->serverHostIP = txtcVerisi->GetValue().ToStdString();
    std::cout << "MEVCUT HAMACHI HOST : " << serverHostIP << "\n";
    boost::asio::io_context ioserv;
    client = new rconClient(ioserv,this->serverHostIP,25575);
    
    if(client->rconConnect()){
        if(client->rconValidate(rconPass)){
            wxMessageBox("BAGLANTI BASARILIDIR : RCON PAROLASI DOGRUDUR !");
            {
            config_parser cfgParse("settings.cfg");
            cfgParse.updateConfig(CONFIG_SETTINGS_RCON_PASSWORD,rconPass);
            cfgParse.writeConfig();
            }
        }
        else 
        wxMessageBox("BAGLANTI BASARILIDIR : RCON PAROLASI HATALIDIR !");
    }
    else 
        wxMessageBox("BAGLANTI BASARISIZDIR : ADRES YANLIS OLABILIR !");

    delete client;
}
