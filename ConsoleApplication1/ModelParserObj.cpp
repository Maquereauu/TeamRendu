#include "ModelParserObj.h"

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

std::vector<std::vector<int>> getIntPoints(std::vector<std::vector<std::string>>* pStrPoints)
{
    std::vector<std::vector<int>> intPoints;

    for (int i = 0; i < pStrPoints->size(); i++)
    {
        std::vector<int> tempVect;
        for (int j = 0; j < pStrPoints->at(i).size(); i++)
        {
            
            tempVect.push_back(stoi(pStrPoints->at(i).at(j));
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
	ObjInfo parsedObj;

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

				parsedObj.vertices.push_back(coordinates);
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

                parsedObj.indices.push_back(getIntPoints(&strTrianglePoints));
            }
		}
	}

}

Geometry ModelParserObj::BuildObj() 
{
    /*TODO*/
}