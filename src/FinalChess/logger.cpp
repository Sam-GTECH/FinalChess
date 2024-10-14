#include "pch.h"
#ifdef LOG

#define INFO_COLOR (0 << 4 | 3)
#define WARN_COLOR (0 << 4 | 6)
#define ERROR_COLOR (0 << 4 | 12)
#define DEFAULT_COLOR (0 << 4 | 15)

Logger::Logger()
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Logger::Debug(std::string msg)
{
	std::string header = "[DEBUG] ";
	std::pair<int, std::string> data(DEFAULT_COLOR, header + msg);
#ifndef SFML_STATIC
	history.push_back(data);
#else
	SetConsoleTextAttribute(handle, data.first);
	cout << data.second << endl;
	SetConsoleTextAttribute(handle, DEFAULT_COLOR);
#endif
}

void Logger::Info(std::string msg)
{
	std::string header = "[INFO] ";
	std::pair<int, std::string> data(INFO_COLOR, header+msg);
#ifndef SFML_STATIC
	history.push_back(data);
#else
	SetConsoleTextAttribute(handle, data.first);
	cout << data.second << endl;
	SetConsoleTextAttribute(handle, DEFAULT_COLOR);
#endif
}

void Logger::Warn(std::string msg)
{
	std::string header = "[WARN] ";
	std::pair<int, std::string> data(WARN_COLOR, header + msg);
#ifndef SFML_STATIC
	history.push_back(data);
#else
	SetConsoleTextAttribute(handle, data.first);
	cout << data.second << endl;
	SetConsoleTextAttribute(handle, DEFAULT_COLOR);
#endif
}

void Logger::Error(std::string msg)
{
	std::string header = "[ERROR] ";
	std::pair<int, std::string> data(ERROR_COLOR, header + msg);
#ifndef SFML_STATIC
	history.push_back(data);
#else
	SetConsoleTextAttribute(handle, data.first);
	cout << data.second << endl;
	SetConsoleTextAttribute(handle, DEFAULT_COLOR);
#endif
}

#ifndef SFML_STATIC
void Logger::printHistory()
{
	cout << endl << endl;
	cout << "Log History:" << endl;

    int count = history.size() < 7 ? history.size() : 7;

    for (size_t i = 0; i < 7 - count; i++)
    {
        cout << endl;
    }

    for (size_t i = 0; i < count; i++)
    {
        std::pair<int, std::string> data = history[history.size() - 1 - i];
        SetConsoleTextAttribute(handle, data.first);
        cout << data.second << endl;
    }
	SetConsoleTextAttribute(handle, DEFAULT_COLOR);
}
#endif
#endif