#version 330
uniform sampler2DRect s_texture0;
uniform sampler2DRect s_texture1;
uniform sampler2DRect s_texture2;
uniform sampler2DRect before_texture;
uniform float s_opacity0;
uniform float s_opacity1;
uniform float s_opacity2;
uniform vec2 s_resolution0;
uniform vec2 s_resolution1;
uniform vec2 s_resolution2;

uniform vec2 resolution;
uniform vec4 seeds;
uniform float time;
out vec4 outputColor;

void main() {
    vec3 final;
    vec2 st = gl_FragCoord.xy / resolution;
    float sum_opacity = max(s_opacity0 + s_opacity1 + s_opacity2, 1.0);

    if (s_opacity0 > 0.0) {
        final += texture(s_texture0, st * s_resolution0).xyz * s_opacity0 / sum_opacity;
    }
    if (s_opacity1 > 0.0) { 
        final += texture(s_texture1, st * s_resolution1).xyz * s_opacity1 / sum_opacity;
    }
    if (s_opacity2 > 0.0) {
        final += texture(s_texture2, st * s_resolution2).xyz * s_opacity2 / sum_opacity;
    }

    final = mix(final, texture(before_texture, gl_FragCoord.xy * 2.).xyz, seeds.z * .01 + .98);

    outputColor = vec4(final, 1.0);
}