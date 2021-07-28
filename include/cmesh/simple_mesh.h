//////////////////////////////////
// Created by frol on 23.11.19. //
//////////////////////////////////

#ifndef CMESH_SIMPLE_MESH_H
#define CMESH_SIMPLE_MESH_H

#include <vector>
#include <cassert>

#include "LiteMath.h"
#include "aligned_alloc.h"

namespace cmesh
{
  using LiteMath::float4;
  using LiteMath::float2;
  using cvex::aligned;

  // very simple utility mesh representation for working with geometry on the CPU in C++
  //
  struct SimpleMesh
  {
    static const uint64_t POINTS_IN_TRIANGLE = 3;
    SimpleMesh(){}
    SimpleMesh(int a_vertNum, int a_indNum) { Resize(a_vertNum, a_indNum); }

    inline size_t VerticesNum()  const { return vPos4f.size(); }
    inline size_t IndicesNum()   const { return indices.size();  }
    inline size_t TrianglesNum() const { return IndicesNum() / POINTS_IN_TRIANGLE;  }
    inline void   Resize(uint32_t a_vertNum, uint32_t a_indNum)
    {
      vPos4f.resize(a_vertNum);
      vNorm4f.resize(a_vertNum);
      vTang4f.resize(a_vertNum);
      vTexCoord2f.resize(a_vertNum);
      indices.resize(a_indNum);
      matIndices.resize(a_indNum / POINTS_IN_TRIANGLE);
      assert(a_indNum % POINTS_IN_TRIANGLE == 0); // PLEASE NOTE THAT CURRENT IMPLEMENTATION ASSUME ONLY TRIANGLE MESHES! 
    };

    inline size_t SizeInBytes() const
    {
      return vPos4f.size()*sizeof(float)*4  +
             vNorm4f.size()*sizeof(float)*4 +
             vTang4f.size()*sizeof(float)*4 +
             vTexCoord2f.size()*sizeof(float)*2 +
             indices.size()*sizeof(int) +
             matIndices.size()*sizeof(int);
    }

    //enum SIMPLE_MESH_TOPOLOGY {SIMPLE_MESH_TRIANGLES = 0, SIMPLE_MESH_QUADS = 1};
    //SIMPLE_MESH_TOPOLOGY topology = SIMPLE_MESH_TRIANGLES;
    LiteMath::Box4f GetAABB() const;

    float GetAvgTriArea() const;
    float GetAvgTriPerimeter() const;

    void ApplyMatrix(const LiteMath::float4x4& m);

    cvex::vector<LiteMath::float4> vPos4f;      //
    cvex::vector<LiteMath::float4> vNorm4f;     //
    cvex::vector<LiteMath::float4> vTang4f;     //
    std::vector<float2>                       vTexCoord2f; //
    std::vector<unsigned int>                 indices;     // size = 3*TrianglesNum() for triangle mesh, 4*TrianglesNum() for quad mesh
    std::vector<unsigned int>                 matIndices;  // size = 1*TrianglesNum()
  };

  void WeldVertices(SimpleMesh& mesh, int indexNum);
};


#endif // CMESH_SIMPLE_MESH_H
