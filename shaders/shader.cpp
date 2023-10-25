#include "./shader.hpp"

std::string get_file_contents(const char* fn) {
    try {
        std::ifstream in(fn, std::ios::binary);

        if (in) {
            std::string content;
            in.seekg(0, std::ios::end);
            content.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&content[0], content.size());
            in.close();
            return content;
        }
        throw std::runtime_error("Failed to open file");
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return "";
    }
}

void Shader::SetMatrix4(const std::string& name, const glm::mat4& matrix) const {
    GLuint uniformLocation = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

Shader::Shader(const char* vertexf,const char* fragmentf){
    std::string vertex = get_file_contents(vertexf);
    std::string fragment = get_file_contents(fragmentf);

    const char* vertexsrc = vertex.c_str();
    const char* fragmentsrc = fragment.c_str();

    GLuint vertexSh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexSh,1,&vertexsrc,NULL);
    glCompileShader(vertexSh);
    compileErrors(vertexSh,"VERTEX");

    GLuint fragmentSh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentSh,1,&fragmentsrc,NULL);
    glCompileShader(fragmentSh);
    compileErrors(fragmentSh,"FRAGMENT");
    ID = glCreateProgram();

    glAttachShader(ID,vertexSh);
    glAttachShader(ID,fragmentSh);

    glLinkProgram(ID);
    compileErrors(ID,"PROGRAM");
    glDeleteShader(vertexSh);
    glDeleteShader(fragmentSh);
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}