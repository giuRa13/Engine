local EngineRootDir = '../../../'

workspace "Sandbox"
	architecture "x86_64"
	startproject "Sandbox"
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

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Sandbox"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.7.2"
	targetdir ("Binaries")
	objdir ("Intermediates")

	files 
	{
		"Source/**.cs",
		"Properties/**.cs"
	}

	links
	{
		"Engine-ScriptCore"
	}
	
	filter "configurations:Debug"
		optimize "Off"
		symbols "Default"
	filter "configurations:Release"
		optimize "On"
		symbols "Default"
	filter "configurations:Dist"
		optimize "Full"
		symbols "Off"

group "Engine"
	include (EngineRootDir .. "/Engine-ScriptCore")
group ""