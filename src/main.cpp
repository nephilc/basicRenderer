#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.hpp"
#include "model.hpp"
#include "camera.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <filesystem>
#include "mainlayout.hpp"
#include "worldinst.hpp"
//a call back is usually necessary for input, getting input in the loop is not always suitable.
//easily add or remove elements from a window at runtime, using switches
//pass these switches to elements in the menu bar
//the menu elements are meant to bes used by switches, however switches can be use anywhere
//window title ids
#define UI_MODE 1
#define GAME_MODE 2
typedef unsigned int imode;
   
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
ImGuiConfigFlags_ keyflag = ImGuiConfigFlags_None;
ImGuiConfigFlags_ mouseflag = ImGuiConfigFlags_None;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
//glm::mat4 proj(1.0f);

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

imode currentMode = UI_MODE;
std::vector <Model> models;
glm::mat4 proj ;
int main()
{   
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

    // tell GLFW to capture our mouse
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    const char* glsl_version = "#version 420";
IMGUI_CHECKVERSION();

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    // Setup Dear ImGui style 
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
  
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    Shader shad("shader.vert", "shader.frag");
    worldinst wi;
    wi.shaders.push_back(shad);
    wi.cameras.push_back(camera);
      
    layoutsp::mainlayout lay1(models, wi);
    
    /*std::string str;
    std::cout << "Enter path in the ressouce folder of obj: "<< endl;
    std::getline(cin, str);
    Model ourModel("resource/"+str);
    */
    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop
    // -----------
    proj = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 world = glm::mat4(1.0f); 
    //the camera will not be part of the world inst;
    //later, the data will be united in one place
    //the camera class will have to change  
       
    bool show_demo_window = true;
    bool show_another_window = false;
     ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
      
    while (!glfwWindowShouldClose(window))
    {
    io.ConfigFlags = mouseflag | keyflag;
 	
     ImGui_ImplOpenGL3_NewFrame(); 
     ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //keep this one as a reference
        ImGui::ShowDemoWindow(&show_demo_window);
        //directoryLayout(shad);         
        lay1.directoryLayout1(); 
        lay1.instancelayout(); 
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
	        
	// input    
        // -----  
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        /*
        
        glm::mat4 view = camera.GetViewMatrix();
        shad.setMat4("camera", view);
        shad.use();
        shad.setMat4("world", world);
        shad.setMat4("perspective", proj);
        for (int z = 0; z < wi.models.size(); z++)
            {

                    
                if(wi.models[z].todraw) wi.models[z].Draw(shad);
            }
        */
     wi.view = camera.GetViewMatrix();
        wi.proj = proj;
            wi.draw(deltaTime);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());        
	    glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	
ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
     
glfwTerminate();
    return 0;
}
 
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    
if(currentMode == GAME_MODE){
if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

}
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{ 
    if (firstMouse)
    {
        lastX = xpos;  
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;  
if(currentMode == GAME_MODE){
    camera.ProcessMouseMovement(xoffset, yoffset);
} 
 
} 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS){
  	if(currentMode == UI_MODE){ 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	currentMode = GAME_MODE;	
	keyflag = ImGuiConfigFlags_NavNoCaptureKeyboard;     // Enable Keyboard Controls
    mouseflag = ImGuiConfigFlags_NoMouse;       // Enable Gamepad Controls

    }
	else{
	currentMode = UI_MODE;	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);	
	keyflag = ImGuiConfigFlags_None;
    mouseflag = ImGuiConfigFlags_None;
    }
}
}
 
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

    camera.ProcessMouseScroll(yoffset); 
}
//the point is pick an object from the tree, load it

  