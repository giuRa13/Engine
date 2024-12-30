#pragma once

#include "Core.hpp"
#include "Events/KeyCode.hpp"
#include "Events/MouseCode.hpp"
#include <glm/glm.hpp>

namespace ENGINE {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
