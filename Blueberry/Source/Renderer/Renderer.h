// Copyright to Avram Traian. 2022 - 2022.
// File created on July 10 2022.

#pragma once

#include "Core/CoreMinimal.h"

#include "GraphicsContext.h"

namespace Blueberry { namespace Renderer {

	enum class API : uint8_t
	{
		// Invalid value.
		Unknown = 0,

		None    = 1,
		Vulkan  = 2,
		D3D12   = 3,
		Metal   = 4
	};

	struct Config
	{
		API RendererAPI = API::Unknown;
	};

	struct Specification
	{
		Config RendererConfig;
	};

	enum ResultEnum : int32_t
	{
		RESULT_Success = 0,
		RESULT_Unknown
	};
	using Result = int32_t;

	Result CreateGraphicsContext(Ref<GraphicsContext>& out_graphics_context, const GraphicsContextSpecification& specification);

	BLUEBERRY_API const Specification& GetSpecification();

	Result Initialize(const Specification& specification);

	void Shutdown();

} }