#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 textureCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec4 vertexColor;
out vec2 vertexTextureCoord;

void main()
{
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * position;
	vertexColor = vec4(color.r, color.g, color.b, 1.0f);
	vertexTextureCoord = textureCoord;
}
