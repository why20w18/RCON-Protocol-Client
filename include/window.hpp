#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <wx/wx.h>
#include <wx/sizer.h>
#include "funcEnums.hpp"

class pencere_frame : public wxFrame{
private:
    const char *pencereAdi;
    int pencereGenislik;
    int pencereYukseklik;

    //SLOTLAR//
    void OnExit(wxCloseEvent &e);


public:
    //constructorlar
    pencere_frame(int pencereGenislik , int pencereYukseklik , const char *pencereAdi); //anapencere
    pencere_frame(int pencereGenislik , int pencereYukseklik , const char *pencereAdi,pencere_frame *ustPencere); //alt pencereler
   ~pencere_frame();



protected:
    pencere_frame *ustPencere;
    wxBoxSizer *pencereSizer; 

    int* getPencereGenislikYukseklikNow();
    int getPencereGenislikSetted();
    int getPencereYukseklikSetted();
    const char* getPencereAd();

    wxMenu* setMenuSekme1(const char *sekmeAdi,int sekmeBarSayisi,const char **sekmeBarAdlari,
                          const char **sekmeKisayolTuslari,int *sekmeFonksiyonlari);    
    pencere_frame* setPencereGenislik(int pgenis);
    pencere_frame* setPencereYukseklik(int pyuksek);
    pencere_frame* setPencereAd(const char *yeniPencereAdi);    

    void componentPositioner(wxWindow *object,COMP_POSITION pos,int margin = 20);

};



#endif 