#ifndef __MAIN_FRAME_HPP__
#define __MAIN_FRAME_HPP__

#include "window.hpp"
#include "rcon.hpp"
#include "debug.hpp"


//bu pencere programin ana baslangic penceresidir burada olaylar yakalanir
class main_frame : public pencere_frame{
private:
    remoteControl *connectServerData;

    //SLOT FONKSIYONLARI//
    void slot_exit(wxCloseEvent &e);
    void slot_sendCommand(wxCommandEvent &e,const std::string &command,wxTextCtrl *readOnly);
    void slot_github(wxCommandEvent &e);
    void slot_issuesProblemReport(wxCommandEvent &e);


    void slot_testButton1(wxCommandEvent &event);
    void slot_testButton2(wxCommandEvent &event);

public:
    main_frame(int pGenislik , int pYukseklik , const char *pAdi,remoteControl *connectServerData,pencere_frame *login_frame);
    ~main_frame();



};


#endif 