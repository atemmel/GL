#pragma once
#include <GL/glew.h>
#include <cassert>
#include <vector>

struct VertexBufferElement
{
	static uint32_t getTypeSize(uint32_t type)
	{
		switch(type)
		{
			case GL_FLOAT:		return sizeof(float);
			case GL_UNSIGNED_INT:	return sizeof(uint32_t);
			case GL_UNSIGNED_BYTE:	return sizeof(uint8_t);
		}

		assert(false);
		return 0;
	}

	uint32_t count;
	uint32_t type;
	uint8_t  normalized;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		: m_stride(0) {}

	void push(uint32_t count, uint32_t type)
	{
		bool normalized = type == GL_UNSIGNED_BYTE;

		m_elements.push_back({count, type, normalized});

		m_stride += count * VertexBufferElement::getTypeSize(type);
		
	}

	inline uint32_t getStride() const { return m_stride; }

	inline std::vector<VertexBufferElement> getElements() const
	{
		return m_elements;
	}
	
private:
	std::vector<VertexBufferElement> m_elements;
	uint32_t m_stride;
};

