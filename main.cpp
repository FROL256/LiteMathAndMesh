#include <iostream>
#include "include/LiteMath.h"
#include "cmesh/vsgf_loader.h"

#include "tests/tests.h"

int main(int argc, const char** argv)
{
  run_all_tests();
  // auto mesh = cmesh::LoadMeshFromVSGF("chunk_00005.vsgf"); Set your filename here for load test.
  return 0;
}
