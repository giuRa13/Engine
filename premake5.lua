workspace "Engine"
    architecture "x64"
    startproject "Editor"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
	{
		"MultiProcessorCompile"
	}

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/Vendor/glfw/include"
IncludeDir["Glad"] = "Engine/Vendor/glad/include"
IncludeDir["ImGui"] = "Engine/Vendor/imgui"
IncludeDir["glm"] = "Engine/Vendor/glm"
IncludeDir["stb_image"] = "Engine/Vendor/stb_image"
IncludeDir["entt"] = "Engine/Vendor/entt/include"

include "Engine/Vendor/glfw"
include "Engine/Vendor/glad"
include "Engine/Vendor/imgui"


-------------------------------------------------------------------------------
project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files
    {
        "Engine/src/**.h",
        "Engine/src/**.c",
        "Engine/src/**.hpp",
        "Engine/src/**.cpp",
        "Engine/Vendor/stb_image/**.h",
        "Engine/Vendor/stb_image/**.cpp",
        "Engine/Vendor/glm/glm/**.hpp",
		"Engine/Vendor/glm/glm/**.inl",
    }

    includedirs
    {
        "Engine/src",
        "Engine/Vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    defines
    {
        GLFW_INCLUDE_NONE
    }

    filter "system:windows"
		systemversion "latest"
        buildoptions { "/utf-8"}
    
    filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"


---------------------------------------------------
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++17"
    staticruntime "on"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"Sandbox/src/**.h",
		"Sandbox/src/**.c",
        "Sandbox/src/**.hpp",
		"Sandbox/src/**.cpp"
	}

	includedirs
	{
		"Engine/Vendor/spdlog/include",
		"Engine/src",
        "Engine/Vendor",
        "%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
	}

	links
	{
		"Engine"
	}

	filter "system:windows"	
		systemversion "latest"
        buildoptions { "/utf-8"}

		defines
		{

		}

    
    filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "on"



---------------------------------------------------
project "Editor"
	location "Editor"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++17"
    staticruntime "on"

	targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

	files
	{
		"Editor/src/**.h",
		"Editor/src/**.c",
        "Editor/src/**.hpp",
		"Editor/src/**.cpp"
	}

	includedirs
	{
		"Engine/Vendor/spdlog/include",
		"Engine/src",
        "Engine/Vendor",
        "%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
	}

	links
	{
		"Engine"
	}

	filter "system:windows"	
		systemversion "latest"
        buildoptions { "/utf-8"}

		defines
		{

		}

    
    filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "on"
