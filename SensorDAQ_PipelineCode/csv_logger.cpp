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

/* 

The #include <stdexcept> directive in C++ makes a family of standard exception classes available for use in a program. These classes are all derived, directly or indirectly, from the base class std::exception, which is defined in the separate 
<exception> header. 

The header defines two main categories of exceptions, both of which inherit from std::exception: 
std::logic_error: These exceptions report errors that theoretically could be detected by reading the code, often caused by programmer mistakes.

std::domain_error
std::invalid_argument
std::length_error
std::out_of_range

std::runtime_error: These exceptions report errors that depend on events beyond the program's control and cannot easily be foreseen at the time of coding.

std::overflow_error
std::range_error
std::underflow_error
*/
