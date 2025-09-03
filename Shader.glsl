// VERTEX

#version 460 core

struct Material {
    vec4 Color;
};

layout(std430, binding = 0) buffer Materials {
    Material materials[];
};

layout(location = 0) in vec3 aPos;
layout(location = 2) in mat4 aTransform;

uniform mat4 uProjection;
uniform mat4 uView;

out vec4 vColor;

void main()
{
    int id = gl_InstanceID;
    vColor = materials[id].Color;

    gl_Position = uProjection * uView * aTransform * vec4(aPos, 1.0);
}


// FRAGMENT

#version 460 core
in vec4 vColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(vColor.rgb/255, 1.0);
}

