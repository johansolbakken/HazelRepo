-- Premake.lua
workspace "truckapp"
    architecture "x64"
	language "C++"
    configurations { 
        "Debug", 
        "Release" 
    }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
    sysincludedirs { "/Library/Frameworks" }

    links { "glfw3", "GLEW", "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

