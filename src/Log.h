//----------------------------------------------------
// © 2016-2020 Francesco Balzani - thecocce
// 
// License: MIT
// Site: https://github.com/thecocce/steamwrapper
//----------------------------------------------------

#include <fstream>

using namespace std;

void LogToFile(string str);

class Log {
  public:
    Log(string filename);
    ~Log();
    void Write(string logline);
  private:
	  string logfilename;
};