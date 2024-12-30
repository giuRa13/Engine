#pragma once

#include <entt.hpp>
#include <Timestep.hpp>


namespace ENGINE
{

	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();
		void OnUpdate(Timestep ts);

		// TEMP
		entt::registry& Reg() { return m_Registry; }


	private:
		entt::registry m_Registry;

	};

}