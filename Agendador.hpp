#ifndef AGENDADOR_H
#define AGENDADOR_H
#include <vector>
#include "Persona.h"
#include "vectorSaver.hpp"
#include <algorithm>
using namespace std;

class Agendador : public vectorSaver<Persona>
{
public:
	inline Agendador(){ }
	inline Agendador( string file ) : vectorSaver<Persona>( file ) { }
	inline void insert( const string& nombre, const string& telefono, const string& mail )
	{
		assert( nombre.length() <= 20 );
		assert( telefono.length() <= 13 );
		assert( mail.length() <= 40 ); 
		const Persona p( nombre, telefono, mail );
		auto it = upper_bound( begin(), end(), p );
		vectorSaver<Persona>::insert( it, p );
	}
	
	inline void insert( const Persona & p )
	{
		insert( p.getNombre(), p.getTelefono(), p.getMail() );
	}
	
	inline Agendador& operator=( const Agendador & agenda )
	{
		this->clear();
		for( auto it = agenda.begin() ; it != agenda.end() ; ++it )
			this->push_back( *it );
		return *this;
	}
	
//	inline bool buscarPorNombre( const string &nombre )
//	{
//		for( auto it = begin() ; it != end() ; ++it )
//			if( it->getNombre().find( nombre ) != string::npos )
//				return &(*it);
//		return nullptr;
//	}	
//	
//	inline Persona * buscarPorTelefono( const string & tel )
//	{
//		for( auto it = begin() ; it != end() ; ++it )
//			if( it->getTelefono().find( tel ) != string::npos )
//				return &(*it);
//		return nullptr;
//	}
//	
//	inline Persona * buscarPorMail( const string & mail )
//	{
//		for( auto it = begin() ; it != end() ; ++it )
//			if( it->getMail().find( mail ) != string::npos )
//				return &(*it);
//		return nullptr;
//	}
};

#endif

