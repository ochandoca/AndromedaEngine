#include <assert.h>

#include <functional>
#include <algorithm>
#include <utility>

#include <optional>
#include <memory>

#include <string>
#include <vector>

#include "Common/Engine.h"
#include "Common/Window.h"
#include "Common/GraphicsContext.h"
#include "Common/Renderer.h"
#include "Common/Shader.h"
#include "Common/Triangle.h"

#include "Common/Input.h"

#include <windows.h>


// que te parece si hacemos que la ventana tenga una instancia del input, es muy poarecido a lo que esta diciendo el
// hacemos lo del input de mientras o que
// espera porqie si nos ponemos focus no atendemos y esta diciendo cosas importantes


int main(int argc, char** argv){
  And::Engine e;

  std::shared_ptr<And::Window> window = And::Window::make(e, 1024, 720, "Andromeda Engine");
  std::shared_ptr<And::GraphicsContext> g_context = window->get_context();
  And::Renderer g_renderer(*window);

  // Show pc info
  g_context->create_info();


  // Creamos el shader
  And::ShaderInfo s_info;
  s_info.path_fragment = "../../data/fshader.fs";
  s_info.path_vertex = "../../data/vshader.vs";

   std::optional<And::Shader> g_shader = And::Shader::make(s_info);


  float clear_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  g_renderer.set_clear_color(clear_color);


  And::Input input{*window};


  double mouseX = -1.0f, mouseY = -1.0f;
  double mouseXx = -1.0f, mouseYy = -1.0f;

  
    

  And::Vertex ver[3] = {
    {-0.5f, -0.5f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 1.0f},
    {2, 1, 0},

    {0.0f, 0.5f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 1.0f},
    {2, 1, 0},

    {0.5f, -0.5f, 0.0f},
    {0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 1.0f},
    {2, 1, 0},
  
  };

  And::Triangle tri{ver};

  
  while (window->is_open()){
    window->update();
    g_renderer.new_frame();
    
    if (input.IsKeyDown(And::KeyCode::Space)){

      printf("Space down!\n");
    }

    if (input.IsKeyPressed(And::KeyCode::Space)){

      printf("Space pressed!\n");
    }

    if (input.IsKeyRelease(And::KeyCode::Space)){

      printf("Space released!\n");
    }

    if(g_shader.has_value()){
      g_shader->use();
    }
    
    //g_renderer.showDemo();
    g_renderer.draw_triangle(&tri);
    
    //input.update_input();
    g_renderer.end_frame();
  }


  
  

  
  return 0;
}