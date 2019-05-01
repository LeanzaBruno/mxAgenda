#include "Application.h"
#include "wxVentana.h"
#include <wx/settings.h>

IMPLEMENT_APP(mxApplication)

bool mxApplication::OnInit() {
	wxVentana * ventana = new wxVentana;
	ventana->SetSize( wxSystemSettings::GetMetric ( wxSYS_SCREEN_X )*0.7, wxSystemSettings::GetMetric ( wxSYS_SCREEN_Y )*0.7  );
	ventana->Show();
	ventana->Center();
	return true;
}


