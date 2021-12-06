-- Premake.lua
workspace "truckapp"
    architecture "x64"
	language "C++"
    configurations { 
        "Debug", 
        "Release" 
    }
	--buildoptions { "-stdlib=libc++"}
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ui"
    kind "WindowedApp"
    cppdialect "C++17"
    location "ui"
    systemversion "10.15"
    staticruntime "On"
    targetdir ("bin/" .. outputdir)
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    
    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs { "./vendor/include" }
    libdirs { "./vendor/lib" }
    sysincludedirs { "/Library/Frameworks" }

    links { "glfw3", "GLEW", "CoreVideo.framework", "IOKit.framework", "OpenGL.framework", "Cocoa.framework" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"

