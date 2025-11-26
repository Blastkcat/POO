#ifndef JUGADOR_H
#define JUGADOR_H

#include "Base/Model.h"
#include "Billboard2D.h"
#include <glm/glm.hpp>

class Jugador {
private:
    float vidaActual;
    float vidaMax;
    float invulnerabilityCD; // Cooldown 
    float anchoBarraOriginal;

    // UI
    Billboard2D* barraFondo;
    Billboard2D* barraRojo;

public:
    Jugador(Model* camModel) {
        vidaMax = 100.0f;
        vidaActual = 100.0f;
        invulnerabilityCD = 0.0f;
        anchoBarraOriginal = 300.0f; 

        glm::vec3 escala(anchoBarraOriginal, 100.0f, 1.0f);
        

        // Barra Roja (Vida)
        barraRojo = new Billboard2D((WCHAR*)L"billboards/redline.png", 1, 1, 10, 80, 0, camModel->cameraDetails);
        barraRojo->setScale(&escala);
    }

    ~Jugador() {
       
        delete barraRojo;
    }

    void Update(float dt) {
        // Reducir cooldown
        if (invulnerabilityCD > 0.0f) {
            invulnerabilityCD -= dt / 1000.0f;
        }
    }

    // Retorna true si c murio
    bool RecibirDano(float cantidad) {
        if (invulnerabilityCD <= 0.0f) {
            vidaActual -= cantidad;
            if (vidaActual < 0) vidaActual = 0;

            
            float porcentaje = vidaActual / vidaMax;
            glm::vec3 nuevaEscala = glm::vec3(anchoBarraOriginal * porcentaje, 100.0f, 1.0f);
            barraRojo->setScale(&nuevaEscala);

            invulnerabilityCD = 1.0f; 
        }
        return (vidaActual <= 0);
    }

    void DrawUI() {
       
        barraRojo->Draw();
    }

    float GetVida() { return vidaActual; }
};

#endif