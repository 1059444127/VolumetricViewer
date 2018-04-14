#include "AxisObject.hpp"


#include "Util.hpp"


std::string AxisObject::vertSrc= R"(
#version 330
//attribs
layout(location = 0) in vec4 pointPosition;
layout(location = 1) in vec4 pointColor;

//transforms
uniform mat4 modelViewProjectionMatrix;

//outputs
out vec4 fragColor;

//main
void main()
{
	//compute outputs
	fragColor = pointColor; 
	gl_Position = modelViewProjectionMatrix * vec4(pointPosition.x, pointPosition.y, pointPosition.z, 1.0f);
}
)";
 
std::string AxisObject::fragSrc = R"(
#version 330
//inputs
in vec4 fragColor;

//uniforms

//output
layout(location = 0) out vec4 outputColor;

//main
void main()
{
  	outputColor = fragColor;
}
)";
 
int AxisObject::programShaderObject;
int AxisObject::vertexShaderObject;
int AxisObject::fragmentShaderObject;
 
void AxisObject::InitSystem()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
	
	//make array to pointer for source code (needed for opengl )
	const char* vsrc[1];
	const char* fsrc[1];
	vsrc[0] = vertSrc.c_str();
	fsrc[0] = fragSrc.c_str();
	
	//compile vertex and fragment shaders from source
	vertexShaderObject = ogl->glCreateShader(GL_VERTEX_SHADER);
	ogl->glShaderSource(vertexShaderObject, 1, vsrc, NULL);
	ogl->glCompileShader(vertexShaderObject);
	fragmentShaderObject = ogl->glCreateShader(GL_FRAGMENT_SHADER);
	ogl->glShaderSource(fragmentShaderObject, 1, fsrc, NULL);
	ogl->glCompileShader(fragmentShaderObject);
	
	//link vertex and fragment shader to create shader program object
	programShaderObject = ogl->glCreateProgram();
	ogl->glAttachShader(programShaderObject, vertexShaderObject);
	ogl->glAttachShader(programShaderObject, fragmentShaderObject);
	ogl->glLinkProgram(programShaderObject);
	
	//Check status of shader and log any compile time errors
	int linkStatus;
	ogl->glGetProgramiv(programShaderObject, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) 
	{
		char log[5000];
		int logLen; 
		ogl->glGetProgramInfoLog(programShaderObject, 5000, &logLen, log);
		std::cerr << "AxisObject:Could not link program: " << std::endl;
		std::cerr << log << std::endl;
		ogl->glGetShaderInfoLog(vertexShaderObject, 5000, &logLen, log);
		std::cerr << "vertex shader log:\n" << log << std::endl;
		ogl->glGetShaderInfoLog(fragmentShaderObject, 5000, &logLen, log);
		std::cerr << "fragment shader log:\n" << log << std::endl;
		ogl->glDeleteProgram(programShaderObject);
		programShaderObject = 0;
	}
	else
	{
		std::cout << "AxisObject::CompileShader:compile success " << std::endl;
	}
}


AxisObject::AxisObject()
{
	
}


void AxisObject::Init()
{
	//Init Buffers and VAO for rendering	
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();

	ogl->glGenBuffers(1, &vertexBuffer);
	ogl->glGenBuffers(1, &elementBuffer);
	ogl->glGenVertexArrays(1, &vertexArrayObject);
	
	//Bind VAO
	ogl->glBindVertexArray(vertexArrayObject);
	
	//build buffers
	std::vector<Vertex> vertexData(6); 

	Vertex v;
	v.w = 1;
	v.a = 255;
	
	v.x = -1000;
	v.y = 0;
	v.z = 0;
	v.r = 255;
	v.g = 0;
	v.b = 0;
	vertexData[0] = v;
	v.x = 1000;
	v.y = 0;
	v.z = 0;
	v.r = 255;
	v.g = 0;
	v.b = 0;
	vertexData[1] = v;
	v.x = 0;
	v.y = -1000;
	v.z = 0;
	v.r = 0;
	v.g = 255;
	v.b = 0;
	vertexData[2] = v;
	v.x = 0;
	v.y = 1000;
	v.z = 0;
	v.r = 0;
	v.g = 255;
	v.b = 0;
	vertexData[3] = v;
	v.x = 0;
	v.y = 0;
	v.z = -1000;
	v.r = 0;
	v.g = 0;
	v.b = 255;
	vertexData[4] = v;
	v.x = 0;
	v.y = 0;
	v.z = 1000;
	v.r = 0;
	v.g = 0;
	v.b = 255;
	vertexData[5] = v;
	
	std::vector<unsigned int> elementData(6); 
	for(int i = 0; i < 6; i++)
	{
		elementData[i] = i;
	}
	
	ogl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	ogl->glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), (char*)&vertexData[0], GL_STATIC_DRAW);

	ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	ogl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementData.size() * sizeof(unsigned int), (char*)&elementData[0], GL_STATIC_DRAW);

	//set vertex attributes
	ogl->glEnableVertexAttribArray(0);
	ogl->glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(Vertex), (void*)((uintptr_t)0));
	ogl->glEnableVertexAttribArray(1);
	ogl->glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void*)((uintptr_t)(0 + sizeof(float) * 4 )));
	
	//Unbind VAO
	ogl->glBindVertexArray(0);
	
	//Unbind array and element buffers
	ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);
	ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void AxisObject::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	if(!visible) return; 
	
	std::cout << "Rendering Axis" << std::endl; 
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
	
	//compute mvp matrix
	glm::mat4 modelMatrix = GetModelMatrix(); 
	glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * GetModelMatrix();
		
	ogl->glEnable(GL_DEPTH_TEST);
	
	//enable backface culling 
	ogl->glEnable(GL_CULL_FACE); 
	
	//enable blending
	ogl->glEnable(GL_BLEND);
	ogl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	//bind shader
	ogl->glUseProgram(programShaderObject);
	
	//update mvp transform uniform in shader
	int modelViewProjectionMatrixLocation = ogl->glGetUniformLocation(programShaderObject, "modelViewProjectionMatrix"); 
	ogl->glUniformMatrix4fv(modelViewProjectionMatrixLocation, 1, false, glm::value_ptr(mvpMatrix));
	
	//bind VAO
	ogl->glBindVertexArray(vertexArrayObject);
	
	//draw elements
	ogl->glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
	//ogl->glDrawArrays(GL_TRIANGLES, 0, volumeSlices * 6);
	
	//unbind VAO
	ogl->glBindVertexArray(0);
	
	//unbind shader program
	ogl->glUseProgram(0);
	
	PrintGLErrors();
}


void AxisObject::Destroy()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
	ogl->glDeleteBuffers(1, &vertexBuffer);
	ogl->glDeleteBuffers(1, &elementBuffer);
	ogl->glDeleteVertexArrays(1, &vertexArrayObject);
}
