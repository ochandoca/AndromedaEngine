#pragma once

#include "Graphics/GraphicsContext.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>

class OpenGLContext : public GraphicsContext
{
public:
  OpenGLContext(GLFWwindow* window);

  virtual ~OpenGLContext();

  virtual void create_info() override;

  virtual std::shared_ptr<Renderer> create_renderer() override;
    
private:
  GLFWwindow* m_Window;
  std::string m_ContextInfo;
};