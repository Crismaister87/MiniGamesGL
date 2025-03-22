#version 460 core

in vec4 vertexColor;
in vec2 vertexTextureCoord;

uniform sampler2D Texture;

out vec4 fragmentColor;

void main()
{
	//fragmentColor = vertexColor;
	fragmentColor = texture(Texture, vertexTextureCoord);
}