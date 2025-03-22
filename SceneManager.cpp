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