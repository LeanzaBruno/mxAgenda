#include "wxPanelContacto.h"
#include <wx/button.h>
#include <wx/sizer.h>
#include "wxVentana.h"
#include <wx/msgdlg.h>
#include <functional>
using namespace std;

wxPanelContacto::wxPanelContacto( wxWindow * parent, Agendador & agenda, function<void (void)>& func ) 
	:wxPanel( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN )
	, m_Agenda( agenda )
	, m_refreshGrid( func )
	, m_stNombre( new wxStaticText( this, wxID_ANY, "Nombre" ) )
	, m_tNombre( new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE  ) )
	, m_stTelefono( new wxStaticText( this, wxID_ANY, "Telefono" ) )
	, m_tTelefono( new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE ) )
	, m_stMail( new wxStaticText( this, wxID_ANY, "Mail" ) )
	, m_tMail( new wxTextCtrl( this, wxID_ANY, "" , wxDefaultPosition, wxDefaultSize, wxTE_CENTRE ) )
	, m_bCancelar(new wxButton( this, wxID_ANY, "Cancelar" ) )
	, m_bGuardar(new wxButton( this, wxID_ANY, "Guardar" ) )
	, m_bBorrar( new wxButton( this, wxID_ANY, "Borrar contacto" ) )
{
	m_tNombre->Enable(false);
	m_tTelefono->Enable(false);
	m_tMail->Enable(false);
	m_bBorrar->Enable(false);
	m_bGuardar->Hide();
	m_bCancelar->Hide();
	
	m_tNombre->SetMaxLength(20);
	m_tTelefono->SetMaxLength(13);
	m_tMail->SetMaxLength(40);

	wxBoxSizer * sizer1 = new wxBoxSizer( wxVERTICAL );
	sizer1->AddSpacer(5);
	sizer1->Add( m_stNombre , wxSizerFlags().Left() );
	sizer1->AddSpacer(5);
	sizer1->Add( m_tNombre, wxSizerFlags().Expand() );
	sizer1->AddSpacer(5);
	sizer1->Add( m_stTelefono, wxSizerFlags().Left() );
	sizer1->AddSpacer(5);
	sizer1->Add( m_tTelefono, wxSizerFlags().Expand() );
	sizer1->AddSpacer(5);
	sizer1->Add( m_stMail, wxSizerFlags().Left() );
	sizer1->AddSpacer(5);
	sizer1->Add( m_tMail, wxSizerFlags().Expand() );
	sizer1->AddSpacer(5);
	sizer1->Add( m_bCancelar, wxSizerFlags().Expand() );
	sizer1->AddSpacer(5);
	sizer1->Add( m_bGuardar, wxSizerFlags().Expand() );
	sizer1->AddSpacer(5);
	sizer1->Add( m_bBorrar, wxSizerFlags().Expand() );
	SetSizer(sizer1);
	Layout();
	
	m_bCancelar->Bind( wxEVT_BUTTON, &wxPanelContacto::onCancelar, this );
	m_bGuardar->Bind( wxEVT_BUTTON, &wxPanelContacto::onGuardar, this );
	m_bBorrar->Bind( wxEVT_BUTTON, &wxPanelContacto::onBorrar, this );
}

void
wxPanelContacto :: onText( wxCommandEvent & event )
{
	m_bCancelar->Show();
	m_bGuardar->Show();
	Layout();
}

void
wxPanelContacto :: onCancelar( wxCommandEvent & event )
{
	m_tNombre->SetValue( m_Agenda[m_Id].getNombre() );
	m_tTelefono->SetValue( m_Agenda[m_Id].getTelefono() );
	m_tMail->SetValue( m_Agenda[m_Id].getMail() );
	
	m_bCancelar->Hide();
	m_bGuardar->Hide();
	Layout();
}

void
wxPanelContacto :: fillPanel( unsigned int id )
{
	m_tNombre->Unbind( wxEVT_TEXT, &wxPanelContacto::onText, this );
	m_tTelefono->Unbind( wxEVT_TEXT, &wxPanelContacto::onText, this );
	m_tMail->Unbind( wxEVT_TEXT, &wxPanelContacto::onText, this );
	
	m_Id = m_Id;
	m_tNombre->SetValue( m_Agenda[m_Id].getNombre() );
	m_tNombre->Enable();
	m_tTelefono->SetValue( m_Agenda[m_Id].getTelefono() );
	m_tTelefono->Enable();
	m_tMail->SetValue( m_Agenda[m_Id].getMail() );
	m_tMail->Enable();
	m_bBorrar->Enable();
	
	m_tNombre->Bind( wxEVT_TEXT, &wxPanelContacto::onText, this );
	m_tTelefono->Bind( wxEVT_TEXT, &wxPanelContacto::onText, this );
	m_tMail->Bind( wxEVT_TEXT, &wxPanelContacto::onText, this );
}

void
wxPanelContacto :: onGuardar( wxCommandEvent & event )
{
	m_Agenda[m_Id].setNombre( m_tNombre->GetValue().ToStdString() );
	m_Agenda[m_Id].setTelefono( m_tTelefono->GetValue().ToStdString() );
	m_Agenda[m_Id].setMail( m_tMail->GetValue().ToStdString() );
}

void
wxPanelContacto :: onBorrar( wxCommandEvent & event )
{
	wxMessageDialog msg( this, "Seguro quieres borrar el contacto?", "Borrar contacto", wxYES | wxNO | wxNO_DEFAULT );
	if( msg.ShowModal() == wxID_YES )
	{
		m_Agenda.erase( m_Agenda.begin() + m_Id );
		m_refreshGrid();
	}
}

