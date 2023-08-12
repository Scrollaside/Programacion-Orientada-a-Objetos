#pragma once
#include "scene.h"

class SpriteAnimation
{
private:
	//Billboard* OurSprites;
	std::vector<Billboard*> billBoard;
	Billboard* BillboardActual;
	int FrameActual = 0;
	int contador = 0;
	float cambio;
	bool Activate = false;

public:
	SpriteAnimation(std::vector<Billboard*>& NewBillboard);
	void CambioDeSprite();
	void SetState(bool State);
	Billboard* GetSprite();
	~SpriteAnimation();

	void Lluvia(glm::vec3 CameraPosition);
	void HUD(glm::vec3 CameraPosition);
};
