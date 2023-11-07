#include "Common/ObjLoader.h"
#include "tiny_obj_loader.h"
#include <iostream>

namespace And{


std::optional<ObjLoader> ObjLoader::load(std::string filename, std::string base_path){

  std::cout << "Loading obj... " << filename << std::endl;

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials_obj;
  std::string warn;
  std::string err;

  std::vector<float> vertices;
  std::vector<float> vertices_wheights;
  std::vector<float> colors;
  std::vector<float> normals;
  std::vector<float> tex_coords;
  std::vector<unsigned int> indices;

  Material_info mat;

  // Si le pasamos la ruta y luego el nombre, cogera los .mtl del directorio
  //bool error = tinyobj::LoadObj(&attrib, &shapes, &materials_obj, &warn, &err, filename.c_str(), base_path.c_str());
  bool error = tinyobj::LoadObj(&attrib, &shapes, &materials_obj, &warn, &err, filename.c_str(), base_path.c_str());

  if (!err.empty()) {
    //m_obj_info.replace(0, err.length(), err.c_str());
    printf("Obj not loaded correctly %s\n", err.c_str());
    return std::nullopt;
  }else{
    printf("Obj loaded correctly\n");

    // Guardar vertices en vector de floats
    vertices = attrib.GetVertices();
    vertices_wheights = attrib.GetVertexWeights();
    normals = attrib.normals;
    tex_coords = attrib.texcoords;
    colors = attrib.colors;
    std::vector<tinyobj::index_t> indices_tmp = shapes[0].mesh.indices;

    for(auto& element : indices_tmp){
      std::cout << element.vertex_index << " ";
      indices.push_back((unsigned int)element.vertex_index);
    }


    /*if(material_name.length() != 0){

      std::map<std::string, int> *material_map;
      std::vector<tinyobj::material_t> *materials;
      std::istream *inStream;
      std::string *warning = new std::string("nothing");
      std::string *error_mat = new std::string("nothing");

      std::ifstream matIStream(material_name.c_str());
      if(matIStream){
        //tinyobj::LoadMtl(material_map, materials, inStream, warning, error_mat);
      }
    }*/

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



  ObjLoader obj{vertices, vertices_wheights, normals, tex_coords, colors, indices, mat};
  return std::optional<ObjLoader>(std::move(obj));
}

ObjLoader::ObjLoader(std::vector<float> v, std::vector<float> v_w, std::vector<float> normals, std::vector<float> tex_coords, std::vector<float> colors, std::vector<unsigned int> indices, Material_info mat) :
 m_vertex(v), m_vertex_weights(v_w), m_normals(normals), m_texcoords(tex_coords), m_colors(colors), m_mat_info(mat), m_indices(indices){

}

const std::vector<float>& ObjLoader::getVertices(){
  return m_vertex;
}

const std::vector<float>& ObjLoader::getNormals(){
  return m_normals;
}

const std::vector<float>& ObjLoader::getColors(){
  return m_colors;
}

const std::vector<float>& ObjLoader::getTexCoords(){
  return m_texcoords;
}

const Material_info& ObjLoader::getMaterialInfo(){
  return m_mat_info;
}

const std::vector<unsigned int>& ObjLoader::getIndices(){
  return m_indices;
}


}