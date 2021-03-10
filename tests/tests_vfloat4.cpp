#include <iostream>
#include <cmath>

#include "include/LiteMath.h"

using namespace cvex;
using namespace LiteMath;

bool vf4_test001_basic()
{
  const float4 Cx1(1.0f, 2.0f, 3.0f, 4.0f);
  const float4 Cx2(5.0f, 5.0f, 6.0f, 7.0f);

  const auto Cx3 = Cx1 - Cx2;
  const auto Cx4 = (Cx1 + Cx2)*Cx1;
  const auto Cx5 = (Cx2 - Cx1)/Cx1;

  float result1[4];
  float result2[4];
  float result3[4];

  store_u(result1, Cx3);
  store_u(result2, Cx4);
  store_u(result3, Cx5);
  
  // check 
  //
  bool passed = true;

  float expr1[4], expr2[4], expr3[4];

  for(int i=0;i<4;i++)
  {
    expr1[i] = Cx1[i] - Cx2[i];
    expr2[i] = (Cx1[i] + Cx2[i])*Cx1[i];
    expr3[i] = (Cx2[i] - Cx1[i])/Cx1[i];

    if(fabs(result1[i] - expr1[i]) > 1e-6f || fabs(result2[i] - expr2[i]) > 1e-6f || fabs(result3[i] - expr3[i]) > 1e-5f) // 1e-2f
      passed = false;
  }

  if(!passed)
  {
    std::cout << "exp1_res:" << result1[0] << " " << result1[1] << " " << result1[2] << " " << result1[3] << std::endl;
    std::cout << "exp1_ref:" << expr1  [0] << " " << expr1  [1] << " " << expr1  [2] << " " << expr1[3] << std::endl;
    std::cout << std::endl;

    std::cout << "exp2_res:" << result2[0] << " " << result2[1] << " " << result2[2] << " " << result2[3] << std::endl;
    std::cout << "exp2_ref:" << expr2  [0] << " " << expr2  [1] << " " << expr2  [2] << " " << expr2[3] << std::endl;
    std::cout << std::endl;

    std::cout << "exp3_res:" << result3[0] << " " << result3[1] << " " << result3[2] << " " << result3[3] << std::endl;
    std::cout << "exp3_ref:" << expr3  [0] << " " << expr3  [1] << " " << expr3  [2] << " " << expr3[3] << std::endl;
    std::cout << std::endl;
  }
  
  return passed;
}

bool vi4_test002_basic()
{
  const int4 Cx1 = {10, 20, -3, 4};
  const int4 Cx2 = {50, -5, 6,  7};

  const auto Cx3 = Cx1 - Cx2;
  const auto Cx4 = (Cx1 + Cx2)*Cx1;
  const auto Cx5 = (Cx2 - Cx1)/Cx1;

  int result1[4];
  int result2[4];
  int result3[4];

  store_u(result1, Cx3);
  store_u(result2, Cx4);
  store_u(result3, Cx5);
  
  // check 
  //
  bool passed = true;

  const int Cx1_copy[4] = {10, 20, -3, 4};
  const int Cx2_copy[4] = {50, -5, 6,  7};

  for(int i=0;i<4;i++)
  {
    const int expr1 = Cx1_copy[i] - Cx2_copy[i];
    const int expr2 = (Cx1_copy[i] + Cx2_copy[i])*Cx1_copy[i];
    const int expr3 = (Cx2_copy[i] - Cx1_copy[i])/Cx1_copy[i];

    if(result1[i] - expr1 != 0 || result2[i] - expr2 != 0 || result3[i] - expr3 != 0)  
    {
      passed = false;
      break;
    } 
  }
  
  return passed;
}

bool vu4_test003_basic()
{
  const vuint4 Cx1 = {10, 20, 3, 4};
  const vuint4 Cx2 = {50, +5, 6, 7};

  const auto Cx3 = Cx1 - Cx2;
  const auto Cx4 = (Cx1 + Cx2)*Cx1;
  const auto Cx5 = (Cx2 - Cx1)/Cx1;

  unsigned int result1[4];
  unsigned int result2[4];
  unsigned int result3[4];

  store_u(result1, Cx3);
  store_u(result2, Cx4);
  store_u(result3, Cx5);
  
  // check 
  //
  bool passed = true;

  const uint32_t Cx1_copy[4] = {10, 20, 3, 4};
  const uint32_t Cx2_copy[4] = {50, +5, 6, 7};

  for(int i=0;i<4;i++)
  {
    const unsigned int expr1 = Cx1_copy[i] - Cx2_copy[i];
    const unsigned int expr2 = (Cx1_copy[i] + Cx2_copy[i])*Cx1_copy[i];
    const unsigned int expr3 = (Cx2_copy[i] - Cx1_copy[i])/Cx1_copy[i];

    if(result1[i] - expr1 != 0 || result2[i] - expr2 != 0 || result3[i] - expr3 != 0)  
    {
      passed = false;
      break;
    } 
  }
  
  return passed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool vf4_test004_basic()
{
  const float4 Cx1 = {1.0f, 2.0f, 3.0f, 4.0f};
  const float  Cx2 = 5.0f;

  const float4 Cx3 = Cx2*(Cx2 - Cx1) - 2.0f;
  const float4 Cx4 = 1.0f + (Cx1 + Cx2)*Cx2;
  const float4 Cx5 = 3.0f - Cx2/(Cx2 - Cx1);
  const float4 Cx6 = (Cx2 + Cx1)/Cx2 + 5.0f;
  const float4 Cx7 = LiteMath::rcp_e(Cx1);

  CVEX_ALIGNED(16) float result1[4];
  CVEX_ALIGNED(16) float result2[4];
  CVEX_ALIGNED(16) float result3[4];
  CVEX_ALIGNED(16) float result4[4];
  CVEX_ALIGNED(16) float result5[4];

  store(result1, Cx3);
  store(result2, Cx4);
  store(result3, Cx5);
  store(result4, Cx6);
  store(result5, Cx7);
  
  // check 
  //
  bool passed = true;

  for(int i=0;i<4;i++)
  {
    const float expr1 = Cx2*(Cx2 - Cx1[i]) - 2.0f;
    const float expr2 = 1.0f + (Cx1[i] + Cx2)*Cx2;
    const float expr3 = 3.0f - Cx2/(Cx2 - Cx1[i]);
    const float expr4 = (Cx2 + Cx1[i])/Cx2 + 5.0f;
    const float expr5 = 1.0f/Cx1[i];

    if(fabs(result1[i] - expr1) > 1e-6f || fabs(result2[i] - expr2) > 1e-6f || 
       fabs(result3[i] - expr3) > 1e-6f || fabs(result4[i] - expr4) > 1e-6f || fabs(result5[i] - expr5) > 1e-2f) // require less precition for reciprocal
    {
      passed = false;
      break;
    } 
  }
  
  return passed;
}

bool vi4_test005_basic()
{
  const int4 Cx1 = {1, -2, 3, -4};
  const int   Cx2 = 5;

  const auto Cx3 = Cx2*(Cx2 - Cx1) - 2;
  const auto Cx4 = 1 + (Cx1 + Cx2)*Cx2;
  const auto Cx5 = 3 - Cx2/(Cx2 - Cx1);
  const auto Cx6 = (Cx2 + Cx1)/Cx2 + 5;

  CVEX_ALIGNED(16) int result1[4];
  CVEX_ALIGNED(16) int result2[4];
  CVEX_ALIGNED(16) int result3[4];
  CVEX_ALIGNED(16) int result4[4];

  store(result1, Cx3);
  store(result2, Cx4);
  store(result3, Cx5);
  store(result4, Cx6);
  
  // check 
  //
  bool passed = true;

  const int Cx1_copy[4] = {1, -2, 3, -4};

  for(int i=0;i<4;i++)
  {
    const int expr1 = Cx2*(Cx2 - Cx1_copy[i]) - 2;
    const int expr2 = 1 + (Cx1_copy[i] + Cx2)*Cx2;
    const int expr3 = 3 - Cx2/(Cx2 - Cx1_copy[i]);
    const int expr4 = (Cx2 + Cx1_copy[i])/Cx2 + 5;

    if(result1[i] != expr1 || result2[i] != expr2 || 
       result3[i] != expr3 || result4[i] != expr4)  
    {
      passed = false;
      break;
    } 
  }
  
  return passed;
}

bool vu4_test006_basic()
{
  const vuint4       Cx1 = {1, 2, 3, 4};
  const unsigned int Cx2 = 5;

  const auto Cx3 = Cx2*(Cx2 - Cx1) - 2;
  const auto Cx4 = 1 + (Cx1 + Cx2)*Cx2;
  const auto Cx5 = 3 - Cx2/(Cx2 - Cx1);
  const auto Cx6 = (Cx2 + Cx1)/Cx2 + 5;

  CVEX_ALIGNED(16) unsigned int result1[4];
  CVEX_ALIGNED(16) unsigned int result2[4];
  CVEX_ALIGNED(16) unsigned int result3[4];
  CVEX_ALIGNED(16) unsigned int result4[4];

  store(result1, Cx3);
  store(result2, Cx4);
  store(result3, Cx5);
  store(result4, Cx6);
  
  // check 
  //
  bool passed = true;

  const uint32_t Cx1_copy[4] = {1, 2, 3, 4};

  for(int i=0;i<4;i++)
  {
    const unsigned int expr1 = Cx2*(Cx2 - Cx1_copy[i]) - 2;
    const unsigned int expr2 = 1 + (Cx1_copy[i] + Cx2)*Cx2;
    const unsigned int expr3 = 3 - Cx2/(Cx2 - Cx1_copy[i]);
    const unsigned int expr4 = (Cx2 + Cx1_copy[i])/Cx2 + 5;

    if(result1[i] != expr1 || result2[i] != expr2 || 
       result3[i] != expr3 || result4[i] != expr4)    
    {
      passed = false;
      break;
    } 
  }
  
  return passed;
}

bool vi4_test007_and_or()
{
  const int4 Cx1 = {-1, -2, 3, 4};
  const int4 Cx2 = {+1, +2, 63355, 63355};
  const int4 Cx3 = {-1, -1, int(0xF0F00000), 0x00000000};

  const auto Cr1 = (Cx1 & (~Cx3)) | Cx2;
  const auto Cr2 = (Cx2 & Cx3)    | Cx1;

  int result1[4];
  int result2[4];

  store_u(result1, Cr1);
  store_u(result2, Cr2);

  bool passed = true;

  const int Cx1_copy[4] = {-1, -2, 3, 4};
  const int Cx2_copy[4] = {+1, +2, 63355, 63355};
  const int Cx3_copy[4] = {-1, -1, int(0xF0F00000), 0x00000000};

  for(int i=0;i<4;i++)
  {
    const int expr1 = (Cx1_copy[i] & (~Cx3_copy[i])) | Cx2_copy[i];
    const int expr2 = (Cx2_copy[i] & Cx3_copy[i])    | Cx1_copy[i];

    if(result1[i] != expr1 || result2[i] != expr2)    
    {
      passed = false;
      break;
    } 
  }

  return passed;
}

bool vu4_test008_and_or()
{
  const vuint4 Cx1 = {0xFFFFFFFF, (unsigned int)(-2), 3, 4};
  const vuint4 Cx2 = {+1, +2, 63355, 63355};
  const vuint4 Cx3 = {0xFFFFFFFF, 0xFFFFFFFF, 0xF0F00000, 0x00000000};

  const auto Cr1 = (Cx1 & (~Cx3)) | Cx2;
  const auto Cr2 = (Cx2 & Cx3)    | Cx1;

  unsigned int result1[4];
  unsigned int result2[4];

  store_u(result1, Cr1);
  store_u(result2, Cr2);

  bool passed = true;

  const uint32_t Cx1_copy[4] = {0xFFFFFFFF, (unsigned int)(-2), 3, 4};
  const uint32_t Cx2_copy[4] = {+1, +2, 63355, 63355};
  const uint32_t Cx3_copy[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xF0F00000, 0x00000000};


  for(int i=0;i<4;i++)
  {
    const unsigned int expr1 = (Cx1_copy[i] & (~Cx3_copy[i])) | Cx2_copy[i];
    const unsigned int expr2 = (Cx2_copy[i] & Cx3_copy[i])    | Cx1_copy[i];

    if(result1[i] != expr1 || result2[i] != expr2)    
    {
      passed = false;
      break;
    } 
  }

  return passed;
}

bool vi4_test009_shift()
{
  const int4 Cx1 = {-1, -2, 3, 4};
  const int4 Cx2 = {+1, +2, 63355, 63355};
  const int4 Cx3 = {-1, -1, int(0xF0F00000), 0x00000000};

  const auto Cr1 = (Cx1 << 8); // | (Cx2 >> 17);
  const auto Cr2 = (Cx3 >> 9); // | (Cx3 >> 4);

  int result1[4];
  int result2[4];

  store_u(result1, Cr1);
  store_u(result2, Cr2);

  bool passed = true;

  const int Cx1_copy[4] = {-1, -2, 3, 4};
  const int Cx3_copy[4] = {-1, -1, int(0xF0F00000), 0x00000000};

  for(int i=0;i<4;i++)
  {
    const int expr1 = (Cx1_copy[i] << 8); // | (Cx2[i] >> 17);
    const int expr2 = (Cx3_copy[i] >> 9); //   (Cx3[i] >> 4);

    if(result1[i] != expr1 || result2[i] != expr2)    
    {
      passed = false;
      break;
    } 
  }

  return passed;
}


bool vu4_test010_shift()
{
  const vuint4 Cx1 = {0xFFFFFFFF, (unsigned int)(-2), 3, 4};
  const vuint4 Cx2 = {+1, +2, 63355, 63355};
  const vuint4 Cx3 = {0xFFFFFFFF, 0xFFFFFFFF, 0xF0F00000, 0x00000000};

  const auto Cr1 = (Cx1 << 8) | (Cx2 >> 17); 
  const auto Cr2 = (Cx3 << 9) | (Cx3 >> 4); 

  unsigned int result1[4];
  unsigned int result2[4];

  store_u(result1, Cr1);
  store_u(result2, Cr2);

  bool passed = true;

  const unsigned int Cx1_copy[4] = {0xFFFFFFFF, (unsigned int)(-2), 3, 4};
  const unsigned int Cx2_copy[4] = {+1, +2, 63355, 63355};
  const unsigned int Cx3_copy[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xF0F00000, 0x00000000};

  for(int i=0;i<4;i++)
  {
    const unsigned int expr1 = (Cx1_copy[i] << 8) | (Cx2_copy[i] >> 17);
    const unsigned int expr2 = (Cx3_copy[i] << 9) | (Cx3_copy[i] >> 4); 

    if(result1[i] != expr1 || result2[i] != expr2)    
    {
      passed = false;
      break;
    } 
  }

  return passed;
}


bool vf4_test011_splat()
{
  const float4 Cx1 = cvex::splat(1.0f);
  const float4 Cx2 = cvex::splat(-5.0f);

  float result1[4];
  float result2[4];

  store_u(result1, Cx1);
  store_u(result2, Cx2);
  
  // check 
  //
  bool passed = true;

  for(int i=0;i<4;i++)
  {
    if(fabs(result1[i] - 1.0f) > 1e-6f || fabs(result2[i] - (-5.0f)) > 1e-6f)  
    {
      passed = false;
      break;
    } 
  }
  
  return passed;
}


bool vi4_test012_splat()
{
  const int4 Cx1 = cvex::splat(1);
  const int4 Cx2 = cvex::splat(-5);

  int result1[4];
  int result2[4];

  store_u(result1, Cx1);
  store_u(result2, Cx2);
  
  // check 
  //
  bool passed = true;

  for(int i=0;i<4;i++)
  {
    if(result1[i] != 1 || result2[i] != -5)  
    {
      passed = false;
      break;
    } 
  }
  
  return passed;
}

bool vu4_test013_splat()
{
  const vuint4 Cx1 = cvex::splat((unsigned int)(1));
  const vuint4 Cx2 = cvex::splat(0xFFFF0000);

  unsigned int result1[4];
  unsigned int result2[4];

  store_u(result1, Cx1);
  store_u(result2, Cx2);
  
  // check 
  //
  bool passed = true;

  for(int i=0;i<4;i++)
  {
    if(result1[i] != (unsigned int)(1) || result2[i] != 0xFFFF0000)  
    {
      passed = false;
      break;
    } 
  }
  
  return passed;
}

bool vfi4_test014_convert()
{
  const int4  Cx1  = splat(-2456);
  const vuint4 Cx2 = splat(0xFFFFFF00);

  const float4 Cf1 = LiteMath::to_float32(Cx1);
  const float4 Cf2 = LiteMath::to_float32(Cx2);

  float result1[4];
  float result2[4];

  store_u(result1, Cf1);
  store_u(result2, Cf2);

  // check 
  //
  bool passed = true;
  
  const float res1 = float(-2456);
  const float res2 = float(0xFFFFFF00);

  for (int i = 0; i<4; i++)
  {
    if (fabs(result1[i] - res1) > 1e-6f || fabs(result2[i] - res2) > 1e-6f)
    {
      passed = false;
      break;
    }
  }

  return passed;
}

bool viu4_test015_convert()
{
  const float4 Cx1 = { -334324.0f, -0.0f, 1.0f, 23423523.0f };
  const float4 Cx2 = { -10000.0f, 0.0f, 100.0f, 0.000005f };

  const int4  Cr1  = to_int32(Cx1);
  const vuint4 Cr2 = to_uint32(Cx2);
  const vuint4 Cr3 = to_uint32(Cr1);
  const int4  Cr4  = to_int32(Cr2);

  int          result1[4];
  unsigned int result2[4];
  unsigned int result3[4];
  int          result4[4];

  store_u(result1, Cr1);
  store_u(result2, Cr2);
  store_u(result3, Cr3);
  store_u(result4, Cr4);

  // check 
  //
  bool passed = true;

  const int          res1[4] = { int(-334324.0f), int(-0.0f), int(1.0f), int(23423523.0f) };
  const unsigned int res2[4] = { (unsigned int)(-10000.0f),  (unsigned int)(0.0f),  (unsigned int)(100.0f),  (unsigned int)(0.000005f) };
  const unsigned int res3[4] = { (unsigned int)(res1[0]), (unsigned int)(res1[1]), (unsigned int)(res1[2]), (unsigned int)(res1[3]) };
  const          int res4[4] = { (int)(res2[0]), (int)(res2[1]), (int)(res2[2]), (int)(res2[3]) };

  for (int i=0; i<4; i++)
  {
    if (result1[i] != res1[i] || result2[i] != res2[i] || 
        result3[i] != res3[i] || result4[i] != res4[i])
    {
      passed = false;
      break;
    }
  }

  return passed;
}

bool vfi4_test016_cast()
{
  const float4 Cx1 = { -334324.0f, -0.0f, 1.0f, 23423523.0f };
  const float4 Cx2 = { -10000.0f, 0.0f, 100.0f, 0.000005f };
  
  const int4   Cx3 = as_int32 (Cx1);
  const vuint4 Cx4 = as_uint32(Cx2);

  const float4 Cr1 = LiteMath::as_float32(Cx3);
  const float4 Cr2 = LiteMath::as_float32(Cx4);

  float result1[4];
  float result2[4];
  store_u(result1, Cr1);
  store_u(result2, Cr2);

  bool passed = true;

  const float res1[4] = { -334324.0f, -0.0f, 1.0f, 23423523.0f };
  const float res2[4] = { -10000.0f,  0.0f,  100.0f, 0.000005f };
 
  for (int i = 0; i<4; i++)
  {
    if (result1[i] != res1[i] || result2[i] != res2[i])
    {
      passed = false;
      break;
    }
  }

  return passed;
}


bool vf4_test017_mMcRcp()
{
  const float4 Cx1 = { +10000.0f,  -1.0f, 1.0f,   -99999999.0f };
  const float4 Cx2 = { +334324.0f, +1.0f, 100.0f, -0.000005f };
  const float4 Cx3 = { +10.0f,  +10.0f, +10.0f, +10.0f };

  const float4 Cr1 = LiteMath::min(Cx1, Cx2);
  const float4 Cr2 = LiteMath::max(Cx1, Cx2);
  const float4 Cr3 = LiteMath::clamp(Cx3, Cx1, Cx2);
  const float4 Cr4 = LiteMath::rcp_e(Cx2);

  float result1[4];
  float result2[4];
  float result3[4];
  float result4[4];

  store_u(result1, Cr1);
  store_u(result2, Cr2);
  store_u(result3, Cr3);
  store_u(result4, Cr4);

  bool passed = true;

  const float res1[4] = { +10000.0f,  -1.0f, 1.0f,   -99999999.0f };
  const float res2[4] = { +334324.0f, +1.0f, 100.0f, -0.000005f };
  const float res3[4] = { +10000.0f,  +1.0f, +10.0f, -0.000005f };
  const float res4[4] = { 1.0f/Cx2[0],  1.0f / Cx2[1], 1.0f / Cx2[2], 1.0f / Cx2[3] };

  for (int i = 0; i<4; i++)
  {
    const bool b1 = fabs(result1[i] - res1[i]) > 1e-6f;
    const bool b2 = fabs(result2[i] - res2[i]) > 1e-6f;
    const bool b3 = fabs(result3[i] - res3[i]) > 1e-6f;
    const bool b4 = fabs(result4[i] - res4[i]) > 1e-2f && (i != 3); // arm neon have low precition

    if (b1 || b2 || b3 || b4)
      passed = false;
  }
  

  if(!passed)
  {
    std::cout << "exp1_res:" << result1[0] << " " << result1[1] << " " << result1[2] << " " << result1[3] << std::endl;
    std::cout << "exp1_ref:" << res1   [0] << " " << res1   [1] << " " << res1   [2] << " " << res1   [3] << std::endl;
    std::cout << std::endl;

    std::cout << "exp2_res:" << result2[0] << " " << result2[1] << " " << result2[2] << " " << result2[3] << std::endl;
    std::cout << "exp2_ref:" << res2   [0] << " " << res2   [1] << " " << res2   [2] << " " << res2   [3] << std::endl;
    std::cout << std::endl;

    std::cout << "exp3_res:" << result3[0] << " " << result3[1] << " " << result3[2] << " " << result3[3] << std::endl;
    std::cout << "exp3_ref:" << res3   [0] << " " << res3   [1] << " " << res3   [2] << " " << res3   [3] << std::endl;
    std::cout << std::endl;

    std::cout << "exp4_res:" << result4[0] << " " << result4[1] << " " << result4[2] << " " << result4[3] << std::endl;
    std::cout << "exp4_ref:" << res4   [0] << " " << res4   [1] << " " << res4   [2] << " " << res4   [3] << std::endl;
    std::cout << std::endl;
  }

  return passed;
}

bool vi4_test018_minMax()
{
  const int4 Cx1 = { 10000,  -1, 1, -99999999 };
  const int4 Cx2 = { 334324, +1, 100, 1 };
  const int4 Cx3 = { 10,  10, +10, +10 };

  const int4 Cr1 = LiteMath::min(Cx1, Cx2);
  const int4 Cr2 = LiteMath::max(Cx1, Cx2);
  const int4 Cr3 = LiteMath::clamp(Cx3, Cx1, Cx2);

  int result1[4];
  int result2[4];
  int result3[4];

  store_u(result1, Cr1);
  store_u(result2, Cr2);
  store_u(result3, Cr3);

  bool passed = true;

  const int res1[4] = { 10000,  -1, 1, -99999999 };
  const int res2[4] = { 334324, +1, 100, 1 };
  const int res3[4] = { 10000,  +1, 10,  1};

  for (int i = 0; i<4; i++)
  {
    const bool b1 = result1[i] != res1[i];
    const bool b2 = result2[i] != res2[i];
    const bool b3 = result3[i] != res3[i];

    if (b1 || b2 || b3)
    {
      passed = false;
      break;
    }
  }

  return passed;
}

bool vu4_test019_minMax()
{
  const vuint4 Cx1 = { 10000,  1,  1,   1 };
  const vuint4 Cx2 = { 334324, 1,  100, 99999999 };
  const vuint4 Cx3 = { 10,     10, 10,  10 };

  const vuint4 Cr1 = cvex::min(Cx1, Cx2);
  const vuint4 Cr2 = cvex::max(Cx1, Cx2);
  const vuint4 Cr3 = cvex::clamp(Cx3, Cx1, Cx2);

  unsigned int result1[4];
  unsigned int result2[4];
  unsigned int result3[4];

  store_u(result1, Cr1);
  store_u(result2, Cr2);
  store_u(result3, Cr3);

  bool passed = true;

  const unsigned int res1[4] = { 10000,  1, 1,   1 };
  const unsigned int res2[4] = { 334324, 1, 100, 99999999 };
  const unsigned int res3[4] = { 10000,  1, 10,  10 };

  for (int i = 0; i<4; i++)
  {
    const bool b1 = result1[i] != res1[i];
    const bool b2 = result2[i] != res2[i];
    const bool b3 = result3[i] != res3[i];

    if (b1 || b2 || b3)
    {
      passed = false;
      break;
    }
  }

  return passed;
}

bool vf4_test020_blend()
{
  const float4 Cx1  = { +1.0f, +2.0f, +3.0f, +4.0f };
  const float4 Cx2  = { -1.0f, -2.0f, -3.0f, -4.0f };

  const int4 mask1  = {int(0xFFFFFFFF), 0, int(0xFFFFFFFF), 0};
  const vuint4 mask2 = {0, 0xFFFFFFFF, 0xFFFFFFFF, 0 };

  const float4 Cr1 = cvex::blend(Cx1.v, Cx2.v, mask1.v);
  const float4 Cr2 = cvex::blend(Cx1.v, Cx2.v, mask2);

  float result1[4];
  float result2[4];
  store_u(result1, Cr1);
  store_u(result2, Cr2);

  bool passed = true;

  const float res1[4] = { +1.0f, -2.0f, +3.0f, -4.0f };
  const float res2[4] = { -1.0f, +2.0f, +3.0f, -4.0f };

  for (int i = 0; i<4; i++)
  {
    const bool b1 = fabs(result1[i] - res1[i]) > 1e-6f;
    const bool b2 = fabs(result2[i] - res2[i]) > 1e-6f;

    if (b1 || b2)
    {
      passed = false;
      break;
    }
  }
  return passed;
}

bool vi4_test021_blend()
{
  const int4 Cx1 = { +1, +2, +3, +4 };
  const int4 Cx2 = { -1, -2, -3, -4 };

  const int4 mask1 = { int(0xFFFFFFFF), 0, int(0xFFFFFFFF), 0 };
  const int4 mask2 = { 0, int(0xFFFFFFFF), int(0xFFFFFFFF), 0 };

  const int4 Cr1 = cvex::blend(Cx1.v, Cx2.v, mask1.v);
  const int4 Cr2 = cvex::blend(Cx1.v, Cx2.v, mask2.v);

  int result1[4];
  int result2[4];
  store_u(result1, Cr1);
  store_u(result2, Cr2);

  bool passed = true;

  const int res1[4] = { +1, -2, +3, -4 };
  const int res2[4] = { -1, +2, +3, -4 };

  for (int i = 0; i<4; i++)
  {
    if (result1[i] != res1[i] || result2[i] != res2[i])
    {
      passed = false;
      break;
    }
  }
  return passed;
}


bool vu4_test022_blend()
{
  const vuint4 Cx1 = { +1, +2, +3, +4 };
  const vuint4 Cx2 = { (unsigned int)-1, (unsigned int)-2, (unsigned int)-3, (unsigned int)-4 };

  const vuint4 mask1 = { 0xFFFFFFFF, 0, 0xFFFFFFFF, 0 };
  const vuint4 mask2 = { 0, 0xFFFFFFFF, 0xFFFFFFFF, 0 };

  const vuint4 Cr1 = cvex::blend(Cx1, Cx2, mask1);
  const vuint4 Cr2 = cvex::blend(Cx1, Cx2, mask2);

  unsigned int result1[4];
  unsigned int result2[4];
  store_u(result1, Cr1);
  store_u(result2, Cr2);

  bool passed = true;

  const unsigned int res1[4] = { +1,  (unsigned int)-2, +3,  (unsigned int)-4 };
  const unsigned int res2[4] = { (unsigned int)-1, +2, +3,  (unsigned int)-4 };

  for (int i = 0; i<4; i++)
  {
    if (result1[i] != res1[i] || result2[i] != res2[i])
    {
      passed = false;
      break;
    }
  }
  return passed;
}

bool vf4_test023_floor_ceil()
{
  const float4 Cx1 = { +1.5f, -2.5f, +3.2f, -4.8f };

  const float4 Cr1 = floor(Cx1);
  const float4 Cr2 = ceil (Cx1);

  CVEX_ALIGNED(16) float result1[4];
  CVEX_ALIGNED(16) float result2[4];
  store(result1, Cr1);
  store(result2, Cr2);

  const float res1[4] = { +1.0f, -3.0f, +3.0f, -5.0f };
  const float res2[4] = { +2.0f, -2.0f, +4.0f, -4.0f };

  bool passed = true;
  for (int i = 0; i<4; i++)
  {
    const bool b1 = fabs(result1[i] - res1[i]) > 1e-10f;
    const bool b2 = fabs(result2[i] - res2[i]) > 1e-10f;

    if (b1 || b2)
    {
      passed = false;
      break;
    }
  }
  return passed;
}

bool vfiu_test024_test_bits()
{
  const float4 Cx1 = { 0.0f, 0.5f, 0.0f, 0.0f };
  const float4 Cx2 = { 0.0f, 0.0f, 0.0f, 0.0f };

  const int4 Cx3 = { 0, 0, 4, 0 };
  const int4 Cx4 = { 0, 0, 0, 0 };

  const vuint4 Cx5 = { 0, 0, 0, 8 };
  const vuint4 Cx6 = { 0, 0, 0, 0 };

  const bool b1 = cvex::test_bits_any(Cx1.v);
  const bool b2 = cvex::test_bits_any(Cx2.v);
  const bool b3 = cvex::test_bits_any(Cx3.v);
  const bool b4 = cvex::test_bits_any(Cx4.v);
  const bool b5 = cvex::test_bits_any(Cx5);
  const bool b6 = cvex::test_bits_any(Cx6);

  return (b1 && !b2 && b3 && !b4 && b5 && !b6);
}

bool vfiu_test025_test_bits()
{
  const float4 Cx1 = { 0.0f, 0.5f, 0.0f, 0.0f };
  const float4 Cx2 = { 0.0f, 0.0f, 0.0f, 0.0f };

  const int4 Cx3 = { -1, -1, -1, -1 };
  const int4 Cx4 = { -1, -1, -1, -10 };

  const vuint4 Cx5 = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
  const vuint4 Cx6 = { 0xFFFFFFFF, 0, 0xFFFFFFFF, 0xFFFFFFFF };

  const bool b1 = cvex::test_bits_all(Cx1.v);
  const bool b2 = cvex::test_bits_all(Cx2.v);
  const bool b3 = cvex::test_bits_all(Cx3.v);
  const bool b4 = cvex::test_bits_all(Cx4.v);
  const bool b5 = cvex::test_bits_all(Cx5);
  const bool b6 = cvex::test_bits_all(Cx6);

  const bool passed = (!b1 && !b2 && b3 && !b4 && b5 && !b6);
  if(!passed)
  {
    std::cout << "b1:" << b1 << std::endl;
    std::cout << "b2:" << b2 << std::endl;
    std::cout << "b3:" << b3 << std::endl;
    std::cout << "b4:" << b4 << std::endl;
    std::cout << "b5:" << b5 << std::endl;
    std::cout << "b6:" << b6 << std::endl;
  }

  return passed;
}

bool vf4_test026_dot_cross()
{
  const float4 Cx1 = { 1.0f, 2.0f, 3.0f, 4.0f };
  const float4 Cx2 = { 5.0f, 6.0f, 7.0f, 8.0f };

  const float   dot1 = dot3f(Cx1, Cx2);
  const float4 dot2  = dot3v(Cx1, Cx2);
  const float   dot3 = dot4f(Cx1, Cx2);
  const float4 dot4  = dot4v(Cx1, Cx2);
  const float4 crs3  = cross3(Cx1, Cx2);

  CVEX_ALIGNED(16) float result1[4];
  CVEX_ALIGNED(16) float result2[4];
  CVEX_ALIGNED(16) float result3[4];
  store(result1, dot2);
  store(result2, dot4);
  store(result3, crs3);

  const float ref_dp3 = 1.0f*5.0f + 2.0f*6.0f + 3.0f*7.0f;
  const float ref_dp4 = 1.0f*5.0f + 2.0f*6.0f + 3.0f*7.0f + 4.0f*8.0f;

  const float crs_ref[3] = { Cx1[1]*Cx2[2] - Cx1[2]*Cx2[1], 
                             Cx1[2]*Cx2[0] - Cx1[0]*Cx2[2], 
                             Cx1[0]*Cx2[1] - Cx1[1]*Cx2[0] };

  const bool b1 = fabs(dot1 - ref_dp3) < 1e-6f;
  const bool b2 = fabs(result1[0] - ref_dp3) < 1e-6f && 
                  fabs(result1[1] - ref_dp3) < 1e-6f && 
                  fabs(result1[2] - ref_dp3) < 1e-6f &&
                  fabs(result1[3] - ref_dp3) < 1e-6f;

  const bool b3 = fabs(dot3 - ref_dp4) < 1e-6f;
  const bool b4 = fabs(result2[0] - ref_dp4) < 1e-6f &&
                  fabs(result2[1] - ref_dp4) < 1e-6f &&
                  fabs(result2[2] - ref_dp4) < 1e-6f &&
                  fabs(result2[3] - ref_dp4) < 1e-6f;

  const bool b5 = fabs(result3[0] - crs_ref[0]) < 1e-6f && 
                  fabs(result3[1] - crs_ref[1]) < 1e-6f &&
                  fabs(result3[2] - crs_ref[2]) < 1e-6f;

  return b1 && b2 && b3 && b4 && b5;
}

bool vf4_test027_shuffle()
{
  const float4 Cx1 = { 1.0f, 2.0f, 3.0f, 4.0f };

  const float4 Cr1 = shuffle_zyxw(Cx1.v);
  const float4 Cr2 = shuffle_yzxw(Cx1.v);
  const float4 Cr3 = shuffle_zxyw(Cx1.v);
  const float4 Cr4 = shuffle_xyxy(Cx1.v);
  const float4 Cr5 = shuffle_zwzw(Cx1.v);

  CVEX_ALIGNED(16) float result1[4];
  CVEX_ALIGNED(16) float result2[4];
  CVEX_ALIGNED(16) float result3[4];
  CVEX_ALIGNED(16) float result4[4];
  CVEX_ALIGNED(16) float result5[4];
  store(result1, Cr1);
  store(result2, Cr2);
  store(result3, Cr3);
  store(result4, Cr4);
  store(result5, Cr5);

  const bool b1 = (result1[0] == 3.0f) && (result1[1] == 2.0f) && (result1[2] == 1.0f) && (result1[3] == 4.0f);
  const bool b2 = (result2[0] == 2.0f) && (result2[1] == 3.0f) && (result2[2] == 1.0f) && (result2[3] == 4.0f);
  const bool b3 = (result3[0] == 3.0f) && (result3[1] == 1.0f) && (result3[2] == 2.0f) && (result3[3] == 4.0f);
  const bool b4 = (result4[0] == 1.0f) && (result4[1] == 2.0f) && (result4[2] == 1.0f) && (result4[3] == 2.0f);
  const bool b5 = (result5[0] == 3.0f) && (result5[1] == 4.0f) && (result5[2] == 3.0f) && (result5[3] == 4.0f);
 
  const bool passed = (b1 && b2 && b3 && b4 && b5);

  if(!passed)
  {
    std::cout << result1[0] << " " << result1[1] << " " << result1[2] << " " << result1[3] << std::endl;
    std::cout << result2[0] << " " << result2[1] << " " << result2[2] << " " << result2[3] << std::endl;
    std::cout << result3[0] << " " << result3[1] << " " << result3[2] << " " << result3[3] << std::endl;
    std::cout << result4[0] << " " << result4[1] << " " << result4[2] << " " << result4[3] << std::endl;
    std::cout << result5[0] << " " << result5[1] << " " << result5[2] << " " << result5[3] << std::endl;
  }

  return passed;
}

bool vf4_test028_length()
{
  const float4 Cx1 = { 1.0f, 2.0f, 3.0f, 4.0f };

  const float   dot1 = length3f(Cx1);
  const float4 dot2  = length3v(Cx1);
  const float   dot3 = length4f(Cx1);
  const float4 dot4  = length4v(Cx1);

  CVEX_ALIGNED(16) float result1[4];
  CVEX_ALIGNED(16) float result2[4];
  store(result1, dot2);
  store(result2, dot4);

  const float ref_dp3 = sqrtf(1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f);
  const float ref_dp4 = sqrtf(1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f + 4.0f*4.0f);

  const bool b1 = fabs(dot1 - ref_dp3) < 1e-6f;
  const bool b2 = fabs(result1[0] - ref_dp3) < 1e-6f && 
                  fabs(result1[1] - ref_dp3) < 1e-6f && 
                  fabs(result1[2] - ref_dp3) < 1e-6f &&
                  fabs(result1[3] - ref_dp3) < 1e-6f;

  const bool b3 = fabs(dot3 - ref_dp4) < 1e-6f;
  const bool b4 = fabs(result2[0] - ref_dp4) < 1e-6f &&
                  fabs(result2[1] - ref_dp4) < 1e-6f &&
                  fabs(result2[2] - ref_dp4) < 1e-6f &&
                  fabs(result2[3] - ref_dp4) < 1e-6f;
                  
  return (b1 && b2 && b3 && b4);
}

bool vf4_test029_ext_splt()
{
  const float4 Cx1 = { 1.0f, 2.0f, 3.0f, 4.0f };

  const float4 Cr1 = splat_0(Cx1);
  const float4 Cr2 = splat_1(Cx1);
  const float4 Cr3 = splat_2(Cx1);
  const float4 Cr4 = splat_3(Cx1);

  CVEX_ALIGNED(16) float result1[4];
  CVEX_ALIGNED(16) float result2[4];
  CVEX_ALIGNED(16) float result3[4];
  CVEX_ALIGNED(16) float result4[4];

  store(result1, Cr1);
  store(result2, Cr2);
  store(result3, Cr3);
  store(result4, Cr4);

  const float x = extract_0(Cx1);
  const float y = extract_1(Cx1);
  const float z = extract_2(Cx1);
  const float w = extract_3(Cx1);

  bool passed = true;
  for (int i = 0; i<4; i++)
  {
    const bool b1 = (result1[i] == 1.0f);
    const bool b2 = (result2[i] == 2.0f);
    const bool b3 = (result3[i] == 3.0f);
    const bool b4 = (result4[i] == 4.0f);

    if (!b1 || !b2 || !b3 || !b4)
    {
      passed = false;
      break;
    }
  }
  return passed && (x == 1.0f) && (y == 2.0f) && (z == 3.0f) && (w == 4.0f);
}


bool vi4_test030_ext_splt()
{
  const int4 Cx1 = { 1, 2, 3, 4 };

  const int4 Cr1 = splat_0(Cx1.v);
  const int4 Cr2 = splat_1(Cx1.v);
  const int4 Cr3 = splat_2(Cx1.v);
  const int4 Cr4 = splat_3(Cx1.v);

  CVEX_ALIGNED(16) int result1[4];
  CVEX_ALIGNED(16) int result2[4];
  CVEX_ALIGNED(16) int result3[4];
  CVEX_ALIGNED(16) int result4[4];

  cvex::store(result1, Cr1.v);
  cvex::store(result2, Cr2.v);
  cvex::store(result3, Cr3.v);
  cvex::store(result4, Cr4.v);


  const int x = extract_0(Cx1.v);
  const int y = extract_1(Cx1.v);
  const int z = extract_2(Cx1.v);
  const int w = extract_3(Cx1.v);

  bool passed = true;
  for (int i = 0; i<4; i++)
  {
    const bool b1 = (result1[i] == 1);
    const bool b2 = (result2[i] == 2);
    const bool b3 = (result3[i] == 3);
    const bool b4 = (result4[i] == 4);

    if (!b1 || !b2 || !b3 || !b4)
    {
      passed = false;
      break;
    }
  }
  return passed && (x == 1) && (y == 2) && (z == 3) && (w == 4);
}

bool vu4_test031_ext_splt()
{
  const cvex::vuint4 Cx1 = { 1, 2, 3, 4 };

  const cvex::vuint4 Cr1 = splat_0(Cx1);
  const cvex::vuint4 Cr2 = splat_1(Cx1);
  const cvex::vuint4 Cr3 = splat_2(Cx1);
  const cvex::vuint4 Cr4 = splat_3(Cx1);

  CVEX_ALIGNED(16) unsigned int result1[4];
  CVEX_ALIGNED(16) unsigned int result2[4];
  CVEX_ALIGNED(16) unsigned int result3[4];
  CVEX_ALIGNED(16) unsigned int result4[4];

  cvex::store(result1, Cr1);
  cvex::store(result2, Cr2);
  cvex::store(result3, Cr3);
  cvex::store(result4, Cr4);


  const unsigned int x = extract_0(Cx1);
  const unsigned int y = extract_1(Cx1);
  const unsigned int z = extract_2(Cx1);
  const unsigned int w = extract_3(Cx1);

  bool passed = true;
  for (int i = 0; i<4; i++)
  {
    const bool b1 = (result1[i] == 1);
    const bool b2 = (result2[i] == 2);
    const bool b3 = (result3[i] == 3);
    const bool b4 = (result4[i] == 4);

    if (!b1 || !b2 || !b3 || !b4)
    {
      passed = false;
      break;
    }
  }
  return passed && (x == 1) && (y == 2) && (z == 3) && (w == 4);
}

bool vf4_test032_compare()
{
  const float4 Cx1 = { 1.0f, 2.0f, 3.0f,  4.0f };
  const float4 Cx2 = { 0.0f, 3.0f, -3.0f, 4.0f };

  const int4 Cr1 = (Cx1 < Cx2);
  const int4 Cr2 = (Cx1 > Cx2);
  const int4 Cr3 = (Cx1 <= Cx2);
  const int4 Cr4 = (Cx1 >= Cx2);
  const int4 Cr5 = (Cx1 == Cx2);
  const int4 Cr6 = (Cx1 != Cx2);

  CVEX_ALIGNED(16) int result1[4];
  CVEX_ALIGNED(16) int result2[4];
  CVEX_ALIGNED(16) int result3[4];
  CVEX_ALIGNED(16) int result4[4];
  CVEX_ALIGNED(16) int result5[4];
  CVEX_ALIGNED(16) int result6[4];

  cvex::store(result1, Cr1.v);
  cvex::store(result2, Cr2.v);
  cvex::store(result3, Cr3.v);
  cvex::store(result4, Cr4.v);
  cvex::store(result5, Cr5.v);
  cvex::store(result6, Cr6.v);

  const bool b1 = (result1[0] == 0) && (result1[1] == -1) && (result1[2] == 0) && (result1[3] == 0);
  const bool b2 = (result2[0] == -1) && (result2[1] == 0) && (result2[2] == -1) && (result2[3] == 0);
  const bool b3 = (result3[0] == 0) && (result3[1] == -1) && (result3[2] == 0) && (result3[3] == -1);
  const bool b4 = (result4[0] == -1) && (result4[1] == 0) && (result4[2] == -1) && (result4[3] == -1);
  const bool b5 = (result5[0] == 0) && (result5[1] == 0) && (result5[2] == 0) && (result5[3] == -1);
  const bool b6 = (result6[0] == -1) && (result6[1] == -1) && (result6[2] == -1) && (result6[3] == 0);

  return b1 && b2 && b3 && b4 && b5 && b6;
}

bool vf4_test033_compare()
{
  const float4 Cx1 = { 1.0f, 2.0f, 7.0f, 2.0f };
  const float4 Cx2 = { 5.0f, 6.0f, 7.0f, 4.0f };
  const float4 Cx3 = { 5.0f, 6.0f, 8.0f, -4.0f };

  const auto cmp1 = (Cx1 > Cx2);
  const auto cmp2 = (Cx1 <= Cx3);

  const bool b1 = any_of(cmp1);
  const bool b2 = all_of(cmp1);

  const bool b3 = any_of(cmp2);
  const bool b4 = all_of(cmp2);

  return (!b1 && !b2 && b3 && !b4);
}

bool vf4_test034_colpack()
{
  const float4 Cx1 = { 0.25f, 0.5f, 0.0, 1.0f };

  const unsigned int packed_rgba = color_pack_rgba(Cx1);
  const unsigned int packed_bgra = color_pack_bgra(Cx1);

  const bool passed = ((packed_bgra == 0xFF408000) || (packed_bgra == 0xFF3f7f00)) && 
                      ((packed_rgba == 0xFF008040) || (packed_rgba == 0xFF007f3f));

  if(!passed)
  {
    std::cout << std::hex << "bgra_res: " << packed_bgra << std::endl;
    std::cout << std::hex << "bgra_ref: " << 0xFF408000  << std::endl;

    std::cout << std::hex << "rgba_res: " << packed_rgba << std::endl;
    std::cout << std::hex << "rgba_ref: " << 0xFF008040  << std::endl;
  }

  return passed;
}

bool vf4_test037_fabs()
{
  LiteMath::float4 Cx1(-1.0f,2.0f,-0.03f,0.005f);
  LiteMath::float4 Cr = fabs(Cx1);

  return (Cr.x == 1.0f) && (Cr.y == 2.0f) && (Cr.z == 0.03f) && (Cr.w == 0.005f);
}

bool vf4_test038_matrix_brackets()
{
  LiteMath::float4x4 m;

  m(1,2) = 3.0f;
  m(3,1) = 4.0f; 

  return (m[1][2] == 3.0f) && (m[3][1] == 4.0f) && 
         (m[0][0] == 1.0f) && (m[1][1] == 1.0f) && (m[0][3] == 0.0f);
}

bool vf4_test039_horiz_minmax()
{
  cvex::vfloat4 c1{1,2,3,4};
  cvex::vfloat4 c2{10,-2,3,-4};
  
  const float max1 = cvex::hmax3(c1);
  const float min1 = cvex::hmin3(c1);
  
  const float max2 = cvex::hmax3(c2);
  const float min2 = cvex::hmin3(c2);
  
  return (max1 == 3.0f) && (min1 == 1.0f) && (max2 == 10.0f) && (min2 == -2.0f);
}

bool vf4_test040_horiz_minmax4()
{
  cvex::vfloat4 c1{1,2,3,4};
  cvex::vfloat4 c2{3,-2,10,-4};
  
  const float max1 = cvex::hmax(c1);
  const float min1 = cvex::hmin(c1);
  
  const float max2 = cvex::hmax(c2);
  const float min2 = cvex::hmin(c2);
  
  return (max1 == 4.0f) && (min1 == 1.0f) && (max2 == 10.0f) && (min2 == -4.0f);
}