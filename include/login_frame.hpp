#ifndef __LOGIN_FRAME_HPP__
#define __LOGIN_FRAME_HPP__

#include "window.hpp"
#include "rcon.hpp"
#include "main_frame.hpp"
#include "configParser.hpp"

#include <string>

class login_frame : public pencere_frame{
private:
    remoteControl *client;
    main_frame *main_frame_window;
    
    //SLOTLAR//
    void slot_exit(wxCloseEvent &e);
    
    void slot_rconAuthValidate(wxCommandEvent &e,const std::string &hostIP,uint32_t rconPort , 
                               const std::string &rconPass , uint32_t serverPort);
    


public:
    login_frame(int pGenislik , int pYukseklik , const char *pAd);
    ~login_frame();
};


#endif 