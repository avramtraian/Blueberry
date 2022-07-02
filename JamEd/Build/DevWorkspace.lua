IncludeDirectories = {}
LibraryDirectories = {}
LibraryNames = {}

workspace "Blueberry"
	location "../../"

	configurations {
		"Debug", "Release", "Shipping"
	}

	platforms {
		"Win64"
	}

	filter "platforms:Win64"
		system "Windows"
		architecture "x86_64"
	filter {}

	startproject "JamEd"

	IncludeDirectories["Blueberry"] = "%{wks.location}/Blueberry/Source"
	IncludeDirectories["JamEd"]     = "%{wks.location}/JamEd/Source"

	VulkanSDKPath = os.getenv("VULKAN_SDK")
	IncludeDirectories["VulkanSDK"] = (VulkanSDKPath.."/Include")
	LibraryDirectories["VulkanSDK"] = (VulkanSDKPath.."/Lib")
	LibraryNames["VulkanSDK"]       = "vulkan-1.lib"

	group "Core"
		include "DevBlueberry.lua"	

	group "Tools"
		include "DevJamEd.lua"

	group "ThirdParty"
	group ""