#type vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCord;
uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
out vec2 u_TextureCord;
void main()
{
    u_TextureCord = aTextureCord;
    gl_Position = u_ViewProjection * u_Transform * vec4(aPos, 1.0);
};

#type fragment
#version 330 core
out vec4 FragColor;

in vec2 u_TextureCord;
uniform sampler2D u_Texture;
void main()
{
    FragColor = texture(u_Texture, u_TextureCord);
};
