#pragma once
#include "Model.h"
#include "MainModel.h"
#include "SkyDome.h"
#include "Terreno.h"
#include "Billboard.h"
#include "ModelResource.h"
#include "Estructura.h"
#include "Animales.h"
#include "Herramientas.h"

class Scene {
	public:
		virtual float getAngulo() = 0;
		virtual void setAngulo(float angulo) = 0;
		virtual MainModel* getMainModel() = 0;
		virtual Scene* Render(HDC hDC) = 0;
		virtual SkyDome* getSky() = 0;
		virtual Terreno* getTerreno() = 0;
		float x, y, z;
		virtual Estructura* GetGranero() = 0;
		virtual Animales* GetAnimal() = 0;

	/*	virtual ModelResource* GetAxe() = 0;
		virtual ModelResource* GetHammer() = 0;
		virtual ModelResource* GetCow() = 0;
		virtual ModelResource* GetTape() = 0;
		virtual ModelResource* GetWrench() = 0;
		virtual ModelResource* GetHay() = 0;
		virtual ModelResource* GetUte() = 0;
		virtual ModelResource* GetBarn() = 0;*/
	
		virtual std::vector<Model*>* getLoadedModels() = 0;
		virtual std::vector<Billboard*>* getLoadedBillboards() = 0;
		Model* lookForCollition() {
			std::vector<Model*> *ourModel = getLoadedModels();
			MainModel *camara = getMainModel();
			Estructura* barn = GetGranero();
			Animales* animal = GetAnimal();
			/*ModelResource* axe = GetAxe();
			ModelResource* hammer = GetHammer();
			ModelResource* cow = GetCow();
			ModelResource* tape = GetTape();
			ModelResource* wrench = GetWrench();
			ModelResource* hay = GetHay();
			ModelResource* ute = GetUte();
			ModelResource* barn = GetBarn();

			for (int i = 0; i < ourModel->size(); i++) {
				if ((*ourModel)[i] != camara) {
					if (camara->colisionaCon((*ourModel)[i])) {
						if (i == 5) {
							hay->ObtenerObjeto();
							hay->DesaparecerObjeto();
						}
						else if (i == 2) {
							if (hay->GetObjectState() == true) {
								cow->ObtenerObjeto();
								cow->DesaparecerObjeto();
							}
						}
					}
				}
			}*/
			if (barn->CheckColision(camara))
			{
				return barn->GetGranero();
			}
			if (animal->CheckColision(camara))
			{
				return animal->GetAnimal();
			}
			
			for (int i = 0; i < ourModel->size(); i++) {
				if ((*ourModel)[i] != camara) {
					if (camara->colisionaCon((*ourModel)[i])) {
						return (*ourModel)[i];
					}
				}
			}

			return NULL;
		}
};