#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include "src/libgap.h"

#include "src/config.h"
#include "src/system.h"
#include "src/objects.h"
#include "src/gasman.h"
#include "src/code.h"
#include "src/vars.h"
#include "src/read.h"


void handler(char* msg)
{
  printf("Caught an error: %s", msg);
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
  libgap_set_error_handler(handler);
  libgap_initialize(argc, argv);
  libgap_mark_stack_bottom();

  libgap_start_interaction("1/0");

  libgap_enter();
  ReadEvalCommand(BottomLVars);
  ViewObjHandler(ReadEvalResult);
  libgap_exit()

  libgap_finish_interaction();
  return 0;
}
