#pragma once
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"


class VertexArray 
{
public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer & vb, const VertexBufferLayout & layout);

	void bind() const;
	void unbind() const;
private:
	uint32_t m_rendererId;

};
