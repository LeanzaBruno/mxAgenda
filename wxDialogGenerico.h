#ifndef WXDIALOGGENERICO_H
#define WXDIALOGGENERICO_H
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include "Agendador.hpp"

class wxDialogGenerico : public wxDialog {
private:
	wxBoxSizer * m_Sizer_Nombre;
	wxStaticText* m_staticText4;
	
	wxBoxSizer * m_Sizer_Telefono;
	wxStaticText* m_staticText5;
	
	wxBoxSizer * m_Sizer_Mail;
	wxStaticText* m_staticText6;
	
	wxBoxSizer * m_Sizer_buttons;
	wxButton * m_Cancel;
	
	wxStaticText * m_error1;
	wxStaticText * m_error2;
	wxStaticText * m_error3;
	
	void onCancel( wxCommandEvent & event );
protected:
	Agendador & m_agenda;
	wxTextCtrl* m_Nombre;
	wxTextCtrl* m_Telefono;
	wxTextCtrl* m_Mail;
	wxButton * m_Save;
	
	bool checkMissingWrongData();
	virtual void onSave( wxCommandEvent & event ) = 0;
public:
	wxDialogGenerico( wxWindow * parent, Agendador & agenda, const string & title );
	
	string GetNombre() const;
	string GetTelefono() const;
	string GetMail() const;
	
	
	
};

#endif

