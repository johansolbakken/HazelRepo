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
IncludeDir["GLFW"] = "vendor/include"
IncludeDir["Glad"] = "Hazel/vendor/glad/include"
IncludeDir["imgui"] = "Hazel/vendor/imgui"
IncludeDir["glm"] = "Hazel/vendor/glm"
IncludeDir["spdlog"] = "Hazel/vendor/spdlog/include"

--include "Hazel/vendor/glfw"
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
    staticruntime "Off"

    -- Output for Lib
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")

    -- Output for intermediate files
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    -- Pre compiled header
    pchheader "src/hzpch.h"
    pchsource "hazel/src/hzpch.cpp"

    -- Project files
    files { "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.h" }

	

    libdirs {"vendor/lib"}

    includedirs {
        "./hazel/src"
    }

    -- Libraries
	sysincludedirs {
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}"
    }
    
    links { "glfw3", "Glad", "ImGui", "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework" }

    -- Configuration setup
    filter "configurations:Debug"
        defines { "HZ_DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "HZ_RELEASE" }
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines { "HZ_DIST" }
        runtime "Release"
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
	staticruntime "Off"

    -- Intermediate and target dirs
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.h" }

	sysincludedirs { 
        "./hazel/src", 
        "%{IncludeDir.glm}",
        "%{IncludeDir.spdlog}"
    }

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
