#ifndef _terreno
#define _terreno

class Terreno : public Model {

private:
	float anchof;
	float proff;
	float deltax, deltaz;
	bool water = false;
	bool WaterUp = false;
	bool WaterDown = true;
	bool WaterLeft;
	bool WaterRight;
	float waterH = 3.5;
	float waterL;
public:
	int verx, verz;
	Camera* cameraDetails = NULL;
	//el nombre numerico de la textura en cuestion, por lo pronto una

	void moveWater() {
		if (WaterUp == true) {
			waterH = waterH + 0.005;
		}
		else if (WaterDown == true) {
			waterH = waterH - 0.005;
		}
		if (waterH <= 3.5) {
			WaterUp = true;
			WaterDown = false;
		}
		if (waterH >= 4) {
			WaterUp = false;
			WaterDown = true;
		}
		if (WaterLeft == false) {
			waterL = waterL + 0.01;
		}
		else {
			waterL = waterL - 0.01;
		}
		if (waterL >= 2) {
			WaterLeft = true;
		}
		if (waterL <= 0) {
			WaterLeft = false;
		}
	}



	Terreno(HWND hWnd, WCHAR alturas[], WCHAR textura[], float ancho, float prof, Camera* camera) {
		cameraDetails = camera;
		vector<unsigned int> indices;
		vector<Texture>      textures;
		vector<Material> materials;
		vector<Vertex>       vertices;
		unsigned int planoTextura;
		int mapAlturaX, mapAlturaY, mapAlturaComp;
		setHWND(hWnd);
		anchof = ancho;
		proff = prof;
		//cargamos la textura de la figura
		wstring tex(alturas);
		string text(tex.begin(), tex.end());
		unsigned char* mapaAlturas = loadFile(text.c_str(), &mapAlturaX, &mapAlturaY, &mapAlturaComp, 0);
		//en caso del puntero de la imagen sea nulo se brica esta opcion
		tex.assign(textura);
		text.assign(tex.begin(), tex.end());
		UTILITIES_OGL::Maya terreno = UTILITIES_OGL::Plano(mapAlturaX, mapAlturaY, ancho, prof, mapaAlturas, mapAlturaComp, 30);
		UTILITIES_OGL::vectoresEsfera(terreno, vertices, indices, mapAlturaX * mapAlturaY * 3, mapAlturaX * mapAlturaY * 6);
		delete terreno.maya;
		delete terreno.indices;
		verx = mapAlturaX;
		verz = mapAlturaY;
		deltax = anchof / verx;
		deltaz = proff / verz;
		//disponemos la textura del gdi.
		delete []mapaAlturas;

		// cargamos la textura de la figura
		wstring n(textura);
		string texturan(n.begin(), n.end());
		planoTextura = TextureFromFile(hWnd, texturan.c_str(), this->directory);

		Texture t = { planoTextura , "texture_height", texturan.c_str() };
		textures.push_back(t);
		meshes.push_back(Mesh(vertices, indices, textures, materials));
		setDefaultShader(false);
	}

	void isWater() {
		water = true;
	}


	~Terreno() {
		//nos aseguramos de disponer de los recursos previamente reservados
		if (gpuDemo != NULL) {
			delete gpuDemo;
			gpuDemo = NULL;
		}
	}

	void Draw() {
		if (gpuDemo == NULL) {
			gpuDemo = new Shader("shaders/models/1.model_loading.vs", "shaders/models/1.model_loading.fs");
			setDefaultShader(true);
		}
		if (getDefaultShader()) {
			gpuDemo->use();
			prepShader(*gpuDemo);
			Draw(*gpuDemo);
			gpuDemo->desuse();
		} else Draw(*gpuDemo);
	}

	void Draw(Shader& shader) {
		Model::Draw(shader);
	}

	float Superficie(float x, float z) {
		vector<Vertex> vertices = meshes[0].vertices;
		//obtenemos el indice pero podria incluir una fraccion
		float indicefx = (x + anchof / 2) / deltax;
		float indicefz = (z + proff / 2) / deltaz;
		//nos quedamos con solo la parte entera del indice
		int indiceix = (int)indicefx;
		int indiceiz = (int)indicefz;
		//nos quedamos con solo la fraccion del indice
		float difx = indicefx - indiceix;
		float difz = indicefz - indiceiz;

		float altura;
		float D;

		//el cuadro del terreno esta formado por dos triangulos, si difx es mayor que dify 
		//entonces estamos en el triangulo de abajo en caso contrario arriba
		if (difx > difz)
		{
			//obtenemos el vector 1 de dos que se necesitan
			glm::vec3 v1(vertices[indiceix + 1 + (indiceiz + 1) * verx].Position.x - vertices[indiceix + indiceiz * verx].Position.x,
				vertices[indiceix + 1 + (indiceiz + 1) * verx].Position.y - vertices[indiceix + indiceiz * verx].Position.y,
				vertices[indiceix + 1 + (indiceiz + 1) * verx].Position.z - vertices[indiceix + indiceiz * verx].Position.z);
			//obtenemos el vector 2 de dos
			glm::vec3 v2(vertices[indiceix + 1 + indiceiz * verx].Position.x - vertices[indiceix + indiceiz * verx].Position.x,
				vertices[indiceix + 1 + indiceiz * verx].Position.y - vertices[indiceix + indiceiz * verx].Position.y,
				vertices[indiceix + 1 + indiceiz * verx].Position.z - vertices[indiceix + indiceiz * verx].Position.z);

			//con el producto punto obtenemos la normal y podremos obtener la ecuacion del plano
			//la parte x de la normal nos da A, la parte y nos da B y la parte z nos da C
			glm::vec3 normalPlano = glm::cross(v1, v2);
			//entonces solo falta calcular D
			D = -1 * (normalPlano.x * vertices[indiceix + indiceiz * verx].Position.x +
				normalPlano.y * vertices[indiceix + indiceiz * verx].Position.y +
				normalPlano.z * vertices[indiceix + indiceiz * verx].Position.z);
			//sustituyendo obtenemos la altura de contacto en el terreno
			altura = ((-normalPlano.x * x - normalPlano.z * z - D) / normalPlano.y);
		}
		else
		{
			glm::vec3 v1(vertices[indiceix + (indiceiz + 1) * verx].Position.x - vertices[indiceix + indiceiz * verx].Position.x,
				vertices[indiceix + (indiceiz + 1) * verx].Position.y - vertices[indiceix + indiceiz * verx].Position.y,
				vertices[indiceix + (indiceiz + 1) * verx].Position.z - vertices[indiceix + indiceiz * verx].Position.z);

			glm::vec3 v2(vertices[indiceix + 1 + (indiceiz + 1) * verx].Position.x - vertices[indiceix + indiceiz * verx].Position.x,
				vertices[indiceix + 1 + (indiceiz + 1) * verx].Position.y - vertices[indiceix + indiceiz * verx].Position.y,
				vertices[indiceix + 1 + (indiceiz + 1) * verx].Position.z - vertices[indiceix + indiceiz * verx].Position.z);


			glm::vec3 normalPlano = glm::cross(v1, v2);

			D = -1 * (normalPlano.x * vertices[indiceix + indiceiz * verx].Position.x +
				normalPlano.y * vertices[indiceix + indiceiz * verx].Position.y +
				normalPlano.z * vertices[indiceix + indiceiz * verx].Position.z);

			altura = ((-normalPlano.x * x - normalPlano.z * z - D) / normalPlano.y);
		}
		return altura;
	}

	void prepShader(Shader& shader) {
		glm::vec3 lightColor;
		lightColor.x = sin(7200 * 2.0f);
		lightColor.y = sin(7200 * 0.7f);
		lightColor.z = sin(7200 * 1.3f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
		shader.setVec3("light.ambient", ambientColor);
		shader.setVec3("light.diffuse", diffuseColor);
		shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		shader.setVec3("light.position", lightPos);
		shader.setVec3("viewPos", cameraDetails->getPosition());

		// view/projection transformations
		shader.setMat4("projection", cameraDetails->getProjection());
		shader.setMat4("view", cameraDetails->getView());

		// render the loaded model
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
//			model = glm::translate(model, glm::vec3(cameraDetails.Position->x, cameraDetails.Position->y - 5, cameraDetails.Position->z)); // translate it down so it's at the center of the scene
		//model = glm::scale(model, glm::vec3(0.0025f, 0.0025f, 0.0025f));	// it's a bit too big for our scene, so scale it down
//			model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		if (water == false) {
			model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		}
		else {
			moveWater();
			model = glm::translate(model, glm::vec3(0.0f, waterH, waterL));
		}
		
		shader.setMat4("model", model);
	}
};

#endif 