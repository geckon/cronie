/*
 * Copyright (c) 2012 Copyright Red Hat Software
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
 * OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* Collection of definitions, inline functions, etc, that are useful for
 * both cron and anacron.  */

#ifndef CRONIE_COMMON_H
#define CRONIE_COMMON_H

#include <stdlib.h>

#ifndef __attribute__
# if __GNUC__ < 2 || (__GNUC__ == 2 && __GNUC_MINOR__ < 8)
#  define __attribute__(x)      /* empty */
# endif
#endif

#ifndef ATTRIBUTE_NORETURN
# define ATTRIBUTE_NORETURN __attribute__ ((__noreturn__))
#endif

#ifndef ATTRIBUTE_UNUSED
# define ATTRIBUTE_UNUSED __attribute__ ((__unused__))
#endif

static inline size_t get_hostname_max(void) {
	long len = sysconf(_SC_HOST_NAME_MAX);

	if (0 < len)
		return len;
#ifdef MAXHOSTNAMELEN
	return MAXHOSTNAMELEN;
#elif HOST_NAME_MAX
	return HOST_NAME_MAX;
#endif
	return 64;
}

static inline char *xgethostname(void) {
	char *name;
	size_t sz = get_hostname_max() + 1;

	name = malloc(sizeof (char) * sz);
	if (!name)
		return NULL;
	if (gethostname(name, sz) != 0)
		return NULL;

	name[sz - 1] = '\0';
	return name;
}

#endif /* CRONIE_COMMON_H */