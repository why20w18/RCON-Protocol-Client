#include "../../include/window.hpp"

// direkt bagimsiz calisan pencere ust pencere adresi yoktur
pencere_frame::pencere_frame(int pencereGenislik, int pencereYukseklik,const char *pencereAdi)
:wxFrame(nullptr, wxID_ANY, pencereAdi, wxDefaultPosition, wxDefaultSize) {
  CenterOnScreen();

  if(DEFAULT_HOST_NO == 0)
    SetBackgroundColour(*wxWHITE);

  SetMinSize(wxSize(pencereGenislik - 100, pencereYukseklik - 200));
  SetMaxSize(wxSize(pencereGenislik + 200, pencereYukseklik + 200));

  this->pencereAdi = pencereAdi;
  this->pencereGenislik = pencereGenislik;
  this->pencereYukseklik = pencereYukseklik;

  this->pencereSizer = new wxBoxSizer(wxVERTICAL);
  SetSizer(this->pencereSizer);

  Bind(wxEVT_CLOSE_WINDOW, &pencere_frame::OnExit, this);
}

// alt pencere olustururken kullanilir
pencere_frame::pencere_frame(int pencereGenislik, int pencereYukseklik,const char *pencereAdi, pencere_frame *ustPencere)   
:wxFrame(ustPencere, wxID_ANY, pencereAdi, wxDefaultPosition,wxDefaultSize) {
  this->pencereAdi = pencereAdi;
  this->pencereGenislik = pencereGenislik;
  this->pencereYukseklik = pencereYukseklik;

  if(!DEFAULT_HOST_NO)
    SetBackgroundColour(*wxWHITE);
}

// destructor
pencere_frame::~pencere_frame() {}

// SLOTLAR//
void pencere_frame::OnExit(wxCloseEvent &e) { this->Destroy(); }

// METODLAR//
void pencere_frame::lockWindowSize(LOCK_WINDOW_PARAMS lockParams){
  switch(lockParams){
    case LWP_LOCKED:
      SetMinSize(wxSize(pencereGenislik,pencereYukseklik));
      SetMaxSize(wxSize(pencereGenislik,pencereYukseklik));
      break;

    case LWP_LOCK_MAX100:
      SetMinSize(wxSize(pencereGenislik,pencereYukseklik));
      SetMaxSize(wxSize(pencereGenislik+100,pencereYukseklik+100));
      break;

    case LWP_LOCK_MIN100:
      SetMinSize(wxSize(pencereGenislik-100,pencereYukseklik-100));
      SetMaxSize(wxSize(pencereGenislik,pencereYukseklik));
      break;

    case LWP_LOCK_MIN_MAX100:
      SetMinSize(wxSize(pencereGenislik-100,pencereYukseklik-100));
      SetMaxSize(wxSize(pencereGenislik+100,pencereYukseklik+100));
      break;
    default:
      std::cout << "LOCK WINDOW SIZE GECERSIZ ENUM SECENEGI\n";
  }
}


void pencere_frame::componentPositioner(wxWindow *object, COMP_POSITION pos,
                                        int margin) {
  switch (pos) {
  case UST:
    pencereSizer->Add(object, 0, wxALL | wxALIGN_TOP, margin);
    break;
  case ALT:
    pencereSizer->Add(object, 0, wxALL | wxALIGN_BOTTOM, margin);
    break;
  case SOL:
    pencereSizer->Add(object, 0, wxALL | wxALIGN_LEFT, margin);
    break;
  case SAG:
    pencereSizer->Add(object, 0, wxALL | wxALIGN_RIGHT, margin);
    break;
  case ORTA:
    pencereSizer->Add(object, 0, wxALL | wxALIGN_CENTER_VERTICAL, margin);
    break;
  case GENISLEYEN_SATIR:
    pencereSizer->Add(object, 0, wxALL | wxEXPAND, margin);
    break;
  case GENISLEYEN_SATIRSUTUN:
    pencereSizer->Add(object, 1, wxALL | wxEXPAND, margin);
    break;
  default:
    std::cout << "GECERSIZ COMPONENT POZISYONLANDIRICISI\n";
    break;
  }
}

pencere_frame *pencere_frame::setPencereGenislik(int pgenis) {
  this->SetSize(wxSize(pgenis, this->GetSize().GetHeight()));
  return this;
}

pencere_frame *pencere_frame::setPencereYukseklik(int pyuksek) {
  this->SetSize(wxSize(this->GetSize().GetWidth(), pyuksek));
  return this;
}

pencere_frame *pencere_frame::setPencereAd(const char *yeniPencereAdi) {
  SetTitle(wxString(yeniPencereAdi));
  this->pencereAdi = yeniPencereAdi;
  return this;
}

//cagirildigi yerde delete edilmelidir
DINAMIK_MEMORY int *pencere_frame::getPencereGenislikYukseklikNow() {
  int *genislikYukseklik = new int[2];
  genislikYukseklik[0] = this->GetSize().GetWidth();
  genislikYukseklik[1] = this->GetSize().GetHeight();
  return genislikYukseklik;
}

int pencere_frame::getPencereGenislikSetted() { return this->pencereGenislik; }

int pencere_frame::getPencereYukseklikSetted() {
  return this->pencereYukseklik;
}

const char *pencere_frame::getPencereAd() { return this->pencereAdi; }

// COMPONENT EKLEMEYI KOLAYLASTIRICI METODLAR//
//(1)
wxMenu *pencere_frame::addMenuSekme(const char *sekmeAdi, int sekmeMenuSayisi,
                                    const char **sekmeMenuAdlari,
                                    const char **sekmeKisayolTuslari,
                                    int *sekmeFonksiyonlari) {
  wxMenu *menuMenu = new wxMenu;

  for (int i = 0; i < sekmeMenuSayisi; i++) {
    menuMenu->Append(sekmeFonksiyonlari[i],
                     "&" + std::string(sekmeMenuAdlari[i]) + "\t" +
                         std::string(sekmeKisayolTuslari[i]));
  }

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(menuMenu, "&" + std::string(sekmeAdi));
  SetMenuBar(menuBar);

  return menuMenu;
}

//(2)
