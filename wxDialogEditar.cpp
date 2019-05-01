#include "wxDialogEditar.h"

wxDialogEditar::wxDialogEditar( vectorSaver<Persona> & agenda, int id ) 
			: wxDialog( nullptr, wxID_ANY, "Contacto" )
			, m_agenda( agenda )
			, m_id( id )
			, m_Sizer_Nombre( new wxBoxSizer( wxHORIZONTAL ) )
			, m_Nombre( new wxTextCtrl( this, wxID_ANY, m_agenda[m_id].getNombre() ) )
			, m_Sizer_Telefono( new wxBoxSizer( wxHORIZONTAL ) )
			, m_Telefono( new wxTextCtrl( this, wxID_ANY, m_agenda[m_id].getTelefono() ) )
			, m_Sizer_Mail( new wxBoxSizer( wxHORIZONTAL ) )
			, m_Mail( new wxTextCtrl( this, wxID_ANY, m_agenda[m_id].getMail() ) )
			, m_Save( new wxButton( this, wxID_ANY, wxT("Aceptar"), wxDefaultPosition, wxDefaultSize, 0 ) )
			, m_Cancel( new wxButton( this, wxID_ANY, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0  ) )
{
	m_staticText4 = new wxStaticText( this, wxID_ANY, "Nombre" );
	
	m_Sizer_Nombre->AddSpacer(5);
	m_Sizer_Nombre->Add( m_staticText4, wxSizerFlags().Center() );
	m_Sizer_Nombre->AddSpacer(5);
	m_Sizer_Nombre->Add( m_Nombre, wxSizerFlags(1) );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Telefono"), wxDefaultPosition, wxDefaultSize, 0 );
	
	m_Sizer_Telefono->AddSpacer(5);
	m_Sizer_Telefono->Add( m_staticText5, wxSizerFlags().Center() );
	m_Sizer_Telefono->AddSpacer(5);
	m_Sizer_Telefono->Add( m_Telefono, wxSizerFlags(1).Center() );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Mail"), wxDefaultPosition, wxDefaultSize, 0 );
	
	m_Sizer_Mail->AddSpacer(5);
	m_Sizer_Mail->Add( m_staticText6, wxSizerFlags().Center() );
	m_Sizer_Mail->AddSpacer(5);
	m_Sizer_Mail->Add( m_Mail, wxSizerFlags(1).Expand() );
	
	wxBoxSizer * gSizer2 = new wxBoxSizer( wxHORIZONTAL );
	gSizer2->Add( m_Save, wxSizerFlags() );
	gSizer2->Add( m_Cancel , wxSizerFlags() );
	
	wxBoxSizer * gSizer3 = new wxBoxSizer( wxVERTICAL );
	gSizer3->Add( m_Sizer_Nombre, wxSizerFlags().Expand() );
	gSizer3->Add( m_Sizer_Telefono, wxSizerFlags().Expand() );
	gSizer3->Add( m_Sizer_Mail, wxSizerFlags().Expand() );
	gSizer3->Add( gSizer2 , wxSizerFlags().Expand() );
	SetSizer( gSizer3 );
	Layout();
	
	m_Save->Bind( wxEVT_BUTTON, &wxDialogEditar::onSave, this );
	m_Cancel->Bind( wxEVT_BUTTON, &wxDialogEditar::onCancel, this );
}

bool 
wxDialogEditar :: anyMissingField()
{
	bool r = false;
	wxString name = m_Nombre->GetValue();
	if( name.IsEmpty() )
	{
		if( m_error1 == nullptr ){
			m_error1 = new wxStaticText( this, wxID_ANY, "*" );
			m_error1->SetForegroundColour( wxColour(255,0,0) );
			
			m_Sizer_Nombre->Add( m_error1, wxSizerFlags().Center() );
			Layout();
		}
		r = true;
	} else {
		if( m_error1 != nullptr ){
			m_error1->Hide();
			Layout();
		}
	}
	
	wxString phone = m_Telefono->GetValue();
	if( phone.IsEmpty() )
	{
		if( m_error2 == nullptr ){
			m_error2 = new wxStaticText( this, wxID_ANY, "*" );
			m_error2->SetForegroundColour( wxColour(255,0,0) );
			
			m_Sizer_Telefono->Add( m_error2, wxSizerFlags().Center() );
			Layout();
		}
		r = true;
	} else {
		if( m_error2 != nullptr ) { m_error2->Hide(); Layout(); r = false; }
	}
	
	wxString mail = m_Mail->GetValue();
	if( mail.IsEmpty() == false )
	{
		if( mail.Length() < 5 ){
			if( m_error3 == nullptr ){
				m_error3 = new wxStaticText( this, wxID_ANY, "*" );
				m_error3->SetForegroundColour( wxColour(255,0,0) );
				
				m_Sizer_Mail->Add( m_error3, wxSizerFlags().Center() );
				Layout();
			}
			r = true;
		}
		else if( mail.Length() >= 5 and mail.Find('@') == wxNOT_FOUND )
		{
			if( m_error3 == nullptr ){
				m_error3 = new wxStaticText( this, wxID_ANY, "*" );
				m_error3->SetForegroundColour( wxColour(255,0,0) );
				
				m_Sizer_Mail->Add( m_error3, wxSizerFlags().Center() );
				Layout();
			}
			r = true;
		} else {
			if( m_error3 != nullptr ) { m_error3->Hide(); Layout(); r = false; }
		}
	} else { 
		if( m_error3 != nullptr ) { m_error3->Hide(); Layout(); r = false; }
	}
	return r;
}

void wxDialogEditar :: onSave( wxCommandEvent & event )
{
	if( anyMissingField() ) return;
	
	m_agenda[m_id].setNombre( m_Nombre->GetValue().ToStdString() ); 
	m_agenda[m_id].setTelefono( m_Telefono->GetValue().ToStdString() );
	m_agenda[m_id].setMail( m_Mail->GetValue().ToStdString() );
	EndModal( wxID_SAVE );
}

void
wxDialogEditar :: onCancel( wxCommandEvent & event )
{
	Destroy();
}


