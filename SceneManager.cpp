#include "SceneManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Game.h"

#include <string>

void SceneManager::RenderSceneObjects(unsigned int transformationMatrixID)
{
	for (auto actor : GameObjects)
	{
		actor->Render(transformationMatrixID);
	}
}

std::shared_ptr<Actor> SceneManager::SpawnActor(std::string meshPath, std::string texturePath, SpawnParameters& spawnParameters)
{
	unsigned int indexOffset;
	unsigned int indexCount;
	GameManager::get().GetResourceManager()->LoadMesh(meshPath, indexOffset, indexCount);

	unsigned int textureId;
	GameManager::get().GetResourceManager()->LoadTexture(texturePath, textureId, true);

	std::shared_ptr<Actor> newActor = std::make_shared<Actor>(0, indexOffset, indexCount, true, textureId);	// defaulted to true for now
	newActor->SetPosition(spawnParameters.position.getX(), spawnParameters.position.getY(), spawnParameters.position.getZ());
	newActor->SetAngles(spawnParameters.rotation.getX(), spawnParameters.rotation.getY(), spawnParameters.rotation.getZ());
	newActor->SetScale(spawnParameters.scale.getX(), spawnParameters.scale.getY(), spawnParameters.scale.getZ());
	
	GameObjects.push_back(newActor);
	return newActor;
}