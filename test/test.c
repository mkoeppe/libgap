#include <signal.h>
#include <setjmp.h>
#include <assert.h>

#include "src/config.h"
#include "src/system.h"
#include "src/objects.h"
#include "src/gap.h"
#include "src/scanner.h"
#include "src/sysfiles.h"
#include "src/plist.h"
#include "src/gasman.h"
#include "src/string.h"
#include "src/read.h"
#include "src/code.h"
#include "src/vars.h"
#include "src/libgap.h"
#include "src/libgap_internal.h"

// Path to the GAP root (for the library)
#ifndef SYS_DEFAULT_PATHS
#define SYS_DEFAULT_PATHS "/home/vbraun/Sage/git/local/gap/latest"
#endif


// using namespace std;

/////////////////////////////////////////////////////////////////

void error_handler(char* msg)
{
  printf("Error handler: %s", msg);
}


/////////////////////////////////////////////////////////////////

void init()
{
  printf("Using gap library at %s\n", SYS_DEFAULT_PATHS);
  char* argv[12];
  argv[0] = "sage";
  argv[1] = "-l";
  argv[2] = SYS_DEFAULT_PATHS;
  char* memory_pool = "1000M";
  argv[3] = "-o";
  argv[4] = memory_pool;
  argv[5] = "-s";
  argv[6] = memory_pool;
  argv[7] = "-m";
  argv[8] = "64M";
  argv[9] = "-q";
  argv[10] = "-T";
  argv[11] = NULL;
  int argc=11;
  //  libgap_set_error_handler(&error_handler);
  //  libgap_initialize(argc, argv);

  libgap_initialize(argc, argv);
  libgap_start_interaction("");
  char * output_msg = libgap_get_output();
  if (strlen(output_msg) > 0)
    printf("libGAP initialization failed: %s\n", output_msg);
  char * error_msg = libgap_get_error();
  if (strlen(error_msg) > 0)
    printf("libGAP initialization failed: %s\n", error_msg);
  libgap_finish_interaction();
  libgap_set_error_handler(&error_handler);

  libgap_enter();
  AssGVar(Last, ReadEvalResult);
  libgap_exit();
}   




/////////////////////////////////////////////////////////////////

sigjmp_buf env;

#define signal_occurred   sigsetjmp(env,1)


void signal_handler(int sig) 
{
  printf("Caught signal %i\n", sig);
  siglongjmp(env, sig);
}


void install_signal_handler()
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = signal_handler;
  sa.sa_flags |= SA_NODEFER;
  assert(0 == sigaction(SIGINT, &sa, NULL));
  assert(0 == sigaction(SIGILL, &sa, NULL));
  assert(0 == sigaction(SIGABRT, &sa, NULL));
  assert(0 == sigaction(SIGFPE, &sa, NULL));
  assert(0 == sigaction(SIGBUS, &sa, NULL));
  assert(0 == sigaction(SIGSEGV, &sa, NULL));
}


/////////////////////////////////////////////////////////////////


void eval(char* input)
{
  printf("--------------------\n");
  printf("Input: %s", input);

  libgap_enter();
  libgap_start_interaction(input);
  
  ExecStatus status;
  status = ReadEvalCommand(BottomLVars);
  libgap_exit();
  
  if (signal_occurred) {
    printf("signal caught\n");
    libgap_enter();
    libgap_finish_interaction();
    libgap_exit();
    return;
  }
  

  if (status != STATUS_END) {
    printf("There was an error, no output.\n");
    libgap_finish_interaction();
    return;
  }

  assert(Symbol == S_SEMICOLON);
  libgap_enter();
  GetSymbol();
  libgap_exit();
  if (Symbol!=S_EOF) {
    printf("Multiple statements; aborting!\n");
    libgap_finish_interaction();
    return;
  }

  libgap_enter();
  ViewObjHandler(ReadEvalResult);
  libgap_exit();

  char* out = libgap_get_output();
  printf("Output follows...\n%s", out);

  libgap_enter();
  libgap_finish_interaction();
  libgap_exit();
}




int main(void)
{
  init();
  install_signal_handler();

  eval("0;\n");

  eval("CyclicGroup(2);\n");

  eval("1 + CyclicGroup(2);\n");

  eval("1/0;\n");

  eval("a:=NormalSubgroups;\n");
  eval("b:=SymmetricGroup(4);\n");
  eval("a(b);\n");

  eval("SmallGroup(12,3);\n");
  eval("0;\n");

  eval("0;\n");
  eval("1+3;\n");
  eval("[1, 3, 5];\n");

  eval("if 4>3 then\nPrint(\"hi\n\");\n fi;\n");
  eval("0;\n");

  eval("rec( a:=0, b:=1, c:=3 );\n");
  eval("0;\n");

  eval("rec( a=0, b:1, c;3 );\n");
  eval("0;\n");

  eval("rec( a=0, b:1, c;3 );\n");
  eval("\"back to normal\";\n");

  eval("1/0;\n");
  return 0;
}
