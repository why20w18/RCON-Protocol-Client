#include "../../include/main_frame.hpp"

main_frame::main_frame(int pGenislik , int pYukseklik , const char *pAdi,remoteControl *connectServerData,pencere_frame *login_frame)
: pencere_frame(pGenislik,pYukseklik,pAdi)
{
    login_frame->Destroy();
    DEBUG_LOG("main_frame");
    this->lockWindowSize(LWP_LOCK_MIN_MAX100);
    this->connectServerData = connectServerData;

    const char *sekmeAdlari[] = {"Github","Issues/Problem Report"};
    const char *sekmeKisayol[] = {"CTRL+G","CTRL+R"};
    
    const char **ptr1 = sekmeAdlari;
    const char **ptr2 = sekmeKisayol;

    int sekmeFuncs[] = {MENUSF_GITHUB,MENUSF_ISSUES_PROBLEM_REPORT};
    this->addMenuSekme("Help/Yardim",2,ptr1,ptr2,sekmeFuncs);

    wxTextCtrl *txtc_komutKonsol = new wxTextCtrl(this,TEXTCTRLSF_TANIMSIZ_BIR,
    "RUN COMMAND:\n",wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE | wxTE_PROCESS_ENTER);
     
    wxTextCtrl *txtc_responseREADONLY = new wxTextCtrl(this,TEXTCTRLSF_TANIMSIZ_BIR,wxT("SERVER RESPONSE:\n")
    ,wxDefaultPosition,wxDefaultSize,wxTE_READONLY | wxTE_MULTILINE);
    
    
    componentPositioner(txtc_responseREADONLY,GENISLEYEN_SATIRSUTUN);
    componentPositioner(txtc_komutKonsol,GENISLEYEN_SATIRSUTUN);


    //SLOT BAGLANTI//
    Bind(wxEVT_CLOSE_WINDOW, &main_frame::slot_exit, this);
 
    txtc_komutKonsol->Bind(wxEVT_TEXT_ENTER, 
        [this, txtc_responseREADONLY, txtc_komutKonsol](wxCommandEvent &e){
            std::string command = txtc_komutKonsol->GetValue().ToStdString();

            if(command.length() == 0)
                command = "BOS_KOMUT";

            if(command.at(0) == '#'){
                if(command == "#info"){
                        txtc_responseREADONLY->SetValue(this->connectServerData->rconServerInfoStr());
                        txtc_komutKonsol->Clear();
                }
                else
                    command == "BOS_KOMUT";

            }

            else if(command.at(0) != '#'){
                this->slot_sendCommand(e, command,txtc_responseREADONLY);
                txtc_komutKonsol->Clear();
            }
});

    Bind(wxEVT_MENU,&main_frame::slot_github,this,MENUSF_GITHUB);
    Bind(wxEVT_MENU,&main_frame::slot_issuesProblemReport,this,MENUSF_ISSUES_PROBLEM_REPORT);
}

main_frame::~main_frame(){
    delete this->connectServerData;
    DEBUG_LOG("main_frame destructor");
}



//SLOT DEFINES//
void main_frame::slot_exit(wxCloseEvent &e){
    this->Destroy();
}

void main_frame::slot_sendCommand(wxCommandEvent &e,const std::string &command,wxTextCtrl *readOnly){
    DEBUG_LOG("slot_sendCommand & command : " << command);
    std::string serverResponse = connectServerData->runCommand(command);
    readOnly->SetValue("Gonderilen Komut -> "+command+"\n"+"Gelen Yanit <- "+serverResponse);
}

void main_frame::slot_github(wxCommandEvent &e){
    this->warnMSG("https://github.com/why20w18/RCON-Protocol-Client adresinden projeye destekte bulunabilirsiniz","Github");
}

void main_frame::slot_issuesProblemReport(wxCommandEvent &e){
    this->warnMSG("https://github.com/why20w18/RCON-Protocol-Client/issues adresinden projedeki hatalari bildirebilirsiniz","Report");
}