# include "Memory.h"

namespace syc
{
	byte* Mallocator::s_memory_block = nullptr;
	uint64 Mallocator::s_count = 0;
	uint64 Mallocator::s_raw_size = SYC_M_DEFAULT_SIZE;
	std::stack<void_*> Mallocator::s_record_stack;

	void_ Mallocator::Init()
	{
		if (s_memory_block == nullptr)
		{
			try
			{
				s_memory_block = static_cast<byte*>(malloc(s_raw_size));
			}
			catch (const std::exception& e)
			{
				throw e;
				free(s_memory_block);
				s_memory_block = nullptr;
			}
		}
		return void_();
	}

	void_ Mallocator::Destory()
	{
		if (s_memory_block != nullptr)
		{
			free(s_memory_block);
			//memset(s_memory_block, 0, s_raw_size);
			s_memory_block = nullptr;
		}
		return void_();
	}

	void_ Mallocator::FreeMemory(void* ptr)
	{
		
	}

	void_ Mallocator::FreeMemoryForClass(void* ptr)
	{

	}


	void_ Mallocator::Realloc(uint16 size)
	{
		uint64 new_size = s_raw_size + s_raw_size * EXPANSION_FACTOR + size;
		byte* new_mem = static_cast<byte*>(malloc(new_size));
		if (new_mem)
		{
			for (uint16 i = 0; i < s_raw_size; i++)
			{
				new_mem[i] = std::move(s_memory_block[i]);
			}
		}
		else
		{
			free(new_mem);
			new_mem = nullptr;
			throw std::runtime_error("Mallocator::Realloc Fail");
		}
		free(s_memory_block);
		s_memory_block = nullptr;
		s_memory_block = new_mem;
		s_raw_size = new_size;
		std::cout << "Alloced! Now size: " << s_raw_size << std::endl;
	}
}