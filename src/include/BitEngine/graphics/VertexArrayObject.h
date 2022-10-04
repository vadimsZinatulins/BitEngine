#pragma once

#include <vector>

namespace be::graphics {

class VertexArrayObject {
public:
	VertexArrayObject() = default;
	~VertexArrayObject() = default;

	static VertexArrayObject create();

	void init();
	void clear();

	void enable();
	void disable();

	void draw();

	void addAttribute(std::vector<char> data, int componentsPerVertex);
	void addAttribute(std::vector<unsigned char> data, int componentsPerVertex);
	void addAttribute(std::vector<short> data, int componentsPerVertex);
	void addAttribute(std::vector<unsigned short> data, int componentsPerVertex);
	void addAttribute(std::vector<int> data, int componentsPerVertex);
	void addAttribute(std::vector<unsigned int> data, int componentsPerVertex);
	void addAttribute(std::vector<float> data, int componentsPerVertex);

	void setElementBuffer(std::vector<unsigned int> data);
private:
	void addAttribute(void *data, long dataSize, int componentsPerVertex, int type, int typeSize);

	std::vector<unsigned int> m_buffers {};
	unsigned int m_id { 0 };
	unsigned int m_vertexCount { 0 };

	unsigned int m_ebo { 0 };
	unsigned int m_indicesCount { 0 };
};

}
