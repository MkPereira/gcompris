/* gcompris - gameutil.h
 *
 * Time-stamp: <2000/07/16 00:32:26 bruno>
 *
 * Copyright (C) 2000 Bruno Coudoin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef SOUNDUTIL_H
#define SOUNDUTIL_H

#include <stdio.h>
#include "gcompris.h"

#define MAX_QUEUE_LENGTH 5
#define MAX_SOUND_FILES 20

void      gc_sound_play_ogg(const gchar *, ...);
void	 gc_sound_play_ogg_list( GList* files );

void	 gc_sound_init(void);
void	 gc_sound_reopen(void);
void	 gc_sound_close(void);
void	 gc_sound_pause(void);
void	 gc_sound_resume(void);

void      gc_music_play();

GcSoundItem *gc_sound_item_from_gc_filename(gchar *filename, const gchar *first_arg_name, ...);

gchar *gc_sound_alphabet(gchar *chars);

void gc_sound_policy_set(GcSoundPolicy policy);
GcSoundPolicy gc_sound_policy_get(void);

#endif
