#pragma once

#include <Core.hpp>
#include <Log.hpp>
#include "../Scene.hpp"
#include "../Entity.hpp"


namespace ENGINE 
{

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);
		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);


	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

		Ref<Scene> m_SceneContext;
		Entity m_SelectionContext;

	};

}