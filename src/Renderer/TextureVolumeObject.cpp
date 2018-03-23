#include "TextureVolumeObject.hpp"


std::string TextureVolumeObject::vertSrc= R"(
#version 330
//attribs
layout(location = 0) in vec3 pointPosition;
//transforms
uniform mat4 modelViewProjectionMatrix;
uniform float brightness;
uniform float contrast;
//outputs
out vec4 fragmentPosition;
//main
void main()
{
	//compute outputs
	fragmentPosition = vec4(pointPosition.x, pointPosition.y, pointPosition.z, 1.0f);
	gl_Position = modelViewProjectionMatrix * vec4(pointPosition.x, pointPosition.y, pointPosition.z, 1.0f);
}
)";
 
std::string TextureVolumeObject::fragSrc = R"(
#version 330
//inputs
in vec4 fragmentPosition;
//uniforms
uniform sampler3D volumeTexture;
//main
void main()
{
  	gl_FragColor = texture3D(volumeTexture, fragmentPosition.xyz);
}
)";
 
int TextureVolumeObject::programShaderObject;
int TextureVolumeObject::vertexShaderObject;
int TextureVolumeObject::fragmentShaderObject;
 
void TextureVolumeObject::InitSystem()
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
		std::cerr << "PointCloud:Could not link program: " << std::endl;
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
		std::cout << "TextureVolumeObject::CompileShader:compile success " << std::endl;
	}
}


TextureVolumeObject::TextureVolumeObject(unsigned int slices)
{
	volumeSlices = slices;
	brightness = 0;
	contrast = 1;
}


void TextureVolumeObject::Init()
{
	//Init Buffers and VAO for rendering	
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();

	ogl->glGenBuffers(1, &vertexBuffer);
	ogl->glGenBuffers(1, &elementBuffer);
	ogl->glGenVertexArrays(1, &vertexArrayObject);
	
	//Bind VAO
	ogl->glBindVertexArray(vertexArrayObject);
	
	//build buffers
	std::vector<Vertex> vertexData(4 * volumeSlices); 
	for(int i = 0; i < volumeSlices; i++)
	{
		Vertex v;
		v.w = 1.0;
		
		v.z = (double)i / (double)volumeSlices * 2.0 - 1.0;
		v.x = -1.0;
		v.y = -1.0;
		vertexData[i * 4 + 0] = v;
		v.x = 1.0;
		v.y = -1.0;
		vertexData[i * 4 + 1] = v;
		v.x = 1.0;
		v.y = 1.0;
		vertexData[i * 4 + 2] = v;
		v.x = -1.0;
		v.y = 1.0;
		vertexData[i * 4 + 3] = v;
	}
	
	std::vector<unsigned int> elementData(volumeSlices * 6); 
	for(int i = 0; i < volumeSlices; i++)
	{
		elementData[i * 6 + 0] = i * 4  + 0;
		elementData[i * 6 + 1] = i * 4  + 1;
		elementData[i * 6 + 2] = i * 4  + 2;
		elementData[i * 6 + 3] = i * 4  + 2;
		elementData[i * 6 + 4] = i * 4  + 3;
		elementData[i * 6 + 5] = i * 4  + 0;
	}
	
	ogl->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	ogl->glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), (char*)&vertexData[0], GL_STATIC_DRAW);

	ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	ogl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementData.size() * sizeof(unsigned int), (char*)&elementData[0], GL_STATIC_DRAW);

	//set vertex attributes
	ogl->glEnableVertexAttribArray(0);
	ogl->glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(Vertex), (void*)((uintptr_t)0));
	
	//Unbind VAO
	ogl->glBindVertexArray(0);
	
	//Unbind array and element buffers
	ogl->glBindBuffer(GL_ARRAY_BUFFER, 0);
	ogl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	volumeTexture = NULL; 
}


void TextureVolumeObject::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
	
	//compute mvp matrix
	glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * GetModelMatrix();
		
	//disable writting to depth buffer
	ogl->glEnable(GL_DEPTH_TEST);
	ogl->glDepthMask(GL_FALSE);
	
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
	
	//update 3d texture
	int volumeTextureLocation = ogl->glGetUniformLocation(programShaderObject, "volumeTexture"); 
	ogl->glUniform1i(volumeTextureLocation, 0);
	ogl->glActiveTexture(GL_TEXTURE0 + 0);
	
	if(volumeTexture != NULL)
	{
		ogl->glBindTexture(GL_TEXTURE_3D, volumeTexture->GetTextureId());
	}
	else
	{
		ogl->glBindTexture(GL_TEXTURE_3D, 0);
	}
	
	//update material uniforms
	int materialAlphaLocation = ogl->glGetUniformLocation(programShaderObject, "brightness"); 
	ogl->glUniform1f(materialAlphaLocation, brightness);
	int materialPointSizeLocation = ogl->glGetUniformLocation(programShaderObject, "contrast"); 
	ogl->glUniform1f(materialPointSizeLocation, contrast);
	
	//bind VAO
	ogl->glBindVertexArray(vertexArrayObject);
	
	//draw elements
	ogl->glDrawElements(GL_TRIANGLES, volumeSlices * 6, GL_UNSIGNED_INT, 0);
	//ogl->glDrawArrays(GL_TRIANGLES, 0, volumeSlices * 6);
	
	//unbind VAO
	ogl->glBindVertexArray(0);
	
	//unbind shader program
	ogl->glUseProgram(0);
	
	//reset opengl state
	//enable writting to depth buffer
	ogl->glDepthMask(GL_TRUE);
}


void TextureVolumeObject::Destroy()
{
	OPENGL_FUNC_MACRO* ogl = QOpenGLContext::currentContext()->versionFunctions<OPENGL_FUNC_MACRO>();
	ogl->glDeleteBuffers(1, &vertexBuffer);
	ogl->glDeleteBuffers(1, &elementBuffer);
	ogl->glDeleteVertexArrays(1, &vertexArrayObject);
}


void TextureVolumeObject::SetVolumeTexture(Texture3D* vt)
{
	volumeTexture = vt; 
}
