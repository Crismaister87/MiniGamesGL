#include "MeshComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"

MeshComponent::MeshComponent(GameObject* owner, std::string meshPath, std::string texturePath)
{
	Owner = owner;
	GameManager::get().GetResourceManager()->LoadMesh(meshPath, IndexOffset, IndexCount);
	GameManager::get().GetResourceManager()->LoadTexture(texturePath, TextureId, true);
}

void MeshComponent::Render(unsigned int transformMatrixId)
{
	if (Owner != nullptr)
	{
		if (TextureId != 0)
			glBindTexture(GL_TEXTURE_2D, TextureId);

		glUniformMatrix4fv(transformMatrixId, 1, false, Owner->GetTransformation().GetData());
		glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, (void*)(IndexOffset * sizeof(GLuint)));
	}
}