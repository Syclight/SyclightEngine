workspace "SyclightEngine"
	architecture "x64"
	startproject "Sandbox"
	configurations {
		"Debug", 
		"Release", 
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Syclight/vendor/GLFW/include"
IncludeDir["Glad"] = "Syclight/vendor/Glad/include"
IncludeDir["ImGui"] = "Syclight/vendor/imgui"
IncludeDir["glm"] = "Syclight/vendor/glm"
-- IncludeDir["spdlog"] = "Syclight/vendor/spdlog-v1.x/include"

include "Syclight/vendor/GLFW"
include "Syclight/vendor/Glad"
include "Syclight/vendor/imgui"
-- include "Syclight/vendor/glm"

project "Syclight"
	location "Syclight"
	-- kind "SharedLib"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "sycpch.h"
	pchsource "Syclight/src/sycpch.cpp"

	files {
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs {
		"%{prj.name}/src/",
		"%{prj.name}/vendor/spdlog-v1.x/include",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links { 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines { 
			"SYC_PLATFORM_WINDOWS", 
			"SYC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		-- postbuildcommands {
		-- 	--  "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox"
		-- 	"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\""
		-- }
		
	filter "configurations:Debug"
		defines "SYC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SYC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SYC_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Syclight/vendor/spdlog-v1.x/include", 
		"Syclight/src",
		"Syclight/vendor",
		"%{IncludeDir.glm}"
	}

	links { 
		"Syclight"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"SYC_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "SYC_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SYC_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SYC_DIST"
		runtime "Release"
		optimize "on"