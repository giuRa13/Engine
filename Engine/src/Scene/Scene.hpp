#pragma once

#include <entt.hpp>
#include <Timestep.hpp>


namespace ENGINE
{
	class Entity;


	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());

		void OnUpdate(Timestep ts);
		void OnViewportResize(uint32_t width, uint32_t height);

		// TEMP
		//entt::registry& Reg() { return m_Registry; }


	private:
		entt::registry m_Registry;
		friend class Entity;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	};

}