#pragma once
#include <vector>

#if defined(_WIN32)
  #if defined(GRADES_DLL_EXPORTS)
    #define GRADES_API __declspec(dllexport)
  #else
    #define GRADES_API __declspec(dllimport)
  #endif
#else
  #define GRADES_API
#endif

// C++ eksportas/importas; naudojame std::vector API
GRADES_API double grades_vidurkis(const std::vector<int>& v);
GRADES_API double grades_mediana(const std::vector<int>& v);

