/* Copyright (C) 2004       Manuel Novoa III    <mjn3@codepoet.org>
 *
 * GNU Library General Public License (LGPL) version 2 or later.
 *
 * Dedicated to Toni.  See uClibc/DEDICATION.mjn3 for details.
 */

#include "_stdio.h"

#include <mosstd.h>
#include <errno.h>

/* SUSv3 states:
 *   If path does not name a directory, remove(path) shall be equivalent
 *   to unlink(path).  If path names a directory, remove(path) shall be
 *   equivalent to rmdir(path). 
 */

int remove(register const char *filename)
{
//	int saved_errno = errno;
	int rv;

	// MOSS
//	if (((rv = rmdir(filename)) < 0) && (errno == ENOTDIR)) {
//		__set_errno(saved_errno); /* Need to restore errno. */
//		rv = unlink(filename);
//	}
	rv = unlink(filename);
	// MOSE
		
	return rv;
}
