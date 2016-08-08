#include"types.h"
int main(int argc, char **argv)
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	// ��������ָ����Ҫ��Ⱦ�����������ε�λ����Ϣ.
	GLfloat  vertices[NumVertices][2] = {
		{ -0.90, -0.90 },  // Triangle 1
		{ 0.85, -0.90 },
		{ -0.90,  0.85 },
		{ 0.90, -0.85 },  // Triangle 2
		{ 0.90,  0.90 },
		{ -0.85,  0.90 }
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		vertices, GL_STATIC_DRAW);
}