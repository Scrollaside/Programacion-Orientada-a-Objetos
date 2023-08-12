#pragma once
#include "model.h"
#include "MainModel.h"
#include <ctime>

class ModelResource : public Model
{
private:
    //vector<Model*>* ResourcesModels;
    Model* Objeto;
    bool ObjectState = false;
    bool Animation = true;
    bool Colision = false;
    std::vector<glm::vec3> PointList;
    MainModel* ola;
    int opcion = 0;
public:
    //ModelResource(vector<Model*>& NewModel);
    ModelResource(Model* NewModel, glm::vec3 MainPoint);
    ModelResource(Model* NewModel);
    ModelResource();
    void SetResources(Model* Objeto, int n);
    void MovCircular();
    void ObtenerObjeto();
    void DesaparecerObjeto();
    bool GetObjectState();
    glm::vec3  RandomPosition(glm::vec3 Pos1, glm::vec3 Pos2, glm::vec3 Pos3);
    Model* GetObjeto();

    bool CheckDistance(int i, MainModel* Camera);
    bool CheckAllDistances(MainModel* Camera);

    void SetAnimationLever();
    void DectivateAnimation();
    bool GetAnimationState();
    int ReturnRand();
    //void GetKey(vector<Mod);
    ~ModelResource();
};

