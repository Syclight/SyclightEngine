#pragma once

namespace syc {
	class SYC_API Timestep
	{
	public:
		Timestep(float32 time = 0.0f)
			: m_Time(time)
		{}

		operator float32() const { return m_Time; }

		float32 GetSeconds() const { return m_Time; }
		float32 GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float32 m_Time;
	};
}