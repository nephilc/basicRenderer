#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textcoord;
layout (location = 3) in vec3 vtan;
layout (location = 4) in vec3 vbitan;
uniform float d;
//there was a problem with the bmw model data there was no material file
out vec2 textcoord1 ;
//attributes set in the mesh
//uniforms set in shader
//the property of being a controllable object and setting an objects 
//controlls
//texture filtering, mipmaps
//uniforms can be declared in any shader stage
uniform mat4 mov;
uniform mat4 perspective, camera, world;
//first world then camera,determine wehter objects are visible in current camera by transforming them in camera ref, then perspective 
//one could add some transforms in local model referential if he wants
//methods for timing events independently of cpu frequency, defining velocity quantities
//bind vao, bind buffer1 set attributes, bind buffer2, set attribute etc
//loading model/scene into scene object (materials of all it meshes and it childrens meshes, its meshes, and children nodes, 
//it being root nodes)
//node array pointing to arrays of nodes and so on, children of the node and meshes of the node 
//the deal is that when a model has all the vertex data but not mtl like file
//aasimp will have an empty material object, one should use a different function
void main()
{
    textcoord1 = textcoord;
    gl_Position = perspective * camera *  world *  vec4(aPos, 1.0);
}

