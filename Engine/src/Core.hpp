#pragma once

#include <memory>


#define BIT(x) (1 << x)

namespace ENGINE 
{

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}