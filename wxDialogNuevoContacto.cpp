#include "wxDialogNuevoContacto.h"


wxDialogNuevoContacto :: wxDialogNuevoContacto( wxWindow * parent, Agendador & agenda ) 
					: wxDialogGenerico( parent , agenda, "Crear nuevo contacto" )
{
	
}

void 
wxDialogNuevoContacto :: onSave( wxCommandEvent & event )
{
	if( checkMissingWrongData() ) return;
	
	m_agenda.insert( m_Nombre->GetValue().ToStdString(), m_Telefono->GetValue().ToStdString(), m_Mail->GetValue().ToStdString() );
	EndModal(wxID_SAVE);
}
