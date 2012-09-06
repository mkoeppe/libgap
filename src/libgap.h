#ifndef LIBGAP__H
#define LIBGAP__H

/*****************************************************************************
*   SAGE: Open Source Mathematical Software
*
*       Copyright (C) 2009, William Stein <wstein@gmail.com>
*       Copyright (C) 2012, Volker Braun <vbraun.name@gmail.com>
*
*  Distributed under the terms of the GNU General Public License (GPL) v3+.
*  The full text of the GPL is available at: http://www.gnu.org/licenses/
*****************************************************************************/



/*************************************************************************/
/*** Initialize / Finalize ***********************************************/
/*************************************************************************/

/* To setup libGAP, you must call libgap_set_command_line_options() to
 * set argv and env
 *
 * Two mandatory component of argv is "-K", "memory_pool_size" to set the
 * libgap memory pool size. For example,
 *
 * argc = 5
 * argv = "libgap", "-l", "/path/to/gap-library", "-K", "64M", NULL
 * env = NULL
 */
void libgap_initialize(int argc, char** argv);


/* Currently, this does nothing. One day, it should correctly
 * finalize libgap so that it can be reinitialized with a different
 * memory pool...
 */
void libgap_finalize();


/*************************************************************************/
/*** Local (per-function) Initialization  ********************************/
/*************************************************************************/

/* You must call libgap_local_initialize() in every function that
 * calls into the libGAP C functions. The reason is that the GAP
 * memory manager will automatically keep objects alive that are
 * referenced in local (stack-allocated) variables. While convenient,
 * this requires to look through the stack to find anything that looks
 * like an address to a memory bag. 
 */

extern void* StackBottomBags;

 /* This is implemented as a macro to access EBP of the calling function */
#define libgap_local_initialize()   \
  register void* ebp asm("ebp");     \ 
  StackBottomBags = ebp;


/*************************************************************************/
/*** Input/Output interaction ********************************************/
/*************************************************************************/

/* Set a function that will be called if an error occurs If set, this
 * will be called instead of a longjmp() back to the GAP main loop.
 */

typedef void(*libgap_error_func_ptr)(char* msg);
void libgap_set_error_handler(libgap_error_func_ptr callback);


/* GAP uses this function to call our error handler */
void libgap_call_error_handler();


/* libGAP is supposed to be used as follows from your code:
 *
 * 1. call libgap_start_interaction(char* inputline). The inputline
 *    buffer is not copied, it is your responsibility to keep it alive
 *    until you call libgap_finish_interaction()
 *
 * 2. Make GAP perform some computation, for example by calling
 *    ReadEvalCommand()
 *
 * 3. The output is accumulated in the buffer returned by
 *    libgap_get_output(). The buffer is owned by libgap, you must not
 *    free it.
 *
 * 4. call libgap_finish_interaction() when you are finished with the
 *    GAP commands. The GAP parser is reset and the output buffer is
 *    freed.
 */
void libgap_start_interaction(char* inputline);
void libgap_set_input(char* line);
char* libgap_get_output();
void libgap_finish_interaction();


/* For GAP to access the buffers */
char* libgap_get_input(char* line, int length);
char* libgap_get_error();
void libgap_clear_error();
void libgap_append_stdout(char ch);
void libgap_append_stderr(char ch);



#endif
