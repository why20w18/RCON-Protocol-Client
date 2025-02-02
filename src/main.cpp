#include <wx/wx.h>
#include "../include/login_frame.hpp"

class MyApp : public wxApp
{
public:
    bool OnInit() override{
        login_frame *frame = new login_frame(400,600,LOGIN_FRAME_NAME);
        frame->Show();
        return true;
    }
};
wxIMPLEMENT_APP(MyApp);
