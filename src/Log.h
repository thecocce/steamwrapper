#include <fstream>

void LogToFile(char* str);

using namespace std;

class Log {
  public:
    Log(char* filename);
    ~Log();
    void Write(char* logline);
  private:
    ofstream m_stream;
};