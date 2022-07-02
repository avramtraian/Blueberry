-- Copyright to Avram Traian. 2022 - 2022.
-- File created on June 13 2022.

project "JamEd"
	location "%{wks.location}/JamEd"

	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	characterset "Unicode"
	rtti "Off"
	exceptionhandling "Off"

	BinariesDir = "%{wks.location}/Binaries/%{cfg.platform}/%{cfg.buildcfg}"
	objdir "%{wks.location}/Intermediate/Binaries/%{cfg.buildcfg}/%{prj.name}"
	targetdir (BinariesDir)
	targetname "JamEd-Editor"

	debugdir (BinariesDir)

	files {
		"%{prj.location}/Source/**.cpp",
		"%{prj.location}/Source/**.h",

		"%{prj.location}/Build/**.lua"
	}

	includedirs {
		IncludeDirectories["JamEd"],
		IncludeDirectories["Blueberry"]
	}

	forceincludes {

	}

	defines {
		"BLUE_USE_SHARED_LIBRARY"
	}

	links {
		"Blueberry"
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

		kind "ConsoleApp"
		
	filter "configurations:Release"
		defines {
			"BLUE_BUILD_RELEASE=(1)"
		}

		runtime "Release"
		optimize "On"
		symbols "On"

		kind "ConsoleApp"
		
	filter "configurations:Shipping"
		defines {
			"BLUE_BUILD_SHIPPING=(1)"
		}

		runtime "Release"
		optimize "Speed"
		symbols "Off"

		kind "WindowedApp"
		
	filter {}