// Copyright to Avram Traian. 2022 - 2022.
// File created on July 10 2022.

#include "Renderer.h"

#include "Platform/Vulkan/VulkanRenderer.h"

namespace Blueberry { namespace Renderer {

	struct RendererData
	{
		Specification Specification;
		Ref<GraphicsContext> GraphicsContextPtr;

		Result(*APIInitialize)() = nullptr;
		void(*APIShutdown)() = nullptr;
		Result(*APICreateGraphicsContext)(Ref<GraphicsContext>& out_graphics_context, const GraphicsContextSpecification&) = nullptr;
	};
	static RendererData* s_RendererData = nullptr;

	Result Initialize(const Specification& specification)
	{
		if (s_RendererData)
			return false;

		s_RendererData = bbnew RendererData();
		if (!s_RendererData)
			return false;

		switch (specification.RendererConfig.RendererAPI)
		{
			case API::Vulkan:
			{
				BLUB_CORE_TRACE(TEXT("Renderer initializing for Vulkan API..."));

				s_RendererData->APIInitialize             = VulkanRenderer::Initialize;
				s_RendererData->APIShutdown               = VulkanRenderer::Shutdown;
				s_RendererData->APICreateGraphicsContext  = VulkanRenderer::CreateGraphicsContext;
				break;
			}
		}

		Result result;
		result = s_RendererData->APIInitialize();
		if (result != RESULT_Success)
		{
			BLUB_CORE_ERROR(TEXT("Failed to initialize the API specific renderer!"));
			return result;
		}

		GraphicsContextSpecification graphics_context_specification;
		result = Renderer::CreateGraphicsContext(s_RendererData->GraphicsContextPtr, graphics_context_specification);
		if (result != RESULT_Success)
		{
			BLUB_CORE_ERROR(TEXT("Failed to create the graphics context!"));
			return result;
		}

		BLUB_CORE_INFO(TEXT("Renderer initialized successfully!"));
		return RESULT_Success;
	}

	void Shutdown()
	{
		if (!s_RendererData)
			return;

		s_RendererData->GraphicsContextPtr.Release();

		s_RendererData->APIShutdown();

		delete s_RendererData;
		s_RendererData = nullptr;
	}

	const Specification& GetSpecification()
	{
		return s_RendererData->Specification;
	}

	Result CreateGraphicsContext(Ref<GraphicsContext>& out_graphics_context, const GraphicsContextSpecification& specification)
	{
		return s_RendererData->APICreateGraphicsContext(out_graphics_context, specification);
	}

} }