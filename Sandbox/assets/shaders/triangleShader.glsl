#type vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec3 rPos;
out vec3 rColor;
void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
    rPos = aPos;
    rColor = aColor;
};

#type fragment
#version 330 core
out vec4 FragColor;
in vec3 rPos;
in vec3 rColor;

void main()
{
    FragColor = vec4(rColor, 1.0f);
};
