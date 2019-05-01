#ifndef PERSONA_H
#define PERSONA_H
#include <cstring>
#include <string>
using namespace std;

class Persona {
public:
	Persona( const string& nombre = "", const string& telefono = "", const string& mail = "");
	Persona( const Persona& p );
	string getNombre() const;
	string getTelefono() const;
	string getMail() const;
	void setNombre( const string &);
	void setTelefono( const string &);
	void setMail( const string &);
	
	bool operator<( const Persona & p ) const;
	bool contieneNombre( const string & name ) const;
	bool contieneTelefono( const string & phone ) const;
	bool contieneMail( const string & mail ) const;
	string to_lower( const string & s ) const;
private:
	char m_nombre[20];
	char m_telefono[13];
	char m_mail[40];
};

#endif

