#pragma once

#include "Base.h"
#include "KeyCodes.h"

namespace Blueberry {

	class BLUEBERRY_API Input
	{
	public:
		static bool Initialize();

		static void Shutdown();

	public:
		static bool IsKeyPressed(Key key);
		static bool WasKeyPressedThisTick(Key key);
		static bool WasKeyReleasedThisTick(Key key);

		static bool IsMouseButtonPressed(MouseButton button);
		static bool WasMouseButtonPressedThisTick(MouseButton button);
		static bool WasMouseButtonReleasedThisTick(MouseButton button);

		static Pair<int32_t, int32_t> GetMousePosition();
		static int32_t GetMouseX();
		static int32_t GetMouseY();

		static Pair<int32_t, int32_t> GetMouseDelta();
		static int32_t GetMouseDeltaX();
		static int32_t GetMouseDeltaY();

		static double GetMouseWheelDelta();

	public:
		static void OnUpdate();
		static void OnMinimized();

		static void SetKeyPressed(Key key);
		static void SetKeyReleased(Key key);
		static void SetMouseButtonPressed(MouseButton button);
		static void SetMouseButtonReleased(MouseButton button);
		static void SetMousePosition(int32_t mouse_x, int32_t mouse_y);
		static void SetMouseWheelDelta(double delta);
	};

}