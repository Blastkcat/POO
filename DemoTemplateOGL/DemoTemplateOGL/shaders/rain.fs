#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D dropTex; // Lo mantenemos para que no de error el código de C++, pero no lo usamos.

void main() {
    // 1. Calcular distancia al centro del punto (coordenadas van de 0 a 1)
    // El centro es (0.5, 0.5)
    vec2 centro = TexCoord - vec2(0.5);
    float dist = length(centro);

    // 2. Si está fuera del circulo, descartar (hacer transparente)
    if (dist > 0.5) discard;

    // 3. Crear un borde suave (difuso) para que parezca nieve y no un punto duro
    // smoothstep hace una transición suave entre 0.0 y 1.0
    // Ajusta 0.25 y 0.5 para hacer el copo más denso o más difuso
    float alpha = 1.0 - smoothstep(0.25, 0.5, dist);

    // 4. Color blanco nieve (1, 1, 1) con la transparencia calculada
    FragColor = vec4(1.0, 1.0, 1.0, alpha); 
}