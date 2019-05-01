#ifndef __SAVER__
#define __SAVER__
#include <vector>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <typeinfo>
using namespace std;

template<typename T>
class vectorSaver : public vector<T>{
private:
	const string _M_Archivo;
public:
	vectorSaver();
	vectorSaver( string filename );
	~vectorSaver();
};

template<typename T>
vectorSaver< T > :: vectorSaver()
			: _M_Archivo("")
{
	vector<T>::clear();
}

//Constructor = lector
template<typename T>
vectorSaver< T > :: vectorSaver( string archivo ) 
				  : _M_Archivo( archivo )
{
	assert( this->_M_Archivo != "" );
	ifstream file;
	file.open( this->_M_Archivo , ios::binary );
	
	T obj;
	while( file.read( reinterpret_cast<char*>(&obj) , sizeof(T)))
		vector<T>::push_back(obj);
}

//Destructor = cargador
template<typename T>
vectorSaver< T > :: ~vectorSaver()
{
	if( this->_M_Archivo == "" ) return;
	ofstream file;
	file.open( this->_M_Archivo , ios::trunc | ios::binary );
	assert(file.is_open());
	
	typename vector<T>::iterator itr = vector<T>::begin(), end = vector<T>::end();
	while( itr != end )
	{
		T obj( *itr );
		assert(file.write( reinterpret_cast<char*>( &obj ) ,sizeof(obj)));
		++itr;
	}
}
#endif
