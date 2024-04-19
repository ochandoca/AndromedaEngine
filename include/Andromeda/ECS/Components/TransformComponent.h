#pragma once

#include "Andromeda/Misc/CoreMiscDefines.h"
#include "Andromeda/HAL/Types.h"

#include "Andromeda/ECS/ComponentBase.h"

namespace And
{
  struct Mat4
  {
    float d[16] = { 0.0f };
  };

  class TransformComponent : public ComponentBase{

  public:
    float position[3] = { 0.0f };
    float rotation[3] = { 0.0f };
    float scale[3] = { 1.0f };

    TransformComponent* m_parent = nullptr;

    // hijo  * padre

    Mat4 matrix;

    float* GetModelMatrix();
    void SetParent(TransformComponent* parent);
    void SetPosition(float* p);
    void SetPosition(float x, float y, float z);

    void SetRotation(float* r);
    void SetRotation(float x, float y, float z);

    void SetScale(float* t);
    void SetScale(float x, float y, float z);

  private:
      bool m_should_recalculate = true;
      float* m_model_matrix = nullptr;
  };
}