#include "Andromeda/Graphics/ObjLoader.h"
#include "tiny_obj_loader.h"
#include "Backends/OpenGL/OpenGL.h"
#include <iostream>

namespace And{


std::shared_ptr<ObjLoader> ObjLoader::load(std::string filename, std::string base_path){

  std::cout << "Loading obj... " << filename << std::endl;

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials_obj;
  std::string warn;
  std::string err;

  std::vector<unsigned int> indices;
  std::vector<Vertex_info> vertex_info;
  Material_info mat;

  // Si le pasamos la ruta y luego el nombre, cogera los .mtl del directorio
  bool error = tinyobj::LoadObj(&attrib, &shapes, &materials_obj, &warn, &err, filename.c_str(), base_path.c_str(), true);

  if (!err.empty()) {
    //m_obj_info.replace(0, err.length(), err.c_str());
    printf("Obj not loaded correctly %s\n", err.c_str());
    return nullptr;
  }else{
    printf("Obj loaded correctly\n");

    int inner = 0;
    int outer = 0;
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {

            Vertex_info v_info;
  
            // Load vertex
            v_info.position[0] = attrib.vertices[3 * index.vertex_index + 0];
            v_info.position[1] = attrib.vertices[3 * index.vertex_index + 1];
            v_info.position[2] = attrib.vertices[3 * index.vertex_index + 2];
            
            // Load normals
            if (attrib.normals.size() > 0) {
                v_info.normal[0] = attrib.normals[3 * index.normal_index + 0];
                v_info.normal[1] = attrib.normals[3 * index.normal_index + 1];
                v_info.normal[2] = attrib.normals[3 * index.normal_index + 2];
            }

            // Load UV
            if(attrib.texcoords.size() > 0){
              v_info.uv[0] = attrib.texcoords[2 * index.texcoord_index + 0];
              v_info.uv[1] = attrib.texcoords[2 * index.texcoord_index + 1];
            }

            vertex_info.push_back(v_info);
            indices.push_back(static_cast<unsigned int>(indices.size()));

            inner++;
        }
        outer++;
    }


    if(materials_obj.size() > 0){

      for(auto& m : materials_obj){
        if(m.ambient){
          mat.ambient[0] = m.ambient[0];
          mat.ambient[1] = m.ambient[1];
          mat.ambient[2] = m.ambient[2];
        }

        if(m.diffuse){
          mat.diffuse[0] = m.diffuse[0];
          mat.diffuse[1] = m.diffuse[1];
          mat.diffuse[2] = m.diffuse[2];
        }

        if(m.specular){
          mat.specular[0] = m.specular[0];
          mat.specular[1] = m.specular[1];
          mat.specular[2] = m.specular[2];
        }
      }
    }


  }

  ObjLoader obj{indices, vertex_info, mat};

  printf("Init obj\n");

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  obj.set_VAO(VAO);
  
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  obj.set_VBO(VBO);

  glBindVertexArray(obj.get_vao());
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, vertex_info.size() * sizeof(Vertex_info), &vertex_info[0], GL_STATIC_DRAW);
  
  // Desbindeamos el vao
  glBindVertexArray(0);  

  WAIT_GPU_LOAD()
  return std::make_shared<ObjLoader>(obj);
}

ObjLoader::ObjLoader(std::vector<unsigned int> indices, std::vector<Vertex_info> vertex_info, Material_info mat) :
 m_mat_info(mat), m_vertex_info(vertex_info),m_indices(indices){
}

const std::vector<Vertex_info>& ObjLoader::getVertexInfo(){
  return m_vertex_info;
}


const std::vector<unsigned int>& ObjLoader::getIndices(){
  return m_indices;
}


}