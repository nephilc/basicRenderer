#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include<vector>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "model.hpp"
#include <filesystem>
#include "worldinst.hpp"
#include "oinstance.hpp"
//so you store the data somewhere and pass to each layout the data its supposed to access 
//display and modify
//this way way one can manage the two separately

namespace layoutsp{
namespace fs = std::filesystem;
class mainlayout
{
private:
std::vector<fs::path> paths = {};    
    
public:
    std::vector<Model> &models;
    worldinst& inst1;
    mainlayout(std::vector<Model> &mod1, worldinst& inst2): models(mod1), inst1(inst2){
        getpaths();

    }
    ~mainlayout(){

    }
void getpaths(){
	for(auto& p : fs::recursive_directory_iterator("resource")){
if(p.path().extension() == ".obj" ||p.path().extension() == ".gltf"
 ||p.path().extension() == ".fbx") {
     paths.push_back(p.path());
     std::cout<<p<<std::endl;
     
     }

}


}
void textpopup3(){

 ImVec2 center1(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
        ImGui::SetNextWindowPos(center1, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        static int selected = 0;
        if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            
            
            ImGui::BeginChild("left pane", ImVec2(0, 140), true);
            for (int i = 0; i < paths.size(); i++)
            {
                char label[128];
                sprintf(label, "MyObject %d", i);
                if (ImGui::Selectable(paths[i].filename().c_str(), selected == i))
                    selected = i;
                    
            }
            ImGui::EndChild();
            
            
            /*ImGui::Text("type the path relative to the current directory");
            ImGui::Separator();

            static char buf1[64] = ""; ImGui::InputText("default",     buf1, 64);
            std::string path(buf1);
            */

            if (ImGui::Button("Load", ImVec2(120, 0))) { 
            //here load the model add it to themodel stack
            Model m1(paths[selected].string());
            m1.modelname = paths[selected].filename();
            //models.push_back(m1);
            inst1.models.push_back(m1);
            ImGui::CloseCurrentPopup(); }
            ImGui::SetItemDefaultFocus();
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
            ImGui::EndPopup();

}
}


void directoryLayout1(){
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    bool opendilay = true;
    if (ImGui::Begin("world objects outline", &opendilay, ImGuiWindowFlags_MenuBar))
    {   bool b = false;
        if (ImGui::BeginMenuBar())
        {
            
            if (ImGui::BeginMenu("File"))
            {
            
                if (ImGui::MenuItem("Load")) 
                {
                b= true;
                }
                ImGui::EndMenu();
            
                }
            
            ImGui::EndMenuBar();
        }
        if(b){
        ImGui::OpenPopup("Delete?");
            b=false;
            }// Left
        mainlayout::textpopup3();
        static int selected = 0;
        {//two child windows on the same line
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < inst1.models.size(); i++)
            {
                //the numbering might change so its best to do it here, instead of in model name
                char label[128];
                sprintf(label, "%i %s",i, inst1.models[i].modelname.c_str());
                
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
                    //one could add useful funcs next to the selectable
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        //elements of the same group will be affected by same line 
        // Right
        {
            ImGui::BeginGroup();
            //a perk of child windows is that they enable scrolling on their own without changing
            //parent window size 
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            if(inst1.models.size()) ImGui::Text(inst1.models[selected].modelname.c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
                if (ImGui::BeginTabItem("Description"))
                {
                    ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Details"))
                {
                    ImGui::Text("ID: 0123456789");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            if (ImGui::Button("inst")) {
              //inst1.models[selected].todraw = true;
                inst1.instances.push_back(oinstance(selected, 0));
            }
        // Always center this window when appearing
        
            
            ImGui::SameLine();
            if (ImGui::Button("hide")) {

              inst1.models[selected].todraw = false;
            }
            ImGui::EndGroup();
        }
    }

    ImGui::End();
//in this paradigm, one gets input on the go        
}

void instancelayout(){
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    bool opendilay = true;
    if (ImGui::Begin("instance objects outline", &opendilay, ImGuiWindowFlags_MenuBar))
    {   static int selected = 0;
        {//two child windows on the same line
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < inst1.instances.size(); i++)
            {
                //the numbering might change so its best to do it here, instead of in model name
                char label[128];
                sprintf(label, "%i %s",i, inst1.models[inst1.instances[i].modeli].modelname.c_str());
                if (ImGui::Selectable(label, selected == i))
                    selected = i;
                    //one could add useful funcs next to the selectable
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();
        //elements of the same group will be affected by same line 
        // Right
        {
            ImGui::BeginGroup();
            //a perk of child windows is that they enable scrolling on their own without changing
            //parent window size 
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            if(inst1.instances.size()) ImGui::Text(inst1.models[inst1.instances[selected].modeli].modelname.c_str());
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
                if (ImGui::BeginTabItem("Description"))
                {
                    //make sure the tab or win isnt in focus when hitting tab
                    //and using numpad, will mess with values
                    instinfo(selected);    
                    ImGui::EndTabItem();
                
            }
                if (ImGui::BeginTabItem("Details"))
                {
                    ImGui::Text("ID: 0123456789");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            if (ImGui::Button("draw")) {
              inst1.instances[selected].todraw = true;

            }
        // Always center this window when appearing
        
            
            ImGui::SameLine();
            if (ImGui::Button("hide")) {

              inst1.instances[selected].todraw = false;
            }
            ImGui::EndGroup();
        }
    }

    ImGui::End();
//in this paradigm, one gets input on the go        
}
void cameralayout(){



}
void instinfo(int instindex){
            
            static float position[3] = {0.0f, 0.0f, 0.0f };
            static float orientation[3] = {0.0f, 0.0f, 0.0f };
            static float rotaxe[3] = {0.0f, 0.0f, 0.0f };
            static float velocity[3] = {0.0f, 0.0f, 0.0f };
            static float direction[3] = {0.0f, 0.0f, 0.0f };
            static float rotmtm[3] = {0.0f, 0.0f, 0.0f };
            
            
            if(ImGui::InputFloat3("position", position))
            {
                inst1.instances[instindex].position.x = position[0];
                inst1.instances[instindex].position.y = position[1];
                inst1.instances[instindex].position.z = position[2];
                }
            if(ImGui::InputFloat3("orientation",orientation ))
            {
                inst1.instances[instindex].orientation.x = orientation[0];
                inst1.instances[instindex].orientation.y = orientation[1];
                inst1.instances[instindex].orientation.z = orientation[2];
                }
            if(ImGui::InputFloat3("rotaxe",rotaxe ))
            {
                inst1.instances[instindex].rotaxe.x = rotaxe[0];
                inst1.instances[instindex].rotaxe.y = rotaxe[1];
                inst1.instances[instindex].rotaxe.z = rotaxe[2];
                }
            if(ImGui::InputFloat3("velocity",velocity ))
            {
                inst1.instances[instindex].velocity.x = velocity[0];
                inst1.instances[instindex].velocity.y = velocity[1];
                inst1.instances[instindex].velocity.z = velocity[2];
                }
            if(ImGui::InputFloat3("direction", direction))
            {
                inst1.instances[instindex].direction.x = direction[0];
                inst1.instances[instindex].direction.y = direction[1];
                inst1.instances[instindex].direction.z = direction[2];
                }
            if(ImGui::InputFloat3("rotmtm",rotmtm ))
            {
                inst1.instances[instindex].rotmtm.x = rotmtm[0];
                inst1.instances[instindex].rotmtm.y = rotmtm[1];
                inst1.instances[instindex].rotmtm.z = rotmtm[2];
                }
            /*static bool tomovec = false;
            static bool todrawc = false;
            ImGui::Checkbox("tomove", &tomovec);
            ImGui::Checkbox("todraw", &todrawc);
            */
            static float v = 0.0f;
            ImGui::InputFloat("uni rotv", &v , 0.1f ,0.1f, "%.3f");
            if (inst1.instances.size()) 
                inst1.instances[instindex].rotv = v;
            static float scale = 1.0f;
            ImGui::InputFloat("scale", &scale , 0.1f ,0.1f, "%.3f");
            if (inst1.instances.size()){ 
                inst1.instances[instindex].scale = scale;
                if(inst1.instances[instindex].update)
                {
                    inst1.instances[instindex].world = glm::scale(inst1.instances[instindex].world, glm::vec3(scale));
                    inst1.instances[instindex].update = false;
            }}
            if(ImGui::Button("uptd"))
                inst1.instances[instindex].update = true;
            if(ImGui::Button("move"))
                if(inst1.instances[instindex].tomove)
                    inst1.instances[instindex].tomove = false;
                    
                else
                    inst1.instances[instindex].tomove=true;
                
            
            
            

}

};




}

#endif
