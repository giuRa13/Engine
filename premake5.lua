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
VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["GLFW"] = "Engine/Vendor/glfw/include"
IncludeDir["Glad"] = "Engine/Vendor/glad/include"
IncludeDir["ImGui"] = "Engine/Vendor/imgui"
IncludeDir["glm"] = "Engine/Vendor/glm"
IncludeDir["stb_image"] = "Engine/Vendor/stb_image"
IncludeDir["entt"] = "Engine/Vendor/entt/include"
IncludeDir["yaml_cpp"] = "Engine/Vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "Engine/Vendor/imGuizmo"
IncludeDir["Box2D"] = "Engine/Vendor/Box2D/include"
IncludeDir["mono"] = "Engine/Vendor/mono/include"
IncludeDir["shaderc"] = "Engine/Vendor/shaderc/include"
IncludeDir["SPIRVCross"] = "Engine/Vendor/SPIRV-Cross/include"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}
LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["Mono"] = "%{wks.location}/Engine/Vendor/mono/lib/%{cfg.buildcfg}"
--LibraryDir["mono"] = "Engine/Vendor/mono/lib/Debug/mono-2.0-sgen.lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["mono"] = "%{LibraryDir.Mono}/libmono-static-sgen.lib"
Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
--Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
--Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
--Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"
Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
--Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
--Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"

-- Windows only
Library["WinSock"] = "Ws2_32.lib"
Library["WinMM"] = "Winmm.lib"
Library["WinVersion"] = "Version.lib"
Library["BCrypt"] = "Bcrypt.lib"

group "Dependencies"
	include "Engine/Vendor/glfw"
	include "Engine/Vendor/glad"
	include "Engine/Vendor/imgui"
	include "Engine/Vendor/yaml-cpp"
	include "Engine/Vendor/Box2D"
	include "Engine/Vendor/SPIRV-Cross"
group ""

include "Engine-ScriptCore"


-------------------------------------------------------------------------------
project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

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
		"Engine/Vendor/imGuizmo/ImGuizmo/ImGuizmo.h",
		"Engine/Vendor/imGuizmo/ImGuizmo/ImGuizmo.cpp"
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
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.mono}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.SPIRVCross}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
		"yaml-cpp",
		"Box2D",
		"%{Library.mono}",
		"SPIRVCross",
        "opengl32.lib"
    }

    defines
    {
        --"GLFW_INCLUDE_NONE",
		"YAML_CPP_STATIC_DEFINE",
		"VK_USE_PLATFORM_WIN32_KHR",
		"MONO_USE_STATICLIB_MONO"
    }

    filter "system:windows"
		systemversion "latest"
        buildoptions { "/utf-8"}
		links
		{
			"%{Library.WinSock}",
			"%{Library.WinMM}",
			"%{Library.WinVersion}",
			"%{Library.BCrypt}",
		}
    
    filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"
		links
		{
			"%{Library.ShaderC_Debug}",
			--"%{Library.SPIRV_Cross_Debug}",
			--"%{Library.SPIRV_Cross_GLSL_Debug}"
		}

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"
		links
		{
			"%{Library.ShaderC_Release}",
			--"%{Library.SPIRV_Cross_Release}",
			--"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter "configurations:Dist"
		defines "DIST"
		runtime "Release"
		optimize "on"


---------------------------------------------------
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
    cppdialect "C++17"
    staticruntime "off"

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
    staticruntime "off"

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
		"%{IncludeDir.ImGuizmo}"
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
			"YAML_CPP_STATIC_DEFINE"
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
