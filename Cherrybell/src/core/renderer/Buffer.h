#pragma once

namespace CherryBell {
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Int, Int2, Int3, Int4,
		Mat3, Mat4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return sizeof(float);
		case ShaderDataType::Float2:	return sizeof(float)	* 2;
		case ShaderDataType::Float3:	return sizeof(float)	* 3;
		case ShaderDataType::Float4:	return sizeof(float)	* 4;
		case ShaderDataType::Int:		return sizeof(int);
		case ShaderDataType::Int2:		return sizeof(int)		* 2;
		case ShaderDataType::Int3:		return sizeof(int)		* 3;
		case ShaderDataType::Int4:		return sizeof(int)		* 4;
		case ShaderDataType::Mat3:		return sizeof(float)	* 3 * 3;
		case ShaderDataType::Mat4:		return sizeof(float)	* 4 * 4;
		case ShaderDataType::Bool:		return sizeof(bool);
		default: 
			CB_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	}
	
	struct BufferElement
	{
		ShaderDataType Type;
		std::string Name;
		uint32_t Size;
		size_t Offset;
		bool Normalized;

		BufferElement()
			: Type(ShaderDataType::None), Name(), Size(0), Offset(0), Normalized(false)
		{}

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Type(type), Name(name), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Bool:		return 1;
			default:
				CB_CORE_ASSERT(false, "Unknown ShaderDataType!");
				return 0;
			}
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;

		BufferLayout(const std::initializer_list<BufferElement>& elements) 
			: _elements(elements)
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return _elements; };
		inline const uint32_t GetStride() const { return _stride; }

		std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }
	private:
		void CalculateOffsetAndStride()
		{
			size_t offset = 0u;
			_stride = 0u;
			for (auto& element : _elements)
			{
				element.Offset = offset;
				offset += element.Size;
				_stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> _elements;
		uint32_t _stride = 0u;
	};

	class VertexBuffer 
	{
	public:
		virtual ~VertexBuffer() = default;

		static Ref<VertexBuffer> Create(float* vertices, size_t size);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
	};
}
