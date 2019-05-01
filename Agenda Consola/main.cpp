#include<iostream>
#include "../Agendador.hpp"
#include <cctype>
#include <algorithm>
using namespace std;

int main (int argc, char *argv[]) {
		string up = "ASDNNNSDndnf SMDNFS";
		string copy;
		for( auto & p : up ) copy.push_back( tolower(p) );
		cout << copy;
	
	
	return 0;
}

