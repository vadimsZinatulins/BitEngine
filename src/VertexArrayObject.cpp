#include "VertexArrayObject.h"

#include <glad/glad.h>

namespace be::graphics {

VertexArrayObject VertexArrayObject::create() {
	VertexArrayObject vao;

	vao.init();

	return vao;
}

void VertexArrayObject::init() {
	if(!m_id) {
		glGenVertexArrays(1, &m_id);
	}
}

void VertexArrayObject::clear() {
	if(m_id) {
		if(m_ebo) {
			glDeleteBuffers(1, &m_ebo);
			m_ebo = 0;
		}

		glDeleteBuffers(m_buffers.size(), m_buffers.data());
		
		glDeleteVertexArrays(1, &m_id);
		m_id = 0;

		m_vertexCount = 0;
	}
}

void VertexArrayObject::enable() {
	if(!m_id) {
		return;
	}

	glBindVertexArray(m_id);
}

void VertexArrayObject::disable() {
	glEnableVertexAttribArray(0);
}

void VertexArrayObject::draw() {
	if(m_ebo) {
		glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, nullptr);
	} else {
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void VertexArrayObject::addAttribute(std::vector<char> data, int componentsPerVertex) {
	addAttribute(data.data(), data.size(), componentsPerVertex, GL_BYTE, sizeof(char));
}

void VertexArrayObject::addAttribute(std::vector<unsigned char> data, int componentsPerVertex) {
	addAttribute(data.data(), data.size(), componentsPerVertex, GL_UNSIGNED_BYTE, sizeof(unsigned char));
}

void VertexArrayObject::addAttribute(std::vector<short> data, int componentsPerVertex) {
	addAttribute(data.data(), data.size(), componentsPerVertex, GL_SHORT, sizeof(short));
}

void VertexArrayObject::addAttribute(std::vector<unsigned short> data, int componentsPerVertex) {
	addAttribute(data.data(), data.size(), componentsPerVertex, GL_UNSIGNED_SHORT, sizeof(unsigned short));
}

void VertexArrayObject::addAttribute(std::vector<int> data, int componentsPerVertex) {
	addAttribute(data.data(), data.size(), componentsPerVertex, GL_INT, sizeof(int));
}

void VertexArrayObject::addAttribute(std::vector<unsigned int> data, int componentsPerVertex) {
	addAttribute(data.data(), data.size(), componentsPerVertex, GL_UNSIGNED_INT, sizeof(unsigned int));
}

void VertexArrayObject::addAttribute(std::vector<float> data, int componentsPerVertex) {
	addAttribute(data.data(), data.size(), componentsPerVertex, GL_FLOAT, sizeof(float));
}

void VertexArrayObject::addAttribute(void *data, long dataSize, int componentsPerVertex, int type, int typeSize) {
	// Make sure the Vertex Arary Object has been initialized before setting attributes
	if(!m_id) {
		return;
	}

	// Get the number of vertices in the attribute
	unsigned int vertexCount = dataSize / componentsPerVertex;

	if(!m_vertexCount) {
		// If the number of vertices hasn't been set then set it
		m_vertexCount = vertexCount;
	} else if(vertexCount != m_vertexCount) {
		// If the number of vertices is different from what has been sent then the data is invalid
		return;
	}

	glBindVertexArray(m_id);

	unsigned int buffer;
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, dataSize * typeSize, data, GL_STATIC_DRAW);

	glVertexAttribPointer(m_buffers.size(), componentsPerVertex, type, GL_FALSE, componentsPerVertex * typeSize, (void*)0);
	glEnableVertexAttribArray(m_buffers.size());

	m_buffers.push_back(buffer);

	glBindVertexArray(0);
}

void VertexArrayObject::setElementBuffer(std::vector<unsigned int> data) {
	// Make sure the Vertex Arary Object has been initialized before setting attributes
	if(!m_id) {
		return;
	}

	// Make sure that Element Buffer Object hasn't been set yet
	if(m_ebo) {
		return;
	}

	m_indicesCount = data.size();

	glBindVertexArray(m_id);

	glGenBuffers(1, &m_ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size(), data.data(), GL_STATIC_DRAW);

	glBindVertexArray(m_id);
}

}
