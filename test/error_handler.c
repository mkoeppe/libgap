#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#include "src/config.h"
#include "src/system.h"
#include "src/objects.h"
#include "src/gasman.h"
#include "src/code.h"
#include "src/calls.h"
#include "src/vars.h"
#include "src/gap.h"
#include "src/read.h"
#include "src/libgap.h"
#include "src/libgap_internal.h"


// Path to the GAP root (for the library)
#ifndef SYS_DEFAULT_PATHS
#define SYS_DEFAULT_PATHS "/home/vbraun/Sage/sage/local/gap/latest"
#endif


void handler(char* msg)
{
  printf("Caught an error: %s", msg);
}

int main()
{
  char* argv[8];
  argv[0] = "gap";
  argv[1] = "-l";
  argv[2] = SYS_DEFAULT_PATHS;
  argv[3] = "-m";
  argv[4] = "24M";
  argv[5] = "-T";
  argv[6] = "-A";
  argv[7] = NULL;
  int argc=7;
  libgap_set_error_handler(handler);
  libgap_initialize(argc, argv);
  libgap_mark_stack_bottom();

  libgap_start_interaction("1/0");

  libgap_enter();
  ReadEvalCommand(BottomLVars, 0);
  ViewObjHandler(ReadEvalResult);
  libgap_exit()

  libgap_finish_interaction();
  return 0;
}
