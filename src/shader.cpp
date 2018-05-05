#include "shader.h"

Shader::Shader(const std::string & filepath)
	: m_path(filepath)
{
	ShaderSource source = parseShader(filepath.c_str());
	m_rendererId = createShader(source.vertex, source.fragment);
}

Shader::~Shader()
{
	glDeleteProgram(m_rendererId);
}

void Shader::bind() const
{
	glUseProgram(m_rendererId);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform4f(const std::string & name, float f0, float f1,
		float f2, float f3) 
{
	int location = getUniformLocation(name);
	glUniform4f(location, f0, f1, f2, f3);
}

uint32_t Shader::createShader(const std::string & vertexShader,
			const std::string & fragmentShader)
{
	u_int32_t program = glCreateProgram();
	auto vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	auto fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


uint32_t Shader::compileShader(u_int32_t type, const std::string & source)
{
	u_int32_t id = glCreateShader(type);
	const char * src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE)
	{
		int len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
		char message[1024];

		glGetShaderInfoLog(id, len, &len, &message[0]);
		
		std::cout << "Could not compile " << (type == GL_VERTEX_SHADER ? 
				"vertex" : "fragment") << " shader!\n" << message << '\0';

		glDeleteShader(id);

		return 0;
	}
	
	return id;
}


ShaderSource Shader::parseShader(const std::string & filepath)
{
	std::ifstream file(filepath.c_str());

	if(!file.is_open())
		std::cerr << "File " << filepath << " did not open.\n";

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::stringstream ss[2];
	std::string line;
	ShaderType mode = ShaderType::NONE;

	while(std::getline(file, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos)
				mode = ShaderType::VERTEX;
			else if(line.find("fragment") != std::string::npos)
				mode = ShaderType::FRAGMENT;
		}
		else
			ss[(int)mode] << line << '\n';
	}

	return {ss[0].str(), ss[1].str()};
}

int32_t Shader::getUniformLocation(const std::string & name)
{
	if(m_cache.find(name) != m_cache.end())
		return m_cache[name];

	int location = glGetUniformLocation(m_rendererId, name.c_str());
	if(location == -1)
		std::cerr << "Warning: uniform " << name << " does not exist!\n";
	m_cache[name] = location;

	return location;
}
