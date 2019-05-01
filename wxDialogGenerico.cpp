#include "wxDialogGenerico.h"

wxDialogGenerico :: wxDialogGenerico( wxWindow * parent, Agendador & agenda, const string & title) 
			: wxDialog( parent, wxID_ANY, title )
			, m_agenda( agenda )
			, m_Sizer_Nombre( new wxBoxSizer( wxHORIZONTAL ) )
			, m_Nombre( new wxTextCtrl( this, wxID_ANY, "" ) )
			, m_staticText4( new wxStaticText( this, wxID_ANY, wxT("Nombre"), wxDefaultPosition, wxDefaultSize, 0 ) )
	
			, m_Sizer_Telefono( new wxBoxSizer( wxHORIZONTAL ) )
			, m_staticText5( new wxStaticText( this, wxID_ANY, wxT("Telefono"), wxDefaultPosition, wxDefaultSize, 0 ) )
			, m_Telefono( new wxTextCtrl( this, wxID_ANY, "" ) )
	
			, m_Sizer_Mail( new wxBoxSizer( wxHORIZONTAL ) )
			, m_staticText6 ( new wxStaticText( this, wxID_ANY, wxT("Mail"), wxDefaultPosition, wxDefaultSize, 0 ) )
			, m_Mail( new wxTextCtrl( this, wxID_ANY, "" ) )
	
			, m_Sizer_buttons( new wxBoxSizer( wxHORIZONTAL ) )
			, m_Save( new wxButton( this, wxID_ANY, "Guardar" ) )
			, m_Cancel( new wxButton( this, wxID_ANY, "Cancelar" ) )
	
			, m_error1( new wxStaticText( this, wxID_ANY, "*" ) ) 
			, m_error2( new wxStaticText( this, wxID_ANY, "*" ) ) 
			, m_error3( new wxStaticText( this, wxID_ANY, "*" ) ) 
{
	m_Nombre->SetMaxLength(20);
	m_Telefono->SetMaxLength(13);
	m_Mail->SetMaxLength(40);
	
	m_error1->Hide(); m_error1->SetForegroundColour( wxColour(255,0,0) );
	m_error2->Hide(); m_error2->SetForegroundColour( wxColour( 255,0,0) );
	m_error3->Hide(); m_error3->SetForegroundColour( wxColour( 255,0,0) );
	
	m_Sizer_Nombre->AddSpacer(5);
	m_Sizer_Nombre->Add( m_staticText4, wxSizerFlags().Center() );
	m_Sizer_Nombre->AddSpacer(5);
	m_Sizer_Nombre->Add( m_Nombre, wxSizerFlags(1) );
	m_Sizer_Nombre->Add( m_error1, wxSizerFlags().Center() );
	
	m_Sizer_Telefono->AddSpacer(5);
	m_Sizer_Telefono->Add( m_staticText5, wxSizerFlags().Center() );
	m_Sizer_Telefono->AddSpacer(5);
	m_Sizer_Telefono->Add( m_Telefono, wxSizerFlags(1).Center() );
	m_Sizer_Telefono->Add( m_error2, wxSizerFlags().Center() );
	
	m_Sizer_Mail->AddSpacer(5);
	m_Sizer_Mail->Add( m_staticText6, wxSizerFlags().Center() );
	m_Sizer_Mail->AddSpacer(5);
	m_Sizer_Mail->Add( m_Mail, wxSizerFlags(1).Expand() );
	m_Sizer_Mail->Add( m_error3, wxSizerFlags().Center() );

	m_Sizer_buttons->Add( m_Save , wxSizerFlags().Expand() );
	m_Sizer_buttons->Add( m_Cancel , wxSizerFlags().Expand() );
	
	wxBoxSizer * gSizer3 = new wxBoxSizer( wxVERTICAL );
	gSizer3->Add( m_Sizer_Nombre, wxSizerFlags().Expand() );
	gSizer3->Add( m_Sizer_Telefono, wxSizerFlags().Expand() );
	gSizer3->Add( m_Sizer_Mail, wxSizerFlags().Expand() );
	gSizer3->Add( m_Sizer_buttons , wxSizerFlags().Center() );
	SetSizer( gSizer3 );
	Layout();
	
	m_Save->Bind( wxEVT_BUTTON, &wxDialogGenerico::onSave, this );
	m_Cancel->Bind( wxEVT_BUTTON, &wxDialogGenerico::onCancel, this );
	
	m_Nombre->SetFocus();
}

string wxDialogGenerico :: GetNombre() const { return m_Nombre->GetStringSelection().ToStdString(); } 
string wxDialogGenerico :: GetTelefono() const { return m_Telefono->GetStringSelection().ToStdString(); }
string wxDialogGenerico :: GetMail() const { return m_Mail->GetStringSelection().ToStdString(); }

bool 
wxDialogGenerico:: checkMissingWrongData()
{
	bool r = false;
	if( m_Nombre->GetValue().IsEmpty() )
	{
		if( m_error1->IsShown() == false ) m_error1->Show(); 
		r = true;
	} else m_error1->Hide();
	
	if( m_Telefono->GetValue().IsEmpty() )
	{
		if( m_error2->IsShown() == false ) m_error2->Show();
		r = true;
	} else m_error2->Hide();
	
	const wxString & mail = m_Mail->GetValue();
	if( mail.IsEmpty() == false )
	{
		if( mail.Length() < 8 )
		{
			if( m_error3->IsShown() == false ) m_error3->Show();
			r = true;
		}
		else if( mail.Length() >= 8 and mail.Find('@') == wxNOT_FOUND )
		{
			if( m_error3->IsShown() == false ) m_error3->Show();
			r = true;
		} else m_error3->Hide();
	} else 
	{ 
		if( m_error3->IsShown() ) m_error3->Hide();
	}
	Layout();
	return r;
}


void wxDialogGenerico :: onCancel( wxCommandEvent & event ){ EndModal(wxID_CANCEL); }
