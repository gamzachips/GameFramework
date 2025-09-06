#include "Mesh.h"
#include "TestMesh.h"
#include "TestMesh.h"
#include "pch.h"
#include "TestMesh.h"

Mesh::TestMesh(D3DRenderer* renderer) : _renderer(renderer)
{
	CreateGeometry();
}

void Mesh::Init()
{
}

void Mesh::Update()
{
	UpdateTransform();
}

void Mesh::Render()
{
}

Matrix Mesh::GetWorldTransform()
{
	return Matrix();
}

void Mesh::CreateGeometry()
{
	{ //Craete Cube
		_vertices.resize(8);

		_vertices[0].position = Vector3(-0.1f, -0.1f, 0.1f);
		_vertices[0].color = Color(1.f, 0.f, 0.f, 1.f);

		_vertices[1].position = Vector3(-0.1f, 0.1f, 0.1f);
		_vertices[1].color = Color(0.f, 1.f, 0.f, 1.f);

		_vertices[2].position = Vector3(0.1f, 0.1f, 0.1f);
		_vertices[2].color = Color(0.f, 0.f, 1.f, 1.f);

		_vertices[3].position = Vector3(0.1f, -0.1f, 0.1f);
		_vertices[3].color = Color(0.5f, 0.5f, 0.f, 1.f);

		_vertices[4].position = Vector3(-0.1f, -0.1f, -0.1f);
		_vertices[4].color = Color(1.f, 0.f, 0.f, 1.f);

		_vertices[5].position = Vector3(-0.1f, 0.1f, -0.1f);
		_vertices[5].color = Color(0.f, 1.f, 0.f, 1.f);

		_vertices[6].position = Vector3(0.1f, 0.1f, -0.1f);
		_vertices[6].color = Color(0.f, 0.f, 1.f, 1.f);

		_vertices[7].position = Vector3(0.1f, -0.1f, -0.1f);
		_vertices[7].color = Color(0.5f, 0.5f, 0.f, 1.f);
	}

	{
		_vertexBuffer = make_shared<VertexBuffer>();
		_vertexBuffer->Create(_vertices, &_renderer);

		_indexBuffer = make_shared<IndexBuffer>();
		vector<unsigned int> indices 
			= { 0, 1, 2, 
				0, 2, 3 
			//TODO
				};
		_indexBuffer->Create(indices, &_renderer);
	}
}

void TestMesh::UpdateTransform()
{

}

void TestMesh::CreateMesh()
{

}
