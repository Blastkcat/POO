#include "Scenario.h"

#ifdef __linux__ 
#define ZeroMemory(x,y) memset(x,0,y)
#define wcscpy_s(x,y,z) wcscpy(x,z)
#define wcscat_s(x,y,z) wcscat(x,z)
#endif
extern bool KEYS[256];
Scenario::Scenario(Camera *cam) {
    glm::vec3 translate;
	glm::vec3 scale;
    Model* model = new Model("models/Cube/Cube.obj", cam);
	translate = glm::vec3(0.0f, 0.0f, 3.0f);
	scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
	model->setScale(&scale);
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	InitGraph(model);
}
Scenario::Scenario(Model *camIni) {
    InitGraph(camIni);
}
void Scenario::InitGraph(Model *main) {
    float matAmbient[] = { 1,1,1,1 };
	float matDiff[] = { 1,1,1,1 };
	angulo = 0;
	camara = main;
	//creamos el objeto skydome
	sky = new SkyDome(32, 32, 20, (WCHAR*)L"skydome/night_sky.jpg", main->cameraDetails);
	terreno = new Terreno((WCHAR*)L"skydome/terreno.jpg", (WCHAR*)L"skydome/texterr2.jpg", 800, 800, main->cameraDetails);
	
	lago=new Water((WCHAR*)L"textures/terreno.bmp", (WCHAR*)L"textures/water.bmp", 20, 20, camara->cameraDetails);
	glm::vec3 translate;
	glm::vec3 scale;
	glm::vec3 rotation;
	translate = glm::vec3(0.0f, 18.0f, 30.0f);
	scale = glm::vec3(50.0f, 1.0f, 50.0f);
	

	// Configura lo mismo para el segundo lago si lo usas
	if (lago != NULL) {
		translate = glm::vec3(150.0f, 15.0f, -50.0f); // Altura distinta
		lago->setTranslate(&translate);

		scale = glm::vec3(10.0f, 1.0f, 10.0f); // Lago más pequeño (200x200)
		lago->setScale(&scale);
	}
	
	ourModel.emplace_back(main);
	

	Model* model;
	model = new Model("models/Camp/campfire.glb", main->cameraDetails);
	translate = glm::vec3(0.0f, terreno->Superficie(0,20)+0.1f, 20.0f);
	scale= glm::vec3(1.5f, 1.5f, 1.5f);	// it's a bit too big for our scene, so scale it down
	model->setScale(&scale);
	model->setTranslate(&translate);
	model->setNextTranslate(&translate);
	rotation = glm::vec3(1.0f, 0.0f, 0.0f); //rotation X
	model->setNextRotX(270);
	ourModel.emplace_back(model);

	Model* log = new Model("models/Camp/log.glb", main->cameraDetails);
	translate = glm::vec3(0.0f, terreno->Superficie(0.0f, 30.0f)+0.2f, 30.0f);
	log->setNextTranslate(&translate);
	log->setTranslate(&translate);
	scale = glm::vec3(0.25f, 0.25f, 0.25f);	// it's a bit too big for our scene, so scale it down
	log->setScale(&scale);
	ourModel.emplace_back(log);

	Model* camp = new Model("models/Camp/camp.glb", main->cameraDetails);
	translate = glm::vec3(-30.0f, terreno->Superficie(-30.0f, 20.0f) + 6, 20.0f);
	camp->setNextTranslate(&translate);
	camp->setTranslate(&translate);
	scale = glm::vec3(3.0f, 3.0f, 3.0f);	// it's a bit too big for our scene, so scale it down
	camp->setScale(&scale);
	camp->setNextRotY(90);
	ourModel.emplace_back(camp);
	delete camp->getModelAttributes()->at(0).hitbox;
	camp->getModelAttributes()->at(0).hitbox = NULL;

	
	// arboles
	treesEnv = new Arboles(camara, terreno);
	ourModel.emplace_back(treesEnv->GetModel()); 

	// casas
	housesEnv = new Houses(camara, terreno);
	std::vector<Model*>& houseList = housesEnv->GetModels();
	ourModel.insert(ourModel.end(), houseList.begin(), houseList.end());



	//objetos
	srand((unsigned int)time(NULL));

	
	bottle = new Model("models/Items/aguita.glb", main->cameraDetails);

	int azarAgua = rand() % 3; 
	float aguaX = 0, aguaZ = 0;

	if (azarAgua == 0) { aguaX = 143.0f; aguaZ = -7.0f; }
	else if (azarAgua == 1) { aguaX = 142.0f; aguaZ = 2.0f; }
	else { aguaX = 150.0f; aguaZ = 17.0f; }

	translate = glm::vec3(aguaX, terreno->Superficie(aguaX, aguaZ) + 1.0f, aguaZ);

	bottle->setNextTranslate(&translate);
	bottle->setTranslate(&translate);
	scale = glm::vec3(0.05f, 0.05f, 0.05f);
	bottle->setScale(&scale);
	ourModel.emplace_back(bottle);
	
	can = new Model("models/Items/can.glb", main->cameraDetails);

	int azarCan = rand() % 3;
	float canX = 0, canZ = 0;

	if (azarCan == 0) { canX = 255.0f; canZ = 206.0f; }
	else if (azarCan == 1) { canX = 252.0f; canZ = 214.0f; }
	else { canX = 240.0f; canZ = 197.0f; }

	translate = glm::vec3(canX, terreno->Superficie(canX, canZ) + 1.0f, canZ);

	can->setNextTranslate(&translate);
	can->setTranslate(&translate);
	scale = glm::vec3(10.0f, 10.0f, 10.0f);
	can->setScale(&scale);
	can->setNextRotX(-90); 
	ourModel.emplace_back(can);

	medkit = new Model("models/Items/medkit.glb", main->cameraDetails);

	int azarMed = rand() % 3;
	float medX = 0, medZ = 0;

	if (azarMed == 0) { medX = -40.0f; medZ = 42.0f; }
	else if (azarMed == 1) { medX = -40.0f; medZ = 12.0f; }
	else { medX = -22.0f; medZ = 41.0f; }

	translate = glm::vec3(medX, terreno->Superficie(medX, medZ) + 1.0f, medZ);

	medkit->setNextTranslate(&translate);
	medkit->setTranslate(&translate);
	scale = glm::vec3(4.0f, 4.0f, 4.0f);
	medkit->setScale(&scale);
	medkit->setNextRotX(-90);
	ourModel.emplace_back(medkit);

	flare = new Model("models/Items/flare.glb", main->cameraDetails);
	translate = glm::vec3(-203.0f, terreno->Superficie(-203, 232) + 3, 232.0f);
	flare->setTranslate(&translate);
	flare->setNextTranslate(&translate);
	scale = glm::vec3(0.01f, 0.01f, 0.01f); 
	flare->setScale(&scale);
	flare->setNextRotX(-90); 

	ourModel.emplace_back(flare);

	helicopter=new Model("models/Helicopter/helicopter.fbx", main->cameraDetails);
	translate = glm::vec3(-243.0f, 100, 225.0f);
	scale = glm::vec3(0.05f, 0.05f, 0.05f);	// it's a bit too big for our scene, so scale it down
	helicopter->setScale(&scale);
	helicopter->setNextTranslate(&translate);
	helicopter->setTranslate(&translate);
	
	try {
		std::vector<Animation> animheli = Animation::loadAllAnimations("models/Helicopter/helicopter.fbx", helicopter->GetBoneInfoMap(), helicopter->getBonesInfo(), helicopter->GetBoneCount());
		if (animheli.size() > 0) {
			helicopter->setAnimator(Animator(animheli[0])); 
		}
	}catch (...) {
		ERRORL("Error cargando animaciones del helicoptero", "ANIMACION");
	}

	ourModel.emplace_back(helicopter);


	Model* wendigo= new Model("models/enemigos/wendigo_walk.fbx", main->cameraDetails);
	translate = glm::vec3(-300.0f, terreno->Superficie(-300.0f, -300.0f), -300.0f);
	scale = glm::vec3(0.0005f, 0.0005f, 0.0005f);	// it's a bit too big for our scene, so scale it down
	wendigo->setTranslate(&translate);
	wendigo->setNextTranslate(&translate);
	wendigo->setScale(&scale);
	float factorHitbox = 70.0f;
	Node cajaGrande = wendigo->AABBsize;
	cajaGrande.m_halfWidth *= factorHitbox;
	cajaGrande.m_halfHeight *= factorHitbox;
	cajaGrande.m_halfDepth *= factorHitbox;
	cajaGrande.m_center.y += 8000.0f;
	Model* nuevaHitbox = CollitionBox::GenerateAABB(*wendigo->getTranslate(), cajaGrande, main->cameraDetails);

	nuevaHitbox->setScale(wendigo->getScale());
	nuevaHitbox->setTranslate(wendigo->getTranslate()); // Sincronizamos posición
	nuevaHitbox->setNextTranslate(wendigo->getNextTranslate());

	if (wendigo->getModelAttributes()->at(0).hitbox != NULL)
		delete wendigo->getModelAttributes()->at(0).hitbox; 
	wendigo->getModelAttributes()->at(0).hitbox = nuevaHitbox;

	try {
		//caminar
		std::vector<Animation> animWalk = Animation::loadAllAnimations("models/enemigos/wendigo_walk.fbx", wendigo->GetBoneInfoMap(), wendigo->getBonesInfo(), wendigo->GetBoneCount());
		if (animWalk.size() > 0) {
			wendigo->setAnimator(Animator(animWalk[0])); 
		}

		//atacar
		std::vector<Animation> animAttack = Animation::loadAllAnimations("models/enemigos/wendigo_punch.fbx", wendigo->GetBoneInfoMap(), wendigo->getBonesInfo(), wendigo->GetBoneCount());
		if (animAttack.size() > 0) {
			wendigo->setAnimator(Animator(animAttack[0]));
		}

		wendigo->setAnimation(0);

	}
	catch (...) {
		ERRORL("Error cargando animaciones del enemigo", "ANIMACION");
	}
	wendigoObj = new EnemyWendigo(wendigo);
	ourModel.emplace_back(wendigo);


	Model* soldado = new Model("models/Soldado/soldier_pain.fbx", main->cameraDetails);
	glm::vec3 posSoldado = glm::vec3(-100.0f, terreno->Superficie(-100.0f, 205.0f), 205.0f);
	scale = glm::vec3(0.028f, 0.028f, 0.028f);	// it's a bit too big for our scene, so scale it down
	soldado->setTranslate(&posSoldado);
	soldado->setNextTranslate(&posSoldado);
	
	soldado->setScale(&scale);
	
	try {
		//acostado
		std::vector<Animation> animPain = Animation::loadAllAnimations("models/Soldado/soldier_pain.fbx", soldado->GetBoneInfoMap(), soldado->getBonesInfo(), soldado->GetBoneCount());
		if (animPain.size() > 0) {
			soldado->setAnimator(Animator(animPain[0])); 
		}

		//pararse
		std::vector<Animation> animStand = Animation::loadAllAnimations("models/Soldado/soldier_stand.fbx", soldado->GetBoneInfoMap(), soldado->getBonesInfo(), soldado->GetBoneCount());
		if (animStand.size() > 0) {
			soldado->setAnimator(Animator(animStand[0])); 
		}

		//uy kieto
		std::vector<Animation> animIdle = Animation::loadAllAnimations("models/Soldado/soldier_idle.fbx", soldado->GetBoneInfoMap(), soldado->getBonesInfo(), soldado->GetBoneCount());
		if (animIdle.size() > 0) {
			soldado->setAnimator(Animator(animIdle[0])); 
		}

		//caminar
		std::vector<Animation> animWalk = Animation::loadAllAnimations("models/Soldado/soldier_run.fbx", soldado->GetBoneInfoMap(), soldado->getBonesInfo(), soldado->GetBoneCount());
		if (animWalk.size() > 0) {
			soldado->setAnimator(Animator(animWalk[0]));
		}
		
		soldado->setAnimation(0);


	}catch(...) {
		ERRORL("Error cargando animaciones del soldado", "ANIMACION");
	}

	



	inicializaBillboards();
	
	iconoInteraccion = new Billboard((WCHAR*)L"billboards/e.png", 2, 2, 0, -100, 0, main->cameraDetails);
	billBoard.emplace_back(iconoInteraccion);

	//dialogo
	dialogoUI = new Billboard2D((WCHAR*)L"billboards/dialog_box3.png", 1, 1, 100, 200, 0, camara->cameraDetails);

	billBoard2D.emplace_back(dialogoUI);

	glm::vec3 escalaInvisible = glm::vec3(0, 0, 0);
	dialogoUI->setScale(&escalaInvisible);


	medkitUI = new Billboard2D((WCHAR*)L"billboards/medkitpro.png", 1, 1, 50, SCR_HEIGHT - 50, 0, camara->cameraDetails);
	scale = glm::vec3(50.0f, 50.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	medkitUI->setScale(&scale);
	billBoard2D.emplace_back(medkitUI);
	medkitUI->setScale(&escalaInvisible);

	canUI = new Billboard2D((WCHAR*)L"billboards/canpro.png", 1, 1, 150, SCR_HEIGHT - 50, 0, camara->cameraDetails);
	scale = glm::vec3(50.0f, 50.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	canUI->setScale(&scale);
	billBoard2D.emplace_back(canUI);
	canUI->setScale(&escalaInvisible);

	bottleUI = new Billboard2D((WCHAR*)L"billboards/waterpro.png", 1, 1, 250, SCR_HEIGHT - 50, 0, camara->cameraDetails);
	scale = glm::vec3(50.0f, 50.0f, 0.0f);	// it's a bit too big for our scene, so scale it down
	bottleUI->setScale(&scale);
	billBoard2D.emplace_back(bottleUI);
	bottleUI->setScale(&escalaInvisible);

	CollectibleItem* bottleItem = new CollectibleItem(bottle, bottleUI);
	items.push_back(bottleItem);
	CollectibleItem* canItem = new CollectibleItem(can, canUI);
	items.push_back(canItem);
	CollectibleItem* medkitItem = new CollectibleItem(medkit, medkitUI);
	items.push_back(medkitItem);

	soldierObj = new NpcSoldier(soldado, iconoInteraccion, dialogoUI, camara);
	ourModel.emplace_back(soldado);
	
	playerObj = new Jugador(camara);

}

void Scenario::inicializaBillboards() {
	
}

Scene* Scenario::Render() {
	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

	if (this->animacion > 10) { 
		for (BillboardAnimation *b : billBoardAnim){
			b->nextAnimation();
		}
		this->animacion = 0;
	} else {
		animacion = animacion + (1 * gameTime.deltaTime/100);
	}

	glm::vec3 posLuzFogata = glm::vec3(0.0f, 15.0f, 25.0f);
	
	// Decimos que dibuje la media esfera
	sky->Draw();
	// Ahora el terreno
	
	terreno->Draw();
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	
	// Si agregaste el segundo lago, también ponlo aquí:
	if (lago != NULL) {
		lago->Draw();
	}
	glDepthMask(GL_TRUE);    // Volver a escribir profundidad para el resto de cosas
	glDisable(GL_BLEND);     // Apagar transparencia
	glEnable(GL_CULL_FACE);
	// Dibujamos cada billboard 
	for (int i = 0; i < billBoard.size(); i++)
		billBoard[i]->Draw();
	for (int i = 0; i < billBoardAnim.size(); i++)
		billBoardAnim[i]->Draw();
	for (int i = 0; i < billBoard2D.size(); i++)
		billBoard2D[i]->Draw();


	// Dibujamos cada modelo que este cargado en nuestro arreglo de modelos
	for (int i = 0; i < ourModel.size(); i++) {
		if (ourModel[i]->gpuDemo != NULL) {
			ourModel[i]->gpuDemo->use();

			ourModel[i]->gpuDemo->setVec3("lightPlayer.position", *camara->getNextTranslate());
			ourModel[i]->gpuDemo->setVec3("lightPlayer.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
			ourModel[i]->gpuDemo->setVec3("lightPlayer.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
			ourModel[i]->gpuDemo->setVec3("lightPlayer.specular", glm::vec3(1.0f, 1.0f, 1.0f));
			ourModel[i]->gpuDemo->setFloat("lightPlayer.radius", 20.0f);

			// 2. LUZ DE LA FOGATA (Posición Fija Directa)
			// Sin preguntar nada, solo mandamos la coordenada
			ourModel[i]->gpuDemo->setVec3("lightFogata.position", posLuzFogata);
			ourModel[i]->gpuDemo->setVec3("lightFogata.ambient", glm::vec3(0.2f, 0.05f, 0.0f));
			ourModel[i]->gpuDemo->setVec3("lightFogata.diffuse", glm::vec3(1.0f, 0.6f, 0.0f));
			ourModel[i]->gpuDemo->setVec3("lightFogata.specular", glm::vec3(1.0f, 0.5f, 0.0f));
			ourModel[i]->gpuDemo->setFloat("lightFogata.radius", 50.0f);

			// Otros datos necesarios
			


			ourModel[i]->gpuDemo->desuse();
		}
		if (ourModel[i]->name == "InvisibleWall") {
			continue;
		}
		

		
		ourModel[i]->Draw();
	}
	float dt = gameTime.deltaTime;
	glm::vec3 playerPos = *camara->getTranslate();
	bool playerHasItems = (objetosRecogidos >= 3);

	// 1. Actualizar Items
	for (auto item : items) {
		item->Update(dt, playerPos, terreno);
		if (item->IsPicked()) {
			objetosRecogidos++;
		}

	}
	soldierObj->Update(gameTime.deltaTime, playerPos, terreno, playerHasItems);

	//soldado
	if (objetosRecogidos >= 3) {
		tieneObjetos = true;
		soldierObj->Update(gameTime.deltaTime, playerPos, terreno, playerHasItems);
	}
	if ((soldierObj->IsFollowing()) && !flareAparecio) {
		flareAparecio = true;

		glm::vec3 escalaVisible = glm::vec3(0.1f, 0.1f, 0.1f); // Ajusta tamaño
		flare->setScale(&escalaVisible);
	}
	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < ourText.size(); i++) {
		ourText[i]->Draw();
	}

	soldierObj->DrawInternalText();

	glEnable(GL_DEPTH_TEST);
	
	//wendigo
	wendigoObj->Update(dt, playerPos, terreno);
	if (wendigoObj->TryDealDamage()) {
		if (playerObj->RecibirDano(20.0f)) { 
			MessageBox(NULL, L"Has sido devorado por el Wendigo.", L"GAME OVER", MB_OK | MB_ICONERROR);
			exit(0);
		}
			
		
	}
	playerObj->Update(dt);
	
	if (vidaJugador <= 0) {
		MessageBox(NULL, L"Has sido derrotado por el Wendigo...", L"GAME OVER", MB_OK | MB_ICONERROR);
		exit(0); 
	}

	
	

	

	// recoger flare
	if (flareAparecio && !pickedFlare) {
		// Animacion
		flare->setNextRotY(flare->getRotY() + 0.5f);

		
		glm::vec3 posJugador = *camara->getTranslate();
		glm::vec3 posFlare = *flare->getTranslate();

		if (glm::distance(posJugador, posFlare) < 6.0f) {
			pickedFlare = true;

			if (flare != nullptr) {
				glm::vec3 pos = *flare->getTranslate();
				pos.y -= 10.0f; // Restamos 10 en Y para enterrarlo

				flare->setTranslate(&pos);
				flare->setNextTranslate(&pos);
			}

			//HELICOPTER HELICOPTER
			helicopteroBajando = true;
			timerHelicoptero = 0.0f;
		}
	}

	if (pickedFlare && helicopteroBajando) {
		timerHelicoptero += gameTime.deltaTime;

		if (timerHelicoptero > 2000.0f) {
			glm::vec3 posHeli = *helicopter->getTranslate();
			float destinoY = terreno->Superficie(-243.0f, 225.0f);
			if (posHeli.y > destinoY) {
				posHeli.y -= 0.1f * (gameTime.deltaTime / 10.0f); // Velocidad de descenso
				helicopter->setTranslate(&posHeli);
				helicopter->setNextTranslate(&posHeli);

			}
			else {
				helicopteroBajando = false;
			}
		}
	}
	// win
	if (pickedFlare) {
		glm::vec3 posJugador = *camara->getTranslate();
		glm::vec3 posHeli = *helicopter->getTranslate();

		if (glm::distance(posJugador, posHeli) < 25.0f && !juegoGanado) {
			juegoGanado = true;

			MessageBox(NULL, L"Lograste escapar uwu", L"VICTORIA", MB_OK | MB_ICONASTERISK);

			exit(0);
		}
	}


	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < ourText.size(); i++) {
		ourText[i]->Draw();
	}
	glEnable(GL_DEPTH_TEST);

	
	glDisable(GL_DEPTH_TEST);
	
	playerObj->DrawUI(); 
	glEnable(GL_DEPTH_TEST);


	return this;
}
	
std::vector<Model*> *Scenario::getLoadedModels() {
	return &ourModel;
}
std::vector<Billboard*> *Scenario::getLoadedBillboards() {
	return &billBoard;
}
std::vector<Billboard2D*> *Scenario::getLoadedBillboards2D(){
	return &billBoard2D;
}
std::vector<Texto*> *Scenario::getLoadedText(){
	return &ourText;
}
std::vector<BillboardAnimation*> *Scenario::getLoadedBillboardsAnimation(){
	return &billBoardAnim;
}

Model* Scenario::getMainModel() {
	return this->camara;
}
void Scenario::setMainModel(Model* mainModel){
	this->camara = mainModel;
}
float Scenario::getAngulo() {
	return this->angulo;
}
void Scenario::setAngulo(float angulo) {
	this->angulo = angulo;
}
SkyDome* Scenario::getSky() {
	return sky;
}
Terreno* Scenario::getTerreno() {
	return terreno;
}

Scenario::~Scenario() {
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
	if (billBoardAnim.size() > 0)
		for (int i = 0; i < billBoardAnim.size(); i++)
			delete billBoardAnim[i];
	if (billBoard2D.size() > 0)
		for (int i = 0; i < billBoard2D.size(); i++)
			delete billBoard2D[i];
	this->billBoard.clear();
	if (ourText.size() > 0)
		
		for (int i = 0; i < ourText.size(); i++)
			if (!(ourText[i]->name.compare("FPSCounter") || ourText[i]->name.compare("Coordenadas")))
				delete ourText[i];
		
	this->ourText.clear();
	if (ourModel.size() > 0)
		for (int i = 0; i < ourModel.size(); i++)
			if (ourModel[i] != camara)
			delete ourModel[i];
	this->ourModel.clear();
	if (this->lago != NULL) {
		delete this->lago;
		this->lago = NULL;
	}
}
