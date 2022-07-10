// Copyright to Avram Traian. 2022 - 2022.
// File created on July 10 2022.

#include "VulkanRenderer.h"

#include "Core/Application.h"

namespace Blueberry { namespace Renderer { namespace VulkanRenderer {

	Result Initialize()
	{
		return RESULT_Success;
	}

	void Shutdown()
	{

	}

	Result CreateGraphicsContext(Ref<GraphicsContext>& out_graphics_context, const GraphicsContextSpecification& specification)
	{
		Ref<VulkanContext> graphics_context = Ref<VulkanContext>(bbnew VulkanContext());
		graphics_context->Specification = specification;

		VkApplicationInfo application_info = {};
		application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		// application_info.pApplicationName = Application::Get()->GetSpecification().Name.CStr();
		application_info.pApplicationName = "Blueberry Application";
		application_info.pEngineName = "Blueberry Engine";
		application_info.apiVersion = VK_API_VERSION_1_3;
		application_info.applicationVersion = VK_MAKE_API_VERSION(1, 1, 0, 0);
		application_info.engineVersion = VK_MAKE_API_VERSION(1, 1, 0, 0);

		Vector<const char*> required_layers;

		Vector<const char*> required_extensions;
		required_extensions.Add(VK_KHR_SURFACE_EXTENSION_NAME);

		VkInstanceCreateInfo instance_info = {};
		instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instance_info.pApplicationInfo = &application_info;
		instance_info.ppEnabledLayerNames = required_layers.Data();
		instance_info.enabledLayerCount = (uint32_t)required_layers.Size();
		instance_info.ppEnabledExtensionNames = required_extensions.Data();
		instance_info.enabledExtensionCount = (uint32_t)required_extensions.Size();

		VkResult result = vkCreateInstance(&instance_info, nullptr, &graphics_context->Instance);
		if (result != VK_SUCCESS)
		{
			BLUB_CORE_ERROR(TEXT("vkCreateInstance failed with result: {}"), (int64_t)result);
			return RESULT_Unknown;
		}

		BLUB_CORE_INFO(TEXT("GraphicsContext (Vulkan) created successfully!"));

		out_graphics_context = graphics_context.As<GraphicsContext>();
		return RESULT_Success;
	}

	void DestroyGraphicsContext(VulkanContext* graphics_context)
	{
		vkDestroyInstance(graphics_context->Instance, nullptr);
	}

} } }