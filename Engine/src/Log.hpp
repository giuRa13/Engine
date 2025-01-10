#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

namespace ENGINE
{

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core log macros
#define ENGINE_CORE_TRACE(...)    ::ENGINE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)     ::ENGINE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)     ::ENGINE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_DEBUG(...)     ::ENGINE::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)    ::ENGINE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_CORE_FATAL(...)    ::ENGINE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define ENGINE_APP_TRACE(...)	      ::ENGINE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_APP_INFO(...)	      ::ENGINE::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_APP_WARN(...)	      ::ENGINE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_APP_DEBUG(...)         ::ENGINE::Log::GetClientLogger()->debug(__VA_ARGS__)
#define ENGINE_APP_ERROR(...)	      ::ENGINE::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENGINE_APP_FATAL(...)	      ::ENGINE::Log::GetClientLogger()->critical(__VA_ARGS__)

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}