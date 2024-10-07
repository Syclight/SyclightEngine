#pragma once

// syc base

#ifndef __SYC_COMMON_H__
#define __SYC_COMMON_H__

namespace syc
{

	typedef void                 void_;

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


	#define Pos2d std::pair<float32, float32>
}

#endif // !__SYC_COMMON_H__