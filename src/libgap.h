/*****************************************************************************
*   SAGE: Open Source Mathematical Software
*
*       Copyright (C) 2009, William Stein <wstein@gmail.com>
*       Copyright (C) 2012, Volker Braun <vbraun.name@gmail.com>
*
*  Distributed under the terms of the GNU General Public License (GPL) v3+.
*  The full text of the GPL is available at: http://www.gnu.org/licenses/
*****************************************************************************/


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
void libgap_reset_output_buffer();
void libgap_finish_interaction();


/* For GAP to access the buffers */
char* libgap_get_input(char* line, int length);
void libgap_append_output(char ch);

