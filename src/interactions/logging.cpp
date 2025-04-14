#include "interactions/logging.hpp"
#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>

std::string logs;               // Logs
std::ofstream log_file_stream;  // Log file stream

// Adds new log
void log(LogType type, std::string text)
{
    // Get current time as string
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm* localtime = std::localtime(&t);
    std::ostringstream time_stream;
    time_stream << std::setfill('0')
        << std::setw(2) << localtime->tm_hour << ":"
        << std::setw(2) << localtime->tm_min << ":"
        << std::setw(2) << localtime->tm_sec << "."
        << std::setw(3)
        << std::chrono::duration_cast<std::chrono::milliseconds>
            (now.time_since_epoch()).count() % 1000;
    std::string time_str = time_stream.str();

    // Get the log type as string
    std::string type_str;
    switch(type)
    {
        case INFO:  type_str = "INFO";  break;
        case WARN:  type_str = "WARN";  break;
        case ERROR: type_str = "ERROR"; break;
        case FATAL: type_str = "FATAL"; break;
    }

    // Final log
    std::string log = time_str + " - " + type_str + " - " + text + "\n";

    logs += log;                // Display the log in the developer console
    std::cout << log;           // Display the log in terminal
    if (log_file_stream)
        log_file_stream << log; // Append the log to the log file
}

// Opens log file
bool openLogFile()
{
    log_file_stream.open(LOG_FILE_PATH, std::ios::app);
    if (!log_file_stream)
    {
        log(ERROR, "Unable to open the log file.");
        log(WARN, "LOGS WILL NOT BE SAVED!!!");
        return false;
    }
    return true;
}

// Closes log file
void closeLogFile()
{
    if (log_file_stream)
        log_file_stream.close();
}
