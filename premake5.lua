workspace "SyclightEngine"
	architecture "x64"
	configurations {
		"Debug", 
		"Release", 
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Syclight"
	location "Syclight"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	pchheader "sycpch.h"
	pchsource "Syclight/src/sycpch.cpp"

	files {
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}

	includedirs {
		"%{prj.name}/src/",
		"%{prj.name}/3rd_party_libs/spdlog-v1.x/include" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines { 
			"SYC_PLATFORM_WINDOWS", 
			"SYC_BUILD_DLL" 
		}
		postbuildcommands {
			 "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		}
		
	filter "configurations:Debug"
		defines "SYC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SYC_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "SYC_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin_int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Syclight/3rd_party_libs/spdlog-v1.x/include", 
		"Syclight/src"
	}

	links { 
		"Syclight"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "10.0.19041.0"
		defines {
			"SYC_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "SYC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SYC_RELEASE"
		optimize "On"

	filter "configurations:Distribution"
		defines "SYC_DIST"
		optimize "On"