#ifndef __LOGIN_FRAME_HPP__
#define __LOGIN_FRAME_HPP__

#include "window.hpp"
#include "rcon.hpp"
#include <string>

class login_frame : public pencere_frame{
private:
    std::string oyuncuAdi;
    std::string oyuncuParola;
    std::string hamachiHostAdresi;
    rconClient *client;
    
    //SLOTLAR//
    void slot_validater(wxTextCtrl *txtcVerisi,std::string rconPass); //buradaki ip adresi hamachi uzerinden cekilecektir
    
public:
    login_frame(int pGenislik , int pYukseklik , const char *pAd);
    ~login_frame();
};


#endif 