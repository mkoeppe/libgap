#ifndef LIBGAP_INTERNAL__H
#define LIBGAP_INTERNAL__H

/*****************************************************************************
*   SAGE: Open Source Mathematical Software
*
*       Copyright (C) 2009, William Stein <wstein@gmail.com>
*       Copyright (C) 2012, Volker Braun <vbraun.name@gmail.com>
*
*  Distributed under the terms of the GNU General Public License (GPL) v3+.
*  The full text of the GPL is available at: http://www.gnu.org/licenses/
*****************************************************************************/

/* Allow environment access to OSX dylib, see http://trac.sagemath.org/14038 */
#ifdef __APPLE__
#include <crt_externs.h>
#define environ (*_NSGetEnviron())
#else
extern char** environ;
#endif /* __APPLE__ */


/* libGAP functions that are used in the modified GAP kernel, not part
 * of the libGAP api */

/* GAP uses this function to call the gasman callback */
void libgap_call_gasman_callback();

/* For GAP to access the buffers */
char* libgap_get_input(char* line, int length);
char* libgap_get_error();
void libgap_append_stdout(char ch);
void libgap_append_stderr(char ch);
void libgap_set_error(char* msg);

/* do not install any signal handles in the GAP kernel code */
#undef LIBGAP_SIGNALS

#endif /* LIBGAP_INTERNAL__H */
