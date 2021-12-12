-- Premake.lua
workspace "Hazel"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release",
        "Dist"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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

    -- Project files
    files { "%{prj.name}/src/**.cpp", "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.h" }

    -- Libraries
	sysincludedirs {"./hazel/vendor/spdlog/include"} -- include directories
    links { }

    -- Configuration setup
    filter "configurations:Debug"
        defines { "HZ_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "HZ_RELEASE" }
        optimize "On"

    filter "configurations:Dist"
        defines { "HZ_DIST" }
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
	
	sysincludedirs { "./hazel/src", "./hazel/vendor/spdlog/include" }

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




--[[ My own ui project from earlier
project "ui"
    kind "WindowedApp"
    cppdialect "C++17"
    location "ui"
    systemversion "10.15"
    staticruntime "On"
    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    files { "%{prj.name}/src/**", "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp", "%{prj.name}/res/**.glsl"}
    debugdir "%{prj.name}"

    includedirs { "./vendor/include", "%{prj.name}/res/**.glsl" }
    libdirs { "./vendor/lib" }
    sysincludedirs { "/Library/Frameworks", "./vendor/include", "%{prj.name}/res/**.glsl" }

    links { "glfw3", "GLEW", "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework" }
    xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
--]]