#pragma once
#include <iostream>
#include <chrono>
#include <sstream>
#include <string>
#include <mutex>

static std::mutex mtx;

struct Loger
{
	Loger(const std::string&& message, 
		  const std::string& path,
		  int line = 0);
};

