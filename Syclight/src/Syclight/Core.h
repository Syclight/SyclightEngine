#pragma once

#ifndef __SYC_CORE_H__

#include <memory>

#ifdef SYC_PLATFORM_WINDOWS
#if SYC_DYNAMIC_LINK
	#ifdef SYC_BUILD_DLL
		#define SYC_API __declspec(dllexport)
	#else
		#define SYC_API __declspec(dllimport)
	#endif // SYC_BUILD_DLL
#else // SYC_DYNAMIC_LINK
	#define SYC_API
#endif
	
#else
	#error Syclight only support Windows!
#endif // SYC_PLATFORM_WINDOWS

#ifdef SYC_DEBUG
	#define SYC_ENABLE_ASSERTS
#endif // DEBUG


#ifdef SYC_ENABLE_ASSERTS
	#define SYC_ASSERT(x, ...) { if(!(x)) { SYC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SYC_CORE_ASSERT(x, ...) { if(!(x)) { SYC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SYC_ASSERT(x, ...)
	#define SYC_CORE_ASSERT(x, ...)
#endif // define SYC_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define SYC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define SYCNAMESPEC_BEGIN   namespace syc {
#define SYCNAMESPEC_END     }

namespace syc
{
	typedef void                 void_;
	typedef size_t               size1d;

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

	template<typename T>
	using Ref = std::shared_ptr<T>;
}

#endif // !__SYC_CORE_H__
