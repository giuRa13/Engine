#pragma once

#include "Core.hpp"
#include "Events/KeyCode.hpp"
#include "Events/MouseCode.hpp"

namespace ENGINE {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
