#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
void myprintf (char *, ...);
char *convert (unsigned int num, int base);
int mystrlen (const char *str);
int myatoi (char *buffer, int base);
void myscanf (char *format, ...);

void
myprintf (char *format, ...)
{
  char *traverse;
  unsigned int arg;
  char *arg2;

  char *p = (((char *) &format) + sizeof (format));

  for (traverse = format; *traverse != '\0'; traverse++)
    {
      if (*traverse == '%')
	{
	  traverse++;
	  if (*traverse == 'd')
	    {
	      arg = *((int *) p);
	      p += sizeof (int);
	      write (1, convert (arg, 10), sizeof (convert (arg, 10)));
	    }
	  else if (*traverse == 'x')
	    {
	      arg = *((int *) p);
	      p += sizeof (int);
	      write (1, convert (arg, 16), sizeof (convert (arg, 10)));
	    }
	  else if (*traverse == 'b')
	    {
	      arg = *((int *) p);
	      p += sizeof (int);
	      write (1, convert (arg, 2), sizeof (convert (arg, 10)));
	    }
	  else if (*traverse == 's')
	    {
	      arg2 = *((char **) p);
	      p += sizeof (char *);
	      write (1, arg2, mystrlen (arg2));
	    }
	}
      else
	{
	  write (1, (void *) traverse, 1);
	}
    }
}


int
mystrlen (const char *str)
{
  int len = 0;
  while (*str != '\0')
    {
      str++;
      len++;
    }
  return len;
}


char *
convert (unsigned int num, int base)
{
  static char Representation[] = "0123456789ABCDEF";
  static char buffer[50];
  char *ptr;

  ptr = &buffer[49];
  *ptr = '\0';

  do
    {
      *--ptr = Representation[num % base];
      num /= base;
    }
  while (num != 0);

  return (ptr);
}

void
myscanf (char *format, ...)
{
  char *traverse;
  char *p = (((char *) &format) + sizeof (format));
  char *input = malloc (1024 * sizeof (char));

  int *arg;
  char **arg2;

  for (traverse = format; *traverse != '\0'; traverse++)
    {
      if (*traverse == '%')
	{
	  traverse++;
	  if (*traverse == 'd')
	    {
	      arg = *((int **) p);
	      read (0, input, 1024);
	      *arg = myatoi (input, 10);
	      p += sizeof (int *);
	    }
	  else if (*traverse == 'x')
	    {
	      arg = *((int **) p);
	      read (0, input, 1024);
	      *arg = myatoi (input, 16);
	      p += sizeof (int *);
	    }
	  else if (*traverse == 'b')
	    {
	      arg = *((int **) p);
	      read (0, input, 1024);
	      *arg = myatoi (input, 2);
	      p += sizeof (int *);
	    }
	  else if (*traverse == 's')
	    {
	      arg2 = *((char ***) p);
	      p += sizeof (char *);
	      read (0, input, 1024);
	      *arg2 = input;
	    }
	}
    }
}

int
myatoi (char *s, int base)
{
  int result = 0;
  int sign = 0;

  while (*s != '\0' && *s != 10)
    {
      if (*s >= 'a' && *s <= 'f')
	result = result * base + (*s - 'a' + 10);
      else
	result = result * base + (*s - '0');

      s++;
    }
  return result;
}



int
main ()
{
  int i;
  myscanf ("%d", &i);
  myprintf ("\nxd\n");
  myprintf ("%d\n", i);
  return 0;
}
