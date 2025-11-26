#ifndef GRAPHICSRR_H
#define GRAPHICSRR_H

#ifdef _WIN32 
#include <windows.h>
#include <windowsx.h>
#endif
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "Base/camera.h"
#include "Base/Billboard.h"
#include "Base/BillboardAnimation.h"
#include <iostream>
#include "Base/Scene.h"
#include "Texto.h"
#include "Billboard2D.h"
#include "CollitionBox.h"
#include "Item.h"
#include "Soldado.h"
#include "Wendigo.h"
#include "Jugador.h"
#include "Houses.h"
#include "Arboles.h"

class Scenario : public Scene {
private:
	SkyDome* sky;
	Terreno* terreno;
	std::vector<Billboard*> billBoard;
	std::vector<BillboardAnimation*> billBoardAnim;
	std::vector<Billboard2D*> billBoard2D;
	std::vector<Model*> ourModel;
	Model* camara;
	Water* water;
	Water* lago;
	
	EnemyWendigo* wendigoObj;
	NpcSoldier* soldierObj;
	std::vector<CollectibleItem*> items;
	Jugador* playerObj;
	Houses* housesEnv;
	Arboles* treesEnv;

	Model* bottle;
	Model* can;
	Model* medkit;
	Model* helicopter;

	Model* flare;         
	bool flareAparecio = false; 
	bool pickedFlare = false;   

	// Control del Helicóptero
	bool helicopteroBajando = false;
	float timerHelicoptero = 0.0f;     
	bool juegoGanado = false;

	//inventario
	bool pickedBottle = false;
	bool pickedCan = false;
	bool pickedMedkit = false;
	int objetosRecogidos = 0;
	//a
	int estadoEnemigo = 0;
	float angulo;
	float animacion = 0;
	bool textoCreado = false;
	bool textoCreado2 = false;
	bool mostrandoRechazo = false;
	float timerRechazo = 0.0f;

	// Modelos y UI
	
	Billboard* iconoInteraccion; //e
	Billboard2D* dialogoUI;      // dialogo
	Billboard2D* medkitUI;
	Billboard2D* canUI;
	Billboard2D* bottleUI;

	// vida
	float vidaJugador = 100.0f;
	float vidaMax = 100.0f;
	float CD = 0.0f; 
	Billboard2D* barraVidaFondo;
	Billboard2D* barraVidaRojo;
	float anchoBarraOriginal = 300.0f;

	//soldado
	int estadoSoldado = 0;      
	bool tieneObjetos = false;    
	float tiempoLevantarse = 0;  

	std::vector<Texto*> ourText;
public:
	Scenario(Camera *cam);
	Scenario(Model *camIni);
	void InitGraph(Model *main);

	void inicializaBillboards();

	Scene* Render();

	std::vector<Model*> *getLoadedModels();
	std::vector<Billboard*> *getLoadedBillboards();
	std::vector<BillboardAnimation*> *getLoadedBillboardsAnimation();
	std::vector<Billboard2D*> *getLoadedBillboards2D();
	std::vector<Texto*> *getLoadedText();
	Model* getMainModel();
	void setMainModel(Model* mainModel);
	float getAngulo();
	void setAngulo(float angulo);
	SkyDome* getSky();
	Terreno* getTerreno();
    ~Scenario();
};

#endif