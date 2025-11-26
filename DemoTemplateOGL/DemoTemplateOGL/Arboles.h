#ifndef ARBOLES_H
#define ARBOLES_H

#include "Base/Model.h"
#include "Terreno.h"
#include "CollitionBox.h"

class Arboles {
private:
    Model* arbolModel; 

public:
    Arboles(Model* main, Terreno* terreno) {
        arbolModel = new Model("models/Tree/gnarly_trees.glb", main->cameraDetails);
        glm::vec3 scale = glm::vec3(0.01f, 0.01f, 0.01f);
        arbolModel->setScale(&scale);

        if (arbolModel->getModelAttributes() != NULL)
            arbolModel->getModelAttributes()->clear();

        float stepX = 60.0f;
        float stepZ = 60.0f;

        
        for (float x = -50.0f; x >= -400.0f; x -= stepX) {
            for (float z = 110.0f; z <= 400.0f; z += stepZ) {

                float y = terreno->Superficie(x, z);

                if (y < 21.0f) {
                    ModelAttributes m;
                    glm::vec3 posicion(x, y, z);
                    m.translate = posicion;
                    m.nextTranslate = posicion;
                    m.scale = glm::vec3(0.01f, 0.01f, 0.01f);

                    // Hitbox
                    Model* hitboxTree = CollitionBox::GenerateAABB(posicion, arbolModel->AABBsize, main->cameraDetails);
                    hitboxTree->setScale(&m.scale);
                    hitboxTree->setTranslate(&posicion);
                    hitboxTree->setNextTranslate(&posicion);

                    m.hitbox = hitboxTree;
                    arbolModel->getModelAttributes()->push_back(m);
                }
            }
        }
    }

    
    Model* GetModel() {
        return arbolModel;
    }
};

#endif