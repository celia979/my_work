#ifdef GL_ES
precision mediump float;
#endif

#define LAYERS_COUNT 10

uniform sampler2D layers[LAYERS_COUNT];
uniform float layerSpeed[LAYERS_COUNT];

uniform float time;
uniform vec2 resolution;

void main() {
    vec2 baseUV = gl_FragCoord.xy / resolution;
    vec4 finalColor = vec4(0.0);

    for(int i = 0; i < LAYERS_COUNT; i++) {
        vec2 uv = baseUV;
        uv.y = 1.0 - uv.y;
        uv.x += time * layerSpeed[i];
        vec4 pixel_color = texture2D(layers[i], uv);
        finalColor = pixel_color + finalColor * (1.0 - pixel_color.a);
    }

    gl_FragColor = finalColor;
}
