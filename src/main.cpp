#include <wx/wx.h>
#include "../include/main_frame.hpp"

class MyApp : public wxApp
{
public:
    bool OnInit() override{
        main_frame *frame = new main_frame(400,400,"C319-RCON");
        frame->Show();
        return true;
    }
};
wxIMPLEMENT_APP(MyApp);
