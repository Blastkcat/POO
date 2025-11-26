#ifndef COLLECTIBLEITEM_H
#define COLLECTIBLEITEM_H

#include "Objeto.h"
#include "Billboard2D.h"


class CollectibleItem : public GameObject {
private:
    Billboard2D* uiIcon;     // UI asociada al item
    bool isPicked;
    float floatSpeed;
    float floatAmp;
    float timeAccumulator;
    float pickupRange;

public:
    CollectibleItem(Model* m, Billboard2D* icon)
        : GameObject(m), uiIcon(icon), isPicked(false),
        floatSpeed(0.05f), floatAmp(0.5f), timeAccumulator(0), pickupRange(5.0f) {}

    // Sobrescribimos el Update (Polimorfismo)
    void Update(float deltaTime, glm::vec3 playerPos, Terreno* terreno) override {
        if (isPicked) return;

        // 1. Animación de flotar y rotar
        timeAccumulator += deltaTime * 0.01f; // Ajustar velocidad según tu time

        position = *model->getTranslate();
        position.y = terreno->Superficie(position.x, position.z) + 1.5f + sin(timeAccumulator * floatSpeed) * floatAmp;

        model->setTranslate(&position);
        model->setNextTranslate(&position);
        model->setRotY(model->getRotY() + 0.5f);

        // 2. Lógica de Recolección
        if (glm::distance(playerPos, position) < pickupRange) {
            PickUp();
        }
    }

    void PickUp() {
        isPicked = true;

        if (model != nullptr) {
            glm::vec3 pos = *model->getTranslate();
            pos.y -= 10.0f; // Restamos 10 en Y para enterrarlo

            model->setTranslate(&pos);
            model->setNextTranslate(&pos);
        }

        // Mostrar UI 2D
        glm::vec3 scaleUI(50, 50, 0); // Tu escala de UI
        if (uiIcon) uiIcon->setScale(&scaleUI);
    }

    bool IsPicked() const { return isPicked; }
};

#endif