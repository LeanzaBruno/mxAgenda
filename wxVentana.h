#ifndef WXVENTANA_H
#define WXVENTANA_H
#include "wxDialogNuevoContacto.h"
#include <wx/frame.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/textctrl.h>
#include <wx/choicdlg.h>
#include <wx/msgdlg.h>
#include <wx/valnum.h>
#include <wx/valtext.h>
#include "wxDialogEditar.h"
#include "Agendador.hpp"
#include "wxPanelContacto.h"


class wxVentana : public wxFrame {
public:
	wxVentana();
	~wxVentana();
private:
	enum
	{
		NAME = 0,
		PHONE,
		MAIL
	};
	Agendador m_Agenda;
	vector<int> m_indices;
	
	wxMenuBar * m_Menu;
	wxMenu * m_Main;
	wxChoice * m_Criterio;
	wxTextCtrl * m_Buscador;
	wxButton * m_Nuevo;
	wxGrid * m_Grid;
	
	wxStaticText * m_stNombre;
	wxTextCtrl * m_tNombre;
	wxStaticText * m_stTelefono;
	wxTextCtrl * m_tTelefono;
	wxStaticText * m_stMail;
	wxTextCtrl * m_tMail;
	wxButton * m_bCancelar;
	wxButton * m_bGuardar;
	wxButton * m_bQuitar_busq;
	wxButton * m_bBorrar;
	
	void refreshContacts();
	void loadEventos();
	void loadGrilla();
	void loadMenu();
	void cleanPanel();
	void loadDefaults();
	void appendFilteredRow( int id );
	bool searchingInProgress() const;
	bool panelIsEmpty() const;
	void enablePanel( bool enable = true );
	void fillPanel( int row );
	void resizeCols();
	
	void onQuit( wxCommandEvent& event );
	void onCrearContacto( wxCommandEvent& event );
	void onSearch( wxCommandEvent& event );
	void onLimpiarAgenda( wxCommandEvent & event );
	void onSelectCell( wxGridEvent & event );
	void onQuitarBusqueda( wxCommandEvent & event );
	void onBorrar( wxCommandEvent & event );
	void onText( wxCommandEvent & event );
	void onCancelar( wxCommandEvent & event );
	void onGuardar( wxCommandEvent & event );
	void onChoice( wxCommandEvent & event );
	void onCellClick( wxGridEvent & event );
};

#endif

// vector de indices
// hacer una busq individual en la agenda...dejar el for/while afuera
// for mayor a menor
