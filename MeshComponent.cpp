#include "MeshComponent.h"

MeshComponent::MeshComponent(std::string meshPath, std::string texturePath)
{
	/*unsigned int indexOffset;
	unsigned int indexCount;
	GameManager::get().GetResourceManager()->LoadMesh(meshPath, indexOffset, indexCount);

	unsigned int textureId;
	GameManager::get().GetResourceManager()->LoadTexture(texturePath, textureId, true);*/

	IndexOffset = 10;
	IndexCount = 2;
}

void MeshComponent::Render(unsigned int transformMatrixId) //unsigned int transformMatrixId)
{
	std::cout << "Component draw  = " << IndexOffset << std::endl;
	/*if (TextureId += 0)
		glBindTexture(GL_TEXTURE_2D, TextureId);

	glUniformMatrix4fv(transformMatrixId, 1, false, GetTransformation().GetData());
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, (void*)(IndexOffset * sizeof(GLuint)));*/
}