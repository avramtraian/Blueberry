IncludeDirs = {}
LibDirs = {}
LibNames = {}

workspace "Blueberry"
	location "../../"

	configurations
	{
		"Debug", "Release", "Shipping"
	}

	platforms
	{
		"Win64"
	}

	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"
	filter {}

	startproject "JamEd"

	IncludeDirs["Blueberry"] = "%{wks.location}/Blueberry/Source"
	IncludeDirs["JamEd"] = "%{wks.location}/JamEd/Source"

	VulkanSDKPath = os.getenv("VULKAN_SDK")
	IncludeDirs["VulkanSDK"] = "%{VulkanSDKPath}/Include"
	LibDirs["VulkanSDK"] = "%{VulkanSDKPath}/Lib"
	LibNames["VulkanSDK"] = "vulkan-1.lib"

	group "Core"
		include "DevBlueberry.lua"	

	group "Tools"
		include "DevJamEd.lua"

	group "ThirdParty"
	group ""