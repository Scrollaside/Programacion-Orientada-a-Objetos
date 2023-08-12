#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(std::vector<Billboard*>& NewBillboard)
{
	billBoard = NewBillboard;
	BillboardActual = billBoard[0];
}

void SpriteAnimation::CambioDeSprite()
{
	contador++;

	if (contador == 4)
	{
		FrameActual = FrameActual + 1;
		if (FrameActual == 5)
		{
			FrameActual = 0;
		}
		BillboardActual = billBoard[FrameActual];

		contador = 0;
	}
}

void SpriteAnimation::SetState(bool State)
{
	Activate = State;
}


Billboard* SpriteAnimation::GetSprite()
{
	return BillboardActual;
}

void SpriteAnimation::Lluvia(glm::vec3 CameraPosition) {

	if (Activate == true)
	{

		cambio += 0.1;
		if (cambio > 3)
		{
			cambio = 0;
		}

		if (contador % 1 == 0)
		{
			CameraPosition.y -= 3 + cambio;
		}

		if (contador == 5)
		{
			contador = 0;
		}
		contador++;

		for (int i = 0; i < billBoard.size(); i++)
		{
			billBoard[i]->NewPosition(CameraPosition);
			billBoard[i]->Draw();
		}
	}
	else
	{
		for (int i = 0; i < billBoard.size(); i++)
		{
			billBoard[i]->NewPosition(glm::vec3(0, -40, 0));

		}
	}
}

SpriteAnimation::~SpriteAnimation()
{
	/*for (int i; billBoard.size(); i++)
	{
		delete billBoard[i];
	}
	billBoard.clear();*/

	if (BillboardActual != NULL) {
		delete BillboardActual;
	}
}

void SpriteAnimation::HUD(glm::vec3 CameraPosition) {

	if (Activate == true)
	{

		/*cambio += 0.1;
		if (cambio > 3)
		{
			cambio = 0;
		}

		if (contador % 1 == 0)
		{
			CameraPosition.y -= 3 + cambio;
		}

		if (contador == 5)
		{
			contador = 0;
		}
		contador++;*/
		CameraPosition.y = 3;
		for (int i = 0; i < billBoard.size(); i++)
		{
			billBoard[i]->NewPosition(CameraPosition);
			billBoard[i]->Draw();
		}
	}
	else
	{
		for (int i = 0; i < billBoard.size(); i++)
		{
			billBoard[i]->NewPosition(glm::vec3(0, -30, 0));

		}
	}
}

