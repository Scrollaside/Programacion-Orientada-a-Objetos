#include "KeyboardInput.h"

struct Input input;
bool KEYS[256];

void Init() {
	for (int i = 0; i < 256; i++) {
		KEYS[i] = false;
	}
}//Initizalizes keys

bool MouseEvents(Scene* scene, double xPos, double yPos, double xoffset, double yoffset)//-.-..-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.
{
	MainModel* OGLobj = scene->getMainModel();
	bool checkCollition = false;

	OGLobj->ProcessMouseMovement(xoffset, yoffset, true);

	return checkCollision;
}

bool KeysEvents(Scene *scene){
	MainModel* OGLobj = scene->getMainModel();
	SkyDome* Weather = scene->getSky();
	SkyDome* HUD = scene->getSky();
	bool checkCollition = false;
	if (KEYS[input.A]) {
//		OGLobj->ProcessKeyboard(LEFT, 0.50 * 3.0);
		OGLobj->CamaraGiraY(-0.50 * 3.0);
		KEYS[input.A] = false;
//		OGLobj->backCollition = false;
//		OGLobj->frontCollition = false;
	}
	if (KEYS[input.D]) {
//		OGLobj->ProcessKeyboard(RIGHT, 0.50 * 3.0);
		OGLobj->CamaraGiraY(0.50 * 3.0);
//		OGLobj->backCollition = false;
//		OGLobj->frontCollition = false;
		KEYS[input.D] = false;
	}
	if (KEYS[input.W]) {
//		OGLobj->ProcessKeyboard(FORWARD, 0.50);
		KEYS[input.W] = false;
		OGLobj->movePosition(0.50);
//		OGLobj->frontCollition = true;
		checkCollition = true;
	}
	if (KEYS[input.S]) {
//		OGLobj->ProcessKeyboard(BACKWARD, 0.50);
		KEYS[input.S] = false;
		OGLobj->movePosition(-0.50);
//		OGLobj->backCollition = true;
		checkCollition = true;
	}
	if (KEYS[input.L]) {
		KEYS[input.L] = false;

		Weather->SetWeather();

	}
	if (KEYS[input.O]) {
		KEYS[input.O] = false;

		HUD->SetHUD();

	}
	if (KEYS[input.Escape]) {
		KEYS[input.Escape] = false;

		PostQuitMessage(0);

	}
	return checkCollision;
}
