#pragma once

#include <memory>


#define BIT(x) (1 << x)

#define ENGINE_BIND_EVENT_FUNC(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ENGINE 
{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}