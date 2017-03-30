#include "pch.h"

#include <Kore/IO/FileReader.h>
#include <Kore/Graphics4/Graphics.h>
#include <Kore/Graphics4/Shader.h>
#include <Kore/System.h>

#include <limits>

using namespace Kore;

namespace {
	Graphics4::Shader* vertexShader;
	Graphics4::Shader* fragmentShader;
	Graphics4::Program* program;
	Graphics4::VertexBuffer* vertices;
	Graphics4::IndexBuffer* indices;
	Graphics4::Texture* texture;
	Graphics4::TextureUnit texunit;
	Graphics4::ConstantLocation offset;

	void update() {
		Graphics4::begin();
		Graphics4::clear(Kore::Graphics4::ClearColorFlag);

		program->set();
		Graphics4::setMatrix(offset, mat3::RotationZ((float)Kore::System::time()));
		Graphics4::setVertexBuffer(*vertices);
		Graphics4::setIndexBuffer(*indices);
		Graphics4::setTexture(texunit, texture);
		Graphics4::drawIndexedVertices();

		Graphics4::end();
		Graphics4::swapBuffers();
	}
}

int kore(int argc, char** argv) {
	System::init("TextureTest", 1024, 768);
	System::setCallback(update);

	texture = new Graphics4::Texture("parrot.png");

	FileReader vs("texture.vert");
	FileReader fs("texture.frag");
	vertexShader = new Graphics4::Shader(vs.readAll(), vs.size(), Graphics4::VertexShader);
	fragmentShader = new Graphics4::Shader(fs.readAll(), fs.size(), Graphics4::FragmentShader);
	Graphics4::VertexStructure structure;
	structure.add("pos", Graphics4::Float3VertexData);
	structure.add("tex", Graphics4::Float2VertexData);
	program = new Graphics4::Program;
	program->setVertexShader(vertexShader);
	program->setFragmentShader(fragmentShader);
	program->link(structure);

	texunit = program->getTextureUnit("texsampler");
	offset = program->getConstantLocation("mvp");
	
	vertices = new Graphics4::VertexBuffer(3, structure);
	float* v = vertices->lock();
	v[ 0] = -1.0f; v[ 1] = -1.0f; v[ 2] = 0.5f; v[ 3] = 0.0f; v[ 4] = 1.0f;
	v[ 5] =  1.0f; v[ 6] = -1.0f; v[ 7] = 0.5f; v[ 8] = 1.0f; v[ 9] = 1.0f;
	v[10] = -1.0f; v[11] =  1.0f; v[12] = 0.5f; v[13] = 0.0f; v[14] = 0.0f;
	vertices->unlock();
	
	indices = new Graphics4::IndexBuffer(3);
	int* i = indices->lock();
	i[0] = 0; i[1] = 1; i[2] = 2;
	indices->unlock();

	System::start();

	return 0;
}
