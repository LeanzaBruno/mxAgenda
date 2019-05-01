#include "wxVentana.h"
#include "Agendador.hpp"
wxVentana::wxVentana() 
		: wxFrame( nullptr, wxID_ANY, "wxAgendador" )
		, m_Agenda( ".contacts" )
		, m_Menu( new wxMenuBar )
		, m_Main( new wxMenu )
		, m_Buscador( new wxTextCtrl( this, wxID_ANY, "",wxDefaultPosition, wxDefaultSize, wxTE_CENTRE ) )
		, m_Nuevo( new wxButton( this, wxID_ANY, "Nuevo contacto" ) )
		, m_Grid( new wxGrid( this, wxID_ANY ) )
		, m_stNombre( new wxStaticText( this, wxID_ANY, "Nombre" ) )
		, m_tNombre( new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE  ) )
		, m_stTelefono( new wxStaticText( this, wxID_ANY, "Telefono" ) )
		, m_tTelefono( new wxTextCtrl( this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE ) )
		, m_stMail( new wxStaticText( this, wxID_ANY, "Mail" ) )
		, m_tMail( new wxTextCtrl( this, wxID_ANY, "" , wxDefaultPosition, wxDefaultSize, wxTE_CENTRE ) )
		, m_bCancelar(new wxButton( this, wxID_ANY, "Cancelar" ) )
		, m_bGuardar(new wxButton( this, wxID_ANY, "Guardar" ) )
		, m_bQuitar_busq( new wxButton( this , wxID_ANY, "Quitar busqueda" ) )
		, m_bBorrar( new wxButton( this, wxID_ANY, "Borrar contacto(s)" ) )
{
	loadDefaults();
	
	//Structure
	wxBoxSizer* sBuscador = new wxBoxSizer( wxHORIZONTAL );
	sBuscador->AddSpacer(5);
	sBuscador->Add( m_Criterio , wxSizerFlags().Expand() );
	sBuscador->AddSpacer(5);
	sBuscador->Add( m_Buscador, wxSizerFlags(1).Expand() );
	sBuscador->AddSpacer(5);
	sBuscador->Add( m_bQuitar_busq, wxSizerFlags().Center() );

	wxBoxSizer * sRight = new wxBoxSizer( wxVERTICAL );
	sRight->AddSpacer(5);
	sRight->Add( m_stNombre , wxSizerFlags().Left() );
	sRight->AddSpacer(5);
	sRight->Add( m_tNombre, wxSizerFlags().Expand() );
	sRight->AddSpacer(5);
	sRight->Add( m_stTelefono, wxSizerFlags().Left() );
	sRight->AddSpacer(5);
	sRight->Add( m_tTelefono, wxSizerFlags().Expand() );
	sRight->AddSpacer(5);
	sRight->Add( m_stMail, wxSizerFlags().Left() );
	sRight->AddSpacer(5);
	sRight->Add( m_tMail, wxSizerFlags().Expand() );
	sRight->AddSpacer(5);
	sRight->Add( m_bCancelar, wxSizerFlags().Expand() );
	sRight->AddSpacer(5);
	sRight->Add( m_bGuardar, wxSizerFlags().Expand() );
	sRight->AddSpacer(5);
	sRight->Add( m_bBorrar, wxSizerFlags().Expand() );
	sRight->AddSpacer(5);
	sRight->Add( m_Nuevo , wxSizerFlags().Expand() );
	
	
	wxBoxSizer * sizer3 = new wxBoxSizer( wxHORIZONTAL );
	sizer3->AddSpacer(5);
	sizer3->Add( m_Grid, wxSizerFlags(2).Expand() );
	sizer3->AddSpacer(5);
	sizer3->Add( sRight, wxSizerFlags(1).Expand() );
	sizer3->AddSpacer(5);
	
	wxBoxSizer* sPadre = new wxBoxSizer( wxVERTICAL );
	sPadre->AddSpacer(5);
	sPadre->Add( sBuscador, wxSizerFlags().Expand() );
	sPadre->AddSpacer(10);
	sPadre->Add( sizer3 , wxSizerFlags(1).Expand() );
	sPadre->AddSpacer(5);
	SetSizer( sPadre );
	Layout();
	m_Grid->SetSize( this->GetSize() - sRight->GetSize() );
}

void
wxVentana :: onCellClick( wxGridEvent & event )
{
	fillPanel( event.GetRow() );
}


void
wxVentana :: fillPanel( int row )
{
	m_Grid->SelectRow( row, false);
	cleanPanel();
	if( m_Grid->GetSelectedRows().GetCount() > 1 )
	{
		cleanPanel();
		return;
	}
	
	if( searchingInProgress() ){
		const int & selected = m_indices[ row ];
		m_tNombre->SetValue( m_Agenda[selected].getNombre() );
		m_tTelefono->SetValue( m_Agenda[selected].getTelefono() );
		m_tMail->SetValue( m_Agenda[selected].getMail() );
	}
	else
	{
		m_tNombre->SetValue( m_Agenda[ row ].getNombre() );
		m_tTelefono->SetValue( m_Agenda[row].getTelefono() );
		m_tMail->SetValue( m_Agenda[row].getMail() );
	}
	enablePanel();	
}

void
wxVentana :: onSelectCell( wxGridEvent & event )
{
	fillPanel( event.GetRow() );
}

void
wxVentana :: onSearch( wxCommandEvent& event )
{
	const string & value = m_Buscador->GetValue().ToStdString();
	if( m_Agenda.size() < 2 ) return;	
	if( m_Grid->GetNumberRows() > 0 ) m_Grid->DeleteRows(0, m_Grid->GetNumberRows() );
	m_indices.clear();
	const int & choice = m_Criterio->GetSelection();
	for( int p = 0 ; p < m_Agenda.size() ; ++p )
	{
		switch( choice )
		{
		case NAME:
		{
			if( m_Agenda[p].contieneNombre( value ) ) appendFilteredRow(p);
		}
		break;
		
		case PHONE:
		{
			if( m_Agenda[p].contieneTelefono( value ) ) appendFilteredRow(p);
		}break;
		case MAIL:{
			if( m_Agenda[p].contieneMail( value ) ) appendFilteredRow(p);
		}
		}
	}
	if( m_indices.size() == 1 ) fillPanel(0);
	else if( panelIsEmpty() == false ) cleanPanel();
}

void
wxVentana :: onGuardar( wxCommandEvent & event )
{
	if( searchingInProgress() )
	{
		const int row = m_indices[m_Grid->GetSelectedRows().Last()];
		m_Agenda[ row ].setNombre( m_tNombre->GetValue().ToStdString() );
		m_Agenda[ row ].setTelefono( m_tTelefono->GetValue().ToStdString() );
		m_Agenda[ row ].setMail( m_tMail->GetValue().ToStdString() );
	}else{
		m_Agenda[ m_Grid->GetSelectedRows().Last() ].setNombre( m_tNombre->GetValue().ToStdString() );
		m_Agenda[ m_Grid->GetSelectedRows().Last() ].setTelefono( m_tTelefono->GetValue().ToStdString() );
		m_Agenda[ m_Grid->GetSelectedRows().Last() ].setMail( m_tMail->GetValue().ToStdString() );
	}
	
	m_bCancelar->Enable(false);
	m_bGuardar->Enable(false);
	Layout();
	refreshContacts();
}

void
wxVentana :: onBorrar( wxCommandEvent & event )
{
	wxArrayInt rows = m_Grid->GetSelectedRows();
	if( rows.GetCount() == 0 ) return;
	wxMessageDialog msg( this, "Borrar los contactos seleccionados?", "Borrar contacto", wxYES | wxNO | wxNO_DEFAULT );
	if( msg.ShowModal() == wxID_NO ) return;
	
//	vector<int> selected_rows;
//	for( size_t i = 0 ; i < rows.GetCount() ; ++i )
//		selected_rows.push_back( rows.Item(i) );
//	sort( selected_rows.begin(), selected_rows.end(), [](int a, int b){ return a > b; } );
//	
//	for( auto & row : selected_rows )
//	{
//		if( searchingInProgress() )
//			m_Agenda.erase( m_Agenda.begin() +  m_indices[row] );
//		else 
//			m_Agenda.erase( m_Agenda.begin() + row );
//	}
	
	rows.Sort( [](int* a, int* b) -> int { return *a-*b; } );
	for( size_t i = 0 ; i < rows.GetCount() ; ++i )
	{
		if( searchingInProgress() )
			m_Agenda.erase( m_Agenda.begin() +  m_indices[ rows.Item(i) ] );
		else 
			m_Agenda.erase( m_Agenda.begin() + rows.Item(i) );
	}
	
	cleanPanel();
	enablePanel(false);
	refreshContacts();
}

void
wxVentana :: cleanPanel()
{
	m_tNombre->SetValue("");
	m_tTelefono->SetValue("");
	m_tMail->SetValue("");
	m_bCancelar->Enable(false);
	m_bGuardar->Enable(false);
	enablePanel(false);
}

void
wxVentana :: onText( wxCommandEvent & event )
{
	m_bCancelar->Enable();
	m_bGuardar->Enable();
	Layout();
}

void
wxVentana :: onCancelar( wxCommandEvent & event )
{
	if( searchingInProgress() )
	{
		const int row = m_indices[m_Grid->GetSelectedRows().Last()];
		m_tNombre->SetValue( m_Agenda[row].getNombre() );
		m_tTelefono->SetValue( m_Agenda[row].getTelefono() );
		m_tMail->SetValue( m_Agenda[row].getMail() );
	}else{
		m_tNombre->SetValue( m_Agenda[m_Grid->GetSelectedRows().Last()].getNombre() );
		m_tTelefono->SetValue( m_Agenda[m_Grid->GetSelectedRows().Last()].getTelefono() );
		m_tMail->SetValue( m_Agenda[m_Grid->GetSelectedRows().Last()].getMail() );
	}
	
	m_bCancelar->Enable(false);
	m_bGuardar->Enable(false);
	Layout();
}

void wxVentana :: onCrearContacto( wxCommandEvent& event )
{
	wxDialogNuevoContacto dialog( this, m_Agenda );
	if( dialog.ShowModal() == wxID_SAVE ) refreshContacts();
}

void
wxVentana :: appendFilteredRow( int id )
{
	m_Grid->Unbind( wxEVT_GRID_SELECT_CELL, &wxVentana::onSelectCell, this );
	
	m_Grid->AppendRows();
	const int & ultima_celda = m_Grid->GetNumberRows()-1;
	
	m_Grid->SetCellValue(ultima_celda, 0, m_Agenda[id].getNombre() );
	m_Grid->SetCellAlignment( ultima_celda, 0, wxALIGN_CENTRE , wxALIGN_CENTRE  );
	
	m_Grid->SetCellValue(ultima_celda, 1, m_Agenda[id].getTelefono() );
	m_Grid->SetCellAlignment( ultima_celda, 1, wxALIGN_CENTRE , wxALIGN_CENTRE  );
	
	if( m_Agenda[id].getMail().empty() )
		m_Grid->SetCellValue(ultima_celda, 2, "-" );
	else
		m_Grid->SetCellValue(ultima_celda, 2, m_Agenda[id].getMail() );
	m_Grid->SetCellAlignment( ultima_celda, 2, wxALIGN_CENTRE , wxALIGN_CENTRE  );
	
	m_Grid->Bind( wxEVT_GRID_SELECT_CELL, &wxVentana::onSelectCell, this );
	
	m_indices.push_back(id);	
}

void
wxVentana :: onChoice( wxCommandEvent & event )
{
	switch( m_Criterio->GetSelection() ){
	case NAME:{ m_Buscador->SetMaxLength(20); m_Buscador->SetValidator( wxTextValidator() ); }break;
	case PHONE:{ m_Buscador->SetMaxLength(13); m_Buscador->SetValidator( wxIntegerValidator<unsigned int>() ); }break;
	case MAIL:{ m_Buscador->SetMaxLength(40); m_Buscador->SetValidator( wxTextValidator() ); }
	}
	m_Buscador->SetFocus();
}

void
wxVentana :: onQuitarBusqueda( wxCommandEvent & event )
{
	if( m_Buscador->GetValue().IsEmpty() ) return;
	m_Buscador->SetValue("");
	m_indices.clear();
	refreshContacts();
	cleanPanel();
}

void
wxVentana :: onLimpiarAgenda( wxCommandEvent & event )
{
	wxMessageDialog dialog(this, "Borrar todos los contactos?", "Borrar agenda", wxYES | wxNO | wxNO_DEFAULT );
	if( dialog.ShowModal() == wxID_YES )
	{
		m_Agenda.clear();
		m_Grid->DeleteRows( 0, m_Grid->GetNumberRows());
		Layout();
	}
}

void
wxVentana :: enablePanel( bool enable )
{
	if( enable )
	{
		m_tNombre->Bind( wxEVT_TEXT, &wxVentana::onText, this );
		m_tTelefono->Bind( wxEVT_TEXT, &wxVentana::onText, this );
		m_tMail->Bind( wxEVT_TEXT, &wxVentana::onText, this );
	}
	else
	{
		m_tNombre->Unbind( wxEVT_TEXT, &wxVentana::onText, this );
		m_tTelefono->Unbind( wxEVT_TEXT, &wxVentana::onText, this );
		m_tMail->Unbind( wxEVT_TEXT, &wxVentana::onText, this );
	}
	m_tTelefono->Enable(enable);
	m_tNombre->Enable(enable);
	m_tMail->Enable(enable);
}

void
	wxVentana :: loadDefaults()
{
	m_tNombre->SetMaxLength(20);
	m_tTelefono->SetMaxLength(13);
	m_tMail->SetMaxLength(40);
	
	wxString str[] = {"Nombre", "Telefono", "Mail"};
	m_Criterio = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 3, str );
	m_Criterio->SetSelection(0);
	loadEventos();
	loadMenu();
	loadGrilla();
	refreshContacts();
	cleanPanel();
	enablePanel(false);
}

void
	wxVentana :: loadEventos()
{
	m_Main->Bind( wxEVT_MENU , &wxVentana::onCrearContacto, this,  wxID_NEW);
	m_Main->Bind( wxEVT_MENU, &wxVentana::onLimpiarAgenda, this , wxID_CLEAR );
	m_Main->Bind( wxEVT_MENU, &wxVentana::onQuit, this, wxID_EXIT );
	m_Grid->Bind( wxEVT_GRID_SELECT_CELL, &wxVentana::onSelectCell, this );
	m_Nuevo->Bind( wxEVT_BUTTON, &wxVentana::onCrearContacto, this );
	m_bBorrar->Bind( wxEVT_BUTTON, &wxVentana::onBorrar, this );
	m_bCancelar->Bind( wxEVT_BUTTON, &wxVentana::onCancelar, this );
	m_bGuardar->Bind( wxEVT_BUTTON, &wxVentana::onGuardar , this );
	m_Buscador->Bind( wxEVT_TEXT, &wxVentana::onSearch, this );
	m_bQuitar_busq->Bind( wxEVT_BUTTON, &wxVentana::onQuitarBusqueda, this );
	m_Criterio->Bind( wxEVT_CHOICE, &wxVentana::onChoice, this );
	m_tNombre->Bind( wxEVT_TEXT, &wxVentana::onText, this );
	m_tTelefono->Bind( wxEVT_TEXT, &wxVentana::onText, this );
	m_tMail->Bind( wxEVT_TEXT, &wxVentana::onText, this );
}

wxVentana :: ~wxVentana() { }

void
wxVentana :: refreshContacts()
{
	while( m_Grid->GetNumberRows() < m_Agenda.size() )
		m_Grid->AppendRows();
	while( m_Grid->GetNumberRows() > m_Agenda.size() )
		m_Grid->DeleteRows();
	m_Grid->ClearGrid();
	
	m_Grid->Unbind( wxEVT_GRID_SELECT_CELL, &wxVentana::onSelectCell, this );
	for( unsigned int i = 0 ; i < m_Agenda.size() ; ++i )
	{
		m_Grid->SetCellValue(i, 0, m_Agenda[i].getNombre() );
		m_Grid->SetCellAlignment( i, 0, wxALIGN_CENTRE , wxALIGN_LEFT  );
		m_Grid->SetCellValue(i, 1, m_Agenda[i].getTelefono() );
		m_Grid->SetCellAlignment( i, 1, wxALIGN_CENTRE , wxALIGN_CENTRE  );
		if( m_Agenda[i].getMail().empty() ) m_Grid->SetCellValue(i, 2, "-" );
		else m_Grid->SetCellValue(i, 2, m_Agenda[i].getMail() );
		m_Grid->SetCellAlignment( i, 2, wxALIGN_CENTRE , wxALIGN_CENTRE  );
	}
	m_Grid->Bind( wxEVT_GRID_SELECT_CELL, &wxVentana::onSelectCell, this );
	m_Buscador->SetValue("");
	m_Grid->AutoSize();
	m_Grid->ClearSelection();
	m_Buscador->SetFocus();
}

void
wxVentana :: loadMenu()
{
	m_Main->Append( wxID_CLEAR, "Limpiar agenda" );
	m_Main->Append( wxID_EXIT, "Salir" );
	m_Menu->Append( m_Main, "Opciones" );
	SetMenuBar( m_Menu );
}

void
wxVentana :: loadGrilla()
{
	m_Grid->CreateGrid( m_Agenda.size() , 3 ); 
	m_Grid->SetColLabelValue(0, "Nombre" );
	m_Grid->SetColLabelValue(1, "Telefono" );
	m_Grid->SetColLabelValue(2, "Mail" );
	m_Grid->HideRowLabels();
	m_Grid->EnableEditing(false);
	m_Grid->SetSelectionMode(wxGrid::wxGridSelectRows);
}

void
wxVentana :: resizeCols()
{
	m_Grid->SetColSize(0, m_Grid->GetSize().x);
	m_Grid->SetColSize(1, m_Grid->GetSize().x/2);
	m_Grid->SetColSize(2, m_Grid->GetSize().x/3);
	m_Grid->SetMargins(0,0);
}

bool
wxVentana :: searchingInProgress() const
{
	return not m_Buscador->GetValue().IsEmpty();
}

bool
wxVentana :: panelIsEmpty() const
{
	return m_tNombre->IsEmpty() and m_tTelefono->IsEmpty();
}

void wxVentana :: onQuit( wxCommandEvent& event ) { Close(true); }
