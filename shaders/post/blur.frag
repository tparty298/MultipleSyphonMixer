#version 330
#define PI 3.14159265358979
uniform sampler2DRect s_texture0;
uniform sampler2DRect s_texture1;
uniform sampler2DRect s_texture2;
uniform float s_opacity0;
uniform float s_opacity1;
uniform float s_opacity2;
uniform vec2 s_resolution0;
uniform vec2 s_resolution1;
uniform vec2 s_resolution2;

uniform vec2 resolution;
uniform vec4 seeds;
uniform float time;

vec2 st = gl_FragCoord.xy / resolution;

out vec4 outputColor;

void main() {
    vec3 final;
    // st.x += sin(seeds.x) * 10.;
    // st.y += cos(st.x/ resolution.x * PI + time) * 10.;
    vec2 diff = vec2(seeds.x * 10.);
    diff = vec2(0.);

    float size = 3.;

    if (s_opacity0 > 0.0) {
        for (int i = 0; i < 9; i++) {
            // final.r += texture(s_texture0, st + vec2(i%3, floor(i/3.))* 3.).r;
            // final.g += texture(s_texture0, st + vec2(i%3, floor(i/3.)) * 3.).g;
            // final.b += texture(s_texture0, st + vec2(i%3, floor(i/3.)) * 3.).b;
            final += texture(s_texture0, st * s_resolution0 + vec2(i%3, floor(i/3.)) * size).rgb;
        }
    }


    if (s_opacity1 > 0.0) {
        for (int i = 0; i < 9; i++) {
            // final.r += texture(s_texture1, st + vec2(i%3, floor(i/3.)) + diff).r;
            // final.g += texture(s_texture1, st + vec2(i%3, floor(i/3.))).g;
            // final.b += texture(s_texture1, st + vec2(i%3, floor(i/3.)) - diff).b;
            final += texture(s_texture1, st * s_resolution1+ vec2(i%3, floor(i/3.)) * size).rgb;
        }
    }
    if (s_opacity2 > 0.0) {
        for (int i = 0; i < 9; i++) {
            // final.r += texture(s_texture2, st + vec2(i%3, floor(i/3.)) + diff).r;
            // final.g += texture(s_texture2, st + vec2(i%3, floor(i/3.))).g;
            // final.b += texture(s_texture2, st + vec2(i%3, floor(i/3.)) - diff).b;
            final += texture(s_texture2, st * s_resolution2 + vec2(i%3, floor(i/3.)) * size).rgb;
        }
    }
    
    
    final *= 0.1;
    // final *= pow(max(.0, 1. - length((st* 2. - resolution)/ u_resolution) * 0.8), 1.0);
    outputColor = vec4(final, 1.0);
}