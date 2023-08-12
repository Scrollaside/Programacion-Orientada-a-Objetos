#include "ModelResource.h"


//ModelResource::ModelResource(vector<Model*>& NewModel)
//{
//    //vector<Model*>* ResourcesModels;
//    /*ResourcesModels = new vector<Model*>(NewModel);
//    SetResources((*ResourcesModels)[1], 1);*/
//}
//
ModelResource::ModelResource() {};

ModelResource::ModelResource(Model* NewModel)
{
    Objeto = NewModel;
}
ModelResource::ModelResource(Model* NewModel, glm::vec3 MainPoint)
{
    Objeto = NewModel;
    PointList.push_back(MainPoint);
}
void  ModelResource::MovCircular()
{
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotation;

    float mov = 0;
    mov = Objeto->getRotationAngle();
    mov++;
    rotation = glm::vec3(0.0f, 1.0f, 0.0f); //rotation Y
    Objeto->setRotation(mov, &rotation);
}
void ModelResource::DesaparecerObjeto() {
    glm::vec3 translate;
    translate = glm::vec3(0, -100, 0);
    Objeto->setTranslate(&translate);
}
void  ModelResource::ObtenerObjeto()
{
    ObjectState = true;

}
bool ModelResource::GetObjectState()
{
    return ObjectState;
}
bool ModelResource::CheckDistance(int i, MainModel* Camera) {

    bool CERCA = false;
    float powX = (pow(Objeto->getTranslate()->x - Camera->getPosition().x, 2));
    float powZ = (pow(Objeto->getTranslate()->z - Camera->getPosition().z, 2));
    float sumXZ = powX + powZ;

    if (sumXZ < 0)
    {
        sumXZ = sumXZ * -1;
    }
    double distance = sqrt(sumXZ);


    if (distance < 4)
    {
        Colision = true;
    }
    else
    {
        Colision = false;

    }

    return Colision;
}
bool ModelResource::CheckAllDistances(MainModel* Camera) {

    for (int i = 0; i < PointList.size(); i++)
    {
        if (CheckDistance(i, Camera))
        {
            return true;
        }
    }
    return false;
}
Model* ModelResource::GetObjeto() {
    return Objeto;
}




void ModelResource::SetResources(Model* Objeto, int n)
{
    switch (n)
    {
    case 1:
        Objeto = Objeto;
        break;
    }
}
glm::vec3  ModelResource::RandomPosition(glm::vec3 Pos1, glm::vec3 Pos2, glm::vec3 Pos3) {
    // Configura la semilla para generar números aleatorios
    srand(time(nullptr));

    // Genera un número aleatorio entre 0 y 2
    opcion = rand() % 3;

    // Asigna una opción basada en el número aleatorio
    std::string seleccion;
    switch (opcion) {
    case 0:
        return Pos1;
        break;
    case 1:
        return Pos2;
        break;
    case 2:
        return Pos3;
        break;
    default:
        return Pos1;
        break;
    }

}
int ModelResource::ReturnRand() {
    return opcion;
}
void ModelResource::DectivateAnimation() {
    Animation = false;
}
bool ModelResource::GetAnimationState() {
    return Animation;
}
void ModelResource::SetAnimationLever()
{
    glm::vec3 LeverRotation;
    float mov = 0;
    mov = Objeto->getRotationAngle();
    mov = mov + 2;
    if (mov > 160)
    {
        Animation = false;
        ObtenerObjeto();
        //mov = 45;
    }
    LeverRotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation Y
    Objeto->setRotation(mov, &LeverRotation);
}

ModelResource::~ModelResource()
{
    //delete ResourcesModels;
    if (Objeto != NULL)
    {
        delete Objeto;
    }
}
