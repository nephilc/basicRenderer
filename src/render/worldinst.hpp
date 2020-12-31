#ifndef WORLDINST_H
#define WORLDINST_H
#include <vector>
#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "oinstance.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class worldinst
{
private:
    /* data */
public:
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//these are the originals, they dont have to be refs
std::vector<Model> models;
std::vector<Camera> cameras;
std::vector<Shader> shaders;
std::vector<oinstance> instances = {};
glm::mat4 world = glm::mat4(1.0f);
glm::mat4 proj ;//= glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
glm::mat4 view;//this could be otherwise, but it works.
        //create a reference to the camera element
        //set the currrent cam every loop inst to counter reallloc

    worldinst(/* args */){

    }
    ~worldinst(){

    }
    //why do you need an array of cams in the world inst
    //create a cinematics class
    //all i use is the view mat, wich reamins constant for all instances

void draw(float dt){
    //set cam, choose later
    
        
        //cam, pers will be constant for all objects in a frame, but not world
        //coul save up on a matrix operation.
        //will need time here.
        //a timeline will be aded if necessary.
        //should time be in a static class.
    for (int i =0; i<instances.size(); i++)
    {
    /*    */if(instances[i].todraw)
        {
            //modify the worl matrix here depending on static or non static object
            //the world is yours
            if(instances[i].tomove){
                //step here, gpu or cpu
                //combine all movement in one matrix
                
                instances[i].world = glm::rotate(instances[i].world, instances[i].rotv * dt, instances[i].rotaxe);
                
                //updates about position or orientation are not 
                //rotation before orientation
            
            }
            ///instances[i].world = glm::scale(instances[i].world, glm::vec3(instances[i].scale));
            
            
            shaders[instances[i].shadi].setMat4("camera", view);
            shaders[instances[i].shadi].use();
            shaders[instances[i].shadi].setMat4("world", instances[i].world);
            shaders[instances[i].shadi].setMat4("perspective", proj);
    
            models[instances[i].modeli].Draw(shaders[instances[i].shadi]);
        
        
        }
    }
}    


};



#endif