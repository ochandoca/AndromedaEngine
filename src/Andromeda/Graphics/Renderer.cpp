#include "Andromeda/Graphics/Renderer.h"
#include "Backends/OpenGL/RendererOpenGL.h"
#include "Andromeda/HAL/Window.h"

namespace And
{

  std::shared_ptr<Renderer> Renderer::CreateShared(Window& window){

    switch(window.get_api_type()){
      case EGraphicsApiType::OpenGL:

        return std::make_shared<RendererOpenGL>(window);
      break;
      case EGraphicsApiType::DirectX11:
        return nullptr;
        //return std::make_shared<RendererDirectX>(window);
      break;
      default:
          assert(false);
          return nullptr;
      break;
    }
  }

}
  