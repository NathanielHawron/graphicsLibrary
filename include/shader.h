#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include "glm.hpp"

/*
	Tutorial:
	Create a shader using the constructor
	(note that the graphics namespace has been removed here for clarity, but is still required):
	Shader shader = Shader("shaderName");
	You can modify the path that will be used by changing the static variables:
	std::filesystem::path *Shader::shaderFolder 	(folder that has the shaders)
	std::string Shader::vertexShaderExtension		(extension used for vertex shaders)
	std::string Shader::fragmentShaderExtension		(extension used for fragment shaders)
	Note the expected filesystem: <shaderFolder>/<name>/<name>.<extension>

	Then, bind the shader:
	shader.bind();

	Next, set your uniforms, where # is number of elements and T is type (eg 1f for 1 float or 2i for 2 ints):
	shader.setUniform#T("name", value);

	Finally, make sure you bind the shader every time before the draw calls.
*/

namespace graphics{
	class Shader{
	public:
		static std::filesystem::path *shaderFolder;
		static std::string vertexShaderExtension;
		static std::string fragmentShaderExtension;
	private:
		unsigned int ID;
		std::unordered_map<std::string, int> uniformLocationCache;
	public:
		//Shaders should be stored as <shaderFolder>/<name>/<name>.<extension>
		Shader(const std::string &name);
		~Shader();
		void bind() const;
		void unbind() const;
		unsigned int getID() const;
		void setUniform1i(const std::string &name, int value);
		void setUniform1f(const std::string &name, float value);
		void setUniform2i(const std::string &name, int value[2]);
		void setUniform2f(const std::string &name, float value[2]);
		void setUniform3i(const std::string &name, int value[3]);
		void setUniform3f(const std::string &name, float value[3]);
		void setUniform3f(const std::string &name, glm::vec3 vec);
		void setUniform4i(const std::string &name, int value[4]);
		void setUniform4f(const std::string &name, float value[4]);
		void setUniformMat4f(const std::string &name, glm::mat4 &matrix);
	private:
		std::string parseShader(const std::filesystem::path &path);
		unsigned int compileShader(unsigned int type, const std::string& source);
		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
		int getUniformLocation(const std::string& name);
	};
}