/* gcompris - gc-sound-object.h
 *
 * Copyright (C) 2006 Yves Combe
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <gc-sound-object.h>
#include <gc-sound-marshallers.h>

static void       gc_sound_object_base_class_init     (GCSoundObjectClass *class);
static void       gc_sound_object_base_class_finalize (GCSoundObjectClass *class);
static void       gc_sound_object_class_init          (GCSoundObjectClass *klass);
static void       gc_sound_object_init                (GCSoundObject      *object,
						  GCSoundObjectClass *klass);
static void	  gc_sound_object_set_property	 (GObject	 *object,
						  guint           property_id,
						  const GValue   *value,
						  GParamSpec     *pspec);
static void	  gc_sound_object_get_property	 (GObject	 *object,
						  guint           property_id,
						  GValue         *value,
						  GParamSpec     *pspec);
static void       gc_sound_object_dispose            (GObject        *object);
static void       gc_sound_object_real_destroy        (GCSoundObject      *object);
static void       gc_sound_object_finalize            (GObject        *object);

enum {
  DESTROY,
  LAST_SIGNAL
};
enum {
  PROP_0,
  PROP_USER_DATA
};

static guint       gc_sound_object_signals[LAST_SIGNAL] = { 0 };
static gpointer    parent_class = NULL;

/****************************************************
 * GCSoundObject type, class and instance initialization
 *
 ****************************************************/

GType
gc_sound_object_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      const GTypeInfo object_info =
      {
	sizeof (GCSoundObjectClass),
	(GBaseInitFunc) gc_sound_object_base_class_init,
	(GBaseFinalizeFunc) gc_sound_object_base_class_finalize,
	(GClassInitFunc) gc_sound_object_class_init,
	NULL,		/* class_finalize */
	NULL,		/* class_data */
	sizeof (GCSoundObject),
	16,		/* n_preallocs */
	(GInstanceInitFunc) gc_sound_object_init,
	NULL,		/* value_table */
      };
      
      object_type = g_type_register_static (G_TYPE_INITIALLY_UNOWNED, "GCSoundObject", 
					    &object_info, G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

static void
gc_sound_object_base_class_init (GCSoundObjectClass *class)
{
}

static void
gc_sound_object_base_class_finalize (GCSoundObjectClass *class)
{
}

static void
gc_sound_object_class_init (GCSoundObjectClass *class)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (class);

  parent_class = g_type_class_ref (G_TYPE_OBJECT);

  gobject_class->dispose = gc_sound_object_dispose;
  gobject_class->finalize = gc_sound_object_finalize;

  class->destroy = gc_sound_object_real_destroy;

  g_object_class_install_property (gobject_class,
				   PROP_USER_DATA,
				   g_param_spec_pointer ("user-data", 
							 "User Data",
							 "Anonymous User Data Pointer",
							 G_PARAM_READWRITE));

  gc_sound_object_signals[DESTROY] =
    g_signal_new ("destroy",
		  G_TYPE_FROM_CLASS (gobject_class),
		  G_SIGNAL_RUN_CLEANUP | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
		  G_STRUCT_OFFSET (GCSoundObjectClass, destroy),
		  NULL, NULL,
		  gc_sound_marshal_VOID__VOID,
		  G_TYPE_NONE, 0);
}

static void
gc_sound_object_init (GCSoundObject      *object,
		      GCSoundObjectClass *klass)
{
}

/********************************************
 * Functions to end a GCSoundObject's life time
 *
 ********************************************/
void
gc_sound_object_destroy (GCSoundObject *object)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (GC_IS_SOUND_OBJECT (object));
  
  if (!(GC_SOUND_OBJECT_FLAGS (object) & GC_SOUND_IN_DESTRUCTION))
    g_object_run_dispose (G_OBJECT (object));
}

static void
gc_sound_object_dispose (GObject *gobject)
{
  GCSoundObject *object = GC_SOUND_OBJECT (gobject);

  /* guard against reinvocations during
   * destruction with the GTK_IN_DESTRUCTION flag.
   */
  if (!(GC_SOUND_OBJECT_FLAGS (object) & GC_SOUND_IN_DESTRUCTION))
    {
      GC_SOUND_OBJECT_SET_FLAGS (object, GC_SOUND_IN_DESTRUCTION);
      
      g_signal_emit (object, gc_sound_object_signals[DESTROY], 0);
      
      GC_SOUND_OBJECT_UNSET_FLAGS (object, GC_SOUND_IN_DESTRUCTION);
    }

  G_OBJECT_CLASS (parent_class)->dispose (gobject);
}

static void
gc_sound_object_real_destroy (GCSoundObject *object)
{
  g_signal_handlers_destroy (object);
}

static void
gc_sound_object_finalize (GObject *gobject)
{
  GCSoundObject *object = GC_SOUND_OBJECT (gobject);

  if (g_object_is_floating (object))
    {
      g_warning ("GCSoundObject: A floating object was finalized. This means that someone\n"
		 "called g_object_unref() on an object that had only a floating\n"
		 "reference; the initial floating reference is not owned by anyone\n"
		 "and must be removed with g_object_ref_sink().");
    }
  
  G_OBJECT_CLASS (parent_class)->finalize (gobject);
}

/*****************************************
 * GCSoundObject property handlers
 * comes directly from GtkObject
 *
 *****************************************/

static void
gc_sound_object_set_property (GObject      *object,
			 guint         property_id,
			 const GValue *value,
			 GParamSpec   *pspec)
{
  switch (property_id)
    {
    case PROP_USER_DATA:
      g_object_set_data (G_OBJECT (object), "user_data", g_value_get_pointer (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gc_sound_object_get_property (GObject     *object,
			 guint        property_id,
			 GValue      *value,
			 GParamSpec  *pspec)
{
  switch (property_id)
    {
    case PROP_USER_DATA:
      g_value_set_pointer (value, g_object_get_data (G_OBJECT (object), "user_data"));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}