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

ModelParserObj::ModelParserObj() {
}

ModelParserObj::~ModelParserObj() {
}

void ModelParserObj::ParseObj()
{

	std::ifstream objFile ("cube.obj");
	std::string line;

	while (!objFile.eof()) {

		std::getline(objFile, line);

		if (line[0] == 'v' && line[1] == ' ') //vertex coordinates
		{

			std::string templine;

			for (int i = 2; i < line.size(); i++)
			{
				templine.push_back(line[i]);
			}

			line = templine;

            std::vector<std::string> strCoord = split(line, " ");

			std::vector<float> coordinates = getFloatCoordinates(&strCoord);

			m_ParsedObj.coords.push_back(coordinates);
		}

        else if (line[0] == 'f') //face triangles
        {
			std::string templine;

			for (int i = 2; i < line.size(); i++)
			{
				templine.push_back(line[i]);
			}

			line = templine;

            std::vector<std::string> strFace = split(line, " ");

            std::vector<std::vector<std::string>> strVertInfos;

			for (int i = 0; i < strFace.size(); i++)
			{
				strVertInfos.push_back(split(strFace[i], "/"));
			}

			for (int i = 0; i < strVertInfos.size(); i++)
			{
				std::vector<std::uint16_t> tempInfos;

				for (int j = 0; j < strVertInfos[i].size(); j++)
					tempInfos.push_back(static_cast<uint16_t>(std::stoi(strVertInfos[i][j]) - 1));

				m_ParsedObj.facesInfos.push_back(tempInfos);
			}
				
		}

		else if (line[0] == 'v' && line[1] == 't') //UVs
		{
			std::string templine;

			for (int i = 3; i < line.size(); i++)
			{
				templine.push_back(line[i]);
			}

			line = templine;

			std::vector<std::string> strUv = split(line, " ");

			std::vector<float> uv = getFloatCoordinates(&strUv);
			 
			m_ParsedObj.uvs.push_back(uv);
		}
	}
	

}

GeometryTexture* ModelParserObj::BuildObj() 
{
	GeometryTexture* objGeometry = new GeometryTexture();

	for (int i = 0; i < m_ParsedObj.facesInfos.size(); i++)
	{
		objGeometry->vertices.push_back(
			VertexTexture({ 
				DirectX::XMFLOAT3(m_ParsedObj.coords[m_ParsedObj.facesInfos[i][0]][0], m_ParsedObj.coords[m_ParsedObj.facesInfos[i][0]][1], m_ParsedObj.coords[m_ParsedObj.facesInfos[i][0]][2]),
				DirectX::XMFLOAT2(m_ParsedObj.uvs[m_ParsedObj.facesInfos[i][1]][0], m_ParsedObj.uvs[m_ParsedObj.facesInfos[i][1]][1])}));

		objGeometry->indices.push_back(m_ParsedObj.facesInfos[i][0]);
	}

	const UINT vbByteSize = (UINT)objGeometry->vertices.size() * sizeof(VertexTexture);
	const UINT ibByteSize = (UINT)objGeometry->indices.size() * sizeof(std::uint16_t);
	objGeometry->boxGeo = std::make_unique<MeshGeometry>();
	objGeometry->boxGeo->Name = "boxGeo";

	ThrowIfFailed(D3DCreateBlob(vbByteSize, &objGeometry->boxGeo->VertexBufferCPU));
	CopyMemory(objGeometry->boxGeo->VertexBufferCPU->GetBufferPointer(), objGeometry->vertices.data(), vbByteSize);

	ThrowIfFailed(D3DCreateBlob(ibByteSize, &objGeometry->boxGeo->IndexBufferCPU));
	CopyMemory(objGeometry->boxGeo->IndexBufferCPU->GetBufferPointer(), objGeometry->indices.data(), ibByteSize);

	objGeometry->boxGeo->VertexBufferGPU = d3dUtil::CreateDefaultBuffer(GetRender()->Getmd3dDevice(),
		GetRender()->GetCommandList(), objGeometry->vertices.data(), vbByteSize, objGeometry->boxGeo->VertexBufferUploader);

	objGeometry->boxGeo->IndexBufferGPU = d3dUtil::CreateDefaultBuffer(GetRender()->Getmd3dDevice(),
		GetRender()->GetCommandList(), objGeometry->indices.data(), ibByteSize, objGeometry->boxGeo->IndexBufferUploader);

	objGeometry->boxGeo->VertexByteStride = sizeof(VertexTexture);
	objGeometry->boxGeo->VertexBufferByteSize = vbByteSize;
	objGeometry->boxGeo->IndexFormat = DXGI_FORMAT_R16_UINT;
	objGeometry->boxGeo->IndexBufferByteSize = ibByteSize;

	SubmeshGeometry submesh;
	submesh.IndexCount = (UINT)objGeometry->indices.size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	objGeometry->submesh = submesh;

	return objGeometry;
}