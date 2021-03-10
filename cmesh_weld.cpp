#include "cmesh.h"

#include "LiteMath.h"
using LiteMath::float4;
using LiteMath::float3;
using LiteMath::float2;

#include <cmath>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <iostream>

namespace cmesh
{
  struct vertex_cache
  {
    float3 pos;
    float3 normal;
    float4 tangent;
    float2 uv;

    vertex_cache() = default;
  };

  struct vertex_cache_hash
  {
    std::size_t operator()(const vertex_cache &v) const
    {
      using std::size_t;
      using std::hash;
      return ((hash<int>()(int(v.pos.x * 73856093))) ^
        (hash<int>()(int(v.pos.y * 19349663))) ^
        (hash<int>()(int(v.pos.z * 83492791))) ^
        (hash<int>()(int(v.normal.x * 12929173))) ^
        (hash<int>()(int(v.normal.y * 15484457))) ^
        (hash<int>()(int(v.normal.z * 26430499))) ^
        (hash<int>()(int(v.uv.x * 30025883))) ^
        (hash<int>()(int(v.uv.y * 41855327))) ^
        (hash<int>()(int(v.tangent.x * 50040937))) ^
        (hash<int>()(int(v.tangent.y * 57208453))) ^
        (hash<int>()(int(v.tangent.z * 60352007))));
    }
  };

  struct float3_hash
  {
    std::size_t operator()(const float3& k) const
    {
      using std::size_t;
      using std::hash;
      return ((hash<int>()(int(k.x * 73856093))) ^
        (hash<int>()(int(k.y * 19349663))) ^
        (hash<int>()(int(k.z * 83492791))));
    }
  };

  struct vertex_cache_eq
  {
    bool operator()(const vertex_cache & u, const vertex_cache & v) const
    {
      return (fabsf(u.pos.x - v.pos.x) < 1e-6) && (fabsf(u.pos.y - v.pos.y) < 1e-6) && (fabsf(u.pos.z - v.pos.z) < 1e-6) && //pos
        (fabsf(u.normal.x - v.normal.x) < 1e-3) && (fabsf(u.normal.y - v.normal.y) < 1e-3) && (fabsf(u.normal.z - v.normal.z) < 1e-3) && //norm
        (fabsf(u.uv.x - v.uv.x) < 1e-5) && (fabsf(u.uv.y - v.uv.y) < 1e-5) &&
        (fabsf(u.tangent.x - v.tangent.x) < 1e-3) && (fabsf(u.tangent.y - v.tangent.y) < 1e-3) && (fabsf(u.tangent.z - v.tangent.z) < 1e-3); //&&
        //(fabsf(u.tangent.w - v.tangent.w) < 1e-1); //tangents
    }
  };

  float4 vertex_attrib_by_index_f4(const std::string &attrib_name, uint32_t vertex_index, const cmesh::SimpleMesh& mesh)
  {
    float4 res;
    if (attrib_name == "pos")
    {
      res = mesh.vPos4f.at(vertex_index);
    } else if (attrib_name == "normal")
    {
      res = mesh.vNorm4f.at(vertex_index);
    } else if (attrib_name == "tangent")
    {
      res = mesh.vTang4f.at(vertex_index);
    }

    return res;
  }

  void update_vertex_attrib_by_index_f4(float4 new_val, uint32_t vertex_index, std::vector <float> &attrib_vec)
  {
    attrib_vec.at(vertex_index * 4 + 0) = new_val.x;
    attrib_vec.at(vertex_index * 4 + 1) = new_val.y;
    attrib_vec.at(vertex_index * 4 + 2) = new_val.z;
    attrib_vec.at(vertex_index * 4 + 3) = new_val.w;
  }

  float2 vertex_attrib_by_index_f2(const std::string &attrib_name, uint32_t vertex_index, const cmesh::SimpleMesh& mesh)
  {
    float2 res;
    if (attrib_name == "uv")
    {
      res = float2(mesh.vTexCoord2f.at(vertex_index)[0], mesh.vTexCoord2f.at(vertex_index)[1]);
    }

    return res;
  }

  void update_vertex_attrib_by_index_f2(float2 new_val, uint32_t vertex_index, std::vector <float> &attrib_vec)
  {
    attrib_vec.at(vertex_index * 2 + 0) = new_val.x;
    attrib_vec.at(vertex_index * 2 + 1) = new_val.y;
  }

};



void cmesh::WeldVertices(cmesh::SimpleMesh& mesh, int indexNum)
{
  std::vector<uint32_t> indices_new;
  //std::unordered_map<float3, uint32_t, float3_hash, pos_eq> vertex_hash;
  std::unordered_map<vertex_cache, uint32_t, cmesh::vertex_cache_hash, cmesh::vertex_cache_eq> vertex_hash;

  std::vector<float4> vertices_new(mesh.vPos4f.size(), float4(0, 0, 0 ,0));
  std::vector<float4> normals_new(mesh.vNorm4f.size(), float4(0, 0, 0, 0));
  std::vector<float2> uv_new(mesh.vTexCoord2f.size(), float2(0, 0));
  std::vector<float4> tangents_new(mesh.vTang4f.size(), float4(0, 0, 0, 0));
  std::vector<int32_t> mid_new;
  mid_new.reserve(mesh.matIndices.size());

  uint32_t index = 0;
  for (auto i = 0u; i < mesh.indices.size(); i += 3)
  {
    const uint32_t indA = mesh.indices[i + 0];
    const uint32_t indB = mesh.indices[i + 1];
    const uint32_t indC = mesh.indices[i + 2];

    if (indA == indB || indA == indC || indB == indC)
      continue;

    auto old_mid = mesh.matIndices.at(i / 3);
    mid_new.push_back(old_mid);

    float4 tmp = vertex_attrib_by_index_f4("pos", indA, mesh);
    float3 A(tmp.x / tmp.w, tmp.y / tmp.w, tmp.z / tmp.w);
    tmp = vertex_attrib_by_index_f4("normal", indA, mesh);
    float3 A_normal(tmp.x, tmp.y, tmp.z);
    float2 tmp2 = vertex_attrib_by_index_f2("uv", indA, mesh);
    float2 A_uv(tmp2.x, tmp2.y);
    float4 A_tan = vertex_attrib_by_index_f4("tangent", indA, mesh);

    vertex_cache A_cache;
    A_cache.pos = A;
    A_cache.normal = A_normal;
    A_cache.uv = A_uv;
    A_cache.tangent = A_tan;

    auto it = vertex_hash.find(A_cache);

    if (it != vertex_hash.end())
    {
      indices_new.push_back(it->second);
    } else
    {
      vertex_hash[A_cache] = index;
      indices_new.push_back(index);

      if(index == vertices_new.size())
      {
        vertices_new.emplace_back(float4(A.x, A.y, A.z, 1.0f));
        normals_new.emplace_back(float4(A_normal.x, A_normal.y, A_normal.z, 0.0f));
        uv_new.emplace_back(float2(A_uv.x, A_uv.y));
        tangents_new.emplace_back(A_tan);
      }
      else
      {
        vertices_new.at(index) = float4(A.x, A.y, A.z, 1.0f);
        normals_new.at(index) = float4(A_normal.x, A_normal.y, A_normal.z, 0.0f);
        uv_new.at(index) = float2(A_uv.x, A_uv.y);
        tangents_new.at(index) = A_tan;
      }

      index++;
    }

    tmp = vertex_attrib_by_index_f4("pos", indB, mesh);
    float3 B(tmp.x / tmp.w, tmp.y / tmp.w, tmp.z / tmp.w);
    tmp = vertex_attrib_by_index_f4("normal", indB, mesh);
    float3 B_normal(tmp.x, tmp.y, tmp.z);
    tmp2 = vertex_attrib_by_index_f2("uv", indB, mesh);
    float2 B_uv(tmp2.x, tmp2.y);
    float4 B_tan = vertex_attrib_by_index_f4("tangent", indB, mesh);

    vertex_cache B_cache;
    B_cache.pos = B;
    B_cache.normal = B_normal;
    B_cache.uv = B_uv;
    B_cache.tangent = B_tan;

    it = vertex_hash.find(B_cache);
    if (it != vertex_hash.end())
    {
      indices_new.push_back(it->second);
    } else
    {
      vertex_hash[B_cache] = index;
      indices_new.push_back(index);

      if(index == vertices_new.size())
      {
        vertices_new.emplace_back(float4(B.x, B.y, B.z, 1.0f));
        normals_new.emplace_back(float4(B_normal.x, B_normal.y, B_normal.z, 0.0f));
        uv_new.emplace_back(float2(B_uv.x, B_uv.y));
        tangents_new.emplace_back(B_tan);
      }
      else
      {
        vertices_new.at(index) = float4(B.x, B.y, B.z, 1.0f);
        normals_new.at(index) = float4(B_normal.x, B_normal.y, B_normal.z, 0.0f);
        uv_new.at(index) = float2(B_uv.x, B_uv.y);
        tangents_new.at(index) = B_tan;
      }

      index++;
    }

    tmp = vertex_attrib_by_index_f4("pos", indC, mesh);
    float3 C(tmp.x / tmp.w, tmp.y / tmp.w, tmp.z / tmp.w);
    tmp = vertex_attrib_by_index_f4("normal", indC, mesh);
    float3 C_normal(tmp.x, tmp.y, tmp.z);
    tmp2 = vertex_attrib_by_index_f2("uv", indC, mesh);
    float2 C_uv(tmp2.x, tmp2.y);
    float4 C_tan = vertex_attrib_by_index_f4("tangent", indC, mesh);

    vertex_cache C_cache;
    C_cache.pos = C;
    C_cache.normal = C_normal;
    C_cache.uv = C_uv;
    C_cache.tangent = C_tan;


    it = vertex_hash.find(C_cache);
    if (it != vertex_hash.end())
    {
      indices_new.push_back(it->second);
    } else
    {
      vertex_hash[C_cache] = index;
      indices_new.push_back(index);

      if(index == vertices_new.size())
      {
        vertices_new.emplace_back(float4(C.x, C.y, C.z, 1.0f));
        normals_new.emplace_back(float4(C_normal.x, C_normal.y, C_normal.z, 0.0f));
        uv_new.emplace_back(float2(C_uv.x, C_uv.y));
        tangents_new.emplace_back(C_tan);
      }
      else
      {
        vertices_new.at(index) = float4(C.x, C.y, C.z, 1.0f);
        normals_new.at(index) = float4(C_normal.x, C_normal.y, C_normal.z, 0.0f);
        uv_new.at(index) = float2(C_uv.x, C_uv.y);
        tangents_new.at(index) = C_tan;
      }

      index++;
    }
  }
//  std::cout << "MAX INDEX WAS = " << *std::max_element(mesh.indices.begin(), mesh.indices.end()) << std::endl;
//  std::cout << "MAX INDEX NOW = " << index - 1<< std::endl;

  mesh.vPos4f.assign(vertices_new.begin(), vertices_new.begin() + index);
  mesh.vNorm4f.assign(normals_new.begin(), normals_new.begin() + index);
  mesh.vTexCoord2f.assign(uv_new.begin(), uv_new.begin() + index);
  mesh.vTang4f.assign(tangents_new.begin(), tangents_new.begin() + index);
  mesh.indices.assign(indices_new.begin(), indices_new.end());
  mesh.matIndices.assign(mid_new.begin(), mid_new.end());

  indexNum = int(indices_new.size());
}
