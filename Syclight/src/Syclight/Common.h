#pragma once

// syc base

#ifndef __SYC_COMMON_H__
#define __SYC_COMMON_H__

namespace syc
{

	typedef void                 void_;

	typedef unsigned char        byte;
	typedef bool                 bool32;

	typedef signed char          int4;
	typedef signed short         int16s;
	typedef signed int           int16;
	typedef signed long          int16l;
	typedef signed long long     int64;
	typedef float                float32;
	typedef double               float64;

	typedef unsigned char        uint4;
	typedef unsigned short       uint16s;
	typedef unsigned int         uint16;
	typedef unsigned long        uint16l;
	typedef unsigned long long   uint64;

	typedef char                 char1;
	typedef wchar_t              char2;


	class SycObject
	{
	public:
		uint64 m_LocalBegin, m_LocalEnd;
		byte* m_Memory;

	public:
		SycObject() : m_LocalBegin(0L), m_LocalEnd(0L), m_Memory(nullptr)
		{
		}

		~SycObject()
		{
			if (m_Memory)
			{
				for (size_t i = m_LocalBegin; i <= m_LocalEnd; i++)
				{
					m_Memory[i] = 0;
				}
				m_LocalBegin = 0;
				m_LocalEnd = 0;
			}
		}
	};
}

#endif // !__SYC_COMMON_H__