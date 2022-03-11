#shader vertex
#version 330 core

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 MV;
uniform mat4 MVP;

out vec3 fragColor;
out vec4 normal;

void main()
{
	gl_Position = MVP * vec4(vertex_position, 1.0f);
	normal = MV * vec4(vertex_normal, 0.0f);
	fragColor = vertex_color;
};

#shader fragment
#version 330 core

out vec4 color;
in vec3 fragColor;

void main()
{
	color = vec4(fragColor, 1.0f);
};