#pragma once

#include "PlatformDetection.hpp"
#include "Log.hpp"
#include "Assert.hpp"
#include <memory>


#ifdef DEBUG
	#if defined(ENGINE_PLATFORM_WINDOWS)
	#define ENGINE_DEBUGBREAK() __debugbreak()
	#elif defined(ENGINE_PLATFORM_LINUX)
	#include <signal.h>
	#define ENGINE_DEBUGBREAK() raise(SIGTRAP)
	#else
	#error "Platform doesn't support debugbreak yet!"
	#endif
	#define ENGINE_ENABLE_ASSERTS
#else
	#define ENGINE_DEBUGBREAK()
#endif

#define ENGINE_EXPAND_MACRO(x) x
#define ENGINE_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define ENGINE_BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ENGINE 
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}