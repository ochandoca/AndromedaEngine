#include <assert.h>

#include <stdio.h>
#include <iostream>
#include <fstream>

#include <functional>
#include <algorithm>
#include <utility>

#include <optional>
#include <memory>

#include <string>
#include <vector>
#include <queue>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include "Andromeda.h"



int SlowTask()
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
  return 10;
}

void WaitTask(int num)
{
  printf("Num: %d\n", num);
}

int main(int argc, char** argv){

  And::Engine e;

  And::TaskSystem ts;

  And::WorkerCreationInfo workerCreationInfo;
  workerCreationInfo.Name = "Test";
  workerCreationInfo.Function = And::GetGenericWorkerFunction();
  workerCreationInfo.UserData = nullptr;

  ts.AddWorker(workerCreationInfo);

  std::shared_ptr<And::Window> window = And::Window::make(e, 1920, 1080, "Andromeda Engine");
  //window->set_vsync(true);
  std::shared_ptr<And::GraphicsContext> g_context = window->get_context();
  And::Renderer g_renderer(*window);

  std::shared_ptr<And::Shader> s = And::MakeShader("default/geometry.shader");

  And::ResourceManager r_manager{*window, ts};
  //r_manager.AddGenerator<And::ObjGenerator>();
  r_manager.AddGenerator<And::ShaderGenerator>();
  
  And::Editor editor{*window, &r_manager};

  editor.AddWindow(ts.GetEditorWindow());
  // Show pc info
  g_context->create_info();

  //And::Future<int> fi = ts.AddTaskInThread("Resource Thread", SlowTask);
  //ts.AddTaskInThread("Test", WaitTask, fi);

  // Creamos el OldShader
  //And::Resource<And::OldShader> g_OldShader = r_manager.NewResource<And::OldShader>("default/deafult_OldShader.OldShader");
  //And::Resource<And::OldShader> g_OldShader = r_manager.NewResource<And::OldShader>("default/deafult_shader.shader");
  std::shared_ptr<And::Texture> texture = And::MakeTexture("teapot_texture.jpg");
  //And::Resource<OpenGLTexture2D> texture = r_manager.NewResource<OpenGLTexture2D>("teapot_texture.jpg")
  //And::Resource<OpenGLTexture2D> texture = r_manager.NewResource<OpenGLTexture2D>("missing_texture.png");
  //g_OldShader->set_texture(texture);
  //And::Resource<And::OldShader> g_OldShader = r_manager.NewResource<And::OldShader>("default/default_OldShader_normals.OldShader");
  

  float clear_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  g_renderer.set_clear_color(clear_color);


  
  And::EntityComponentSystem entity_comp;
    
  entity_comp.add_component_class<And::MeshComponent>();
  entity_comp.add_component_class<And::TransformComponent>();
  entity_comp.add_component_class<And::SpotLight>();
  entity_comp.add_component_class<And::DirectionalLight>();
  entity_comp.add_component_class<And::PointLight>();

  int num_obj = 10;
  float pos_x = 0.0f;
  float pos_y = -5.0f;

  /*for(int i = -5; i < (int)(num_obj / 2); i++){
    And::Resource<And::ObjLoader> obj_teapot = r_manager.NewResource<And::ObjLoader>("teapot.obj");
    And::Transform tran = {{pos_x + (i*6.0f), pos_y, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    And::Entity obj_id = entity_comp.new_entity(obj_teapot, tran);
  }
  pos_y = 5.0f;
  for(int i = -5; i < (int)(num_obj / 2); i++){
    And::Resource<And::ObjLoader> obj_teapot = r_manager.NewResource<And::ObjLoader>("teapot.obj");
    And::Transform tran = {{pos_x + (i*6.0f), pos_y, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    And::Entity obj_id = entity_comp.new_entity(obj_teapot, tran);
  }*/

  //for(int i = -5; i < 5; i++){
    And::MeshComponent MC, MC_teapot, MC_teapot2;
    //MC.Mesh = r_manager.NewResource<And::ObjLoader>("sponza.obj");
    MC.MeshOBJ = And::ObjLoader::load("sponza.obj");
    MC_teapot.MeshOBJ = And::ObjLoader::load("teapot.obj");
    MC_teapot2.MeshOBJ = And::ObjLoader::load("teapot.obj");

    //std::shared_ptr<And::ObjLoader> obj_teapot = And::ObjLoader::load("teapot.obj");
    //And::Transform tran = {{pos_x + (i*6.0f), pos_y, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    And::TransformComponent tran;
    And::TransformComponent tran_teapot;
    And::TransformComponent tran_teapot2;
    tran.position[0] = 0.0f;
    tran.position[1] = 0.0f;
    tran.position[2] = 0.0f;
    tran.rotation[0] = 1.0f;
    tran.rotation[1] = 1.0f;
    tran.rotation[2] = 1.0f;
    tran.scale[0] = 1.0f;
    tran.scale[1] = 1.0f;
    tran.scale[2] = 1.0f;
    
    tran_teapot.position[0] = 0.0f;
    tran_teapot.position[1] = 5.0f;
    tran_teapot.position[2] = -5.0f;
    tran_teapot.rotation[0] = 0.0f;
    tran_teapot.rotation[1] = 1.0f;
    tran_teapot.rotation[2] = 0.0f;
    tran_teapot.scale[0] = 2.0f;
    tran_teapot.scale[1] = 2.0f;
    tran_teapot.scale[2] = 2.0f;
    
    tran_teapot2.position[0] = 3.0f;
    tran_teapot2.position[1] = 5.0f;
    tran_teapot2.position[2] = -5.0f;
    tran_teapot2.rotation[0] = 0.0f;
    tran_teapot2.rotation[1] = 1.0f;
    tran_teapot2.rotation[2] = 0.0f;
    tran_teapot2.scale[0] = 2.0f;
    tran_teapot2.scale[1] = 2.0f;
    tran_teapot2.scale[2] = 2.0f;
    And::Entity* obj_id = entity_comp.new_entity(MC, tran);
    And::Entity* obj_teapot_id = entity_comp.new_entity(MC_teapot, tran_teapot);
    And::Entity* obj_teapot_id2 = entity_comp.new_entity(MC_teapot2, tran_teapot2);
  //}

  /*And::AmbientLight ambient;
  ambient.enabled = 1.0f;
  ambient.diffuse_color[0] = 0.0f;
  ambient.diffuse_color[1] = 1.0f;
  ambient.diffuse_color[2] = 0.0f;
  ambient.specular_color[0] = 1.0f;
  ambient.specular_color[1] = 1.0f;
  ambient.specular_color[2] = 1.0f;
  ambient.direction[0] = 1.0f;
  ambient.direction[1] = 1.0f;
  ambient.direction[2] = 0.0f;

  ambient.specular_strength = 0.5f;
  ambient.specular_shininess = 1.0f;

  And::PointLight point;
  point.enabled = 1.0f;
  point.position[0] = -5.0f;
  point.position[1] = 7.0f;
  point.position[2] = 0.0f;
  point.diffuse_color[0] = 1.0f;
  point.diffuse_color[1] = 0.55f;
  point.diffuse_color[2] = 0.0f;
  point.specular_color[0] = 1.0f;
  point.specular_color[1] = 1.0f;
  point.specular_color[2] = 1.0f;
  point.specular_strength = 0.5f;
  point.specular_shininess = 1.0f;
  point.constant_att = 1.0f;
  point.linear_att = 0.7f;
  point.quadratic_att = 1.8f;
  point.attenuation = 40.0f;


  And::LightManager l_manager;
  std::shared_ptr<And::AmbientLight> l = std::make_shared<And::AmbientLight>();
  l->enabled = 1.0f;
  l->diffuse_color[0] = 0.4f;
  l->diffuse_color[1] = 0.4f;
  l->diffuse_color[2] = 0.4f;
  l->specular_color[0] = 1.0f;
  l->specular_color[1] = 1.0f;
  l->specular_color[2] = 1.0f;
  l->direction[0] = 1.0f;
  l->direction[1] = 1.0f;
  l->direction[2] = 0.0f;
  //l_manager.add_light(l);
  
  std::shared_ptr<And::DirectionalLight> l2 = std::make_shared<And::DirectionalLight>();
  l2->enabled = 1.0f;
  l2->diffuse_color[0] = 1.0f;
  l2->diffuse_color[1] = 1.0f;
  l2->diffuse_color[2] = 1.0f;
  l2->specular_color[0] = 1.0f;
  l2->specular_color[1] = 1.0f;
  l2->specular_color[2] = 1.0f;
  l2->direction[0] = 1.0f;
  l2->direction[1] = 1.0f;
  l2->direction[2] = 0.0f;
  //l_manager.add_light(l2);
  
  std::shared_ptr<And::PointLight> point_light = std::make_shared<And::PointLight>();
  point_light->enabled = 1.0f;
  point_light->diffuse_color[0] = 0.0f;
  point_light->diffuse_color[1] = 1.0f;
  point_light->diffuse_color[2] = 0.0f;
  point_light->specular_color[0] = 1.0f;
  point_light->specular_color[1] = 1.0f;
  point_light->specular_color[2] = 1.0f;
  point_light->specular_strength = 1.0f;
  point_light->specular_shininess = 1.0f;
  point_light->constant_att = 1.0f;
  point_light->linear_att = 0.7f;
  point_light->quadratic_att = 1.8f;
  point_light->attenuation = 40.0f;
  //l_manager.add_light(point_light);

  


  std::shared_ptr<And::SpotLight> spot_light = std::make_shared<And::SpotLight>();
  spot_light->enabled = 1.0f;
  spot_light->diffuse_color[0] = 1.0f;
  spot_light->diffuse_color[1] = 0.0f;
  spot_light->diffuse_color[2] = 0.0f;
  spot_light->specular_color[0] = 1.0f;
  spot_light->specular_color[1] = 1.0f;
  spot_light->specular_color[2] = 1.0f;
  spot_light->position[0] = 0.0f;
  spot_light->position[1] = 14.0f;
  spot_light->position[2] = 11.0f;
  spot_light->direction[0] = 0.0f;
  spot_light->direction[1] = 0.0f;
  spot_light->direction[2] = -1.0f;
  spot_light->specular_strength = 0.003f;
  spot_light->specular_shininess = 8.0f;
  spot_light->constant_att = 1.0f;
  spot_light->linear_att = 0.014f;
  spot_light->quadratic_att = 0.0007f;
  spot_light->cutt_off = 2.5f;
  spot_light->outer_cut_off= 17.5f;
  l_manager.add_light(spot_light);

  */


  float enabled = 1.0f;
  float diffuse_color[3] = {1.0f, 0.0f, 0.0f};
  float specular_color[3] = {1.0f, 1.0f, 1.0f};
  float position[3] = {0.0f, 14.0f, 11.0f};
  float direction[3] = {0.0f, 0.0f, -1.0f};

  float specular_strength = 0.003f;
  float specular_shininess = 8.0f;
  float constant_att = 1.0f;
  float linear_att = 0.014f;
  float quadratic_att = 0.0007f;
  float cutt_off = 2.5f;
  float outer_cut_off= 17.5f;



  And::SpotLight spot{};
  spot.SetPosition(position);
  spot.SetDirection(direction);
  spot.SetDiffuseColor(diffuse_color);
  spot.SetSpecularColor(specular_color);
  spot.SetSpecularStrength(specular_strength);
  spot.SetSpecularShininess(specular_shininess);
  spot.SetConstantAtt(constant_att);
  spot.SetLinearAtt(linear_att);
  spot.SetQuadraticAtt(quadratic_att);
  spot.SetCuttOff(cutt_off);
  spot.SetOuterCuttOff(outer_cut_off);
  spot.SetCastShadows(true);
  spot.SetEnabled(true);
  entity_comp.new_entity(spot);

  position[1] += 10.0f;
  diffuse_color[0] = 0.0f;
  diffuse_color[1] = 1.0f;

  And::SpotLight spot2{};
  spot2.SetPosition(position);
  spot2.SetDirection(direction);
  spot2.SetDiffuseColor(diffuse_color);
  spot2.SetSpecularColor(specular_color);
  spot2.SetSpecularStrength(specular_strength);
  spot2.SetSpecularShininess(specular_shininess);
  spot2.SetConstantAtt(constant_att);
  spot2.SetLinearAtt(linear_att);
  spot2.SetQuadraticAtt(quadratic_att);
  spot2.SetCuttOff(cutt_off);
  spot2.SetOuterCuttOff(outer_cut_off);
  spot2.SetCastShadows(true);
  spot2.SetEnabled(true);
  And::Entity* spot2_entity = entity_comp.new_entity(spot2);

    
  enabled = 1.0f;


  And::DirectionalLight directional{};
  directional.SetDirection(1.0f, 0.0f, 0.0f);
  directional.SetDiffuseColor(1.0f, 1.0f, 1.0f);
  directional.SetSpecularColor(1.0f, 1.0f, 1.0f);
  directional.SetCastShadows(true);
  directional.SetEnabled(true);
  entity_comp.new_entity(directional);

  float position2[3] = {0.0f, 34.0f, -5.0f};
  diffuse_color[2] = 1.0f;
  diffuse_color[1] = 0.0f;
  And::PointLight point{};
  point.SetPosition(position2);
  point.SetEnabled(1.0f);
  point.SetDiffuseColor(diffuse_color);
  point.SetSpecularStrength(specular_strength);
  point.SetSpecularColor(specular_color);
  point.SetSpecularShininess(specular_shininess);
  point.SetCastShadows(true);
  point.SetLinearAtt(linear_att);
  point.SetConstantAtt(constant_att);
  point.SetQuadraticAtt(quadratic_att);
  And::Entity* point_entity = entity_comp.new_entity(point);
  
  position2[0] += 40.0f;
  diffuse_color[2] = 0.0f;
  diffuse_color[0] = 1.0f;

  And::PointLight point2{};
  point2.SetPosition(position2);
  point2.SetEnabled(1.0f);
  point2.SetDiffuseColor(diffuse_color);
  point2.SetSpecularStrength(specular_strength);
  point2.SetSpecularColor(specular_color);
  point2.SetSpecularShininess(specular_shininess);
  point2.SetCastShadows(true);
  point2.SetLinearAtt(linear_att);
  point2.SetConstantAtt(constant_att);
  point2.SetQuadraticAtt(quadratic_att);
  And::Entity* point_entity2 = entity_comp.new_entity(point2);

  /*Light(Light::Type t, 
  glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), 
  glm::vec3 att = glm::vec3(1.0f, 0.014f, 0.0007f),
  glm::vec3 col = glm::vec3(1.0f, 1.0f, 1.0f), 
  glm::vec3 dir = glm::vec3(0.0f, 0.0f, -1.0f), 
  float cut = 12.5f, 
  float outer_cut = 17.5f);*/



  float fps_count = 0.0f;
  g_renderer.set_draw_on_texture(true);
  while (window->is_open()){

    window->update();
    g_renderer.new_frame();
    editor.ShowWindows();

    position2[0] = cosf(fps_count) * 15.0f;
    position[1] = cosf(fps_count) * 5.0f + 15.0f;
    
    fps_count +=0.01f;
    point_entity->get_component<And::PointLight>()->SetPosition(position2);

    spot2_entity->get_component<And::SpotLight>()->SetPosition(position);
    

    And::DrawForward(entity_comp, g_renderer);
    g_renderer.end_frame();
    window->swap_buffers();
  }

  return 0;
}