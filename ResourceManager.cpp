#include "ResourceManager.h"
#include "GameManager.h"
#include "stb.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cstdlib> 

void ResourceManager::LoadMesh(std::string path, unsigned int& indexOffset, unsigned int& indexCount)
{
    auto resource = MeshMap.find(path);
    if (resource != MeshMap.end())
    {
        std::shared_ptr<MeshResource> meshResource = std::static_pointer_cast<MeshResource>(resource->second);
        indexOffset = meshResource->GetMemoryIndexOffset();
        indexCount = meshResource->GetIndexCount();
    }
    else
    {
        indexOffset = IndexOffset;
        LoadMeshData(path, indexCount);
        MeshMap.emplace(std::pair<std::string, MeshResource*>(path, new MeshResource(indexOffset, indexCount)));
    }
}

void ResourceManager::LoadTexture(std::string path, unsigned int& textureId, bool flipVertical)
{
    auto texture = TextureMap.find(path);
    if (texture != TextureMap.end())
    {
        textureId = texture->second;
    }
    else
    {
        int textureWidth, textureHeight, numColorChannels;  // do we need to also save these?
        stbi_set_flip_vertically_on_load(flipVertical);
        unsigned char* textureData = stbi_load(path.c_str(), &textureWidth, &textureHeight, &numColorChannels, 0);

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        TextureMap.emplace(std::pair<std::string, unsigned int>(path, textureId));

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(textureData);
    }
}

/***** Meshes *****/
void ResourceManager::LoadMeshData(std::string path, unsigned int& indexCount)
{
    std::ifstream meshFile(path);
    if (!meshFile) {
        std::cerr << "Unable to open file\n";
    }

    std::vector<glm::vec3> objectPositionData;
    std::vector<glm::vec2> objectTextureData;
    //std::vector<glm::vec3> objectNormalData;

    std::vector<std::string> objectIndexData;
    std::unordered_map<std::string, VertexData> objectVertexData;
    unsigned int numIndicesInObject = 0;
    
    std::string line;
    while (std::getline(meshFile, line)) {
        std::istringstream lineStringStream(line);
        std::string linePrefix;
        lineStringStream >> linePrefix;

        if (linePrefix == "v")
        {
            float x, y, z;
            lineStringStream >> x >> y >> z;
            objectPositionData.push_back({ x,y,z });
        }

        if (linePrefix == "vt")
        {
            float x, y;
            lineStringStream >> x >> y;
            objectTextureData.push_back({ x,y });
        }

        if (linePrefix == "f")
        {
            unsigned int positionIndex = 0, textureIndex = 0, normalIndex = 0;
            std::string indexLineString;

            while (lineStringStream >> indexLineString) {
                if (LoadIndexData(indexLineString, positionIndex, textureIndex, normalIndex))
                {
                    glm::vec3 position = objectPositionData[positionIndex];
                    glm::vec2 texture = objectTextureData[positionIndex];
                    objectIndexData.push_back(indexLineString);
                    objectVertexData.insert(std::pair<std::string, VertexData>(indexLineString, { position, texture }));
                }
                numIndicesInObject++;
            }
        }
    }
    meshFile.close();

    PushVertexDataInBuffer(objectVertexData);
    PushIndexDataInBuffer(objectIndexData, objectVertexData);
    VertexOffset += static_cast<unsigned int>(objectVertexData.size());
    IndexOffset += numIndicesInObject;
    indexCount = numIndicesInObject;
}

bool ResourceManager::LoadIndexData(std::string& indexLineString, unsigned int& outPositionIndex, unsigned int& outTextureIndex, unsigned int& outNormalIndex)
{
    IndexType indexType = IndexType::POSITION;  

    std::istringstream indexLineStringStream(indexLineString);
    while (indexLineStringStream)
    {
        while (indexLineStringStream.peek() == '/')
            indexLineStringStream.get();

        switch (indexType)
        {
        case IndexType::POSITION:
            indexLineStringStream >> outPositionIndex;
            outPositionIndex--;
            indexType = IndexType::TEXTURE;
            break;
        case IndexType::TEXTURE:
            indexLineStringStream >> outTextureIndex;
            outTextureIndex--;
            indexType = IndexType::NORMAL;
            break;
        case IndexType::NORMAL:
            indexLineStringStream >> outNormalIndex;
            outNormalIndex--;
            indexType = IndexType::END;
            break;
        case IndexType::END:
            break;
        }
    }

    if (indexType != IndexType::END)
    {
        std::cerr << "Error: Error in reading Index Data!";
        return false;
    }

    return true;
}

void ResourceManager::PushVertexDataInBuffer(std::unordered_map<std::string, VertexData>& objectVertexData)
{
    /*
    // position
	VertexData.push_back(x);
	VertexData.push_back(y);
	VertexData.push_back(z);

	// colors
	VertexData.push_back(r);
	VertexData.push_back(g);
	VertexData.push_back(b);

	// texture
	VertexData.push_back(tx);
	VertexData.push_back(ty);
    */


    unsigned int vertexOrderIndex = 0;
    for (auto& vertexData : objectVertexData)
    {
        vertexData.second.Index = vertexOrderIndex;
        
        // position
        VertexBufferData.push_back(vertexData.second.Position.x);
        VertexBufferData.push_back(vertexData.second.Position.y);
        VertexBufferData.push_back(vertexData.second.Position.z);

        //color - this is magic numbers
        VertexBufferData.push_back(1.0f);
        VertexBufferData.push_back(1.0f);
        VertexBufferData.push_back(0.0f);

        // texture
        VertexBufferData.push_back(vertexData.second.Texture.x);
        VertexBufferData.push_back(vertexData.second.Texture.y);


        //VertexBufferData.push_back({ vertexData.second.Position.x, vertexData.second.Position.y, vertexData.second.Position.z });
        //TextureBufferData.push_back({ vertexData.second.Texture.x, vertexData.second.Texture.y });
        //ColorBufferData.push_back({ 1.0f, 1.0f, 0.0f });
        vertexOrderIndex++;
    }
}

void ResourceManager::PushIndexDataInBuffer(std::vector<std::string> objectIndexData, std::unordered_map<std::string, VertexData>& objectVertexData)
{
    for (auto indexData : objectIndexData)
    {
        auto vertexData = objectVertexData.find(indexData);
        if (vertexData != objectVertexData.end())
        {
            VertexDrawOrder.push_back(vertexData->second.Index + VertexOffset);
        }
    }
}

void ResourceManager::LoadVertexBufferData()
{
    glBufferData(GL_ARRAY_BUFFER, VertexBufferData.size() * sizeof(GLfloat), VertexBufferData.data(), GL_STATIC_DRAW);
}

void ResourceManager::LoadIndexBufferData()
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexDrawOrder.size() * sizeof(GLuint), VertexDrawOrder.data(), GL_STATIC_DRAW);
}