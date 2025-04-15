#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>
#include <fstream>

const  std::string   LOG_FILE_PATH = "logs.txt"; // Log file

extern std::string   logs;                 // Logs
extern std::ofstream log_file_stream;      // Log file stream


/* Types of logs:
 * - INFO:  Just harmless information (eg., "Starting...").
 * - WARN:  Warnings, such as when an error may occur, but warning messages
 *          themselves are not errors. Example: "GPU drivers are out of date".
 * - ERROR: Not critical (fatal) errors. This means that the program will
 *          continue to work despite an error.
 * - FATAL: Critical (fatal) errors (eg., "Missing abc.dll").
 */
enum LogType { INFO, WARN, ERROR, FATAL }; // Log types

void log(LogType type, std::string text);  // Adds new log
bool openLogFile();                        // Opens log file
void closeLogFile();                       // Closes log file

#endif // LOGGING_HPP
