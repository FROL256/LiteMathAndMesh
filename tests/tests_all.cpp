#include "tests.h"
#include <iostream>
#include <iomanip>      // std::setfill, std::setw

using TestFuncType = bool (*)();

struct TestRun
{
  TestFuncType pTest;
  const char*  pTestName;
};

void run_all_tests()
{
  TestRun tests[] = { 
      { &vf4_test001_basic, "vf4_test001_basic" },
      { &vi4_test002_basic, "vi4_test002_basic" },
      { &vu4_test003_basic, "vu4_test003_basic" },

      { &vf4_test004_basic, "vf4_test004_basic" },
      { &vi4_test005_basic, "vi4_test005_basic" },
      { &vu4_test006_basic, "vu4_test006_basic" },

      { &vi4_test007_and_or, "vi4_test007_and_or" },
      { &vu4_test008_and_or, "vu4_test008_and_or" },
      { &vi4_test009_shift,  "vi4_test009_shift"  },
      { &vu4_test010_shift,  "vu4_test010_shift"  },

      { &vf4_test011_splat, "vf4_test011_splat" },
      { &vi4_test012_splat, "vi4_test012_splat" },
      { &vu4_test013_splat, "vu4_test013_splat" },

      { &vfi4_test014_convert, "vfi4_test014_convert" },
      { &viu4_test015_convert, "viu4_test015_convert" },
      { &vfi4_test016_cast,    "vfi4_test016_cast"    },

      { &vf4_test017_mMcRcp,   "vf4_test017_mMcRcp"   },
      { &vi4_test018_minMax,   "vi4_test018_minMax"   },
      { &vu4_test019_minMax,   "vu4_test019_minMax"   },

      { &vf4_test020_blend,    "vf4_test020_blend" },
      { &vi4_test021_blend,    "vi4_test021_blend" },
      { &vu4_test022_blend,    "vu4_test022_blend" },

      { &vf4_test023_floor_ceil, "vf4_test023_floor_ceil"}, 
      { &vfiu_test024_test_bits, "vfiu_test024_test_bits"},
      { &vfiu_test025_test_bits, "vfiu_test025_test_bits"},

      { &vf4_test026_dot_cross, "vf4_test026_dot_cross"},
      { &vf4_test027_shuffle,   "vf4_test027_shuffle"  },
      { &vf4_test028_length,    "vf4_test028_length"   },

      { &vf4_test029_ext_splt, "vf4_test029_ext_splt"},
      { &vi4_test030_ext_splt, "vi4_test030_ext_splt"},
      { &vu4_test031_ext_splt, "vu4_test031_ext_splt"},

      { &vf4_test032_compare, "vf4_test032_compare"},
      { &vf4_test033_compare, "vf4_test033_compare"},
      { &vf4_test034_colpack, "vf4_test034_colpack"},

      { &vf4_test035_matrixmul, "vf4_test035_matrixmul"},
      { &vf4_test036_matrixinv, "vf4_test036_matrixinv"},
      { &vf4_test037_fabs,      "vf4_test037_fabs"},
      { &vf4_test038_matrix_brackets, "vf4_test038_matbrackets"},

      { &vf4_test039_horiz_minmax,  "vf4_test039_hz_minmax"},
      { &vf4_test040_horiz_minmax4, "vf4_test040_hz_minmax4"}
  };

  const auto arraySize = sizeof(tests)/sizeof(TestRun);

  for(int i=0;i<int(arraySize);i++)
  {
    const bool res = tests[i].pTest();
    std::cout << "test\t" << std::setfill('0') << std::setw(3) << i+1 << "\t" << tests[i].pTestName << "\t";
    if(res)
      std::cout << "PASSED!";
    else 
      std::cout << "FAILED!\tFAILED!";
    std::cout << std::endl;
    std::cout.flush();
  }

}
