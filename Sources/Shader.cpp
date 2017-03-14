#include "pch.h"

#include <Kore/IO/FileReader.h>
#include <Kore/Graphics/Graphics.h>
#include <Kore/Graphics/Shader.h>
#include <Kore/System.h>

#include <limits>

using namespace Kore;

namespace {
	Shader* vertexShader;
	Shader* fragmentShader;
	Program* program;
	VertexBuffer* vertices;
	IndexBuffer* indices;
	Texture* texture;
	TextureUnit texunit;
	ConstantLocation offset;

	void update() {
		Graphics::begin();
		Graphics::clear(Kore::Graphics::ClearColorFlag);

		program->set();
		Graphics::setMatrix(offset, mat3::RotationZ((float)Kore::System::time()));
		Graphics::setVertexBuffer(*vertices);
		Graphics::setIndexBuffer(*indices);
		Graphics::setTexture(texunit, texture);
		Graphics::drawIndexedVertices();

		Graphics::end();
		Graphics::swapBuffers();
	}
}

int kore(int argc, char** argv) {
	System::init("TextureTest", 1024, 768);
	System::setCallback(update);

	texture = new Texture("parrot.png");

	FileReader vs("texture.vert");
	FileReader fs("texture.frag");
	vertexShader = new Shader(vs.readAll(), vs.size(), VertexShader);
	fragmentShader = new Shader(fs.readAll(), fs.size(), FragmentShader);
	VertexStructure structure;
	structure.add("pos", Float3VertexData);
	structure.add("tex", Float2VertexData);
	program = new Program;
	program->setVertexShader(vertexShader);
	program->setFragmentShader(fragmentShader);
	program->link(structure);

	texunit = program->getTextureUnit("texsampler");
	offset = program->getConstantLocation("mvp");
	
	vertices = new VertexBuffer(3, structure);
	float* v = vertices->lock();
	v[ 0] = -1.0f; v[ 1] = -1.0f; v[ 2] = 0.5f; v[ 3] = 0.0f; v[ 4] = 1.0f;
	v[ 5] =  1.0f; v[ 6] = -1.0f; v[ 7] = 0.5f; v[ 8] = 1.0f; v[ 9] = 1.0f;
	v[10] = -1.0f; v[11] =  1.0f; v[12] = 0.5f; v[13] = 0.0f; v[14] = 0.0f;
	vertices->unlock();
	
	indices = new IndexBuffer(3);
	int* i = indices->lock();
	i[0] = 0; i[1] = 1; i[2] = 2;
	indices->unlock();

	System::start();

	return 0;
}
