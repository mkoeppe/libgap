#include <unistd.h>
#include <stdio.h>
#include "src/libgap.h"

#include "src/config.h"
#include "src/system.h"
#include "src/objects.h"
#include "src/gasman.h"
#include "src/code.h"
#include "src/vars.h"
#include "src/read.h"

extern char **environ;

void print_stack_start()
{
  register void* ebp asm("ebp");     
  int i;
  printf("ebp = %p\n", ebp);
  printf("&i = %p\n", &i);
  printf("frame addres = %p\n", __builtin_frame_address(0));
}

void stacker() 
{
  print_stack_start();
}


void error_handler(char* msg)
{
  printf("Error handler: %s", msg);
}

void eval(char* cmd) {
  printf("Input:\n%s", cmd);
  libgap_start_interaction(cmd);
  libgap_enter();
  ReadEvalCommand(BottomLVars);
  ViewObjHandler(ReadEvalResult);
  libgap_exit()
  char* out = libgap_get_output();
  printf("Output:\n%s", out);
  libgap_finish_interaction();
}

int main()
{
  print_stack_start();
  stacker();
  char* argv[8];
  argv[0] = "gap";
  argv[1] = "-l";
  argv[2] = "/home/vbraun/Sage/sage/local/gap/latest";
  argv[3] = "-m";
  argv[4] = "32M";
  argv[5] = "-q";
  argv[6] = "-T";
  argv[7] = NULL;
  int argc=7;
  // gap_main_loop(argc, argv, environ);
  libgap_set_error_handler(&error_handler);
  libgap_initialize(argc, argv);
  printf("Initialized\n");

  CollectBags(0,1);  // full GC
  eval("1+2+3;\n");
  eval("g:=FreeGroup(2);\n");
  eval("a:=g.1;\n");
  eval("b:=g.2;\n");
  eval("lis:=[a^2, a^2, b*a];\n");
  eval("h:=g/lis;\n");
  eval("c:=h.1;\n");
  eval("Set([1..300000], i->Order(c));\n"); 

  return 0;
}

