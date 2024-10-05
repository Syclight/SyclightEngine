#pragma once

#include "Syclight/Common.h"
#include "Syclight/Core.h"

namespace syc
{
	class SYC_API Input
	{
	public:
		inline static bool4 IsKeyPressed(int16 keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool4 IsMouseButtonPressed(int16 button) { return s_Instance->IsMouseButtonImpl(button); }
		inline static Pos2d GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float16 GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float16 GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool4 IsKeyPressedImpl(int16 keycode) = 0;
		virtual bool4 IsMouseButtonImpl(int16 button) = 0;
		virtual Pos2d GetMousePositionImpl() = 0;
		virtual float16 GetMouseXImpl() = 0;
		virtual float16 GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}