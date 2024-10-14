#pragma once

class Logger
{
public:
	Logger();

	void Debug(const char* msg);
	void Info(const char* msg);
	void Warn(const char* msg);
	void Error(const char* msg);

	void printHistory();

private:
	HANDLE handle;

	std::vector<std::pair<int, std::string>> history;
};