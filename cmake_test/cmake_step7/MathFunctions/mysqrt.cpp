#include <iostream>
// a hack square root calculation using simple operations
#include "Table.h"  //自动生成

double mysqrt(double x)
{
  if (x <= 0) {
    return 0;
  }

  double result = x;
   if (x >= 1 && x < 10) {
    std::cout << "Use the table to help find an initial value " << std::endl;
    result = sqrtTable[static_cast<int>(x)];
    std::cout << "Computing sqrt of " << x << " to be " << result << " using  mysqrt" << std::endl; 
    return result;
  }

  // do ten iterations
  for (int i = 0; i < 10; ++i) {
    if (result <= 0) {
      result = 0.1;
    }
    double delta = x - (result * result);
    result = result + 0.5 * delta / result;
    std::cout << "Computing sqrt of " << x << " to be " << result << " using  mysqrt" << std::endl;
  }
  return result;
}
