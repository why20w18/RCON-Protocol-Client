#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__

#include <wx/wx.h>
#include <wx/sizer.h>
#include "funcEnums.hpp"

#ifdef __linux__
    #define DEFAULT_HOST_NO 1
    #define DEFAULT_HOST_NAME "__linux__"
#elif WIN32
    #define DEFAULT_HOST_NO 0
    #define DEFAULT_HOST_NAME "WIN32"
#endif 

class pencere_frame : public wxFrame{
private:
    const char *pencereAdi;
    int pencereGenislik;
    int pencereYukseklik;
    
    pencere_frame *ustPencere;
    wxBoxSizer *pencereSizer; 

    //SLOTLAR//
    void OnExit(wxCloseEvent &e);


public:
    //constructorlar
    pencere_frame(int pencereGenislik , int pencereYukseklik , const char *pencereAdi); //anapencere
    pencere_frame(int pencereGenislik , int pencereYukseklik , const char *pencereAdi,pencere_frame *ustPencere); //alt pencereler
   ~pencere_frame();



protected:


    int* getPencereGenislikYukseklikNow();
    int getPencereGenislikSetted();
    int getPencereYukseklikSetted();
    const char* getPencereAd();

    pencere_frame* setPencereGenislik(int pgenis);
    pencere_frame* setPencereYukseklik(int pyuksek);
    pencere_frame* setPencereAd(const char *yeniPencereAdi);    

    void componentPositioner(wxWindow *object,COMP_POSITION pos,int margin = 20);
    void lockWindowSize(LOCK_WINDOW_PARAMS lockParams);
    
    wxMenu* addMenuSekme(const char *sekmeAdi,int sekmeBarSayisi,const char **sekmeBarAdlari,
                          const char **sekmeKisayolTuslari,int *sekmeFonksiyonlari);    
    

};



#endif 