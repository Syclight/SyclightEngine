#pragma once

#ifndef __SYC_CORE_H__

#include "PlatformDetection.h"

#include <memory>

//#ifdef _WIN32
//	#ifdef _WIN64
//		#define SYC_PLATFORM_WINDOWS
//	#else
//		#error "Syclight only support Windows x64!"
//	#endif // _WIN64
//#elif defined(__APPLE__) || defined(__MACH__)
//	#include <TargetConditionals.h>
//	#if TARGET_IPHONE_SIMULATOR == 1
//		#error "IOS simulator is not supported!"
//	#elif TARGET_OS_IPHONE == 1
//		#define SYC_PLATFORM_IOS
//		#error "IOS is not supported!"
//	#elif TARGET_OS_MAC == 1
//		#define SYC_PLATFORM_MACOS
//		#error "MACOS is not supported!"
//	#else
//		#error "Unknown Apple platform!"
//	#endif
//
//#elif defined(__ANDORROID__)
//	#define SYC_PLATFORM_ANDROID
//	#error "Android is not supported!"
//#elif defined(__linux__)
//	#define SYC_PLATFORM_LINUX
//	#error "Linux is not supported!"
//#else
//	#error "Unknown platform!"
//#endif //_WIN32

#if defined(SYC_PLATFORM_WINDOWS)
	#if SYC_DYNAMIC_LINK
		#ifdef SYC_BUILD_DLL
		#define SYC_API __declspec(dllexport)
	#else
		#define SYC_API __declspec(dllimport)
		#endif // SYC_BUILD_DLL
	#else // SYC_DYNAMIC_LINK
		#define SYC_API
	#endif
#endif // SYC_PLATFORM_WINDOWS


//#ifdef SYC_DEBUG
//	#define SYC_ENABLE_ASSERTS
//#endif // DEBUG

#ifdef SYC_DEBUG
#if defined(SYC_PLATFORM_WINDOWS)
#define SYC_DEBUGBREAK() __debugbreak()
#elif defined(SYC_PLATFORM_LINUX)
#include <signal.h>
#define SYC_DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define SYC_ENABLE_ASSERTS
#else
#define SYC_DEBUGBREAK()
#endif

#define SYC_EXPAND_MACRO(x) x
#define SYC_STRINGIFY_MACRO(x) #x

//#ifdef SYC_ENABLE_ASSERTS
//	#define SYC_ASSERT(x, ...) { if(!(x)) { SYC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
//	#define SYC_CORE_ASSERT(x, ...) { if(!(x)) { SYC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
//#else
//	#define SYC_ASSERT(x, ...)
//	#define SYC_CORE_ASSERT(x, ...)
//#endif // define SYC_ENABLE_ASSERTS

#define BIT(x) (1 << x)

//#define SYC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define SYC_BIND_EVENT_FN(fn) [this](auto&&... args) { return this->fn(std::forward<decltype(args)>(args)...); }

#define SYCNAMESPEC_BEGIN   namespace syc {
#define SYCNAMESPEC_END     }

namespace syc
{
	typedef void                 void_;
	typedef size_t               size;

	typedef unsigned char        byte;
	typedef bool                 bool8;

	typedef char                 int8;
	typedef short				 int16;
	typedef int					 int32;
	typedef long				 int32l;
	typedef long long			 int64;
	typedef float                float32;
	typedef double               float64;

	typedef unsigned char		 uint8;
	typedef unsigned short       uint16;
	typedef unsigned int         uint32;
	typedef unsigned long        uint32l;
	typedef unsigned long long   uint64;

	typedef char                 char8;
	typedef wchar_t              char16;

	//======================================================
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#define WIND_WIDTH 1920
#define WIND_HEIGHT 1080

const auto ASPECT_RATIO = (syc::float32)WIND_WIDTH / (syc::float32)WIND_HEIGHT;

#include "Assert.h"

#endif // !__SYC_CORE_H__
