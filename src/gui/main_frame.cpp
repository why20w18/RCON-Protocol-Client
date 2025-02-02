#include "../../include/main_frame.hpp"

main_frame::main_frame(int pGenislik , int pYukseklik , const char *pAdi,remoteControl *connectServerData,pencere_frame *login_frame)
: pencere_frame(pGenislik,pYukseklik,pAdi)
{
    login_frame->Destroy();
    std::cout << "main_frame" << std::endl;
    this->lockWindowSize(LWP_LOCK_MAX100);
    this->connectServerData = connectServerData;

    const char *sekmeAdlari[] = {"Github","Issues/Problem Report"};
    const char *sekmeKisayol[] = {"CTRL+G","CTRL+R"};
    
    const char **ptr1 = sekmeAdlari;
    const char **ptr2 = sekmeKisayol;

    int sekmeFuncs[] = {MENUSF_TANIMSIZ_BIR,MENUSF_TANIMSIZ_IKI};
    this->addMenuSekme("Help/Yardim",2,ptr1,ptr2,sekmeFuncs);

    wxButton *btn_runCommand = new wxButton(this,BUTTONSF_TANIMSIZ_BIR,"Send Command");
    wxButton *btn_testButonu2 = new wxButton(this,BUTTONSF_TANIMSIZ_IKI,"TEST_BUTTON_2");

    componentPositioner(btn_runCommand,GENISLEYEN_SATIR);
    componentPositioner(btn_testButonu2,GENISLEYEN_SATIRSUTUN);

    wxTextCtrl *txtc_komutKonsol = new wxTextCtrl(this,TEXTCTRLSF_TANIMSIZ_BIR,
    wxT("Komutlari burada yazarak calistirabilirsiniz"),wxDefaultPosition,wxSize(750,250),wxTE_MULTILINE | wxTE_PROCESS_ENTER);
    
    componentPositioner(txtc_komutKonsol,GENISLEYEN_SATIR);


    //SLOT BAGLANTI//
    Bind(wxEVT_BUTTON,&main_frame::slot_testButton1,this,BUTTONSF_TANIMSIZ_BIR);
    Bind(wxEVT_BUTTON,&main_frame::slot_testButton2,this,BUTTONSF_TANIMSIZ_IKI);
    Bind(wxEVT_CLOSE_WINDOW, &main_frame::slot_exit, this);

}

void main_frame::slot_exit(wxCloseEvent &e){
    this->Destroy();
}


main_frame::~main_frame(){
    delete this->connectServerData;
    cout << "main_frame destructor" << endl;
}

void main_frame::slot_testButton1(wxCommandEvent &event){
    std::cout << "SLOT_TEST_BUTTON_1\n";
    std::cout << "PAD = " << this->getPencereAd() << "\n";
    std::string response = connectServerData->runCommand("say helloRCON");
    cout << "SERVERDAN GELEN YANIT : " << response << endl;
}


DINAMIK_MEMORY void main_frame::slot_testButton2(wxCommandEvent &event){
    std::cout << "SLOT_TEST_BUTTON_2\n";
    int *pgy = getPencereGenislikYukseklikNow();
    std::cout << "genislik = " << pgy[0] << " -- " << "yukseklik = " << pgy[1] << "\n";
    delete pgy;
}