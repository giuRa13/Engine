project "SpirvCross"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

    files
    {
        "spirv_cross/spirv.h",
        "spirv_cross/spirv.hpp",
        "spirv_cross/spirv_cfg.cpp",
        "spirv_cross/spirv_cfg.hpp",
        "spirv_cross/spirv_common.hpp",
        "spirv_cross/spirv_cpp.cpp",
        "spirv_cross/spirv_cpp.hpp",
        "spirv_cross/spirv_cross.cpp",
        "spirv_cross/spirv_cross.hpp",
        "spirv_cross/spirv_cross_c.cpp",
        "spirv_cross/spirv_cross_c.h",
        "spirv_cross/spirv_cross_containers.hpp",
        "spirv_cross/spirv_cross_error_handling.hpp",
        "spirv_cross/spirv_cross_parsed_ir.cpp",
        "spirv_cross/spirv_cross_parsed_ir.hpp",
        "spirv_cross/spirv_cross_util.cpp",
        "spirv_cross/spirv_cross_util.hpp",
        "spirv_cross/spirv_glsl.cpp",
        "spirv_cross/spirv_glsl.hpp",
        "spirv_cross/spirv_hlsl.cpp",
        "spirv_cross/spirv_hlsl.hpp",
        "spirv_cross/spirv_msl.cpp",
        "spirv_cross/spirv_msl.hpp",
        "spirv_cross/spirv_parser.cpp",
        "spirv_cross/spirv_parser.hpp",
        "spirv_cross/spirv_reflect.cpp",
        "spirv_cross/spirv_reflect.hpp"
    }
    includedirs
	{
		"include/spirv_cross"
	}

    filter "system:windows"
        systemversion "latest"

    filter "system:macosx"
        systemversion "11.0"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter "configurations:Production"
        runtime "Release"
        optimize "On"