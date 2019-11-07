#type vertex
#version 330 core

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;

out vec2 v_texCoord;

void main()
{
	v_texCoord = a_texCoord;
	gl_Position = u_viewProjection * u_transform * vec4(a_position,1.0);
}

#type fragment
#version 330 core

uniform vec4 u_color;
uniform sampler2D u_texture;

in vec2 v_texCoord;

layout(location = 0) out vec4 _color;

void main()
{
	_color = texture(u_texture, v_texCoord) * u_color;
}