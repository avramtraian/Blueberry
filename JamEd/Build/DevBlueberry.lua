-- Copyright to Avram Traian. 2022 - 2022.
-- File created on June 13 2022.

project "Blueberry"
	location "%{wks.location}/Blueberry"

	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	characterset "Unicode"
	exceptionhandling "Off"
	rtti "Off"

	BinariesDir = "%{wks.location}/Binaries/%{cfg.platform}/%{cfg.buildcfg}"
	objdir "%{wks.location}/Intermediate/Binaries/%{cfg.buildcfg}/%{prj.name}"
	targetdir (BinariesDir)
	targetname "Blueberry-Core"

	debugdir (BinariesDir)

	pchheader "blubpch.h"
	-- NOTE (Avr): Token expansion seems broken when used in 'pchsource'.
	pchsource "../../Blueberry/Source/blubpch.cpp"

	files {
		"%{prj.location}/Source/**.cpp",
		"%{prj.location}/Source/**.h",

		"%{prj.location}/Content/Shaders/**.glsl"
	}

	includedirs {
		IncludeDirectories["Blueberry"]
	}

	forceincludes {
		"blubpch.h"
	}

	defines {
		"BLUE_BUILD_SHARED_LIBRARY"
	}

	links {

	}

	filter "platforms:Win64"
		defines {
			"BLUE_PLATFORM_WINDOWS=(1)",
			"BLUE_PLATFORM_WIN64=(1)"
		}
		systemversion "Latest"

	filter {}
		
	filter "configurations:Debug"
		defines {
			"BLUE_BUILD_DEBUG=(1)"
		}

		runtime "Debug"
		optimize "Off"
		symbols "On"
		
	filter "configurations:Release"
		defines {
			"BLUE_BUILD_RELEASE=(1)"
		}

		runtime "Release"
		optimize "On"
		symbols "On"
		
	filter "configurations:Shipping"
		defines {
			"BLUE_BUILD_SHIPPING=(1)"
		}

		runtime "Release"
		optimize "Speed"
		symbols "Off"
		
	filter {}