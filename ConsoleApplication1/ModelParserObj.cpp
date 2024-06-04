#include "ModelParserObj.h"
#include "Global.h"

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> v;
    if (!str.empty()) {
        int start = 0;
        do {
            // Find the index of occurrence
            int idx = str.find(delimiter, start);
            if (idx == std::string::npos) {
                break;
            }

            // If found add the substring till that
            // occurrence in the vector
            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }

    return v;
}

std::vector<float> getFloatCoordinates(std::vector<std::string>* pStrCoord)
{
    std::vector<float> floatCoord;

    for (int i = 0; i < pStrCoord->size(); i++)
    {
        floatCoord.push_back(std::stof(pStrCoord->at(i)));
    }

    return floatCoord;
}

std::vector<uint16_t> getIntPoints(std::vector<std::string>* pStrPoints)
{
    std::vector<uint16_t> intPoints;

    for (int i = 0; i < pStrPoints->size(); i++)
    {
        int tempVect;
        for (int j = 0; j < pStrPoints->size(); i++)
        {
            
            tempVect = static_cast<uint16_t>(stoi(pStrPoints->at(i)));

        }

        intPoints.push_back(tempVect);
    }

    return intPoints;
}

ModelParserObj::ModelParserObj() {
}

ModelParserObj::~ModelParserObj() {
}

ObjInfo ModelParserObj::ParseObj()
{

	std::ifstream objFile ("untitled.obj");
	std::string line;

	if (objFile.is_open()) {
		while (objFile) {

			std::getline(objFile, line);

			if (line[0] == 'v') //vertex coordinates
			{
                line.erase(0);
                std::vector<std::string> strCoord = split(line, " ");

				std::vector<float> coordinates = getFloatCoordinates(&strCoord);

				m_ParsedObj.coords.push_back(coordinates);
			}

            else if (line[0] == 'f') //face triangles
            {
                line.erase(0);
                std::vector<std::string> strFace = split(line, " ");

                std::vector<std::vector<std::string>> strTrianglePoints;
                for (int i = 0; i < strFace.size(); i++)
                {
                    strTrianglePoints.push_back(split(strFace[i], "/"));
                }
				
				std::vector<std::string> str1dPoints;
				for (int i = 0; i < strTrianglePoints.size(); i++)
				{
					for (int j = 0; j < strTrianglePoints[i].size(); i++)
						str1dPoints.push_back(strTrianglePoints[i][j]);
				}

                m_ParsedObj.faces = getIntPoints(&str1dPoints);
			}
		}
	}

}

Geometry ModelParserObj::BuildObj() 
{
	Geometry objGeometry;

	for (int i = 0; i < m_ParsedObj.coords.size(); i++)
	{
		objGeometry.vertices.push_back(
			Vertex({ DirectX::XMFLOAT3(m_ParsedObj.coords[i][0], m_ParsedObj.coords[i][1], m_ParsedObj.coords[i][2]), DirectX::XMFLOAT4(DirectX::Colors::White)})
		);
	}

	objGeometry.indices = m_ParsedObj.faces;

	const UINT vbByteSize = (UINT)objGeometry.vertices.size() * sizeof(Vertex);
	const UINT ibByteSize = (UINT)objGeometry.indices.size() * sizeof(std::uint16_t);
	objGeometry.boxGeo = std::make_unique<MeshGeometry>();
	objGeometry.boxGeo->Name = "boxGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &objGeometry.boxGeo->VertexBufferCPU));
	CopyMemory(objGeometry.boxGeo->VertexBufferCPU->GetBufferPointer(), objGeometry.vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &objGeometry.boxGeo->IndexBufferCPU));
	CopyMemory(objGeometry.boxGeo->IndexBufferCPU->GetBufferPointer(), objGeometry.indices.data(), ibByteSize);

	objGeometry.boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(GetRender()->Getmd3dDevice(),
		GetRender()->GetCommandList(), objGeometry.vertices.data(), vbByteSize, objGeometry.boxGeo->VertexBufferUploader);

	objGeometry.boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(GetRender()->Getmd3dDevice(),
		GetRender()->GetCommandList(), objGeometry.indices.data(), ibByteSize, objGeometry.boxGeo->IndexBufferUploader);

	objGeometry.boxGeo->VertexByteStride = sizeof(Vertex);
	objGeometry.boxGeo->VertexBufferByteSize = vbByteSize;
	objGeometry.boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
	objGeometry.boxGeo->IndexBufferByteSize = ibByteSize;

	SubmeshGeometry submesh;
	submesh.IndexCount = (UINT)objGeometry.indices.size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	objGeometry.submesh = submesh;

	return objGeometry;
}