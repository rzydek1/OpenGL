#pragma once

#include "pch.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
private:
	static std::shared_ptr<spdlog::logger> s_ClientLogger;
};

#define LOG_TRACE(...)	      Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)	      Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)	      Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)	      Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)	      Log::GetClientLogger()->fatal(__VA_ARGS__)