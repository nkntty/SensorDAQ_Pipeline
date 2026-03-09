#include "csv_logger.h"
#include <stdexcept>
using namespace std;

// you put Name of class before :: unlike public: base class name
CSVLogger:: CSVLogger(const string& filename) : out_(filename, ios::trunc) {
    //you should open by TRUNCATE mode in CONSTRUCTOR 
    if (!out_.is_open()) throw runtime_error("Could not open " + filename);
    out_ << "time,raw,filtered\n";
}

void CSVLogger::log(double time, double raw, double filtered) {
    out_ << time << "," << raw << "," << filtered << "\n";
}

/* ios::truc:(truncate) When a file is opened with the ios::trunc flag, any existing content in the file is immediately discarded (deleted), and the file size is set to zero.  */
/*ios::app(append): the existing content of the file is retained    */
