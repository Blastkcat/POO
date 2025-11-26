#ifndef HOUSES_H
#define HOUSES_H

#include "Base/Model.h"
#include "Terreno.h"
#include <vector>

class Houses {
private:
    std::vector<Model*> houseModels;

public:
    Houses(Model* camara, Terreno* terreno) {
        GenerarParedes(camara, terreno);
        GenerarMuebles(camara, terreno);
    }

    // No ponemos destructor que borre los modelos porque se los vamos 
    // a pasar al Scenario para que él los gestione en 'ourModel'.

    std::vector<Model*>& GetModels() {
        return houseModels;
    }

private:
    void GenerarParedes(Model* main, Terreno* terreno) {
        Model* pared;
        float alturaPared = 20.0f;
        float grosor = 1.0f;
        glm::vec3 translate, scale;

        // Aquí pegamos toda tu lógica de "InvisibleWall"
        // 1. Pared Izquierda Larga

	// 1. Pared Izquierda Larga (137x 8.5z a 137x -18.6z)
	// Centro: 137, -5.05 | Largo Z: 27.1
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall"; // Le ponemos nombre para poder identificarlo luego
		translate = glm::vec3(137.0f, terreno->Superficie(137.0f, -5.05f) + (alturaPared / 2), -5.05f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(grosor, alturaPared, 27.1f);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 2. Pared Frontal (137x 8.5z a 162x 8.5z)
		// Centro: 149.5, 8.5 | Largo X: 25
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(149.5f, terreno->Superficie(149.5f, 8.5f) + (alturaPared / 2), 8.5f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(25.0f, alturaPared, grosor);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 3. Pared Derecha - Parte 1 (162x 8.5z a 162x 4z)
		// Centro: 162, 6.25 | Largo Z: 4.5
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(162.0f, terreno->Superficie(162.0f, 6.25f) + (alturaPared / 2), 6.25f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(grosor, alturaPared, 4.5f);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 4. Pared Derecha - Parte 2 (162x 1z a 162x -18.6z) -> Deja hueco puerta (4z a 1z)
		// Centro: 162, -8.8 | Largo Z: 19.6
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(162.0f, terreno->Superficie(162.0f, -8.8f) + (alturaPared / 2), -8.8f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(grosor, alturaPared, 19.6f);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 5. Pared Trasera - Derecha (162x -18.6z a 154x -18.6z)
		// Centro: 158, -18.6 | Largo X: 8
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(158.0f, terreno->Superficie(158.0f, -18.6f) + (alturaPared / 2), -18.6f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(8.0f, alturaPared, grosor);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 6. Pared Trasera - Izquierda (137x -18.6z a 145 -18.6z) -> Deja hueco grande (154 a 145)
		// Centro: 141, -18.6 | Largo X: 8
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(141.0f, terreno->Superficie(141.0f, -18.6f) + (alturaPared / 2), -18.6f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(8.0f, alturaPared, grosor);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 7. Pared Interna - Izquierda (137x -3z a 147x -3z)
		// Centro: 142, -3 | Largo X: 10
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(142.0f, terreno->Superficie(142.0f, -3.0f) + (alturaPared / 2), -3.0f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(10.0f, alturaPared, grosor);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 8. Pared Interna - Derecha (155x -3z a 162x -3z) -> Deja hueco puerta interna (147 a 155)
		// Centro: 158.5, -3 | Largo X: 7
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(158.5f, terreno->Superficie(158.5f, -3.0f) + (alturaPared / 2), -3.0f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(7.0f, alturaPared, grosor);
		pared->setScale(&scale);
		houseModels.push_back(pared);


		// 1. Pared Derecha - Parte Superior (257x 210z hasta 257x 202z)
		// Centro: 257, 206 | Largo Z: 8
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(257.0f, terreno->Superficie(257.0f, 206.0f) + (alturaPared / 2), 206.0f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(grosor, alturaPared, 8.0f);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 2. Pared Trasera (257x 210z hasta 243x 210z)
		// Centro: 250, 210 | Largo X: 14
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(250.0f, terreno->Superficie(250.0f, 210.0f) + (alturaPared / 2), 210.0f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(14.0f, alturaPared, grosor);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 3. Pared Izquierda (243x 210z hasta 243x 190z)
		// Centro: 243, 200 | Largo Z: 20
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(243.0f, terreno->Superficie(243.0f, 200.0f) + (alturaPared / 2), 200.0f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(grosor, alturaPared, 20.0f);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		// 4. Pared Frontal (243x 190z hasta 257x 190z)
		// Centro: 250, 190 | Largo X: 14
		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(250.0f, terreno->Superficie(250.0f, 190.0f) + (alturaPared / 2), 190.0f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(14.0f, alturaPared, grosor);
		pared->setScale(&scale);
		houseModels.push_back(pared);

		pared = new Model("models/Cube/Cube.obj", main->cameraDetails);
		pared->name = "InvisibleWall";
		translate = glm::vec3(257.0f, terreno->Superficie(257.0f, 194.0f) + (alturaPared / 2), 194.0f);
		pared->setTranslate(&translate);
		pared->setNextTranslate(&translate);
		scale = glm::vec3(grosor, alturaPared, 8.0f);
		pared->setScale(&scale);
		houseModels.push_back(pared);


        // ... (Copia aquí el resto de las paredes 2, 3, 4, 5, 6, 7, 8...)
        // Para abreviar el ejemplo puse una, pero tú pega todas las paredes aquí.

        // Casa Principal
        Model* house = new Model("models/House/House.glb", main->cameraDetails);
        translate = glm::vec3(150.0f, terreno->Superficie(150.0f, -5.0f) - 1.0f, -5.0f);
        house->setTranslate(&translate); house->setNextTranslate(&translate);
        scale = glm::vec3(9.0f, 9.0f, 9.0f);
        house->setScale(&scale);
        house->setRotX(270); house->setNextRotX(270);
        // Eliminamos hitbox por defecto si molesta
        if (house->getModelAttributes()->at(0).hitbox) {
            delete house->getModelAttributes()->at(0).hitbox;
            house->getModelAttributes()->at(0).hitbox = NULL;
        }
        houseModels.push_back(house);

        // Casa 2
        Model* house2 = new Model("models/House/housepro2.glb", main->cameraDetails);
        translate = glm::vec3(250.0f, terreno->Superficie(250, 200), 200.0f);
        house2->setTranslate(&translate); house2->setNextTranslate(&translate);
        scale = glm::vec3(3.5f, 3.5f, 3.5f);
        house2->setScale(&scale);
        house2->setNextRotX(90);
        if (house2->getModelAttributes()->at(0).hitbox) {
            delete house2->getModelAttributes()->at(0).hitbox;
            house2->getModelAttributes()->at(0).hitbox = NULL;
        }
        houseModels.push_back(house2);
    }

    void GenerarMuebles(Model* main, Terreno* terreno) {
        glm::vec3 translate, scale;

        Model* chair = new Model("models/House/chair.glb", main->cameraDetails);
        translate = glm::vec3(245.0f, terreno->Superficie(245, 205), 205.0f);
        chair->setTranslate(&translate); chair->setNextTranslate(&translate);
        scale = glm::vec3(0.05f, 0.05f, 0.05f);
        chair->setScale(&scale);
        chair->setNextRotX(-90);
        houseModels.push_back(chair);

        Model* table = new Model("models/House/table.glb", main->cameraDetails);
        translate = glm::vec3(250.0f, terreno->Superficie(250, 205) + 2.5f, 205.0f);
        table->setTranslate(&translate); table->setNextTranslate(&translate);
        scale = glm::vec3(2.5f, 2.5f, 2.5f);
        table->setScale(&scale);
        table->setNextRotX(-90);
        houseModels.push_back(table);

		Model* wardrobe = new Model("models/House/wardrobe3.glb", main->cameraDetails);
		translate = glm::vec3(247.0f, terreno->Superficie(247, 194), 194.0f);
		wardrobe->setNextTranslate(&translate);
		wardrobe->setTranslate(&translate);
		scale = glm::vec3(0.015f, 0.015f, 0.015f);	// it's a bit too big for our scene, so scale it down
		wardrobe->setScale(&scale);
		wardrobe->setNextRotZ(180);
		wardrobe->setNextRotX(270);
		houseModels.push_back(wardrobe);
        
    }
};

#endif