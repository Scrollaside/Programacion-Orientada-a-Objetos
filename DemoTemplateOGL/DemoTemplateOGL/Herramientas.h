#pragma once
#include "ModelResource.h"

class Herramientas :
    public ModelResource
{
private:
    bool ObjectState = false;
    bool Animation = false;

    int ActualFrame;
    int Count;

    bool AnimationUp = true;
    bool AnimationDown = false;

    Model* Object;

public:

    Herramientas(Model* NewObject);
    void ActivateAnimation();
    void SetAnimation();
    bool GetAnimationState();
    void Obtener();
    bool GetObjectState();
};

