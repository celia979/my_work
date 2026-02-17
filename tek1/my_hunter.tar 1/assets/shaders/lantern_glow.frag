#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture;

uniform vec2 glowPos;
uniform float glowRadius;
uniform float glowStrength;

uniform vec3 glowColor;

void main() {
    vec4 baseColor = texture2D(texture, gl_TexCoord[0].xy);

    vec2 pixelPos = gl_FragCoord.xy;

    float dist = distance(pixelPos, glowPos);

    float light = smoothstep(glowRadius, 0.0, dist);

    vec3 glow = baseColor.rgb + glowColor * light * glowStrength;

    gl_FragColor = vec4(glow, baseColor.a);
}
