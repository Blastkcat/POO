#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
};

// Definimos la estructura de una luz
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float radius; // Nuevo: Control de radio por luz
};

in vec3 FragPos;
in vec3 Normal;  
  
uniform vec3 viewPos;
uniform Material material;

// AHORA TENEMOS 2 LUCES
uniform Light lightPlayer;
uniform Light lightFogata;

// Función para calcular el aporte de una luz
vec3 CalcLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    
    // Difusa
    float diff = max(dot(normal, lightDir), 0.0);
    
    // Especular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    // Atenuación (Radio de luz)
    float distance = length(light.position - fragPos);
    // Si radius es 0 o muy grande, iluminamos infinito, si no, atenuamos
    float attenuation = 1.0;
    if(light.radius > 0.1) {
        attenuation = 1.0 - smoothstep(0.0, light.radius, distance);
    }
    
    // Combinar resultados
    vec3 ambient  = light.ambient  * material.ambient;
    vec3 diffuse  = light.diffuse  * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    
    return (ambient + diffuse + specular) * attenuation;
}

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Sumar las dos luces
    vec3 result = CalcLight(lightPlayer, norm, FragPos, viewDir);
    result += CalcLight(lightFogata, norm, FragPos, viewDir); // <--- SUMA LA FOGATA
    
    FragColor = vec4(result, 1.0);
}