// Copyright to Avram Traian. 2022 - 2022.
// File created on June 15 2022.

#pragma once

#include "Base.h"

namespace Blueberry {
	
	/**
	* Blueberry mouse button codes.
	* 
	* Extracted from the Windows API virtual key-codes.
	*/
	enum class MouseButton : uint8_t
	{
		Left   = 0x01,
		Right  = 0x02,
		Middle = 0x04
	};

	/**
	* Blueberry key codes.
	*
	* Extracted from the Windows API virtual key-codes.
	*/
	enum class Key : uint16_t
	{
		Zero  = 0x30,
		One   = 0x31,
		Two   = 0x32,
		Three = 0x33,
		Four  = 0x34,
		Five  = 0x35,
		Six   = 0x36,
		Seven = 0x37,
		Eight = 0x38,
		Nine  = 0x39,

		NumpadZero  = 0x60,
		NumpadOne   = 0x61,
		NumpadTwo   = 0x62,
		NumpadThree = 0x63,
		NumpadFour  = 0x64,
		NumpadFive  = 0x65,
		NumpadSix   = 0x66,
		NumpadSeven = 0x67,
		NumpadEight = 0x68,
		NumpadNine  = 0x69,

		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,

		Backspace = 0x08,
		Tab       = 0x09,
		Enter     = 0x0D,
		Shift     = 0x10,
		Control   = 0x11,
		Alt       = 0x12,
		CapsLock  = 0x14,
		Escape    = 0x1B,
		Space     = 0x20,

		NumLock    = 0x90,
		ScrollLock = 0x91,

		F1  = 0x70,
		F2  = 0x71,
		F3  = 0x72,
		F4  = 0x73,
		F5  = 0x74,
		F6  = 0x75,
		F7  = 0x76,
		F8  = 0x77,
		F9  = 0x78,
		F10 = 0x79,
		F11 = 0x7A,
		F12 = 0x7B,
		F13 = 0x7C,
		F14 = 0x7D,
		F15 = 0x7E,
		F16 = 0x7F,
		F17 = 0x80,
		F18 = 0x81,
		F19 = 0x82,
		F20 = 0x83,
		F21 = 0x84,
		F22 = 0x85,
		F23 = 0x86,
		F24 = 0x87,
	};

}