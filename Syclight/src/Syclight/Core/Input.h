#pragma once

#include "Syclight/Core/Core.h"

namespace syc
{
	class SYC_API Input
	{
	public:
		inline static bool8 IsKeyPressed(int32 keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool8 IsMouseButtonPressed(int32 button) { return s_Instance->IsMouseButtonImpl(button); }
		inline static std::pair<float32, float32> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float32 GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float32 GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool8 IsKeyPressedImpl(int32 keycode) = 0;
		virtual bool8 IsMouseButtonImpl(int32 button) = 0;
		virtual std::pair<float32, float32> GetMousePositionImpl() = 0;
		virtual float32 GetMouseXImpl() = 0;
		virtual float32 GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}