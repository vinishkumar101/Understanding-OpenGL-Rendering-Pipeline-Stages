#version 440

out vec4 color;

in vec4 vertices_colors;

void main()	
{			
	color = vertices_colors;
}