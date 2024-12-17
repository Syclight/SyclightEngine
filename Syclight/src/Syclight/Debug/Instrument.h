#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace syc
{
	struct ProfileResult
	{
		std::string Name;
		int64 Start, End;
		uint32 ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int32 m_ProfileCount;

	public:
		Instumentor()
			:m_CurrentSession(nullptr), m_ProfileCount(0)
		{}

		void_ BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ name };
		}

		void_ EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void_ WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
			{
				m_OutputStream << ",";
			}

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');
			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ",";
			m_OutputStream << "\"name\": \"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();

		}

		void_ WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {}, \"traceEvents\": [";
			m_OutputStream.flush();
		}

		void_ WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		static Instumentor& Get()
		{
			static Instumentor instance;
			return instance;
		}
	};

	class InstumentationTimer
	{
	public:
		InstumentationTimer(const char8* name)
			: m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstumentationTimer()
		{
			if (!m_Stopped)
			{
				Stop();
			}
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			int64 start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			int64 end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32 threadID = std::hash<std::thread::id>()(std::this_thread::get_id());
			Instumentor::Get().WriteProfile({ m_Name, start, end, threadID });

			m_Stopped = true;
		}

	private:
		const char8* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool8 m_Stopped;
	};
}

#define SYC_PROFILE 0

#if SYC_PROFILE
	#define SYC_PROFILE_BEGIN_SESSION(name, filepath)   ::syc::Instumentor::Get().BeginSession(name, filepath)
	#define SYC_PROFILE_END_SESSION()                   ::syc::Instumentor::Get().EndSession()
	#define SYC_PROFILE_SCOPE(name)                     ::syc::InstumentationTimer timer##__LINE__(name)
	#define SYC_PROFILE_FUNCTION()                      SYC_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define SYC_PROFILE_BEGIN_SESSION(name, filepath)
	#define SYC_PROFILE_END_SESSION()
	#define SYC_PROFILE_SCOPE(name)
	#define SYC_PROFILE_FUNCTION()
#endif // SYC_PROFILE

