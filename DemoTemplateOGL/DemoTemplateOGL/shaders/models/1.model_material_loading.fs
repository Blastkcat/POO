#version 330 core

// Estructura de Material
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
};
// Estructura de Luz (Ahora con radio para punto de luz)
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float radius; // <--- Importante: agregamos el radio
};

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;  
  
out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
// ACEPTAMOS LAS DOS LUCES DE SCENARIO.CPP
uniform Light lightPlayer;
uniform Light lightFogata;

uniform int textureSample = 1;
uniform sampler2D texture_diffuse1;
uniform vec4 color;

// Función para calcular cada luz por separado
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // Difusa
    float diff = max(dot(normal, lightDir), 0.0);
    // Especular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Atenuación por distancia (Radio)
    float distance = length(light.position - fragPos);
    float attenuation = 1.0;
    if(light.radius > 0.1) {
        // Suavizado del borde de la luz
        attenuation = 1.0 - smoothstep(0.0, light.radius, distance);
    }
    
    // Combinar componentes
    vec3 ambient  = light.ambient  * material.ambient;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    // Aplicar atenuación a todo
    return (ambient + diffuse + specular) * attenuation;
}

void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // --- MODIFICACIÓN DE INTENSIDAD Y ALCANCE ---
    // Creamos una copia local de la luz del jugador para modificarla
    Light playerL = lightPlayer;
    
    // 1. Aumentamos el RADIO para que llegue más lejos (ej. multiplicar por 3.0)
    playerL.radius = lightPlayer.radius * 3.0; 
    
    // 2. Aumentamos la INTENSIDAD de la luz difusa y especular (ej. multiplicar por 1.5)
    playerL.diffuse = lightPlayer.diffuse * 1.5;
    playerL.specular = lightPlayer.specular * 1.5;
    // ---------------------------------------------

    // 1. Calcular luz del Jugador (Usando la copia modificada 'playerL')
    vec3 result = CalcLight(playerL, norm, FragPos, viewDir);

    // 2. Sumar luz de la Fogata (Esa se queda igual)
    result += CalcLight(lightFogata, norm, FragPos, viewDir);

    // Aplicar textura
    if (textureSample == 1) {
        vec4 texColor = texture(texture_diffuse1, TexCoords);
        if (texColor.a < 0.1)
            discard;
        FragColor = vec4(result, 1.0) * texColor;
    } else {
        FragColor = vec4(result, 1.0);
    }
}