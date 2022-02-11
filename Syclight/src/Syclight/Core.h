#pragma once

#ifndef __SYC_CORE_H__

#ifdef SYC_PLATFORM_WINDOWS
	#ifdef SYC_BUILD_DLL
		#define SYC_API __declspec(dllexport)
	#else
		#define SYC_API __declspec(dllimport)
	#endif // SYC_BUILD_DLL
#else
	#error Syclight only support Windows!
#endif // SYC_PLATFORM_WINDOWS

#endif // !__SYC_CORE_H__
