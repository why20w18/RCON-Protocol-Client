#include "../include/main_frame.hpp"

main_frame::main_frame(int pGenislik , int pYukseklik , const char *pAdi)
: pencere_frame(pGenislik,pYukseklik,pAdi)
{
    
    std::cout << "main_frame" << std::endl;

    const char *sekmeAdlari[] = {"Login","Sign-Up"};
    const char *sekmeKisayol[] = {"CTRL+L","CTRL+S"};
    
    const char **ptr1 = sekmeAdlari;
    const char **ptr2 = sekmeKisayol;

    int sekmeFuncs[] = {MENUSF_TANIMSIZ_BIR,MENUSF_TANIMSIZ_IKI};
    this->addMenuSekme("C319",2,ptr1,ptr2,sekmeFuncs);

    wxButton *btn_testButonu1 = new wxButton(this,BUTTONSF_TANIMSIZ_BIR,"TEST_BUTTON_1");
    wxButton *btn_testButonu2 = new wxButton(this,BUTTONSF_TANIMSIZ_IKI,"TEST_BUTTON_2");

    componentPositioner(btn_testButonu1,GENISLEYEN_SATIR);
    componentPositioner(btn_testButonu2,GENISLEYEN_SATIRSUTUN);

    wxTextCtrl *txtc_kullaniciAdi = new wxTextCtrl(this,TEXTCTRLSF_TANIMSIZ_BIR,"why20w18");
    componentPositioner(txtc_kullaniciAdi,GENISLEYEN_SATIR);


    //SLOT BAGLANTI//
    Bind(wxEVT_BUTTON,&main_frame::slot_testButton1,this,BUTTONSF_TANIMSIZ_BIR);
    Bind(wxEVT_BUTTON,&main_frame::slot_testButton2,this,BUTTONSF_TANIMSIZ_IKI);
}

void main_frame::slot_testButton1(wxCommandEvent &event){
    std::cout << "SLOT_TEST_BUTTON_1\n";
    std::cout << "PAD = " << this->getPencereAd() << "\n";
}


DINAMIK_MEMORY void main_frame::slot_testButton2(wxCommandEvent &event){
    std::cout << "SLOT_TEST_BUTTON_2\n";
    int *pgy = getPencereGenislikYukseklikNow();
    std::cout << "genislik = " << pgy[0] << " -- " << "yukseklik = " << pgy[1] << "\n";
    delete pgy;
}