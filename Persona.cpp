#include "Persona.h"
#include <cctype>
using namespace std;


Persona :: Persona(const string& nombre, const string& telefono, const string& mail )
{
	setNombre( nombre );
	setTelefono( telefono );
	setMail( mail );
}

Persona :: Persona( const Persona& p )
{
	strcpy( m_nombre, p.m_nombre );
	strcpy( m_telefono, p.m_telefono);
	strcpy( m_mail , p.m_mail );
}

string Persona :: getNombre() const { return string(m_nombre); }
string Persona :: getTelefono() const { return string( m_telefono ); }
string Persona :: getMail() const { return string( m_mail ); }

void Persona :: setNombre( const string & nombre  ) { strcpy( m_nombre, nombre.c_str() ); }
void Persona :: setTelefono( const string& telefono ) { strcpy( m_telefono, telefono.c_str() ); }
void Persona :: setMail( const string & mail ) { strcpy( m_mail, mail.c_str() ); }

bool
Persona :: operator<( const Persona & p ) const
{
	if( getNombre().compare( p.getNombre() ) < 0 ) return true;
	return false;
}

bool
Persona :: contieneNombre( const string & name ) const
{
	return to_lower(getNombre()).find( to_lower(name) ) != string::npos;
}

bool
Persona :: contieneTelefono( const string & phone ) const
{
	return getTelefono().find( phone ) != string::npos;
}

bool
Persona :: contieneMail( const string & mail ) const
{
	return to_lower(getMail()).find( to_lower(mail) ) != string::npos;
}

string
Persona :: to_lower( const string & s ) const
{
	string copy;
	for( auto & p : s ) copy.push_back( tolower(p) );
	return copy;
}
