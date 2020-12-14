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
#include "test_common.c"

int main(int argc, char ** argv) {
  DECL_BUF(buffer, 3)
#ifdef STATIC_CHECK
  strncat(buffer, "bonjour", 4);
#endif
  if(argc >= 5)
  {
    CHK_FAIL_START
    DECL_BUF(buffer, 5)
    buffer[0] = 'a';
    buffer[1] = 'b';
    buffer[2] = 'c';
    buffer[3] = 'd';
    buffer[4] = argc;
    strncat(buffer, "bonjour", argc);
    CHK_FAIL_END
    puts(buffer);
  }

  if(argc > 1 && argc < 5)
  {
    CHK_FAIL_START
    DECL_BUF(buffer, 3)
    strncat(buffer, "bonjour", argc);
    puts(buffer);
    CHK_FAIL_END
  }

  {
    DECL_BUF(buffer, 3)
    strncat(buffer, "yo", 3);
    puts(buffer);
  }
  return ret;
}
