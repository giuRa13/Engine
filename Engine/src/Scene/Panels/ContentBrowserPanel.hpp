#pragma once

#include "../../Renderer/Texture.hpp"
#include <filesystem>


namespace ENGINE 
{

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();
		void OnImGuiRender();

	private:
		std::filesystem::path m_CurrentDirectory;
		Ref<Texture2D> m_DirectoryIcon;
		Ref<Texture2D> m_FileIcon;
	};

}