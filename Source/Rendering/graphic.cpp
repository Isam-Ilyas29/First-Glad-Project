#include "graphic.hpp"

#include <GLFW/glfw3.h>


/*----------------------------------------------------------------------------------*/

// Context for graphics (glad)

namespace context {

	namespace graphics {

		bool initialiseGraphics() {
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				std::cerr << "Failed to initialize GLAD" << std::endl;
				return false;
			}
			glEnable(GL_DEPTH_TEST);
			return true;
		}
	}
}

/*----------------------------------------------------------------------------------*/

// Error handling

void gladCheckError(const char* file, u32 line_number) {
	GLenum error_code = glad_glGetError(); /// or glGetError() 

	if (error_code != GL_NO_ERROR) {
		std::cerr << '[' << std::filesystem::path(file).generic_string() << ']' << " [" << "Line. " << line_number << ']' << " [GLAD ERROR] " << error_code << std::endl;
	}
}

/*----------------------------------------------------------------------------------*/

// VERTEX

void VertexData::setVBO(unsigned int VBO) {
	mVBO = VBO;
}
void VertexData::setVAO(unsigned int VAO) {
	mVAO = VAO;
}
void VertexData::setEBO(unsigned int EBO) {
	mEBO = EBO;
}

VertexData::~VertexData() {
	if (mVBO != 0) {
		glDeleteBuffers(1, &mVBO);
	}
	if (mEBO != 0) {
		glDeleteBuffers(1, &mEBO);
	}
	if (mVAO != 0) {
		glDeleteVertexArrays(1, &mVAO);
	}
}

void VertexData::bindVBO(const std::vector<f32>& vertices, unsigned int VBO) {		// Accepts Vertices
	glBindBuffer(GL_ARRAY_BUFFER, VBO);											
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
}
void VertexData::bindVBO(f32 vertices[], size_t size, unsigned int VBO) {				// Accepts Arrays
	glBindBuffer(GL_ARRAY_BUFFER, VBO);									   
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
void VertexData::bindEBO(const std::vector<u8>& indices, unsigned int EBO) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW);
}
void VertexData::bindVAO(unsigned int VAO) {
	glBindVertexArray(VAO);
}

// ATTRIBUTES

void VertexData::positionAttrib(unsigned int location, size_t stride) {
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(location);
}

void VertexData::colourAttrib(unsigned int location, size_t stride) {
	glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(location);
}

void VertexData::textureAttrib(unsigned int location, size_t stride) {
	glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(location);
}


/*----------------------------------------------------------------------------------*/

// Transform class

Transform::Transform(u16 rotation_axis, glm::vec3 position, glm::quat rotation, glm::vec3 scale)
	: mRotationAxis(rotation_axis), mPosition(position), mTransform(glm::mat4(1.f)), mRotation(rotation), mScale(scale) {

	createModel();
}

void Transform::createModel() {
	auto const originalMat = glm::mat4(1.0f);

	auto const scale = glm::scale(originalMat, mScale);
	auto const translate = glm::translate(originalMat, mPosition);
	auto const rotate = glm::toMat4(mRotation);

	mTransform = translate * rotate * scale;
}

const glm::mat4 Transform::getModel() const {
	return mTransform;
}

/*----------------------------------------------------------------------------------*/

// Set background colour

void setBackgroundColour(f64 r, f64 g, f64 b, f64 a) {
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*----------------------------------------------------------------------------------*/