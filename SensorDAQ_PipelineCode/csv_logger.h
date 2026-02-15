#pragma once
#include <fstream>
#include <string>
using namespace std;
class CSVLogger {
public:
    explicit CSVLogger(const string& filename);
    void log(double time, double raw, double filtered);

private:
    ofstream out_;
};

/* In C++, a .h (header) file is a text file that contains declarations of functions, classes, variables, and other entities. 
It acts as an interface, allowing these elements to be used across multiple source (.cpp) files without needing to copy the full imple
mentation into every file. */

