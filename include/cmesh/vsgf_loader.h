//////////////////////////////////
// Created by frol on 23.11.19. //
//////////////////////////////////

#ifndef CMESH_VSGF_LOADER_H
#define CMESH_VSGF_LOADER_H

#include "simple_mesh.h"

namespace cmesh
{

#if defined(__ANDROID__)
  SimpleMesh LoadMeshFromVSGF(AAssetManager* mgr, const char* a_fileName);
#else
  SimpleMesh LoadMeshFromVSGF(const char* a_fileName);
#endif
  void       SaveMeshToVSGF  (const char* a_fileName, const SimpleMesh& a_mesh);

  SimpleMesh CreateQuad(const int a_sizeX, const int a_sizeY, const float a_size);
};


#endif // CMESH_VSGF_LOADER_H
