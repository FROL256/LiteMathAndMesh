//// tests entry points
//
void run_all_tests();

//// vector-vector (+,-,*,/)
//
bool vf4_test001_basic();
bool vi4_test002_basic();
bool vu4_test003_basic();

//// vector-scalar (+,-,*,/)
//
bool vf4_test004_basic();
bool vi4_test005_basic();
bool vu4_test006_basic();

//// vector-vector (&,|,~)
//
bool vi4_test007_and_or();
bool vu4_test008_and_or();

//// vector-scalar (>>, <<)
//
bool vi4_test009_shift();
bool vu4_test010_shift();

//// splat
//
bool vf4_test011_splat();
bool vi4_test012_splat();
bool vu4_test013_splat();

//// convert and cast
//
bool vfi4_test014_convert();
bool viu4_test015_convert();
bool vfi4_test016_cast();

//// min, max, clamp, rcp_e
//
bool vf4_test017_mMcRcp();
bool vi4_test018_minMax();
bool vu4_test019_minMax();

//// blend, test_bits
//
bool vf4_test020_blend();
bool vi4_test021_blend();
bool vu4_test022_blend();

//// floor, ceil, test_bits(any,all)
//
bool vf4_test023_floor_ceil();
bool vfiu_test024_test_bits();
bool vfiu_test025_test_bits();

//// dot, cross, shuffle, length
//
bool vf4_test026_dot_cross();
bool vf4_test027_shuffle();
bool vf4_test028_length();

//// extract, splat
//
bool vf4_test029_ext_splt();
bool vi4_test030_ext_splt();
bool vu4_test031_ext_splt();

//// >, <, >=, <=, ==, !=, cmpgt3, cmplt3, ... 
//
bool vf4_test032_compare();
bool vf4_test033_compare();
bool vf4_test034_colpack();

//// matrix*matrix, matrix*vector
//
bool vf4_test035_matrixmul();
bool vf4_test036_matrixinv();
bool vf4_test037_fabs();
bool vf4_test038_matrix_brackets();

//// horizontal operatins tests
//
bool vf4_test039_horiz_minmax();
bool vf4_test040_horiz_minmax4();