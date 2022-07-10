// Copyright to Avram Traian. 2022 - 2022.
// File created on July 10 2022.

#pragma once

#include "Renderer/Renderer.h"

#include "Renderer/GraphicsContext.h"

#include <vulkan/vulkan.h>

namespace Blueberry { namespace Renderer { namespace VulkanRenderer {

	Result Initialize();

	void Shutdown();

	struct VulkanContext : public GraphicsContext
	{
	public:
		VkInstance Instance = VK_NULL_HANDLE;

	public:
		virtual inline ~VulkanContext() override;
	};

	Result CreateGraphicsContext(Ref<GraphicsContext>& out_graphics_context, const GraphicsContextSpecification& specification);

	void DestroyGraphicsContext(VulkanContext* graphics_context);

	VulkanContext::~VulkanContext()
	{
		VulkanRenderer::DestroyGraphicsContext(this);
	}

} } }