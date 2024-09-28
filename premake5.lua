workspace "SyclightEngine"
	architecture "x64"
	configurations {
		"Debug", 
		"Release", 
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Syclight/vendor/GLFW/include"
-- IncludeDir["Glad"] = "Syclight/vendor/glad/include"
-- IncludeDir["ImGui"] = "Syclight/vendor/imgui"
-- IncludeDir["spdlog"] = "Syclight/vendor/spdlog-v1.x/include"

include "Syclight/vendor/GLFW"

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
		"%{prj.name}/vendor/spdlog-v1.x/include",
		"%{IncludeDir.GLFW}"
	}

	links { 
		"GLFW",
		"opengl32.lib"
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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SYC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "SYC_DIST"
		buildoptions "/MD"
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
		"Syclight/vendor/spdlog-v1.x/include", 
		"Syclight/src"
	}

	links { 
		"Syclight"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines {
			"SYC_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "SYC_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "SYC_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Distribution"
		defines "SYC_DIST"
		buildoptions "/MD"
		optimize "On"