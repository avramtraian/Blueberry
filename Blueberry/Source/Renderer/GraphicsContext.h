// Copyright to Avram Traian. 2022 - 2022.
// File created on July 10 2022.

#pragma once

#include "Core/CoreMinimal.h"

namespace Blueberry { namespace Renderer {

	struct GraphicsContextSpecification
	{

	};

	struct GraphicsContext : public RefClass
	{
	public:
		GraphicsContextSpecification Specification;

	public:
		virtual ~GraphicsContext() {}
	};

} }