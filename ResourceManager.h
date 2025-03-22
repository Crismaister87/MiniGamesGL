#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "L3DVector.h"
#include "RGBColor.h"
#include "Game.h"


enum class IndexType
{
	POSITION,
	TEXTURE,
	NORMAL,
	END
};

/***** RESOURCE DATA *****/
class MeshResource
{
public:
	MeshResource(unsigned int startingIndexVertexOffset, unsigned int indexCount) :
		IndexMemoryOffset(startingIndexVertexOffset), IndexCount(indexCount) {
	};

	inline unsigned int GetMemoryIndexOffset() { return IndexMemoryOffset; };
	inline unsigned int GetIndexCount() { return IndexCount; };

private:
	unsigned int IndexMemoryOffset;
	unsigned int IndexCount;
};


struct VertexData
{
	//VertexData(glm::vec3 position, glm::vec2 texture, glm::vec3 normal, unsigned int idx);
	VertexData(glm::vec3 position, glm::vec2 texture) : Position(position), Texture(texture), Index(0) {};

	glm::vec3 Position;
	glm::vec2 Texture;
	//glm::vec3 Normal;
	unsigned int Index;
};

class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	void LoadMesh(std::string path, unsigned int& indexOffset, unsigned int& indexCount);
	void LoadTexture(std::string path, unsigned int& textureId, bool flipVertical);

	void LoadMeshData(std::string path, unsigned int& indexCount);
	bool LoadIndexData(std::string& indexLineString, unsigned int& outPositionIndex, unsigned int& outTextureIndex, unsigned int& outNormalIndex);
	void PushVertexDataInBuffer(std::unordered_map<std::string, VertexData>& objectVertexData);
	void PushIndexDataInBuffer(std::vector<std::string> objectIndexData, std::unordered_map<std::string, VertexData>& objectVertexData);

	void LoadVertexBufferData();
	void LoadIndexBufferData();

private:
	std::unordered_map<std::string, std::shared_ptr<MeshResource>> MeshMap;
	std::unordered_map<std::string, unsigned int> TextureMap;

	std::vector<GLfloat> VertexBufferData;
	std::vector<unsigned int> VertexDrawOrder;

	unsigned int VertexOffset{ 0 };
	unsigned int IndexOffset{ 0 };
};