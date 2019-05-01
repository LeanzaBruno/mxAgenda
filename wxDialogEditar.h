#ifndef WXDIALOGEDITAR_H
#define WXDIALOGEDITAR_H
#include <wx/dialog.h>
#include "vectorSaver.hpp"
#include "Persona.h"
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>

class wxDialogEditar : public wxDialog 
{
public:
	wxDialogEditar( vectorSaver<Persona> & agenda, int id );
private:
	vectorSaver<Persona> & m_agenda;
	int m_id;
	
	wxBoxSizer * m_Sizer_Nombre;
	wxStaticText* m_staticText4;
	wxTextCtrl* m_Nombre;
	wxBoxSizer * m_Sizer_Telefono;
	wxStaticText* m_staticText5;
	wxTextCtrl* m_Telefono;
	wxBoxSizer * m_Sizer_Mail;
	wxStaticText* m_staticText6;
	wxTextCtrl* m_Mail;
	wxButton * m_Save;
	wxButton * m_Cancel;
	
	wxStaticText * m_error1 = nullptr;
	wxStaticText * m_error2 = nullptr;
	wxStaticText * m_error3 = nullptr;
	
	void onSave( wxCommandEvent & event );
	void onCancel( wxCommandEvent & event );
	bool anyMissingField();
};

#endif

