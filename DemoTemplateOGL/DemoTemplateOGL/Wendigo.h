#ifndef ENEMYWENDIGO_H
#define ENEMYWENDIGO_H

#include "Objeto.h"
//hereda de GameObject
class EnemyWendigo : public GameObject {
private:
    float speed;
    float attackRange;
    int state; 
    float damageCooldown;
    float currentCD;

public:
    EnemyWendigo(Model* m) : GameObject(m), speed(0.1f), attackRange(6.0f), state(0), damageCooldown(5.0f), currentCD(0) {}

    void Update(float deltaTime, glm::vec3 playerPos, Terreno* terreno) override {
        // cooldown
        if (currentCD > 0) currentCD -= deltaTime / 1000.0f;

        float dist = glm::distance(glm::vec2(position.x, position.z), glm::vec2(playerPos.x, playerPos.z));

        if (dist > attackRange) {
            ChasePlayer(playerPos, terreno, deltaTime);
        }
        else {
            AttackPlayer();
        }
    }

    void ChasePlayer(glm::vec3 target, Terreno* t, float dt) {
        if (state != 0) {
            model->setAnimation(0); // Caminar
            state = 0;
        }

        // seguir
        glm::vec3 dir = glm::normalize(target - position);
        position += dir * (speed * (dt / 10.0f));
        position.y = t->Superficie(position.x, position.z);

        model->setTranslate(&position);
        model->setNextTranslate(&position);

        //rotar
        float deltaX = target.x - position.x;
        float deltaZ = target.z - position.z;
        float anguloY = glm::degrees(atan2(deltaX, deltaZ));
        model->setRotY(anguloY);
        model->setNextRotY(anguloY);
    }

    void AttackPlayer() {
        if (state != 1) {
            model->setAnimation(1); // Atacar
            state = 1;
        }
    }

    // hizo daño o ne
    bool TryDealDamage() {
        if (state == 1 && currentCD <= 0) {
            currentCD = damageCooldown;
            return true;
        }
        return false;
    }
};

#endif