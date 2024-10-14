#pragma once

class Logger
{
public:
	Logger();

	void Debug(std::string msg);
	void Info(std::string msg);
	void Warn(std::string msg);
	void Error(std::string msg);

#ifndef SFML_STATIC
	void printHistory();
#endif

private:
	HANDLE handle;

#ifndef SFML_STATIC
	std::vector<std::pair<int, std::string>> history;
#endif
};