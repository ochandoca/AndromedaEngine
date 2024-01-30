#type Vertex
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normals;

struct AmbientLight{
  float enabled;
  vec3 direction;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
};

struct DirectionalLight{
  float enabled;
  vec3 direction;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
};

struct PointLight{
  float enabled;
  vec3 position;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
  float constant_att;
  float linear_att;
  float quadratic_att;
  float padding; // 64 bytes
};

struct SpotLight{
  float enabled;
  vec3 position;
  vec3 direction;
  float cutt_off;
  float outer_cut_off;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
  float constant_att;
  float linear_att;
  float quadratic_att; // 80 bytes

};


layout (std140) uniform UniformBlock{
  mat4 model;
  mat4 view;
  mat4 projection;
  AmbientLight ambient;
  DirectionalLight directional;
  PointLight point;
  SpotLight spot;
  vec3 camera_position;
};

out vec3 blend_color;
out vec3 s_normal;
out vec3 s_fragPos;


void main(){
  gl_Position = projection * view * model * vec4(position, 1.0);
  blend_color = vec3(directional.enabled + ambient.enabled, point.enabled, spot.enabled);
  blend_color = vec3(camera_position.x/20.0, camera_position.y/20.0, camera_position.z/20.0);
  s_fragPos = vec3(model * vec4(position, 1.0));
  s_normal = normals;
}


#type Fragment
#version 430 core

//uniform vec3 u_camera_position;

out vec4 FragColor;
in vec3 blend_color;
in vec3 s_normal;
in vec3 s_fragPos;

struct AmbientLight{
  float enabled;
  vec3 direction;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
};

struct DirectionalLight{
  float enabled;
  vec3 direction;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
};

struct PointLight{
  float enabled;
  vec3 position;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
  float constant_att;
  float linear_att;
  float quadratic_att;
  float padding;
};

struct SpotLight{
  float enabled;
  vec3 position;
  vec3 direction;
  float cutt_off;
  float outer_cut_off;
  vec3 diffuse_color;
  vec3 specular_color;
  float specular_strength;
  float specular_shininess;
  float constant_att;
  float linear_att;
  float quadratic_att;
};

layout (std140) uniform UniformBlock{
  mat4 model;
  mat4 view;
  mat4 projection;
  AmbientLight ambient;
  DirectionalLight directional;
  PointLight point;
  SpotLight spot;
  vec3 camera_position;
};



vec3 CalculeDirLight(AmbientLight light, vec3 normal, vec3 viewDir, vec3 color_base) {

  /*---Difuse---*/
  float diff = max(dot(normal, light.direction), 0.0);
  vec3 diffuse = diff * light.diffuse_color * color_base.xyz;

  /*---Specular---*/

  vec3 reflectDir = normalize(reflect(-(light.direction), normalize(normal))  );
  float spec = pow(max(dot(normalize(viewDir), normalize(reflectDir)), 0.0), light.specular_shininess);
  vec3 specular = light.specular_strength * spec * light.specular_color * color_base.xyz;

  //return (diffuse + specular * light.active);
  return (diffuse * light.enabled);
}

void main(){
  vec3 view_direction = normalize(camera_position - s_fragPos);
  float ambient_strength = 0.01;
  vec3 ambient_color = vec3(1.0);
  ambient_color = ambient_strength * ambient_color;
  vec3 color = ambient_color;
  vec3 color_base = vec3(0.5, 0.5, 0.0);

  color += CalculeDirLight(ambient, s_normal, view_direction, color_base);
  //FragColor = vec4(ambient.diffuse_color.x, ambient.diffuse_color.y, ambient.diffuse_color.z, 1.0);
  FragColor = vec4(color, 1.0);
  //FragColor = vec4(1.0, 0.0, 0.5, 1.0);
  //FragColor = vec4(blend_color, 1.0);


}