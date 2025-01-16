#ifndef __MAIN_FRAME_HPP__
#define __MAIN_FRAME_HPP__

#include "window.hpp"

//bu pencere programin ana baslangic penceresidir burada olaylar yakalanir
class main_frame : public pencere_frame{
private:



    //SLOT FONKSIYONLARI//
    void slot_testButton1(wxCommandEvent &event);
    void slot_testButton2(wxCommandEvent &event);

public:
    main_frame(int pGenislik , int pYukseklik , const char *pAdi);



};


#endif 