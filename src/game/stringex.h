////////////////////////////////////////////////////////////////////////////////
//                               --  THYME  --                                //
////////////////////////////////////////////////////////////////////////////////
//
//  Project Name:: Thyme
//
//          File:: STRINGEX.H
//
//        Author:: OmniBlade
//
//  Contributors:: 
//
//   Description:: Some extra string manipulation functions not present in
//                 standard CRTs
//
//       License:: Thyme is free software: you can redistribute it and/or 
//                 modify it under the terms of the GNU General Public License 
//                 as published by the Free Software Foundation, either version 
//                 2 of the License, or (at your option) any later version.
//
//                 A full copy of the GNU General Public License can be found in
//                 LICENSE
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string.h>
#include <ctype.h>

#ifdef __cplusplus
inline char *nstrdup(const char *str)
{
    char *nstr = NULL;

    if ( str != NULL ) {
        nstr = new char[strlen(str) + 1];

        if ( nstr != NULL ) {
            strcpy(nstr, str);
        }
    }

    return nstr;
}
#endif

#ifdef __cplusplus
extern "C" {
#endif

// BSD strl*** functions
#if defined(__linux__) || defined(_WIN32)
/*
* Copyright (c) 1998, 2015 Todd C. Miller <Todd.Miller@courtesan.com>
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
* WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
* ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
* WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
* ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
* OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

// Concatenates strings to a known size.
inline size_t strlcat(char *dst, const char *src, size_t dsize)
{
    const char *odst = dst;
    const char *osrc = src;
    size_t n = dsize;
    size_t dlen;

    /* Find the end of dst and adjust bytes left but don't go past end. */
    while ( n-- != 0 && *dst != '\0' )
        dst++;
    dlen = dst - odst;
    n = dsize - dlen;

    if ( n-- == 0 )
        return(dlen + strlen(src));
    while ( *src != '\0' ) {
        if ( n != 0 ) {
            *dst++ = *src;
            n--;
        }
        src++;
    }
    *dst = '\0';

    return(dlen + (src - osrc));	/* count does not include NUL */
}

// Copies strings to a buffer of known size.
inline size_t strlcpy(char *dst, const char *src, size_t dsize)
{
    const char *osrc = src;
    size_t nleft = dsize;

    /* Copy as many bytes as will fit. */
    if ( nleft != 0 ) {
        while ( --nleft != 0 ) {
            if ( (*dst++ = *src++) == '\0' )
                break;
        }
    }

    /* Not enough room in dst, add NUL and traverse rest of src. */
    if ( nleft == 0 ) {
        if ( dsize != 0 )
            *dst = '\0';		/* NUL-terminate dst */
        while ( *src++ )
            ;
    }

    return(src - osrc - 1);	/* count does not include NUL */
}

#endif

inline char16_t *strcpy16(char16_t *dst, char16_t const *src)
{
    char16_t *tmp = dst;
    while ( (*tmp++ = *src++) );

    return dst;
}

inline size_t strlen16(char16_t const *str)
{
    if ( !str ) {
        return 0;
    }

    size_t len = 0;
    while ( str[len] ) {
        ++len;
    }

    return len;
}

inline char *strtrim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if ( str == NULL ) { return NULL; }
    if ( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
    * characters from each end.
    */
    while ( isspace((unsigned char)*frontp) ) { ++frontp; }
    if ( endp != frontp ) {
        while ( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if ( str + len - 1 != endp ) {
        *(endp + 1) = '\0';
    } else if ( frontp != str &&  endp == frontp ) {
        *str = '\0';
    }

    /* Shift the string so that it starts at str so that if it's dynamically
    * allocated, we can still free it on the returned pointer.  Note the reuse
    * of endp to mean the front of the string buffer now.
    */
    endp = str;
    if ( frontp != str ) {
        while ( *frontp ) { *endp++ = *frontp++; }
        *endp = '\0';
    }

    return str;
}

#ifdef __cplusplus
} // extern "C"
#endif