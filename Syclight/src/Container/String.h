#pragma once

#ifndef __SYC_STRING_H__
#define __SYC_STRING_H__

#include "../Syclight/Common.h"
#include "Memory.h"
#include "../Syclight/Core.h"
#include <vector>
#include <stack>

namespace syc
{
	class SYC_API StrContainer
	{
	public:
		static std::vector<const char1*>  s_str_container;

	public:
		static uint16 Insert(const char1* str);
		static void_ Remove(uint16 index);

	private:
		StrContainer() = default;
		~StrContainer() = default;

	private:
		static std::stack<uint16> s_empty_index_record_stack;
	};

	class SYC_API WStrContainer
	{
	public:
		static std::vector<const char2*>  s_wstr_container;

	public:
		static uint16 Insert(const char2* str);
		static void_ Remove(uint16 index);

	private:
		WStrContainer() = default;
		~WStrContainer() = default;

	private:
		static std::stack<uint16> s_empty_index_record_stack;
	};

	class SYC_API SyString
	{
	public:
		SyString(const char1* str);
		SyString(const char1* str, uint16 begin, uint16 end);
		SyString(const char1* str, uint16 end);
		~SyString();

		uint16 Begin() const noexcept;
		uint16 End() const noexcept;
		const char1* C_Str() const noexcept;

	private:
		uint16 m_begin, m_end, m_index;
		char1* m_c_str;
	};

	class SYC_API SyStringW
	{
	public:
		SyStringW(const char2* str);
		~SyStringW();

	private:
		uint16 m_begin, m_end, m_index;

	};
}

#endif // !__SYC_STRING_H__

