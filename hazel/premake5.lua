-- Premake.lua
workspace "Hazel"
    architecture "x64"
	language "C++"
    configurations { 
        "Debug", 
        "Release" 
    }
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
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

project "Sandbox"
	kind "ConsoleApp"
	cppdialect "C++17"
	location "sandbox"
	systemversion "10.15"
	staticruntime "On"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	files { "%{prj.name}/src/**" }
	
	sysincludedirs {"./hazel/src", "./hazel/vendor/spdlog/include"}
	links { "Hazel" }
xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
	postbuildcommands ("{COPY} %{wks.location}/bin/" .. outputdir .. "/Hazel/libHazel.dylib %{cfg.targetdir}")

	filter "configurations:Debug"
        	defines { "DEBUG" }
        	symbols "On"

   	 filter "configurations:Release"
        	defines { "NDEBUG" }
        	optimize "On"	

project "Hazel"
	kind "SharedLib"
        cppdialect "C++17"
        location "hazel"
        systemversion "10.15"
        staticruntime "On"
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
        files { "%{prj.name}/src/**" }

	sysincludedirs {"./hazel/vendor/spdlog/include"}
        links { }
	
xcodebuildsettings = { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }
        filter "configurations:Debug"
                defines { "DEBUG" }
                symbols "On"

         filter "configurations:Release"
                defines { "NDEBUG" }
                optimize "On"
