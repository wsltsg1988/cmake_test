// A simple program that computes the square root of a number
#include <cmath>
#include <iostream>
#include <string>
#include "TutorialConfig.h"  //自動生成

#ifdef USE_MYMATH
  #include "MathFunctions.h"
#endif

int main(int argc, char* argv[])
{
  if (argc < 2) {
      // report version
      std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
                << Tutorial_VERSION_MINOR << std::endl;
      std::cout << "Usage: " << argv[0] << "number" << std::endl;

      #ifdef USE_MYMATH
        std::cout << "USE_MYMATH: on " << std::endl;
      #else 
        std::cout << "USE_MYMATH: off " << std::endl;
      #endif

      return 1;
    }

    // convert input to double
    const double inputValue = std::stod(argv[1]);

    // calculate square root
    #ifdef USE_MYMATH
      const double outputValue = mysqrt(inputValue);
     #else 
      const double outputValue = sqrt(inputValue);
    #endif

    std::cout << "The square root of " << inputValue << " is " << outputValue
                << std::endl;
    return 0;
}
