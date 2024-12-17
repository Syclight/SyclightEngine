#pragma once

namespace syc
{
	enum class SYC_API ShaderDataType
	{
		None = 0, 
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static SYC_API uint32 ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case syc::ShaderDataType::Float:
			return 4;
		case syc::ShaderDataType::Float2:
			return 4 * 2;
		case syc::ShaderDataType::Float3:
			return 4 * 3;
		case syc::ShaderDataType::Float4:
			return 4 * 4;
		case syc::ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case syc::ShaderDataType::Mat4:
			return 4 * 4 * 3;
		case syc::ShaderDataType::Int:
			return 4;
		case syc::ShaderDataType::Int2:
			return 4 * 2;
		case syc::ShaderDataType::Int3:
			return 4 * 3;
		case syc::ShaderDataType::Int4:
			return 4 * 4;
		case syc::ShaderDataType::Bool:
			return 1;
		default:
			SYC_CORE_ASSERT(false, "Unkonwn ShaderDataType!");
			return 0;
		}
	}

	struct  SYC_API BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32 Size;
		uint32 Offset;
		bool8 Normalized;

		BufferElement() {}

		BufferElement(ShaderDataType type, const std::string& name, bool8 normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32 GetComponentCount() const
		{
			switch (Type)
			{
			case syc::ShaderDataType::Float:
				return 1;
			case syc::ShaderDataType::Float2:
				return 2;
			case syc::ShaderDataType::Float3:
				return 3;
			case syc::ShaderDataType::Float4:
				return 4;
			case syc::ShaderDataType::Mat3:
				return 3 * 3 ;
			case syc::ShaderDataType::Mat4:
				return 4 * 4;
			case syc::ShaderDataType::Int:
				return 1;
			case syc::ShaderDataType::Int2:
				return 2;
			case syc::ShaderDataType::Int3:
				return 3;
			case syc::ShaderDataType::Int4:
				return 4;
			case syc::ShaderDataType::Bool:
				return 1;
			default:
				SYC_CORE_ASSERT(false, "Unkonwn ShaderDataType!");
				return 0;
			}
		}
	};

	class SYC_API BufferLayout
	{
	public:
		BufferLayout() {}

		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements) 
		{
			CalculateOffsetAndStride();
		}

		inline uint32 GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		
	private:
		void_ CalculateOffsetAndStride()
		{
			uint32 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

	private:
		std::vector<BufferElement> m_Elements; 
		uint32 m_Stride = 0;
	};

	class SYC_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void_ Bind() const = 0;
		virtual void_ Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void_ SetLayout(const BufferLayout& layout) = 0;

		virtual void_ SetData(const void* data, uint32_t size) = 0;

		static Ref<VertexBuffer> Create(uint32 size);
		static Ref<VertexBuffer> Create(float32* vertices, size1d size);
	};

	class SYC_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void_ Bind() const = 0;
		virtual void_ Unbind() const = 0;

		virtual uint32 GetCount() const = 0;

		static Ref<IndexBuffer> Create(uint32* indices, size1d count);
	};
}