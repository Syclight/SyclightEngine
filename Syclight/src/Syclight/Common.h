#pragma once

// syc base

#ifndef __SYC_COMMON_H__
#define __SYC_COMMON_H__

namespace syc
{

	typedef void                 void_;

	typedef unsigned char        byte;
	typedef bool                 bool4;

	typedef char                 int4;
	typedef short				 int8;
	typedef int					 int16;
	typedef long				 int16l;
	typedef long long			 int32;
	typedef float                float16;
	typedef double               float32;

	typedef unsigned char		 uint4;
	typedef unsigned short       uint8;
	typedef unsigned int         uint16;
	typedef unsigned long        uint16l;
	typedef unsigned long long   uint32;

	typedef char                 char4;
	typedef wchar_t              char8;


	#define Pos2d std::pair<float16, float16>
}

#endif // !__SYC_COMMON_H__