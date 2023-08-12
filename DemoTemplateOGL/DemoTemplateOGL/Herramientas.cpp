#include "Herramientas.h"

Herramientas::Herramientas(Model* NewObject)
{
	Object = NewObject;
}

void Herramientas::ActivateAnimation()
{
	Animation = true;
}

void Herramientas::SetAnimation()
{
	glm::vec3* ActualTranslate;
	ActualTranslate = Object->getTranslate();

	Count++;
	if (Count == 20)
	{
		AnimationUp = false;
		AnimationDown = false;
	}

	if (Count == 30)
	{
		AnimationUp = false;
		AnimationDown = false;
		Animation = false;
		Count = 0;
		ActualTranslate->y = 0;
		Obtener();
	}

	if (AnimationUp == true)
	{
		ActualTranslate->y = ActualTranslate->y + 0.1;
	}
	else if (AnimationDown == true)
	{
		ActualTranslate->y = ActualTranslate->y - 0.1;
	}
	Object->setTranslate(ActualTranslate);

}

bool Herramientas::GetAnimationState()
{
	return Animation;
}

void Herramientas::Obtener()
{
	ObjectState = true;
}

bool Herramientas::GetObjectState()
{
	return ObjectState;
}