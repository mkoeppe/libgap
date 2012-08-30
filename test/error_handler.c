#include <assert.h>
#include <stddef.h>
#include "src/libgap.h"


void handler(char* msg)
{
  printf("Caught an error.");
}

int main()
{
  char* argv[7];
  argv[0] = "gap";
  argv[1] = "-l";
  argv[2] = "/home/vbraun/Sage/sage/local/gap/latest";
  argv[3] = "-m";
  argv[4] = "24M";
  argv[5] = "-T";
  argv[6] = NULL;
  int argc=6;
  libgap_initialize(argc, argv);

  libgap_set_error_handler(handler);

  

  return 0;
}
