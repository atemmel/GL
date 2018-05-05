#include "vertexarray.h"
#include "renderer.h"
#include "vertexbufferlayout.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_rendererId);
	glBindVertexArray(m_rendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_rendererId);
}

void VertexArray::addBuffer(const VertexBuffer & vb, 
		const VertexBufferLayout & layout)
{
	bind();
	vb.bind();

	const auto & elements = layout.getElements();
	auto size = elements.size();
	uint32_t offset = 0;

	for(uint32_t i = 0; i < size; i++)
	{
		const auto & element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, 
				element.normalized, layout.getStride(), 
				(const void*)offset);

		offset += element.count * element.getTypeSize(element.type);;
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(m_rendererId);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
