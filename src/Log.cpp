//----------------------------------------------------
// @ 2016 Francesco Balzani - thecocce
// 
// License: MIT
// Site: https://github.com/thecocce/steamwrapper
//----------------------------------------------------

#include "Log.h"

#include <fstream>
#include <iostream>
#include <ctime>

Log::Log(char* filename) {
	#ifdef DEBUG
		m_stream.open(filename);
	#endif
}

void Log::Write(char* logline){
	#ifdef DEBUG
	time_t now = time(0);
	struct tm* tm = localtime(&now);   
	m_stream << tm->tm_year+1900 << '/' << tm->tm_mon << '/' << tm->tm_mday
         << ' ' << tm->tm_hour << ':' << tm->tm_min << ':' << tm->tm_sec << ": ";
    m_stream << logline << "\n";
	#endif
}

Log::~Log(){
	#ifdef DEBUG
		m_stream.close();
	#endif
}