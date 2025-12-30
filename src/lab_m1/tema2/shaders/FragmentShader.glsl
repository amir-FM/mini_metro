#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 light_direction1;
uniform vec3 light_position1;
uniform vec3 eye_position;
uniform int spotlight;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;

float point_light_contribution(vec3 light_direction, vec3 light_position)
{
    light_direction = normalize(light_direction);
    vec3 N = normalize(world_normal);
    vec3 L = normalize(light_position - world_position);
    vec3 V = normalize(eye_position - world_position);
    vec3 H = normalize(L + V);
    vec3 R = reflect(-L, N);
    float d = distance(world_position, light_position);
    float attenuation_factor = pow(1 / d, 2);

    float cutoff = 30.0f;
    float spot_light = dot(-L, light_direction);
    float spot_light_limit = cos(cutoff);
    // TODO(student): Define ambient, diffuse and specular light components
    float diffuse_light = material_kd * 1 * max(dot(N, L), 0);
    float specular_light = 0;
    float linear_att = 1;
    float light_att_factor = 1;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * 1 * 1 * pow(max(dot(V, R), 0), material_shininess);
    }

    if(spotlight == 1) {
        linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
        light_att_factor = pow(linear_att, 2);
    }
    return attenuation_factor * light_att_factor * ( diffuse_light + specular_light);

}

void main()
{
    float ambient_light = 0.50 * material_kd;
    float light = ambient_light;
    light += point_light_contribution(light_direction, light_position);
    light += point_light_contribution(light_direction1, light_position1);

    // TODO(student): Write pixel out color
    out_color = vec4(object_color * light, 1.0);

}
