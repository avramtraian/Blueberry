#include "Input.h"

namespace Blueberry {

	enum KeyStateEnum : uint8_t
	{
		BLUE_KEY_STATE_None             = 0,
		BLUE_KEY_STATE_Pressed          = 1 << 0,
		BLUE_KEY_STATE_PressedThisTick  = 1 << 1,
		BLUE_KEY_STATE_ReleasedThisTick = 1 << 2,
	};
	using KeyState = uint8_t;

	#define BLUE_HAS_STATE(Key, State) (s_InputData->KeyStates[(uint16_t)(Key)] & (State))

	#define BLUE_ADD_STATE(Key, State)    s_InputData->KeyStates[(uint16_t)(Key)] |= (State)

	#define BLUE_REMOVE_STATE(Key, State) s_InputData->KeyStates[(uint16_t)(Key)] &= ~(State)

	struct InputData
	{
		KeyState KeyStates[256]  = {};

		int32_t  MouseX          = 0;
		int32_t  MouseY          = 0;

		int32_t  LastTickMouseX  = 0;
		int32_t  LastTickMouseY  = 0;

		double   MouseWheelDelta = 0.0;
	};
	static InputData* s_InputData = nullptr;

	bool Input::Initialize()
	{
		if (s_InputData)
			return false;

		s_InputData = new InputData();
		if (!s_InputData)
			return false;

		return true;
	}

	void Input::Shutdown()
	{
		if (!s_InputData)
			return;

		delete s_InputData;
		s_InputData = nullptr;
	}

	bool Input::IsKeyPressed(Key key)
	{
		return BLUE_HAS_STATE(key, BLUE_KEY_STATE_Pressed);
	}

	bool Input::WasKeyPressedThisTick(Key key)
	{
		return BLUE_HAS_STATE(key, BLUE_KEY_STATE_PressedThisTick);
	}

	bool Input::WasKeyReleasedThisTick(Key key)
	{
		return BLUE_HAS_STATE(key, BLUE_KEY_STATE_ReleasedThisTick);
	}

	bool Input::IsMouseButtonPressed(MouseButton button)
	{
		return BLUE_HAS_STATE(button, BLUE_KEY_STATE_Pressed);
	}

	bool Input::WasMouseButtonPressedThisTick(MouseButton button)
	{
		return BLUE_HAS_STATE(button, BLUE_KEY_STATE_PressedThisTick);
	}

	bool Input::WasMouseButtonReleasedThisTick(MouseButton button)
	{
		return BLUE_HAS_STATE(button, BLUE_KEY_STATE_ReleasedThisTick);
	}

	Blueberry::Pair<int32_t, int32_t> Input::GetMousePosition()
	{
		return { GetMouseX(), GetMouseY() };
	}

	int32_t Input::GetMouseX()
	{
		return s_InputData->MouseX;
	}

	int32_t Input::GetMouseY()
	{
		return s_InputData->MouseY;
	}

	Blueberry::Pair<int32_t, int32_t> Input::GetMouseDelta()
	{
		return { GetMouseDeltaX(), GetMouseDeltaY() };
	}

	int32_t Input::GetMouseDeltaX()
	{
		return s_InputData->MouseX - s_InputData->LastTickMouseX;
	}

	int32_t Input::GetMouseDeltaY()
	{
		return s_InputData->MouseY - s_InputData->LastTickMouseY;
	}

	double Input::GetMouseWheelDelta()
	{
		return s_InputData->MouseWheelDelta;
	}

	void Input::OnUpdate()
	{
		s_InputData->LastTickMouseX = s_InputData->MouseX;
		s_InputData->LastTickMouseY = s_InputData->MouseY;

		s_InputData->MouseWheelDelta = 0.0;

		for (SizeT index = 0; index < BLUE_ARRAY_LENGTH(s_InputData->KeyStates); index++)
		{
			BLUE_REMOVE_STATE(index, BLUE_KEY_STATE_PressedThisTick);
			BLUE_REMOVE_STATE(index, BLUE_KEY_STATE_ReleasedThisTick);
		}
	}

	void Input::OnMinimized()
	{
		s_InputData->MouseWheelDelta = 0.0;

		Memory::Set(s_InputData->KeyStates, BLUE_KEY_STATE_None, sizeof(s_InputData->KeyStates));
	}

	void Input::SetKeyPressed(Key key)
	{
		BLUE_REMOVE_STATE(key, BLUE_KEY_STATE_ReleasedThisTick);

		BLUE_ADD_STATE(key, BLUE_KEY_STATE_Pressed);
		BLUE_ADD_STATE(key, BLUE_KEY_STATE_PressedThisTick);
	}

	void Input::SetKeyReleased(Key key)
	{
		BLUE_REMOVE_STATE(key, BLUE_KEY_STATE_Pressed);
		BLUE_REMOVE_STATE(key, BLUE_KEY_STATE_PressedThisTick);

		BLUE_ADD_STATE(key, BLUE_KEY_STATE_ReleasedThisTick);
	}

	void Input::SetMouseButtonPressed(MouseButton button)
	{
		BLUE_REMOVE_STATE(button, BLUE_KEY_STATE_ReleasedThisTick);

		BLUE_ADD_STATE(button, BLUE_KEY_STATE_Pressed);
		BLUE_ADD_STATE(button, BLUE_KEY_STATE_PressedThisTick);
	}

	void Input::SetMouseButtonReleased(MouseButton button)
	{
		BLUE_REMOVE_STATE(button, BLUE_KEY_STATE_Pressed);
		BLUE_REMOVE_STATE(button, BLUE_KEY_STATE_PressedThisTick);

		BLUE_ADD_STATE(button, BLUE_KEY_STATE_ReleasedThisTick);
	}

	void Input::SetMousePosition(int32_t mouse_x, int32_t mouse_y)
	{
		s_InputData->MouseX = mouse_x;
		s_InputData->MouseY = mouse_y;
	}

	void Input::SetMouseWheelDelta(double delta)
	{
		s_InputData->MouseWheelDelta = delta;
	}

}