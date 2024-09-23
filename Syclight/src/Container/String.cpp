#include "String.h"

namespace syc
{
#define CONTAINER_INSERT(NAME) if (s_empty_index_record_stack.empty())\
		{\
			NAME.emplace_back(str);\
			return NAME.size() - 1;\
		}\
		uint16 index = s_empty_index_record_stack.top();\
		s_empty_index_record_stack.pop();\
		NAME[index] = str; return index

#define CONTAINER_REMOVE(INDEX) s_empty_index_record_stack.push(INDEX); return void_()

	std::stack<uint16>         StrContainer::s_empty_index_record_stack;
	std::stack<uint16>         WStrContainer::s_empty_index_record_stack;
	std::vector<const char1*>  StrContainer::s_str_container{ "/0" };
	std::vector<const char2*>  WStrContainer::s_wstr_container{ L"/0" };

	uint16 StrContainer::Insert(const char1* str)
	{
		CONTAINER_INSERT(s_str_container);
	}

	void_ StrContainer::Remove(uint16 index)
	{
		CONTAINER_REMOVE(index);
	}

	uint16 WStrContainer::Insert(const char2* str)
	{
		CONTAINER_INSERT(s_wstr_container);
	}

	void_ WStrContainer::Remove(uint16 index)
	{
		CONTAINER_REMOVE(index);
	}

	SyString::SyString(const char1* str) :
		m_begin(0u), m_c_str(nullptr)
	{
		m_index = StrContainer::Insert(str);
		m_end = strlen(str);
	}

	SyString::SyString(const char1* str, uint16 begin, uint16 end) :
		m_begin(begin), m_end(end), m_c_str(nullptr)
	{
		m_index = StrContainer::Insert(str);
	}

	SyString::SyString(const char1* str, uint16 end) :
		m_begin(0u), m_end(end), m_c_str(nullptr)
	{
		m_index = StrContainer::Insert(str);
	}

	SyString::~SyString()
	{
		if (m_index != 0u)
		{
			StrContainer::Remove(m_index);
			m_index = 0u;
			m_begin = 0u;
			m_end = 0u;
		}
	}
	
	uint16 SyString::Begin() const noexcept
	{
		return m_begin;
	}

	uint16 SyString::End() const noexcept
	{
		return m_end;
	}

	const char1* SyString::C_Str() const noexcept
	{
		return StrContainer::s_str_container[m_index];
	}

	SyStringW::SyStringW(const char2* str) :
		m_begin(0u), m_index(0u)
	{
		m_index = WStrContainer::Insert(str);
		m_end = wcslen(str);
	}

	SyStringW::~SyStringW()
	{
		if (m_index != 0u)
		{
			WStrContainer::Remove(m_index);
			m_index = 0u;
			m_begin = 0u;
			m_end = 0u;
		}
	}
}
