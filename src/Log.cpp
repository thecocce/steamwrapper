//----------------------------------------------------
// © 2016-2020 Francesco Balzani - thecocce
// 
// License: MIT
// Site: https://github.com/thecocce/steamwrapper
//----------------------------------------------------

#include "Log.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

Log::Log(string filename) {
	#ifdef _DEBUG
		logfilename = filename;
	#endif
}

inline string getCurrentDateTime(string s) {
	#ifdef _DEBUG
		time_t now = time(0);
		struct tm  tstruct;
		char  buf[80];
		tstruct = *localtime(&now);
		if (s == "now")
			strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
		else if (s == "date")
			strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
		return string(buf);
	#endif
};

void Log::Write(string logline){
	#ifdef _DEBUG
		string now = getCurrentDateTime("now");
		ofstream ofs(logfilename.c_str(), std::ios_base::out | std::ios_base::app);
		ofs << now << '\t' << logline << '\n';
		ofs.close();
	#endif
}

Log::~Log(){
	#ifdef _DEBUG
		//do nothing
	#endif
}