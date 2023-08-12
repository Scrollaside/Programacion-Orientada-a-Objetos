
class Animales {

private:
	std::vector<glm::vec3> PointList;
	Model* animal;
	glm::vec3 PrevCamara;
	bool Colision = false;
	bool CambioDeColision = false;
	bool SegundoCambio = false;
	bool Animation = false;

public:
	Animales(Model* newAnim) {

		animal = newAnim;
	}

	void SetPointList(vector<glm::vec3> newPointList)
	{
		PointList = newPointList;
	}

	vector<glm::vec3> GetPointList() {
		return PointList;
	}

	Model* GetAnimal() {
		return animal;
	}

	bool  CheckColision(MainModel* Camera) {
		for (int i = 0; i < PointList.size(); i++)
		{
			if (CheckDistance(i, Camera))
			{
				return true;
			}
		}
		return false;
	}

	bool CheckDistance(int i, MainModel* Camera) {

		bool CERCA = false;
		float powX = (pow(PointList[i].x - Camera->getNextPosition().x, 2));
		float powZ = (pow(PointList[i].z - Camera->getNextPosition().z, 2));
		float sumXZ = powX + powZ;

		if (sumXZ < 0)
		{
			sumXZ = sumXZ * -1;
		}
		double distance = sqrt(sumXZ);


		if (distance < 1)
		{
			Colision = true;
		}
		else
		{
			Colision = false;

		}

		return Colision;
	}

	void ActivateAnimation() {
		Animation = true;
	}
	bool GetAnimationState() {
		return Animation;
	}
	bool GetColision() {
		return Colision;
	}
};
