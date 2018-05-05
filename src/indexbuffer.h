#pragma once
#include <cstdint>

class IndexBuffer
{
public:
	IndexBuffer(const uint32_t * data, uint32_t count);
	~IndexBuffer();

	void bind();
	void unbind();
private:
	uint32_t m_rendererId;
	uint32_t m_count;
};
