project "Blueberry"
	location "%{wks.location}/Blueberry"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "Off"

	targetdir "%{wks.location}/Binaries/%{cfg.platform}/%{cfg.buildcfg}"
	objdir "%{wks.location}/Intermediate/Binaries/%{cfg.buildcfg}/%{prj.name}"
	targetname "Blueberry"

	pchheader "blubpch.h"
	-- NOTE (Avr): Token expansion seems broken when used in 'pchsource'
	pchsource "../../Blueberry/Source/blubpch.cpp"

	rtti "Off"
	exceptionhandling "Off"

	characterset "Unicode"

	files
	{
		"%{prj.location}/Source/**.cpp",
		"%{prj.location}/Source/**.h"
	}

	includedirs
	{
		IncludeDirs["Blueberry"]
	}

	defines
	{
		"BLUE_BUILD_DLL"
	}

	forceincludes
	{
		"blubpch.h"
	}

	filter "platforms:Win64"
		defines
		{
			"BLUE_PLATFORM_WINDOWS=(1)",
			"BLUE_PLATFORM_WIN64=(1)"
		}
		systemversion "Latest"

	filter {}
		
	filter "configurations:Debug"
		defines
		{
			"BLUE_BUILD_DEBUG=(1)"
		}

		runtime "Debug"
		optimize "Off"
		symbols "On"
		
	filter "configurations:Release"
		defines
		{
			"BLUE_BUILD_RELEASE=(1)"
		}

		runtime "Release"
		optimize "On"
		symbols "On"
		
	filter "configurations:Shipping"
		defines
		{
			"BLUE_BUILD_SHIPPING=(1)"
		}

		runtime "Release"
		optimize "Speed"
		symbols "Off"
		
	filter {}