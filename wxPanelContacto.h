#ifndef WXPANELCONTACTO_H
#define WXPANELCONTACTO_H
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include "Agendador.hpp"

class wxPanelContacto : public wxPanel {
public:
	wxPanelContacto( wxWindow * parent,  Agendador & agenda, function<void (void)>& func );
	void fillPanel(unsigned int id );
private:
	Agendador & m_Agenda;
	unsigned int m_Id;
	function<void (void)> & m_refreshGrid;
	wxStaticText * m_stNombre;
	wxTextCtrl * m_tNombre;
	wxStaticText * m_stTelefono;
	wxTextCtrl * m_tTelefono;
	wxStaticText * m_stMail;
	wxTextCtrl * m_tMail;
	
	wxButton * m_bCancelar;
	wxButton * m_bGuardar;
	wxButton * m_bBorrar;
	
	void onText( wxCommandEvent & event );
	void onGuardar( wxCommandEvent & event );
	void onCancelar( wxCommandEvent & event );
	void onBorrar( wxCommandEvent & event );
};

#endif

