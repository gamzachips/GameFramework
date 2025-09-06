#pragma once
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"


class SkyboxCube : public Mesh
{
public:
    SkyboxCube(ComPtr<ID3D11Device> device) : Mesh(device)
    {
        _vertices = {
            { Vector3(-1.0f,  1.0f, -1.0f)}, 
            { Vector3(1.0f,  1.0f, -1.0f)},
            { Vector3(1.0f,  1.0f,  1.0f)},
            { Vector3(-1.0f,  1.0f,  1.0f)},

            { Vector3(-1.0f, -1.0f, -1.0f)},
            { Vector3(1.0f, -1.0f, -1.0f)},
            { Vector3(1.0f, -1.0f,  1.0f)},
            { Vector3(-1.0f, -1.0f,  1.0f)},

            { Vector3(-1.0f, -1.0f,  1.0f)},
            { Vector3(-1.0f, -1.0f, -1.0f)},
            { Vector3(-1.0f,  1.0f, -1.0f)},
            { Vector3(-1.0f,  1.0f,  1.0f)},

            { Vector3(1.0f, -1.0f,  1.0f)}, 
            { Vector3(1.0f, -1.0f, -1.0f)},
            { Vector3(1.0f,  1.0f, -1.0f)},
            { Vector3(1.0f,  1.0f,  1.0f)},

            { Vector3(-1.0f, -1.0f, -1.0f)},
            { Vector3(1.0f, -1.0f, -1.0f)},
            { Vector3(1.0f,  1.0f, -1.0f)},
            { Vector3(-1.0f,  1.0f, -1.0f)},

            { Vector3(-1.0f, -1.0f,  1.0f)}, 
            { Vector3(1.0f, -1.0f,  1.0f)},
            { Vector3(1.0f,  1.0f,  1.0f)},
            { Vector3(-1.0f,  1.0f,  1.0f)},
        };

        _indices =
        {
            3,0,1, 2,3,1,
            6,5,4, 7,6,4,
            11,8,9, 10,11,9,
            14,13,12, 15,14,12,
            19,16,17, 18,19,17,
            22,21,20, 23,22,20
        };

        _vertexBuffer = new VertexBuffer;
        _vertexBuffer->Create(_vertices, _device);

        _indexBuffer = new IndexBuffer;
        _indexBuffer->Create(_indices, _device);

        _vs = new VertexShader(L"SkyboxVS.cso", "VS", _device);
        _ps = new PixelShader(L"SkyboxPS.cso", "PS", _device);
    }

    VertexShader* GetVS() { return _vs; }
    PixelShader* GetPS() { return _ps; }
    void ProcessMesh(aiMesh* mesh) {}

private:
	std::vector<BasicVertexData> _vertices;
    VertexShader* _vs = nullptr;
    PixelShader* _ps = nullptr;
};

