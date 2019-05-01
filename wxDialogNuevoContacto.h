#ifndef WXDIALOGNUEVOCONTACTO_H
#define WXDIALOGNUEVOCONTACTO_H
#include <wx/textctrl.h>
#include "Agendador.hpp"
#include "wxDialogGenerico.h"
using namespace std;

class wxDialogNuevoContacto : public wxDialogGenerico {
public:
	wxDialogNuevoContacto( wxWindow * parent,  Agendador & agenda );
private:
	void onSave( wxCommandEvent & event ) override;
};

#endif

