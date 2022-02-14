#ifndef TEMPSEXCEPTION_H
#define TEMPSEXCEPTION_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Exception.h"
using namespace std;

class TempsException : public Exception{

	private:
		int code;
	public:
		static const int HEURE_INVALIDE;
		static const int MINUTE_INVALIDE;
		static const int DEPASSEMENT;
		static const int FORMAT_INVALIDE;

		void setCode(int);
		int getCode()const;

		TempsException(const char* m,int);
		TempsException(const TempsException& e);
		const char* getMessage()const;
		



};

#endif