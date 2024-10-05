#pragma once

#include "Syclight/Input.h"

namespace syc
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool4 IsKeyPressedImpl(int16 keycode) override;
		virtual bool4 IsMouseButtonImpl(int16 button) override;
		virtual Pos2d GetMousePositionImpl() override;
		virtual float16 GetMouseXImpl() override;
		virtual float16 GetMouseYImpl() override;

	};
}