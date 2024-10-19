#pragma once

#include "Syclight/Core/Input.h"

namespace syc
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool8 IsKeyPressedImpl(int32 keycode) override;
		virtual bool8 IsMouseButtonImpl(int32 button) override;
		virtual std::pair<float32, float32> GetMousePositionImpl() override;
		virtual float32 GetMouseXImpl() override;
		virtual float32 GetMouseYImpl() override;

	};
}