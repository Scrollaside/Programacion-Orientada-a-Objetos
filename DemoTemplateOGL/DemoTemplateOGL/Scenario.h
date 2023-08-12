#ifndef GRAPHICSRR_H
#define GRAPHICSRR_H

#include <windows.h>
#include <windowsx.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "camera.h"
#include <iostream>
#include "Scene.h"
#include "model.h"
#include "Herramientas.h"
#include "SpriteAnimation.h"
//#include "ModelResource.h"


//void ModelResource::MovCircular() {
//	glm::vec3 translate;
//	glm::vec3 scale;
//	
//	
//	float mov = 0;
//	mov = ourModel[1]->getRotationAngle();
//	mov++;
//	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
//	ourModel[1]->setRotation(mov, &rotation);
//}

class Scenario : public Scene {
private:
	int tics = 0, frames = 0, frames2 = 0;
	bool Day = true, anim = true;
	SkyDome* sky;
	SkyDome* skyNight;
	Terreno* terreno;
	Terreno* agua;
	Terreno* aguaNight;
	Terreno* terrenoNight;
	std::vector<Billboard*> billBoard;
	std::vector<Billboard*> RainVector;
	std::vector<Billboard*> HUDVector;
	SpriteAnimation* Lluvia;
	SpriteAnimation* HUD;
	std::vector<Model*> ourModel;
	MainModel* camara;
	HWND hwnd;
	bool gethay = false;
	bool getaxe = false;
	bool gethammer = false;
	bool getwrench = false;
	bool gettape = false;
	bool cowcomplete = false;
	bool toolcomplete = false;
	float angulo;
	int objetos = 0;
	bool ganar = false;
	int wrand, trand, hrand;
	ModelResource* hammer;
	ModelResource* cow;
	ModelResource* tape;
	ModelResource* chiken;
	ModelResource* hay;
	ModelResource* axe;
	ModelResource* crow;
	ModelResource* Barn;
	ModelResource* bucket;
	ModelResource* boots;
	ModelResource* wrench;
	ModelResource* table;
	ModelResource* ute;
	ModelResource* tract;
	ModelResource* saw;
	ModelResource* nail;
	Estructura* barn;
	Animales* animal;
	//Herramientas* axe;
	//Herramientas* wrench;
	//Herramientas* tape;
	//Herramientas* hammer;

public:
	Scenario(HWND hWnd) {

		glm::vec3 translate;
		glm::vec3 scale;
		
		MainModel* model = new MainModel(hWnd, "models/Cube.obj");
		translate = glm::vec3(0.0f, 0.0f, 3.0f);
		scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
		model->setScale(&scale);
		model->setTranslate(&translate);
		InitGraph(hWnd, model);
	}
	Scenario(HWND hWnd, MainModel *camIni) {
		InitGraph(hWnd, camIni);
	}
	void InitGraph(HWND hWnd, MainModel *main) {
		hwnd = hWnd;
		float matAmbient[] = { 1,1,1,1 };
		float matDiff[] = { 1,1,1,1 };
		angulo = 0;
		camara = main;
		//creamos el objeto skydome
		sky = new SkyDome(hWnd, 32, 32, 20, (WCHAR*)L"skydome/sky.png", main);
		skyNight = new SkyDome(hWnd, 32, 32, 20, (WCHAR*)L"skydome/sky2.png", main);
		//creamos el terreno
		terreno = new Terreno(hWnd, (WCHAR*)L"skydome/terreno2.jpg", (WCHAR*)L"skydome/terreno.png", 400, 400, main);
		terrenoNight = new Terreno(hWnd, (WCHAR*)L"skydome/terreno2.jpg", (WCHAR*)L"skydome/terreno2.png", 400, 400, main);
		agua = new Terreno(hWnd, (WCHAR*)L"skydome/agua2.png", (WCHAR*)L"skydome/agua.png", 400, 400, main);
		agua->isWater();
		aguaNight = new Terreno(hWnd, (WCHAR*)L"skydome/agua2.png", (WCHAR*)L"skydome/aguaNight.png", 400, 400, main);
		aguaNight->isWater();
		// load models
		// -----------
		ourModel.push_back(main);
		Model* model;
		glm::vec3 translate;
		glm::vec3 scale;
		glm::vec3 rotation;
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		
		float ye = terreno->Superficie(0, 0);
		model = new Model(this->hwnd, "models/hammer.obj", main);
		//hrand = rand() % 3;
		translate = glm::vec3(0.0f, 7.0f, 25.0f);
		/*switch (hrand) {
		case 0:
			translate = glm::vec3(0.0f, 7.0f, 25.0f);
			break;
		case 1:
			translate = glm::vec3(33.0f, 7.0f, 2.0f);
			break;
		case 2:
			translate = glm::vec3(4.0f, 7.0f, 53.0f);
			break;
		default:
			translate = glm::vec3(0.0f, 7.0f, 25.0f);
			break;
		}*/
		//translate = glm::vec3(0.0f, 7.0f, 25.0f);
		model->setTranslate(&translate);
		//scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
		//model->setScale(&scale);
		rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation Y
		model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);

		hammer = new ModelResource(ourModel[1]);
		translate = hammer->RandomPosition(glm::vec3(0.0f, 7.0f, 25.0f),
			glm::vec3(33.0f, 7.0f, 2.0f),
			glm::vec3(4.0f, 7.0f, 53.0f));

		hammer->GetObjeto()->setTranslate(&translate);
		hrand = hammer->ReturnRand();

		model= new Model(this->hwnd, "models/cow.obj", main);
		translate = glm::vec3(0.0f, 7.2f, 45.0f);
		model->setTranslate(&translate);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setScale(&scale);
		rotation = glm::vec3(0.0f, 1.0f, 0.0f); //rotation Y
		model->setRotation(45, &rotation); // 90° rotation
		
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/Duct_Tape.obj", main);
		translate = glm::vec3(0.0f, 7.0f, 30.0f);
		/*trand = rand() % 3;
		switch (trand) {
		case 0:
			translate = glm::vec3(0.0f, 7.0f, 30.0f);
			break;
		case 1:
			translate = glm::vec3(11.0f, 7.0f, 51.0f);
			break;
		case 2:
			translate = glm::vec3(-47.0f, 7.0f, 18.0f);
			break;
		default:
			translate = glm::vec3(0.0f, 7.0f, 30.0f);
			break;
		}*/
		//translate = glm::vec3(0.0f, 7.0f, 30.0f);
		model->setTranslate(&translate);
		scale = glm::vec3(0.05f, 0.05f, 0.05f);	// it's a bit too big for our scene, so scale it down
		model->setScale(&scale);
		ourModel.push_back(model);

		tape = new ModelResource(ourModel[3]);
		translate = tape->RandomPosition(glm::vec3(0.0f, 7.0f, 30.0f),
			glm::vec3(11.0f, 7.0f, 51.0f),
			glm::vec3(-47.0f, 7.0f, 18.0f));
		tape->GetObjeto()->setTranslate(&translate);
		trand = tape->ReturnRand();

		model = new Model(this->hwnd, "models/Rusty_Nail_obj.obj", main, false, false);
		translate = glm::vec3(-65.2f, 5.8f, 15.2f);
		//scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		//model->setScale(&scale);
		rotation = glm::vec3(0.0f, 1.0f, 0.0f); //rotation Y
		model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/hay.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 5.0f);
		//scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		//model->setScale(&scale);
		ourModel.push_back(model);
		//inicializaBillboards(hWnd);

		model = new Model(this->hwnd, "models/Axe.obj", main, false, false);
		translate = glm::vec3(0.0f, 7.0f, -10.0f);
		//scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		//model->setScale(&scale);
		rotation = glm::vec3(0.0f, 1.0f, 1.0f); //rotation Y
		model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);
		axe = new ModelResource(ourModel[6]);

		model = new Model(this->hwnd, "models/scarecrow.obj", main, false, false);
		translate = glm::vec3(-5.0f, 5.5f, -10.0f);
		//scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		//model->setScale(&scale);
		rotation = glm::vec3(0.0f, 1.0f, 0.0f); //rotation Y
		model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/Medieval_barn_1.obj", main, false, false);
		translate = glm::vec3(-64.8f, 5.5f, 17.0f);
		//scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		//model->setScale(&scale);
		rotation = glm::vec3(0.0f, 1.0f, 0.0f); //rotation Y
	    model->setRotation(130, &rotation); // 90° rotation
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/Bucket.obj", main, false, false);
		translate = glm::vec3(-57.8f, 6.2f, 4.3f);
		model->setTranslate(&translate);
		//scale = glm::vec3(0.5f, 0.5f, 0.5f);	
		//model->setScale(&scale);
		rotation = glm::vec3(0.0f, 1.0f, 0.0f);
		model->setRotation(45, &rotation); 
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/Army_boots.obj", main, false, false);
		translate = glm::vec3(-57.4f, 6.3f, 14.2f);
		scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		//rotation = glm::vec3(0.0f, 1.0f, 0.0f); //rotation Y
		//model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/Wrench.obj", main, false, false);
		translate = glm::vec3(1.0f, 7.0f, -30.0f);
		/*wrand = rand() % 3;
		switch (wrand) {
		case 0:
			translate = glm::vec3(1.0f, 7.0f, -30.0f);
			break;
		case 1:
			translate = glm::vec3(-40.0f, 7.0f, -50.0f);
			break;
		case 2:
			translate = glm::vec3(43.0f, 7.0f, -41.0f);
			break;
		default:
			translate = glm::vec3(1.0f, 7.0f, -30.0f);
			break;
		}*/
		//translate = glm::vec3(1.0f, 6.0f, -30.0f);
		//scale = glm::vec3(0.1f, 0.1f, 0.1f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		//model->setScale(&scale);
		rotation = glm::vec3(0.0f, 1.0f, -1.0f); //rotation Y
		model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);

		wrench = new ModelResource(ourModel[11]);
		translate = wrench->RandomPosition(glm::vec3(1.0f, 7.0f, -30.0f),
			glm::vec3(-40.0f, 7.0f, -50.0f),
			glm::vec3(43.0f, 7.0f, -41.0f));
		wrench->GetObjeto()->setTranslate(&translate);
		wrand = wrench->ReturnRand();

		model = new Model(this->hwnd, "models/table.obj", main, false, false);
		translate = glm::vec3(-70.2f, 6.5f, 20.6f);
		rotation = glm::vec3(0.0f, -1.0f, 0.0f); //rotation Y
		model->setRotation(30, &rotation);
		//scale = glm::vec3(0.2f, 0.2f, 0.2f);
		//model->setScale(&scale);
		model->setTranslate(&translate);
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/SmallTruck_1.obj", main, false, false);
		
		translate = glm::vec3(10.0f, 7.9f, 5.0f);
		scale = glm::vec3(1.5f, 1.5f, 1.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		//rotation = glm::vec3(0.0f, 1.0f, 1.0f); //rotation Y
		//model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/tract.obj", main, false, false);
		translate = glm::vec3(25.0f, 7.5f, 15.0f);
		scale = glm::vec3(1.5f, 1.5f, 1.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		//rotation = glm::vec3(0.0f, 1.0f, 1.0f); //rotation Y
		//model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/saw.obj", main, false, false);
		translate = glm::vec3(-67.1f, 5.0f, 16.9f);
		//scale = glm::vec3(0.02f, 0.02f, 0.02f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		//model->setScale(&scale);
		//rotation = glm::vec3(0.0f, 1.0f, 0.0f); //rotation Y
		//model->setRotation(45, &rotation); // 90° rotation
		ourModel.push_back(model);

		model = new Model(this->hwnd, "models/chikinframes/frame1.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/chikinframes/frame2.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/chikinframes/frame3.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/chikinframes/frame4.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/chikinframes/frame5.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/chikinframes/frame6.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/chikinframes/frame7.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/chikinframes/frame8.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/chikinframes/frame9.obj", main, false, false);
		translate = glm::vec3(20.0f, 6.0f, 0.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		


		model = new Model(this->hwnd, "models/cow/frame1.obj", main, false, false);
		translate = glm::vec3(0.0f, 7.2f, 45.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/cow/frame2.obj", main, false, false);
		translate = glm::vec3(0.0f, 7.2f, 45.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/cow/frame3.obj", main, false, false);
		translate = glm::vec3(0.0f, 7.2f, 45.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/cow/frame4.obj", main, false, false);
		translate = glm::vec3(0.0f, 7.2f, 45.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		model = new Model(this->hwnd, "models/cow/frame5.obj", main, false, false);
		translate = glm::vec3(0.0f, 7.2f, 45.0f);
		scale = glm::vec3(0.5f, 0.5f, 0.5f);	// it's a bit too big for our scene, so scale it down
		model->setTranslate(&translate);
		model->setScale(&scale);
		ourModel.push_back(model);
		animal = new Animales(model);
		vector<glm::vec3> Colisiones2;
		ye = terreno->Superficie(20, 0);
		Colisiones2.push_back(glm::vec3(20.0, ye, 0.0));
		ye = terreno->Superficie(0, 45);
		Colisiones2.push_back(glm::vec3(0.0, ye, 45.0));
		animal->SetPointList(Colisiones2);
		//inicializaBillboards(hWnd);


		vector<glm::vec3> Colisiones;
		//glm::vec3 ColisionPoints;

		//ye = terreno->Superficie(-64, 17);
		/*ColisionPoints = glm::vec3(-64, 0, 17);
		Colisiones.push_back(ColisionPoints);*/
		barn = new Estructura(model);
		ye = terreno->Superficie(-64, 17);
		//translate = glm::vec3(-64.8f, 5.5f, 17.0f);
		Colisiones.push_back(glm::vec3(-69.5, ye, 27.5));
		Colisiones.push_back(glm::vec3(-66.9, ye, 25.2));
		Colisiones.push_back(glm::vec3(-63.4, ye, 22.8));
		Colisiones.push_back(glm::vec3(-61.3, ye, 21.2));
		Colisiones.push_back(glm::vec3(-59.5, ye, 19.5));
		Colisiones.push_back(glm::vec3(-57.6, ye, 18.0));
		Colisiones.push_back(glm::vec3(-55.8, ye, 16.3));
		Colisiones.push_back(glm::vec3(-53.2, ye, 14.2));

		Colisiones.push_back(glm::vec3(-54.5, ye, 12.4));
		Colisiones.push_back(glm::vec3(-58.6, ye, 7.8));
		
		Colisiones.push_back(glm::vec3(-60.0, ye, 5.8));
		Colisiones.push_back(glm::vec3(-62.7, ye, 8.1));
		Colisiones.push_back(glm::vec3(-64.4, ye, 9.9));
		Colisiones.push_back(glm::vec3(-66.2, ye, 11.3));
		Colisiones.push_back(glm::vec3(-68.2, ye, 12.8));
		Colisiones.push_back(glm::vec3(-70.0, ye, 14.4));
		Colisiones.push_back(glm::vec3(-71.8, ye, 16.0));
		Colisiones.push_back(glm::vec3(-73.9, ye, 17.5));
		Colisiones.push_back(glm::vec3(-76.5, ye, 19.8));

		Colisiones.push_back(glm::vec3(-75.0, ye, 21.7));
		Colisiones.push_back(glm::vec3(-73.1, ye, 23.9));
		Colisiones.push_back(glm::vec3(-71.5, ye, 25.6));
		
		Colisiones.push_back(glm::vec3(25.0, ye, 15.0));
		Colisiones.push_back(glm::vec3(-5.0, ye, -10.0));
		Colisiones.push_back(glm::vec3(-70.2, ye, 20.6));
		Colisiones.push_back(glm::vec3(-57.8, ye, 4.3));
		Colisiones.push_back(glm::vec3(7.8, ye, -0.9));
		Colisiones.push_back(glm::vec3(12.2, ye, -1.1));
		Colisiones.push_back(glm::vec3(10.0, ye, -1.5));
		Colisiones.push_back(glm::vec3(8.7, ye, 10.0));
		Colisiones.push_back(glm::vec3(11.4, ye, 9.6));
		Colisiones.push_back(glm::vec3(7.6, ye, 4.5));
		Colisiones.push_back(glm::vec3(12.1, ye, 4.4));
		barn->SetPointList(Colisiones);

		//hammer = new Herramientas(ourModel[1]);
		cow = new ModelResource(ourModel[2]);
		//tape = new Herramientas(ourModel[3]);
		nail = new ModelResource(ourModel[4]);
		hay = new ModelResource(ourModel[5]);
		//axe = new Herramientas(ourModel[6]);
		crow = new ModelResource(ourModel[7]);
		Barn = new ModelResource(ourModel[8]);
		bucket = new ModelResource(ourModel[9]);
		boots = new ModelResource(ourModel[10]);
		//wrench = new Herramientas(ourModel[11]);
	    table = new ModelResource(ourModel[12]);
		ute = new ModelResource(ourModel[13]);
		tract = new ModelResource(ourModel[14]);
		saw = new ModelResource(ourModel[15]);
		chiken = new ModelResource(ourModel[16]);

		inicializaBillboards(hWnd);
	}

	void inicializaBillboards(HWND hWnd)
	{
		float ye;// = terreno->Superficie(51, -51);
		billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Arbol.png", 6, 6, 51, 6 - 1, -51, camara));

		ye = terreno->Superficie(0, 5);
		HUDVector.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/84e.png", 6, 6, 0, ye - 1, 5, camara));
		HUD = new SpriteAnimation(HUDVector);
		//ye = terreno->Superficie(15, -11);
		billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Arbol2.png", 6, 6, 15, 5 - 1, -11, camara));

		//ye = terreno->Superficie(-9, -15);
		billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Arbol3.png", 8, 8, -9, 5.5 - 1, -15, camara));

		ye = terreno->Superficie(0, 0);
		RainVector.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/rain1.png", 4, 16, 0, 0, 0, camara));
		//RainVector.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/rain1.png", 4, 16, 0, 0, 0, camara));
		Lluvia = new SpriteAnimation(RainVector);
	}

	//el metodo render toma el dispositivo sobre el cual va a dibujar
	//y hace su tarea ya conocida
	Scenario* Render(HDC hDC) {
		//borramos el biffer de color y el z para el control de profundidad a la 
		//hora del render a nivel pixel.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		//		glClearColor(255.0f, 255.0f, 255.0f, 255.0f);

				// Actualizamos la camara
		camara->CamaraUpdate();
		float x = camara->getNextPosition().x;
		float z = camara->getNextPosition().z;
		float distancia1 = sqrt(pow(x - 20, 2) + pow(z - 5, 2));
		float distancia2 = sqrt(pow(x - 0, 2) + pow(z - 45, 2));
		float distancia3 = sqrt(pow(x - 0, 2) + pow(z + 10, 2));
		float distancia4;
		hrand = rand() % 3;
		switch (hrand) {
		case 0:
			distancia4 = sqrt(pow(x - 0, 2) + pow(z - 25, 2));
			break;
		case 1:
			distancia4 = sqrt(pow(x - 33, 2) + pow(z - 2, 2));
			//translate = glm::vec3(33.0f, 7.0f, 2.0f);
			break;
		case 2:
			distancia4 = sqrt(pow(x - 4, 2) + pow(z - 53, 2));
			//translate = glm::vec3(4.0f, 7.0f, 53.0f);
			break;
		default:
			distancia4 = sqrt(pow(x - 0, 2) + pow(z - 25, 2));
			break;
		}
		float distancia5;
		wrand = rand() % 3;
		switch (wrand) {
		case 0:
			distancia5 = sqrt(pow(x - 1, 2) + pow(z + 30, 2));
			break;
		case 1:
			distancia5 = sqrt(pow(x + 40, 2) + pow(z + 50, 2));
			//translate = glm::vec3(-40.0f, 6.0f, -50.0f);
			break;
		case 2:
			distancia5 = sqrt(pow(x - 43, 2) + pow(z + 41, 2));
			//translate = glm::vec3(43.0f, 6.0f, -41.0f);
			break;
		default:
			distancia5 = sqrt(pow(x - 1, 2) + pow(z + 30, 2));
			break;
		}
		float distancia6;
		trand = rand() % 3;
		switch (trand) {
		case 0:
			distancia6 = sqrt(pow(x - 0, 2) + pow(z - 30, 2));
			break;
		case 1:
			distancia6 = sqrt(pow(x - 11, 2) + pow(z - 51, 2));
			//translate = glm::vec3(11.0f, 7.0f, 51.0f);
			break;
		case 2:
			distancia6 = sqrt(pow(x + 47, 2) + pow(z - 18, 2));
			//translate = glm::vec3(-47.0f, 7.0f, 18.0f);
			break;
		default:
			distancia6 = sqrt(pow(x - 0, 2) + pow(z - 30, 2));
			break;
		}
		
		float distancia7 = sqrt(pow(x + 64.8, 2) + pow(z - 17, 2));
		//translate = glm::vec3(-64.8f, 5.5f, 17.0f);
		float distancia8 = sqrt(pow(x - 10, 2) + pow(z - 7, 2));
		if (Day == true) {
			if ((distancia1 < 1) && (gethay == false)) {
				gethay = true;
				glm::vec3 translate;
				translate = glm::vec3(-2.0f, -10.0f, -5.0f);
				ourModel[5]->setTranslate(&translate);
			}
			if ((distancia2 < 3) && (gethay == true)) {
				cowcomplete = true;
				glm::vec3 translate;
				glm::vec3 rotation;
				translate = glm::vec3(-0.1f, 5.5f, 42.5f);
				rotation = glm::vec3(0.0f, 1.0f, 0.0f);
				ourModel[5]->setRotation(45, &rotation);
				ourModel[5]->setTranslate(&translate);
				gethay = false;
				objetos = +2;
				animal->ActivateAnimation();
				/*glm::vec3 translate;
				translate = glm::vec3(-2.0f, -10.0f, -5.0f);
				ourModel[2]->setTranslate(&translate);*/
			}
			if ((distancia3 < 1) && (getaxe == 0)) {
				getaxe = true;
				glm::vec3 translate;
				translate = glm::vec3(-2.0f, -10.0f, -5.0f);
				ourModel[6]->setTranslate(&translate);
			}
			if ((distancia4 < 1) && (gethammer == 0)) {
				gethammer = true;
				glm::vec3 translate;
				translate = glm::vec3(-2.0f, -10.0f, -5.0f);
				ourModel[1]->setTranslate(&translate);
			}
			if ((distancia5 < 1) && (getwrench == 0)) {
				getwrench = true;
				glm::vec3 translate;
				translate = glm::vec3(-2.0f, -10.0f, -5.0f);
				ourModel[11]->setTranslate(&translate);
			}
			if ((distancia6 < 1) && (gettape == 0)) {
				gettape = true;
				glm::vec3 translate;
				translate = glm::vec3(-2.0f, -10.0f, -5.0f);
				ourModel[3]->setTranslate(&translate);
			}
			if (distancia7 < 5) {
				if (getaxe == 1) {
					objetos++;
					glm::vec3 translate;
					glm::vec3 rotation;
					translate = glm::vec3(-60.6f, 6.8f, 18.8f);
					rotation = glm::vec3(1.0f, 1.0f, 0.0f); 
					ourModel[6]->setRotation(45, &rotation);
					ourModel[6]->setTranslate(&translate);
					axe->DectivateAnimation();
					getaxe = false;
				}
				if (gethammer == 1) {
					objetos++;
					glm::vec3 translate;
					glm::vec3 rotation;
					translate = glm::vec3(-65.7f, 5.8f, 19.8f);
					rotation = glm::vec3(0.0f, 0.0f, -1.0f);
					ourModel[1]->setRotation(90, &rotation);
					ourModel[1]->setTranslate(&translate);
					hammer->DectivateAnimation();
					gethammer = false;
				}
				if (getwrench == 1) {
					objetos++;
					glm::vec3 translate;
					translate = glm::vec3(-70.7f, 7.25f, 20.27f);
					ourModel[11]->setTranslate(&translate);
					wrench->DectivateAnimation();
					getwrench = false;
				}
				if (gettape == 1) {
					objetos++;
					glm::vec3 translate;
					glm::vec3 rotation;
					translate = glm::vec3(-69.4f, 7.25f, 20.8f);
					rotation = glm::vec3(-1.0f, 0.0f, 0.0f);
					ourModel[3]->setRotation(90, &rotation);
					ourModel[3]->setTranslate(&translate);
					tape->DectivateAnimation();
					gettape = false;
				}

				if ((getaxe == false) && (gethammer == false) && (getwrench == false) && (gettape == false) && (objetos == 4)) {
					/*glm::vec3 translate;
					translate = glm::vec3(-2.0f, -10.0f, -5.0f);
					ourModel[8]->setTranslate(&translate);*/
					toolcomplete = true;
					objetos++;
				}
			}

			if ((distancia8 < 3) /*&& (toolcomplete == true) && (cowcomplete == true)*/) {
				//bool ganar = true;
				if (objetos <= 4) {
					MessageBox(hwnd, L"Perdiste, te falto completar las tareas", L"Juego terminado", MB_ICONINFORMATION);
					PostQuitMessage(0);
				}
				else if (objetos == 5) {
					MessageBox(hwnd, L"Ganaste, completaste casi todas las tareas", L"Juego terminado", MB_ICONINFORMATION);
					PostQuitMessage(0);
				}
				else if (objetos >= 6) {
					MessageBox(hwnd, L"Ganaste, completaste todas las tareas!", L"Juego terminado", MB_ICONINFORMATION);
					PostQuitMessage(0);
				}
			}
		}
		else if (Day == false) {
			if ((distancia8 < 3) /*&& (toolcomplete == true) && (cowcomplete == true)*/) {
				//bool ganar = true;
				if (objetos <= 4) {
					MessageBox(hwnd, L"Perdiste, te falto completar las tareas", L"Juego terminado", MB_ICONINFORMATION);
					PostQuitMessage(0);
				}
				else if (objetos == 5) {
					MessageBox(hwnd, L"Ganaste, completaste casi todas las tareas", L"Juego terminado", MB_ICONINFORMATION);
					PostQuitMessage(0);
				}
				else if (objetos >= 6) {
					MessageBox(hwnd, L"Ganaste, completaste todas las tareas!", L"Juego terminado", MB_ICONINFORMATION);
					PostQuitMessage(0);
				}
			}
		}

		// Decimos que dibuje la media esfera

		if (tics == 3000) {
			tics = 0;
			if (Day == true) {
				Day = false;
			}
			else {
				Day = true;
			}
			for (int i = 0; i < ourModel.size(); i++) {
				ourModel[i]->Shade();
			}
		}
		if (Day == true) {
			sky->Draw();
			terreno->Draw();
			agua->Draw();
		}
		else {
			skyNight->Draw();
			terrenoNight->Draw();
			aguaNight->Draw();

		}
		// Ahora el terreno
		tics++;

		//draw
		bool LluviaState = sky->GetWeather();
		Lluvia->SetState(LluviaState);

		glm::vec3 CameraNextPosition = camara->GetFrontNearbyPosition();
		Lluvia->Lluvia(CameraNextPosition);
		Lluvia->GetSprite()->Draw();

		bool HUDState = sky->GetHUD();
		HUD->SetState(HUDState);

		//glm::vec3 CameraNextPosition = camara->GetFrontNearbyPosition();
		HUD->HUD(CameraNextPosition);
		HUD->GetSprite()->Draw();


		glm::vec3 rotation;
		float mov = 0;
		anim = hammer->GetAnimationState();
		if (anim == true) {
			mov = 0;
			mov = ourModel[1]->getRotationAngle();
			mov++;
			rotation = glm::vec3(0.0f, 1.0f, 0.0f);
			ourModel[1]->setRotation(mov, &rotation);
		}
		anim = wrench->GetAnimationState();
		if (anim == true) {
			mov = 0;
			mov = ourModel[11]->getRotationAngle();
			mov++;
			rotation = glm::vec3(0.0f, 1.0f, 0.0f);
			ourModel[11]->setRotation(mov, &rotation);
		}
		anim = axe->GetAnimationState();
		if (anim == true) {
			mov = 0;
			mov = ourModel[6]->getRotationAngle();
			mov++;
			rotation = glm::vec3(0.0f, 1.0f, 0.0f);
			ourModel[6]->setRotation(mov, &rotation);
		}
		anim = tape->GetAnimationState();
		if (anim == true) {
			mov = 0;
			mov = ourModel[3]->getRotationAngle();
			mov++;
			rotation = glm::vec3(0.0f, 1.0f, 0.0f);
			ourModel[3]->setRotation(mov, &rotation);
		}
		// Dibujamos cada modelo que este cargado en nuestro arreglo de modelos
		for (int i = 0; i < ourModel.size(); i++) {
			if (i < 16) {
				if (cowcomplete == false) {
					ourModel[i]->Draw();
				}
				else {
					if (i != 2) {
						ourModel[i]->Draw();
					}
				}
			}
		}

		// Dibujamos cada billboard que este cargado en el arreglo de billboards.
		for (int i = 0; i < billBoard.size(); i++) {
			billBoard[i]->Draw();
		}


		if (frames > 0 && frames <= 5) {
			ourModel[16]->Draw();//1
		}
		if (frames > 5 && frames <= 10) {
			ourModel[17]->Draw();//2
		}
		if (frames > 10 && frames <= 15) {
			ourModel[18]->Draw();//3
		}
		if (frames > 15 && frames <= 20) {
			ourModel[19]->Draw();//4
		}
		if (frames > 20 && frames <= 25) {
			ourModel[20]->Draw();//5
		}
		if (frames > 25 && frames <= 30) {
			ourModel[21]->Draw();//6
		}
		if (frames > 30 && frames <= 35) {
			ourModel[20]->Draw();//5
		}
		if (frames > 35 && frames <= 40) {
			ourModel[21]->Draw();//6
		}
		if (frames > 40 && frames <= 45) {
			ourModel[20]->Draw();//5
		}
		if (frames > 45 && frames <= 50) {
			ourModel[21]->Draw();//6
		}
		if (frames > 50 && frames <= 55) {
			ourModel[19]->Draw();//4
		}
		if (frames > 55 && frames <= 60) {
			ourModel[18]->Draw();//3
		}
		if (frames > 60 && frames <= 65) {
			ourModel[17]->Draw();//2
		}
		if (frames > 65 && frames <= 80) {
			ourModel[16]->Draw();//1
		}
		if (frames > 80 && frames <= 82) {
			ourModel[22]->Draw();//7
		}
		if (frames > 82 && frames <= 120) {
			ourModel[23]->Draw();//8
		}
		if (frames > 120 && frames <= 122) {
			ourModel[22]->Draw();//7
		}
		if (frames > 122 && frames <= 200) {
			ourModel[16]->Draw();//1
		}
		//if (frames > 40 && frames <= 45) {
		//	ourModel[24]->Draw();//9
		//}
		if (frames >= 200) {
			frames = 0;
		}
		frames++;
		// Le decimos a winapi que haga el update en la ventana
		
		if (animal->GetAnimationState() == true) {
			if (frames2 > 0 && frames2 <= 10) {
				ourModel[29]->Draw();
			}
			if (frames2 > 10 && frames2 <= 20) {
				ourModel[28]->Draw();
			}
			if (frames2 > 20 && frames2 <= 30) {
				ourModel[25]->Draw();
			}
			if (frames2 > 30 && frames2 <= 40) {
				ourModel[26]->Draw();
			}
			if (frames2 > 40 && frames2 <= 50) {
				ourModel[27]->Draw();
			}
			if (frames2 > 50 && frames2 <= 60) {
				ourModel[25]->Draw();
			}
			if (frames2 > 60 && frames2 <= 70) {
				ourModel[26]->Draw();
			}
			if (frames2 > 70 && frames2 <= 80) {
				ourModel[27]->Draw();
			}
			if (frames2 > 80 && frames2 <= 90) {
				ourModel[25]->Draw();
			}
			if (frames2 > 90 && frames2 <= 100) {
				ourModel[26]->Draw();
			}
			if (frames2 > 100 && frames2 <= 110) {
				ourModel[27]->Draw();
			}
			if (frames2 > 110 && frames2 <= 120) {
				ourModel[25]->Draw();
			}
			if (frames2 > 120 && frames2 <= 130) {
				ourModel[26]->Draw();
			}
			if (frames2 > 130 && frames2 <= 140) {
				ourModel[27]->Draw();
			}
			if (frames2 > 140 && frames2 <= 150) {
				ourModel[25]->Draw();
			}
			if (frames2 > 150 && frames2 <= 160) {
				ourModel[26]->Draw();
			}
			if (frames2 > 160 && frames2 <= 170) {
				ourModel[27]->Draw();
			}
			if (frames2 > 170 && frames2 <= 180) {
				ourModel[25]->Draw();
			}
			if (frames2 > 180 && frames2 <= 190) {
				ourModel[26]->Draw();
			}
			if (frames2 > 190 && frames2 <= 200) {
				ourModel[27]->Draw();
			}
			if (frames2 > 200 && frames2 <= 210) {
					ourModel[28]->Draw();
			}
			if (frames2 > 210 && frames2 <= 280) {
					ourModel[29]->Draw();
			}
			if (frames2 >= 280) {
				frames2 = 0;
			}
			frames2++;
		}


		SwapBuffers(hDC);
		return this;
	}
	
	std::vector<Model*> *getLoadedModels() {
		return &ourModel;
	}
	std::vector<Billboard*> *getLoadedBillboards() {
		return &billBoard;
	}
	MainModel* getMainModel() {
		return this->camara;
	}
	float getAngulo() {
		return this->angulo;
	}
	void setAngulo(float angulo) {
		this->angulo = angulo;
	}
	
	/*ModelResource* GetAxe() {
		return axe;
	}
	ModelResource* GetHammer() {
		return hammer;
	}
	ModelResource* GetCow() {
		return cow;
	}
	ModelResource* GetTape() {
		return tape;
	}
	ModelResource* GetWrench() {
		return wrench;
	}
	ModelResource* GetHay() {
		return hay;
	}
	ModelResource* GetUte() {
		return ute;
	}
	ModelResource* GetBarn() {
		return barn;
	}*/


	SkyDome* getSky() {
		return sky;
	}
	Terreno* getTerreno() {
		return terreno;
	}
	Estructura* GetGranero() {
		return barn;
	}
	Animales* GetAnimal() {
		return animal;
	}

	~Scenario() {
		if (this->sky != NULL) {
			delete this->sky;
			this->sky = NULL;
		}
		if (this->terreno != NULL) {
			delete this->terreno;
			this->terreno = NULL;
		}
		if (billBoard.size() > 0)
			for (int i = 0; i < billBoard.size(); i++)
				delete billBoard[i];
		this->billBoard.clear();
		if (ourModel.size() > 0)
			for (int i = 0; i < ourModel.size(); i++)
				if (ourModel[i] != camara)
					delete ourModel[i];
		this->ourModel.clear();
	}
};

#endif




//
//void inicializaBillboards(HWND hWnd)
//{
//
//	float ye = terreno->Superficie(0, 0);
//	billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Imagen1.png", 6, 6, 0, ye - 1, 0, camara));
//
//	ye = terreno->Superficie(0, 0);
//	billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Imagen2.png", 6, 6, 0, ye - 1, 0, camara));
//
//	ye = terreno->Superficie(0, 0);
//	billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Imagen3.png", 6, 6, 0, ye - 1, 0, camara));
//
//	ye = terreno->Superficie(0, 0);
//	billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Imagen4.png", 6, 6, 0, ye - 1, 0, camara));
//
//	ye = terreno->Superficie(0, 0);
//	billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Imagen5.png", 6, 6, 0, ye - 1, 0, camara));
//
//	ye = terreno->Superficie(0, 0);
//	billBoard.push_back(new Billboard(hWnd, (WCHAR*)L"billboards/Imagen6.png", 6, 6, 0, ye - 1, 0, camara));
//
//}
//
////el metodo render toma el dispositivo sobre el cual va a dibujar
////y hace su tarea ya conocida
//Scenario* Render(HDC hDC) {
//	//borramos el biffer de color y el z para el control de profundidad a la 
//	//hora del render a nivel pixel.
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
//	//		glClearColor(255.0f, 255.0f, 255.0f, 255.0f);
//
//	sprite++;
//	// Actualizamos la camara
//	camara->CamaraUpdate();
//
//	// Decimos que dibuje la media esfera
//	sky->Draw();
//	// Ahora el terreno
//	terreno->Draw();
//
//	if (sprite > 0 && sprite <= 5) {
//
//		billBoard[0]->Draw();
//	}
//	if (sprite > 5 && sprite <= 10) {
//
//		billBoard[1]->Draw();
//	}
//	if (sprite > 10 && sprite <= 15) {
//
//		billBoard[2]->Draw();
//
//	}
//	if (sprite > 15 && sprite <= 20) {
//
//		billBoard[3]->Draw();
//
//	}
//	if (sprite > 20 && sprite <= 25) {
//
//		billBoard[4]->Draw();
//
//	}
//	if (sprite > 25 && sprite <= 30) {
//
//		billBoard[5]->Draw();
//
//	}
//	if (sprite >= 30) {
//		sprite = 0;
//	}
//
//	// Dibujamos cada modelo que este cargado en nuestro arreglo de modelos
//	for (int i = 0; i < ourModel.size(); i++) {
//		ourModel[i]->Draw();
//	}
//
//	// Dibujamos cada billboard que este cargado en el arreglo de billboards.
///*	for (int i = 0; i < billBoard.size(); i++) {
//		billBoard[i]->Draw();
//	}*/
//
//	// Le decimos a winapi que haga el update en la ventana
//	SwapBuffers(hDC);
//	return this;
//
//}