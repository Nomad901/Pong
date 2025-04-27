#include "Loger.h"

Loger::Loger(const std::string&& message, const std::string& path, int line)
{
	std::lock_guard<std::mutex> lg(mtx);
	
	auto time = std::chrono::system_clock::now();
	auto nowTime = std::chrono::system_clock::to_time_t(time);

	std::tm vTm;
	localtime_s(&vTm, &nowTime);

	std::ostringstream timeStamp;
	timeStamp << std::put_time(&vTm, "%Y-%m-%d %H:%M:%S");
	
	std::cerr << "[ERROR][" << timeStamp.str() << ']';
	if (!path.empty()) {
		std::cerr << '['<<path;
		if (line > 0)
			std::cerr << ": " << line;
		std::cerr << ']';
	}
	std::cout << '\n';
}
