#version 420 core
out vec4 FragColor;
in  vec2 textcoord1;
//so we are going to assume the number of any kind of texture, whose samplers follow a certain naming convention
//the thing about uniforms is that they can be set at runtime
//unforms are global to the shader program
//a variable doesnt have to be an input or a uniform if its not going to be used outside of the shader program
//use program to update uniform value
//the best thing is to analyze word by word a text file, line by line then word by word
//fragment interpolation
//sampling a texture
//sampling functions
//texture wrapping

uniform sampler2D texture_diffuse0;

void main()
{

//this is  a comment

    FragColor = texture(texture_diffuse0, textcoord1);
} 

//model---->textures for each individual mesh
//a list of {text id,type, path} so a texture can be shared by multiple meshes
//that being the same instance of the texture, the same id
