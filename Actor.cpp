#include "Actor.h"
#include "GLGame.h"
#include "MeshComponent.h"

Actor::Actor(GAME_ObjectID objectId, unsigned int indexOffset, unsigned int indexCount, bool isTextured, unsigned int textureId) :
	GameObject(objectId), IndexOffset(indexOffset), IndexCount(indexCount), IsTextured(isTextured), TextureId(textureId) {

	Components.push_back(std::make_shared<MeshComponent>("19", "a"));
}

void Actor::Render(unsigned int transformMatrixId)
{
	for (const auto& component : Components)
	{
		if (component.get()->IsRenderable())
		{
			component.get()->Render(transformMatrixId);
		}
	}

	if(TextureId != 0)
		glBindTexture(GL_TEXTURE_2D, TextureId);

	glUniformMatrix4fv(transformMatrixId, 1, false, GetTransformation().GetData());
	glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, (void*)(IndexOffset*sizeof(GLuint)));
}

/***** Debug *****/
void Actor::PrintDebugCoordinates()
{
	GetTransformation().PrintDebug({ -1.0f, -1.0f, -2.0f });
	GetTransformation().PrintDebug({ 1.0f, -1.0f, -2.0f });
	GetTransformation().PrintDebug({ -1.0f, 1.0f, -2.0f });
	GetTransformation().PrintDebug({ -1.0f, -1.0f, -2.0f });
}