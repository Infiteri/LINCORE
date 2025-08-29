// VERTEX
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 uProjection;
uniform mat4 uView;

out vec3 vColor;

void main() { 
    gl_Position = uProjection * uView * vec4(aPos, 1.0);
    vColor = aColor;
}


// FRAGMENT
#version 460 core
in vec3 vColor;
out vec4 FragColor;
void main() { FragColor = vec4(vColor, 1.0); }
