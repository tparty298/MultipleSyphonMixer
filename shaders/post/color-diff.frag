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
    vec2 diff = vec2(seeds.x * 10.);
    // st.x += sin(seeds.x) * 10.;
    // st.y += cos(st.x/ u_resolution.x * PI + time) * 10. * seeds.y;
    // st = abs(st-ve2(0.5));

    float sum_opacity = max(s_opacity0 + s_opacity1 + s_opacity2, 1.0);


    if (s_opacity0 > 0.0) {
        final.r += texture(s_texture0, st * s_resolution0 + diff).r * s_opacity0/ sum_opacity;
        final.g += texture(s_texture0, st * s_resolution0).g * s_opacity0/ sum_opacity;
        final.b += texture(s_texture0, st * s_resolution0 - diff).b * s_opacity0/ sum_opacity;
    }
    if (s_opacity1 > 0.0) {
        final.r += texture(s_texture1, st * s_resolution1 + diff).r * s_opacity1 / sum_opacity;
        final.g += texture(s_texture1, st * s_resolution1).g * s_opacity1 / sum_opacity;
        final.b += texture(s_texture1, st * s_resolution1 - diff).b * s_opacity1 / sum_opacity;
    }
    if (s_opacity2 > 0.0) {
        final.r += texture(s_texture2, st * s_resolution2 + diff).r * s_opacity2 / sum_opacity;
        final.g += texture(s_texture2, st * s_resolution2).g * s_opacity2 / sum_opacity;
        final.b += texture(s_texture2, st * s_resolution2 - diff).b * s_opacity2 / sum_opacity ;
    }

    outputColor = vec4(final, 1.0);
}