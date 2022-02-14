#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

class Exception{
	
	friend ostream& operator<<(ostream& s,const Exception& e);

	protected:
		char* message;
	public:
		Exception(const char*);
		Exception(const Exception&);
		virtual int getCode()const = 0;

		~Exception();
};

#endif