/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* 
 * e-unicode.h - utf-8 support functions for gal
 * Copyright 2000, 2001, Ximian, Inc.
 *
 * Authors:
 *   Lauris Kaplinski <lauris@ximian.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License, version 2, as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef _E_UNICODE_H_
#define _E_UNICODE_H_

#include <glib.h>
#include <gunicode.h>
#include <iconv.h>

gchar       *e_utf8_to_iconv_string_sized                   (iconv_t        ic,
							     const gchar   *string,
							     gint           bytes);
gchar       *e_utf8_to_locale_string                        (const gchar   *string);
gchar       *e_utf8_to_locale_string_sized                  (const gchar   *string,
							     gint           bytes);
gchar       *e_unicode_get_utf8                             (const gchar   *text,
							     gunichar      *out);
#endif

