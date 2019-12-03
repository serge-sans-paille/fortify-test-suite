/* reference implementation
 *
 * char *
 * __strncat_chk (char *s1, const char *s2, size_t n, size_t s1len)
 * {
 *   char c;
 *   char *s = s1;
 *
 *   // Find the end of S1.
 *   do
 *     {
 *       if (__glibc_unlikely (s1len-- == 0))
 * 	__chk_fail ();
 *       c = *s1++;
 *     }
 *   while (c != '\0');
 *
 *   // Make S1 point before next character, so we can increment it while memory is read (wins on pipelined cpus).
 *   ++s1len;
 *   s1 -= 2;
 *
 *   if (n >= 4)
 *     {
 *       size_t n4 = n >> 2;
 *       do
 * 	{
 * 	  if (__glibc_unlikely (s1len-- == 0))
 * 	    __chk_fail ();
 * 	  c = *s2++;
 * 	  *++s1 = c;
 * 	  if (c == '\0')
 * 	    return s;
 * 	  if (__glibc_unlikely (s1len-- == 0))
 * 	    __chk_fail ();
 * 	  c = *s2++;
 * 	  *++s1 = c;
 * 	  if (c == '\0')
 * 	    return s;
 * 	  if (__glibc_unlikely (s1len-- == 0))
 * 	    __chk_fail ();
 * 	  c = *s2++;
 * 	  *++s1 = c;
 * 	  if (c == '\0')
 * 	    return s;
 * 	  if (__glibc_unlikely (s1len-- == 0))
 * 	    __chk_fail ();
 * 	  c = *s2++;
 * 	  *++s1 = c;
 * 	  if (c == '\0')
 * 	    return s;
 * 	} while (--n4 > 0);
 *       n &= 3;
 *     }
 *
 *   while (n > 0)
 *     {
 *       if (__glibc_unlikely (s1len-- == 0))
 * 	__chk_fail ();
 *       c = *s2++;
 *       *++s1 = c;
 *       if (c == '\0')
 * 	return s;
 *       n--;
 *     }
 *
 *   if (c != '\0')
 *     {
 *       if (__glibc_unlikely (s1len-- == 0))
 * 	__chk_fail ();
 *       *++s1 = '\0';
 *     }
 *
 *   return s;
 * }
 */
#include <string.h>
#include <stdio.h>

int main(int argc, char ** argv) {
  char buffer[3] = {0};
#ifdef STATIC_CHECK
  strncat(buffer, "bonjour", 4);
#endif
  if(argc >= 5)
  {
    char buffer[5] = {'a', 'b', 'c', 'd', argc};
    strncat(buffer, "bonjour", argc);
    puts(buffer);
  }

  if(argc != 5)
  {
    char buffer[3] = {0};
    strncat(buffer, "bonjour", argc);
    puts(buffer);
  }

  {
    char buffer[3] = {0};
    strncat(buffer, "yo", 3);
    puts(buffer);
  }
  return 0;
}
