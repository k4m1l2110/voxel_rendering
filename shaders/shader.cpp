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
        throw std::runtime_error("Failed to open file"); // Throw a runtime error on file open failure
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return ""; // Return an empty string to indicate an error
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

    //Create vertex shader object and get its ref
    GLuint vertexSh = glCreateShader(GL_VERTEX_SHADER);
    //Bind source code to vs object
    glShaderSource(vertexSh,1,&vertexsrc,NULL);
    //Compile sc of vs
    glCompileShader(vertexSh);
    compileErrors(vertexSh,"VERTEX");

    //Create fragment shader object and get its ref
    GLuint fragmentSh = glCreateShader(GL_FRAGMENT_SHADER);
    //Bind sc to object
    glShaderSource(fragmentSh,1,&fragmentsrc,NULL);
    //Compile fs
    glCompileShader(fragmentSh);
    compileErrors(fragmentSh,"FRAGMENT");
    //Create Shader Program Object and get its ref
    ID = glCreateProgram();

    //Attach shader objects to SPO
    glAttachShader(ID,vertexSh);
    glAttachShader(ID,fragmentSh);

    //Wrap-up all shaders together into SPO
    glLinkProgram(ID);
    compileErrors(ID,"PROGRAM");
    //Delete shaders objects as they are already in SPO
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
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
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