-- Premake.lua
workspace "Hazel"
    architecture "x64"
    startproject "Sandbox"
    configurations { 
        "Debug", 
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["Glad"] = "Hazel/vendor/glad/include"
IncludeDir["imgui"] = "Hazel/vendor/imgui"

include "Hazel/vendor/glad"
include "Hazel/vendor/imgui"

--[[
    HAZEL PROJECT
]]
project "Hazel"
    location "hazel" -- Path of project
	kind "SharedLib" -- Dynamic library
    language "C++" -- Language of project
    cppdialect "C++17" -- Cpp version
    systemversion "10.15"
    staticruntime "On"

    -- Output for Lib
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")

    -- Output for intermediate files
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- Pre compiled header
    pchheader "src/hzpch.h"
    pchsource "hazel/src/hzpch.cpp"

    -- Project files
    files { "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.h" }

	includedirs {"./hazel/src"}

    -- Libraries
	sysincludedirs {
        "./hazel/vendor/spdlog/include",
        "./vendor/include",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}"
    }
     libdirs { "./vendor/lib" }

    links { "glfw3", "Glad", "ImGui", "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework" }

    defines {
        "GLFW_INCLUDE_NONE"
    }

    -- Configuration setup
    filter "configurations:Debug"
        defines { "HZ_DEBUG" }
        --buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines { "HZ_RELEASE" }
        --buildoptions "/MD"
        optimize "On"

    filter "configurations:Dist"
        defines { "HZ_DIST" }
        --buildoptions "/MD"
        optimize "On"


--[[
    Sandbox PROJECT
]]
project "Sandbox"
    location "sandbox"
	kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"
	systemversion "10.15"
	staticruntime "On"

    -- Intermediate and target dirs
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.h" }
	
     libdirs { "./vendor/lib" }
	sysincludedirs { "./hazel/src", "./hazel/vendor/spdlog/include", "./vendor/include" }

    -- Linking hazel into sandbox
	links { "Hazel" }
	postbuildcommands ("{COPY} %{wks.location}/bin/" .. outputdir .. "/Hazel/libHazel.dylib %{cfg.targetdir}")

	filter "configurations:Debug"
        defines { "HZ_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "HZ_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "HZ_DIST" }
        optimize "On"
