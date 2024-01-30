#pragma once
#include "Common/Light.h"
#include <optional>

namespace And{

  enum ShaderType
  {
    Shader_Vertex,
    Shader_Fragment,
    Shader_Geometry,
    Shader_Teselation,
  };

  struct ShaderInfo{
    const char* path_fragment = nullptr;
    const char* path_vertex = nullptr;
    const char* path_teselation = nullptr;
    const char* path_geometry = nullptr;
  };

  struct UniformBlockData{
    float model[16];
    float view[16];
    float projection[16];
    AmbientLight light_ambient;
    DirectionalLight light_directional;
    PointLight light_point;
    SpotLight light_spot;
    float camera_position[3];
  };

  class Shader
  {
  public:

    static std::shared_ptr<Shader> make(ShaderInfo s_info);
    static std::shared_ptr<Shader> make(const std::string& path);
    Shader(const Shader& other) = delete;
    Shader(Shader&& other);
    ~Shader();


    Shader& operator=(const Shader& other) = delete;
    Shader& operator=(Shader&& other);

    void setMat4(std::string name, const float matrix[16]);
    void setVec3(std::string name, const float vector[9]);
    void uploadAmbient(AmbientLight* light);
    void setModelViewProj(const float model[16], const float view[16], const float projection[16]);

    void SetUniformBlock();
    
    void use();
    void configure_shader();
    void un_configure_shader();
    void set_light(AmbientLight* light);


    void set_camera_position(const float position[3]);

    void upload_data();
    void reload();

  private:
    Shader();
    std::unique_ptr<struct ShaderData> m_Data;
    char m_shader_error[1024] = {0};

    std::shared_ptr<UniformBlockData> m_uniform_block;

  };
}