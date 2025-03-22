#include "Actor.h"
#include "GLGame.h"

void Actor::Render(unsigned int transformMatrixId)
{
	for (const auto& component : Components)
	{
		if (component.get()->IsRenderable())
		{
			component.get()->Render(transformMatrixId);
		}
	}	
}

/***** Debug *****/
void Actor::PrintDebugCoordinates()
{
	GetTransformation().PrintDebug({ -1.0f, -1.0f, -2.0f });
	GetTransformation().PrintDebug({ 1.0f, -1.0f, -2.0f });
	GetTransformation().PrintDebug({ -1.0f, 1.0f, -2.0f });
	GetTransformation().PrintDebug({ -1.0f, -1.0f, -2.0f });
}