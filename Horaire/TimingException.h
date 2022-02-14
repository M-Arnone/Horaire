#ifndef TIMINGEXCEPTION_H
#define TIMINGEXCEPTION_H
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Exception.h"
using namespace std;

class TimingException : public Exception{

	private:
		int code;
	public:
		static const int JOUR_INVALIDE;
		static const int AUCUN_TIMING;
		static const int PROF_INDISPO;
		static const int GROUPE_INDISPO;
		static const int LOCAL_INDISPO;

		void setCode(int);

		const char* getMessage()const;
		int getCode()const;

		TimingException(const char* m,int erreur);
		TimingException(const TimingException&);


};

#endif