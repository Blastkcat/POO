#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Base/model.h"
#include "Terreno.h"

// se abstrae con su nombre y los metodos
class GameObject {
protected:
    //aqui se encapsula
    Model* model;
    glm::vec3 position;
    
public:
    GameObject(Model* m) : model(m) {
        if (m) position = *m->getTranslate();
    }
    virtual ~GameObject() {} // destructor

    // polimorfismo pq aqui por cada objeto q demos sera diferente
    virtual void Update(float deltaTime, glm::vec3 playerPos, Terreno* terreno) = 0;

    Model* getModel() { return model; }
    glm::vec3 getPosition() { return position; }
};

#endif