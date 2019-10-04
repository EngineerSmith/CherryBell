workspace "CherryBell"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--
IncludeDir = {}
IncludeDir["GLFW"] = "CherryBell/vendor/GLFW/include"
IncludeDir["Glad"] = "CherryBell/vendor/Glad/include"
IncludeDir["imgui"] = "CherryBell/vendor/imgui"
IncludeDir["glm"] = "CherryBell/vendor/glm"

-- Includes premake5 file
group "Dependencies"
	include "CherryBell/vendor/GLFW"
	include "CherryBell/vendor/Glad"
	include "CherryBell/vendor/imgui"
group ""
	
project "CherryBell"
	location "CherryBell"
	kind "SharedLib"
	language "c++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "cbpch.h"
	pchsource "%{prj.name}/src/cbpch.cpp"
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines {
		"IMGUI_API=__declspec(dllexport)"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"CB_PLATFORM_WINDOWS",
			"CB_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox\"")
		}
		
	filter "configurations:Debug"
		defines {"CB_DEBUG","CB_ENABLE_ASSERTS"}
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CB_DIST"
		runtime "Release"
		optimize "On"
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "c++"
	staticruntime "off"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"CherryBell/vendor/spdlog/include",
		"CherryBell/src",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}
	
	links 
	{
		"CherryBell"
	}

	defines {
		"IMGUI_API=__declspec(dllimport)"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"CB_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "CB_DIST"
		runtime "Release"
		optimize "On"
	
	