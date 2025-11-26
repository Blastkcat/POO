#ifndef NPCSOLDIER_H
#define NPCSOLDIER_H

#include "Objeto.h"
#include "Base/Billboard.h"
#include "Billboard2D.h"
#include "Texto.h"

extern bool KEYS[256]; // Para leer el teclado

class NpcSoldier : public GameObject {
private:
    // Estados 
    enum State { PAIN_IDLE, DIALOG, STANDING_UP, FOLLOWING };
    State currentState;

    // Billboards
    Billboard* interactIcon; 
    Billboard2D* dialogBox; 

    // texto
    Texto* txtLine1;
    Texto* txtLine2;
    Texto* txtLine3;
    Texto* txtReject;

    int dialogPhase; 
    float animTimer;
    bool fKeyReleased; 

public:
    NpcSoldier(Model* m, Billboard* icon, Billboard2D* ui, Model* camModel)
        : GameObject(m), interactIcon(icon), dialogBox(ui),
        currentState(PAIN_IDLE), dialogPhase(0), animTimer(0), fKeyReleased(true)
    {
        std::wstring t1 = L"Hola estoy mal herido con hambre y sed";
        txtLine1 = new Texto(t1, 20, 0, 60, 800, 0.1f, camModel);

        std::wstring t2 = L"Tengo una pistola de bengala para salir de aqui";
        txtLine2 = new Texto(t2, 20, 0, 60, 850, 0.1f, camModel);

        std::wstring t3 = L"Ayudame por favor. (Presiona F)";
        txtLine3 = new Texto(t3, 20, 0, 60, 900, 0.1f, camModel);

        std::wstring tRe = L"No tienes lo que necesito... (F para salir)";
        txtReject = new Texto(tRe, 20, 0, 60, 800, 0.1f, camModel);
    }

    ~NpcSoldier() {
   
        delete txtLine1; delete txtLine2; delete txtLine3; delete txtReject;
    }
    void Update(float deltaTime, glm::vec3 playerPos, Terreno* terreno) override {
        Update(deltaTime, playerPos, terreno, false);
    }
    void Update(float dt, glm::vec3 playerPos, Terreno* t, bool playerHasItems) {
        float dist = glm::distance(playerPos, position);

        
        if (currentState == PAIN_IDLE && dist < 10.0f) {
            glm::vec3 iconPos = position; iconPos.y += 5.0f;
            interactIcon->setTranslate(&iconPos);

            if (KEYS['E']) {
                StartDialog();
            }
        }
        else {
            
            glm::vec3 hide(0, -500, 0);
            interactIcon->setTranslate(&hide);
        }

    
        switch (currentState) {
        case DIALOG:
            HandleDialogInput(playerHasItems);
            break;
        case STANDING_UP:
            animTimer += dt;
            if (animTimer > 2000.0f) { 
                currentState = FOLLOWING;
                model->setAnimation(3); 
            }
            break;
        case FOLLOWING:
            if (dist > 5.0f) {
                ChasePlayer(playerPos, t, dt);
            }
            else {
                model->setAnimation(2); 
            }
            break;
        }
    }


    void DrawInternalText() {
        if (currentState == DIALOG) {
            if (dialogPhase == 0) {
                txtLine1->Draw();
                txtLine2->Draw();
                txtLine3->Draw();
            }
            else {
                txtReject->Draw();
            }
        }
    }

    bool IsFollowing() { return currentState == FOLLOWING; }

private:
    void StartDialog() {
        currentState = DIALOG;
        dialogPhase = 0;

        glm::vec3 escalaUI = glm::vec3((float)SCR_WIDTH, (float)SCR_HEIGHT, 1.0f);
        dialogBox->setScale(&escalaUI);
        glm::vec3 posCentro = glm::vec3((float)SCR_WIDTH / 2.0f, (float)SCR_HEIGHT / 2.0f, 0.0f);
        dialogBox->setTranslate(&posCentro);

        glm::vec3 hide(0, -500, 0);
        interactIcon->setTranslate(&hide);
    }

    void HandleDialogInput(bool hasItems) {
        bool fPressed = KEYS['F'];

        if (fPressed && fKeyReleased) {
            fKeyReleased = false; 

            if (dialogPhase == 0) { 
                if (hasItems) {
                    // Éxito: Se levanta
                    currentState = STANDING_UP;
                    model->setAnimation(1); 
                    CloseDialogUI();
                }
                else {
                    dialogPhase = 1;
                }
            }
            else { 
                currentState = PAIN_IDLE;
                CloseDialogUI();
            }
        }
        else if (!fPressed) {
            fKeyReleased = true; 
        }
    }

    void CloseDialogUI() {
        glm::vec3 zero(0, 0, 0);
        dialogBox->setScale(&zero);
    }

    void ChasePlayer(glm::vec3 target, Terreno* t, float dt) {
        
        float speed = 0.15f * (dt / 10.0f);

        glm::vec3 dir = glm::normalize(target - position);

        if (glm::distance(target, position) > 2.0f) {
            position += dir * speed;
            position.y = t->Superficie(position.x, position.z);

            model->setTranslate(&position);
            model->setNextTranslate(&position);
        }

        float deltaX = target.x - position.x;
        float deltaZ = target.z - position.z;
        float anguloY = glm::degrees(atan2(deltaX, deltaZ));

        model->setRotY(anguloY);
        model->setNextRotY(anguloY);

        model->setAnimation(3); 
    }
};

#endif