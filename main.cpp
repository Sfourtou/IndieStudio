#include <iostream>
#include <stdlib.h>
#include "CoreApplication.h"

int main() {
  srand(42);
  CoreApplication co = CoreApplication();
  co.setConfig();
  return 0;
}
