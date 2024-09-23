#pragma once

#ifndef __SYC_MEMORY_H__
#define __SYC_MEMORY_H__

#include <new>
#include "../Syclight/Common.h"
#include <memory>
#include "../Syclight/Core.h"

#include <stack>
#include <iostream>

#define SYC_M_DEFAULT_SIZE 10
#define EXPANSION_FACTOR 0.5

namespace syc
{
	class SYC_API Mallocator
	{
	public:
		static byte* s_memory_block;

	public:
		static void_ Init();
		static void_ Destory();
		static void_ FreeMemory(void* ptr);
		static void_ FreeMemoryForClass(void* ptr);
		template <typename T> static T* AllocMemory(uint16 size);
		template<typename T, typename... Args> static T* AllocMemoryForClass(uint16 size, Args&&... args);

	private:
		static uint64 s_count;
		static uint64 s_raw_size;
		static std::stack<void_*> s_record_stack;

	private:
		Mallocator() = default;
		~Mallocator() = default;

		static void_ Realloc(uint16 size);
	};

	template<typename T>
	inline static T* Mallocator::AllocMemory(uint16 size)
	{
		s_count += size;
		if (s_count > s_raw_size)
		{
			Realloc(size);
		}
		T* ptr = new(s_memory_block) T[size];
		s_record_stack.push(static_cast<void_*>(ptr));
		return ptr;
	}

	template<typename T, typename... Args>
	inline static T* Mallocator::AllocMemoryForClass(uint16 size, Args&&... args)
	{
		s_count += size;

		if (s_count > s_raw_size)
		{ 
			Realloc(size);
		}
		T* ptr = new(s_memory_block) T(std::forward<Args>(args)...);
		s_record_stack.push(static_cast<void_*>(ptr));
		return ptr;
	}
}

//该宏在Mallocator::Init()后使用
// t 类名，p 空的对象指针，__VA_ARGS__ 对象构造函数参数，可为空
#define SYC_NEW_CLASS(t, p, ...) p = ::syc::Mallocator::AllocMemoryForClass<t>(sizeof(t), __VA_ARGS__);
#define SYC_RELEASE_CLASS(p) if(p != nullptr){ delete(::syc::Mallocator::s_memory_block) p;p=nullptr;}
#define SYC_NEW_ARRAY(t, s, p) p =  ::syc::Mallocator::AllocMemory<t>(sizeof(t) * s);
#define SYC_RELEASE_ARRAY(p) if(p != nullptr){delete[] p;p=nullptr;}

#endif // !__SYC_MEMORY_H__
