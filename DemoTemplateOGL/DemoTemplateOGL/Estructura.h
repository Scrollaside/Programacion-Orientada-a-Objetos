
class Estructura {

private:
	std::vector<glm::vec3> PointList;
	Model* barn;
	glm::vec3 PrevCamara;
	bool Colision = false;
	bool CambioDeColision = false;
	bool SegundoCambio = false;

public:
	Estructura(Model* newCasa) {

		barn = newCasa;
	}

	void SetPointList(vector<glm::vec3> newPointList)
	{
		PointList = newPointList;
	}

	vector<glm::vec3> GetPointList() {
		return PointList;
	}

	Model* GetGranero() {
		return barn;
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


		if (distance < 2)
		{
			Colision = true;
		}
		else
		{
			Colision = false;

		}

		return Colision;
	}

	bool GetColision() {
		return Colision;
	}
};
