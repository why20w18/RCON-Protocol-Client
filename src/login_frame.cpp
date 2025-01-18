#include "../include/login_frame.hpp"
#include <functional> 

login_frame::login_frame(int pGenislik , int pYukseklik , const char *pAd)
:pencere_frame(pGenislik,pYukseklik,pAd)
{
    std::cout << "--->LOGIN_FRAME_INITALIZE\n";
    this->hamachiHostAdresi = "25.38.35.241";
    this->client = nullptr;

    wxTextCtrl *txtc_kullaniciAdi = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_KULLANICI_ADI,"Oyuncu Ad");
    wxTextCtrl *txtc_kullaniciParola = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_KULLANICI_ADI,""
    ,wxDefaultPosition,wxDefaultSize,wxTE_PASSWORD);
    wxTextCtrl *txtc_hamachiHostAdresi = new wxTextCtrl(this,TEXTCTRLSF_LOGIN_HAMACHI_HOST,hamachiHostAdresi.c_str());
    

    componentPositioner(txtc_kullaniciAdi,GENISLEYEN_SATIR);
    componentPositioner(txtc_kullaniciParola,GENISLEYEN_SATIR);
    componentPositioner(txtc_hamachiHostAdresi,GENISLEYEN_SATIR);

    wxButton *btn_girisGonder = new wxButton(this,BUTTONSF_LOGIN_BILGILERI_GONDER,"Giris");
    componentPositioner(btn_girisGonder,GENISLEYEN_SATIRSUTUN);

    
    //SLOT BAGLAMA//
Bind(wxEVT_BUTTON, 
     std::bind(&login_frame::slot_validater, this,txtc_hamachiHostAdresi, "rcon_pass"),
     BUTTONSF_LOGIN_BILGILERI_GONDER);
}

login_frame::~login_frame(){
    
}


void login_frame::slot_validater(wxTextCtrl *txtcVerisi,std::string rconPass){
    this->hamachiHostAdresi = txtcVerisi->GetValue().ToStdString();
    std::cout << "MEVCUT HAMACHI HOST : " << hamachiHostAdresi << "\n";
    boost::asio::io_context ioserv;
    client = new rconClient(ioserv,this->hamachiHostAdresi,25575);
    
    if(client->rconConnect()){
        if(client->rconValidate(rconPass)){
            wxMessageBox("BAGLANTI BASARILIDIR : RCON PAROLASI DOGRUDUR !");
        }
        else 
        wxMessageBox("BAGLANTI BASARILIDIR : RCON PAROLASI HATALIDIR !");
    }
    else 
        wxMessageBox("BAGLANTI BASARISIZDIR : ADRES YANLIS OLABILIR !");

    delete client;
}
