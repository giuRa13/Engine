workspace "Engine"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/Vendor/glfw/include"
IncludeDir["Glad"] = "Engine/Vendor/glad/include"
IncludeDir["ImGui"] = "Engine/Vendor/imgui"
IncludeDir["glm"] = "Engine/Vendor/glm"

include "Engine/Vendor/glfw"
include "Engine/Vendor/glad"
include "Engine/Vendor/imgui"


-------------------------------------------------------------------------------
project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
    objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files
    {
        "Engine/src/**.h",
        "Engine/src/**.c",
        "Engine/src/**.hpp",
        "Engine/src/**.cpp",
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
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
        buildoptions { "/utf-8"}

    filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
        buildoptions "/MDd"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"
        buildoptions "/MD"

	filter "configurations:Dist"
		defines "DIST"
		optimize "On"
        buildoptions "/MD"


---------------------------------------------------
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
        "%{IncludeDir.glm}"
	}

	links
	{
		"Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
        buildoptions { "/utf-8"}

		defines
		{
			--"HZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"
        buildoptions "/MDd"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"
        buildoptions "/MD"

	filter "configurations:Dist"
		defines "DIST"
		optimize "On"
        buildoptions "/MD"