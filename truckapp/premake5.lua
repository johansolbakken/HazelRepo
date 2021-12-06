-- Premake.lua
workspace "truckapp"
    architecture "x64"
    configurations { 
        "Debug", 
        "Release" 
    }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ui"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    location "ui"
    staticruntime "On"
    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs { "./vendor/include" }
    libdirs { "./vendor/lib" }

    links { "glfw3", "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

