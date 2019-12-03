#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* reference implementation
 *
 * char *
 * __strcat_chk (char *dest, const char *src, size_t destlen)
 * {
 *   char *s1 = dest;
 *   const char *s2 = src;
 *   char c;
 *
 *   // Find the end of the string.
 *   do
 *     {
 *       if (__glibc_unlikely (destlen-- == 0))
 * 	__chk_fail ();
 *       c = *s1++;
 *     }
 *   while (c != '\0');
 *
 *   // Make S1 point before the next character, so we can increment it while memory is read (wins on pipelined cpus).
 *   ++destlen;
 *   s1 -= 2;
 *
 *   do
 *     {
 *       if (__glibc_unlikely (destlen-- == 0))
 * 	__chk_fail ();
 *       c = *s2++;
 *       *++s1 = c;
 *     }
 *   while (c != '\0');
 *
 *   return dest;
 * }
 *
 * __fortify_function char *
 * __NTH (strcat (char *__restrict __dest, const char *__restrict __src))
 * {
 *   return __builtin___strcat_chk (__dest, __src, __bos (__dest));
 * }
 *
 */

int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  strcat(buffer, "bonjour");
#endif

  char from[] = "bonjour";
  if(argc == 5)
  {
    char buffer[3] = {'a', 'b', 'c'};
    strcat(buffer, from);
    puts(buffer);
  }

  from[argc] = 0;

  if(argc != 5)
  {
    char buffer[3] = {0};
    strcat(buffer, from);
    puts(buffer);
  }


  {
    char buffer[3] = {0};
    from[3] = 0;
    strcat(buffer, "yo");
    puts(buffer);
  }
  return 0;
}
