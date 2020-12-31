#ifndef OINSTANCE_H
#define OINSTANCE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class oinstance
{
private:
    /* data */
public:
    unsigned int modeli, shadi;
    bool todraw = true;
    bool tomove = false;//step the simulation
    glm::vec3 position;
    glm::vec3 orientation;
    glm::vec3 rotaxe;//normalized, want to change it indipendently
    glm::vec3 velocity;//metres per sec
    glm::vec3 direction;//normalized
    glm::vec3 rotmtm;//rad per sec
    glm::mat4 world  = glm::mat4(1.0f);//the object will have to have its own world matrix
    float weight;//in kg
    float scale;
    float  rotv = 0;
    bool update = false;


    
    
    
    oinstance(int modelii, int shadii) : modeli(modelii), shadi(shadii){

    }
    ~oinstance(){

    }


};


#endif