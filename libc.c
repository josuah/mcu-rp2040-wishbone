#include "libc.h"

/* <string.h> */

void *
memset(void *mem, int val, size_t sz)
{
	for (char *mp = mem; sz > 0; sz--, mp++)
		*mp = (char)val;
	return mem;
}

void *
memcpy(void *mem, void const *src, size_t sz)
{
	for (char *mp = mem, *sp = (char *)src; sz > 0; mp++, sp++)
		*mp = *sp;
	return mem;
}

size_t
strlen(char const *s)
{
	for (size_t len = 0 ;; s++, len++)
		if (*s == '\0')
			return len;
}

char *
strchr(const char *s, int c)
{
	for (; *s != c; s++)
		if (*s == '\0')
			return NULL;
	return (char *)s;
}

/* <ctype.h> */

int
isalnum(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
	 || (c >= '0' && c <= '9');
}

int
isalpha(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int
isascii(int c)
{
	return c < 0x80;
}

int
isblank(int c)
{
	return c == ' ' || c == '\t';
}

int
iscntrl(int c)
{
	return c <= 0x1F || c == 0x7F;
}

int
isdigit(int c)
{
	return c >= '0' && c <= '9';
}

int
isgraph(int c)
{
	return c >= 0x20 && c <= 0x7E && c != ' ';
}

int
islower(int c)
{
	return c >= 'a' && c <= 'z';
}

int
isprint(int c)
{
	return c >= 0x20 && c <= 0x7E;
}

int
ispunct(int c)
{
	return (c >= '!' && c <= '/') || (c >= '[' && c <= '`')
	 || (c >= '{' && c <= '~');
}

int
isspace(int c)
{
	return (c >= 0x09 && c <= 0x0D) || c == ' ';
}

int
isupper(int c)
{
	return c >= 'A' && c <= 'Z';
}

int
isxdigit(int c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
	 || (c >= 'A' && c <= 'F');
}

int
tolower(int c)
{
	return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : (c);
}

int
toupper(int c)
{
	return (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : (c);
}
