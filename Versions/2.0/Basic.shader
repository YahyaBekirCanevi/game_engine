#shader vertex
#version 330 core 

layout(location = 0) in vec4 position; 
void main() 
{ 
   gl_Position = position; 
};

#shader fragment
#version 330 core 

layout(location = 0) out vec4 color; 
void main() 
{ 
   color = vec4(0.6f, 0.1f, 0.9f, 1.0f); 
};