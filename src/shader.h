#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "renderer.h"

struct ShaderSource
{
	std::string vertex, fragment;
};

class Shader
{
public:
	Shader(const std::string & filepath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform4f(const std::string & name, float f0, float f1,
			float f2, float f3);

private:
	uint32_t createShader(const std::string & vertexShader, 
			const std::string & fragmentShader);
	uint32_t compileShader(uint32_t type, const std::string & source);
	ShaderSource parseShader(const std::string & filepath);

	int32_t getUniformLocation(const std::string & name);

	std::unordered_map<std::string, uint32_t> m_cache;

	uint32_t m_rendererId;
	std::string m_path;
};

