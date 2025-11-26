#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

// A menudo los motores usan View y Projection con mayúscula.
// Intenta cambiar estos nombres si sigue fallando.
uniform mat4 model;
uniform mat4 view;       // <--- Si esto no coincide con C++, el agua te seguirá
uniform mat4 projection; 

uniform float time;

void main() {
    vec3 modifiedPos = aPos;

    // Generar olas
    float waveFactorX = sin(0.5 * modifiedPos.x + 0.1 * time);
    float waveFactorZ = sin(0.5 * modifiedPos.z + 0.1 * time);
    modifiedPos.y += 0.5 * (waveFactorX + waveFactorZ);

    // Calcular la posición real en el mundo (World Space) para iluminación futura
    FragPos = vec3(model * vec4(modifiedPos, 1.0));
    
    TexCoords = aTexCoords;
    
    // Calcular Normal correcta (si rotas el modelo, la normal debe rotar)
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Posición final en pantalla
    gl_Position = projection * view * vec4(FragPos, 1.0);
}