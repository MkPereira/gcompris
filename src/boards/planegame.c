/* gcompris - planegame.c
 *
 * Copyright (C) 2000 Bruno Coudoin
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

#include "gcompris/gcompris.h"

#define SOUNDLISTFILE PACKAGE

static GList *item_list = NULL;
static GList *item2del_list = NULL;

static gboolean board_paused = TRUE;
static GcomprisBoard *gcomprisBoard = NULL;

static gint dummy_id = 0;
static gint drop_items_id = 0;

static GnomeCanvasItem *planeitem = NULL;
static gint plane_x, plane_y;
static gint planespeed_x, planespeed_y;

#define MAXSPEED 7

/* These are the index for managing the game rule */
static gint plane_target, plane_last_target;

typedef struct {
  gint number;
  GnomeCanvasItem *rootitem;
} CloudItem;


static void start_board (GcomprisBoard *agcomprisBoard);
static void pause_board (gboolean pause);
static void end_board (void);
static gboolean is_our_board (GcomprisBoard *gcomprisBoard);
static void set_level (guint level);
static gint key_press(guint keyval, gchar *commit_str, gchar *preedit_str);

static GnomeCanvasItem *planegame_create_item(GnomeCanvasGroup *parent);
static gint planegame_drop_items (GtkWidget *widget, gpointer data);
static gint planegame_move_items (GtkWidget *widget, gpointer data);
static void planegame_destroy_item(CloudItem *clouditem);
static void planegame_destroy_items(void);
static void planegame_destroy_all_items(void);
static void setup_item(GnomeCanvasItem *item);
static void planegame_next_level(void);

static  guint32              fallSpeed = 0;
static  double               speed = 0.0;
static  double               imageZoom = 0.0;

/* Description of this plugin */
static BoardPlugin menu_bp =
{
   NULL,
   NULL,
   N_("Numbers in Order"),
   N_("Move the plane to catch the clouds in the correct order"),
   "Bruno Coudoin <bruno.coudoin@free.fr>",
   NULL,
   NULL,
   NULL,
   NULL,
   start_board,
   pause_board,
   end_board,
   is_our_board,
   key_press,
   NULL,
   set_level,
   NULL,
   NULL,
   NULL,
   NULL
};

/*
 * Main entry point mandatory for each Gcompris's game
 * ---------------------------------------------------
 *
 */

GET_BPLUGIN_INFO(planegame)

/*
 * in : boolean TRUE = PAUSE : FALSE = CONTINUE
 *
 */
static void pause_board (gboolean pause)
{
  if(gcomprisBoard==NULL)
    return;

  if(pause)
    {
      if (dummy_id) {
	gtk_timeout_remove (dummy_id);
	dummy_id = 0;
      }
      if (drop_items_id) {
	gtk_timeout_remove (drop_items_id);
	drop_items_id = 0;
      }
    }
  else
    {
      if(!drop_items_id) {
	drop_items_id = gtk_timeout_add (1000,
					 (GtkFunction) planegame_drop_items, NULL);
      }
      if(!dummy_id) {
	dummy_id = gtk_timeout_add (1000, (GtkFunction) planegame_move_items, NULL);
      }
    }
  board_paused = pause;
}

/*
 */
static void start_board (GcomprisBoard *agcomprisBoard)
{

  if(agcomprisBoard!=NULL)
    {
      gcomprisBoard=agcomprisBoard;

      /* disable im_context */
      gcomprisBoard->disable_im_context = TRUE;

      gc_set_background(gnome_canvas_root(gcomprisBoard->canvas), "opt/scenery3_background.png");


      /* set initial values for this level */
      gcomprisBoard->level = 1;
      gcomprisBoard->maxlevel = 2;
      gc_bar_set(GC_BAR_LEVEL);

      planegame_next_level();

      pause_board(FALSE);

    }

}

static void
end_board ()
{

  if(gcomprisBoard!=NULL)
    {
      pause_board(TRUE);
      gc_score_end();
      planegame_destroy_all_items();
      gcomprisBoard->level = 1;       // Restart this game to zero
    }
  gcomprisBoard = NULL;
}

static void
set_level (guint level)
{

  if(gcomprisBoard!=NULL)
    {
      gcomprisBoard->level=level;
      planegame_next_level();
    }
}

static gint key_press(guint keyval, gchar *commit_str, gchar *preedit_str)
{

  if(board_paused || !gcomprisBoard)
    return FALSE;

  /* Add some filter for control and shift key */
  switch (keyval)
    {
      /* Avoid all this keys to be interpreted by this game */
    case GDK_Shift_L:
    case GDK_Shift_R:
    case GDK_Control_L:
    case GDK_Control_R:
    case GDK_Caps_Lock:
    case GDK_Shift_Lock:
    case GDK_Meta_L:
    case GDK_Meta_R:
    case GDK_Alt_L:
    case GDK_Alt_R:
    case GDK_Super_L:
    case GDK_Super_R:
    case GDK_Hyper_L:
    case GDK_Hyper_R:
    case GDK_Num_Lock:
      return FALSE;
    case GDK_KP_Enter:
    case GDK_Return:
      return TRUE;
    case GDK_Right:
      if(planespeed_x < MAXSPEED)
	planespeed_x++;
      return TRUE;
    case GDK_Left:
      if(planespeed_x > -MAXSPEED)
	planespeed_x--;
      return TRUE;
    case GDK_Up:
      if(planespeed_y > -MAXSPEED)
      planespeed_y--;
      return TRUE;
    case GDK_Down:
      if(planespeed_y < MAXSPEED)
      planespeed_y++;
      return TRUE;
    }
  return TRUE;
}

gboolean
is_our_board (GcomprisBoard *gcomprisBoard)
{
  if (gcomprisBoard)
    {
      if(g_strcasecmp(gcomprisBoard->type, "planegame")==0)
	{
	  /* Set the plugin entry */
	  gcomprisBoard->plugin=&menu_bp;

	  return TRUE;
	}
    }
  return FALSE;
}


/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/

/* set initial values for the next level */
static void planegame_next_level()
{
  GdkPixbuf *pixmap = NULL;

  gc_bar_set_level(gcomprisBoard);

  planegame_destroy_all_items();

  /* Try the next level */
  speed=100+(40/(gcomprisBoard->level));
  fallSpeed=10000-gcomprisBoard->level*200;
  /* Make the images tend to 0.5 ratio */
  imageZoom=0.3+(0.5/(gcomprisBoard->level));

  /* Setup and Display the plane */
  planespeed_y = 0;
  planespeed_x = 0;
  pixmap = gc_pixmap_load("gcompris/misc/tuxhelico.png");
  plane_x = 50;
  plane_y = 300;
  planeitem = gnome_canvas_item_new (gnome_canvas_root(gcomprisBoard->canvas),
				     gnome_canvas_pixbuf_get_type (),
				     "pixbuf", pixmap,
				     "x", (double) plane_x,
				     "y", (double) plane_y,
				     "width", (double) gdk_pixbuf_get_width(pixmap)*imageZoom,
				     "height", (double) gdk_pixbuf_get_height(pixmap)*imageZoom,
				     "width_set", TRUE,
				     "height_set", TRUE,
				     NULL);
  gdk_pixbuf_unref(pixmap);

  /* Game rules */
  plane_target = 1;
  plane_last_target = 10;

  gcomprisBoard->number_of_sublevel=plane_last_target;

  gcomprisBoard->sublevel=plane_target;

  if(gcomprisBoard->level>1)
    {
      /* No scoring after level 1 */
      gc_score_end();
    }
  else
    {
      gc_score_start(SCORESTYLE_NOTE,
			   gcomprisBoard->width - 220,
			   gcomprisBoard->height - 50,
			   gcomprisBoard->number_of_sublevel);
      gc_score_set(gcomprisBoard->sublevel);
    }
}

#define ISIN(x1, y1, px1, py1, px2, py2) (x1>px1 && x1<px2 && y1>py1 && y2<py2 ? TRUE : FALSE)

static void planegame_cloud_colision(CloudItem *clouditem)
{
  double px1, px2, py1, py2;
  double x1, x2, y1, y2;
  GnomeCanvasItem *item;

  if(clouditem==NULL)
    return;

  item = clouditem->rootitem;

  gnome_canvas_item_get_bounds(planeitem,  &px1, &py1, &px2, &py2);
  gnome_canvas_item_get_bounds(item,  &x1, &y1, &x2, &y2);

  if(
     ISIN(x1, y1, px1, py1, px2, py2) ||
     ISIN(x2, y1, px1, py1, px2, py2) ||
     ISIN(x1, y2, px1, py1, px2, py2) ||
     ISIN(x2, y2, px1, py1, px2, py2)
     )
    {
      if(plane_target == clouditem->number)
	{
	  gc_sound_play_ogg ("sounds/gobble.wav", NULL);
	  item2del_list = g_list_append (item2del_list, clouditem);
	  plane_target++;

	  if(gcomprisBoard->level==1)
	    {
	      gc_score_set(plane_target);
	    }

	  if(plane_target==plane_last_target)
	    {
	      /* Try the next level */
	      gcomprisBoard->level++;
	      if(gcomprisBoard->level>gcomprisBoard->maxlevel) { // the current board is finished : bail out
		gc_bonus_end_display(GC_BOARD_FINISHED_RANDOM);
		return;
	      }
	      planegame_next_level();
	      gc_sound_play_ogg ("sounds/bonus.wav", NULL);
	    }
	}
    }
}

/* Move the plane */
static void planegame_move_plane(GnomeCanvasItem *item)
{
  if(plane_x>gcomprisBoard->width-150 && planespeed_x>0)
    planespeed_x=0;

  if(plane_x<0 && planespeed_x<0)
    planespeed_x=0;

  if(plane_y>gcomprisBoard->height-50 && planespeed_y>0)
    planespeed_y=0;

  if(plane_y<10 && planespeed_y<0)
    planespeed_y=0;

  gnome_canvas_item_move(item, (double)planespeed_x, (double)planespeed_y);
  plane_x+=planespeed_x;
  plane_y+=planespeed_y;
}

static void planegame_move_item(CloudItem *clouditem)
{
  double x1, y1, x2, y2;
  GnomeCanvasItem *item = clouditem->rootitem;

  gnome_canvas_item_move(item, -2.0, 0.0);

  gnome_canvas_item_get_bounds    (item,
				   &x1,
				   &y1,
				   &x2,
				   &y2);

  if(x2<0) {
    item2del_list = g_list_append (item2del_list, clouditem);
  }

}

static void planegame_destroy_item(CloudItem *clouditem)
{
  GnomeCanvasItem *item = clouditem->rootitem;

  item_list = g_list_remove (item_list, clouditem);
  item2del_list = g_list_remove (item2del_list, clouditem);
  gtk_object_destroy (GTK_OBJECT(item));

  g_free(clouditem);
}

/* Destroy items that falls out of the canvas */
static void planegame_destroy_items()
{
  CloudItem *clouditem;

  while(g_list_length(item2del_list)>0)
    {
      clouditem = g_list_nth_data(item2del_list, 0);
      planegame_destroy_item(clouditem);
    }
}

/* Destroy all the items */
static void planegame_destroy_all_items()
{
  CloudItem *clouditem;

  while(g_list_length(item_list)>0)
    {
      clouditem = g_list_nth_data(item_list, 0);
      planegame_destroy_item(clouditem);
    }

  if(planeitem)
    {
      gtk_object_destroy (GTK_OBJECT(planeitem));
      planeitem = NULL;
    }
}

/*
 * This does the moves of the game items on the play canvas
 *
 */
static gint planegame_move_items (GtkWidget *widget, gpointer data)
{
  g_list_foreach (item_list, (GFunc) planegame_move_item, NULL);
  g_list_foreach (item_list, (GFunc) planegame_cloud_colision, NULL);

  /* Destroy items that falls out of the canvas */
  planegame_destroy_items();

  /* move the plane */
  planegame_move_plane(planeitem);
  dummy_id = gtk_timeout_add (speed,
			      (GtkFunction) planegame_move_items, NULL);

  return(FALSE);
}

static GnomeCanvasItem *planegame_create_item(GnomeCanvasGroup *parent)
{
  GdkPixbuf *pixmap = NULL;
  GnomeCanvasItem *itemgroup;
  char *number = NULL;
  int i, min;
  CloudItem *clouditem;

  /* Random cloud number */
  if(g_random_int()%2==0)
    {
      /* Put the target */
      i = plane_target;
    }
  else
    {
      min = MAX(1, plane_target - 1);
      i   = min + g_random_int()%(plane_target - min + 3);
    }
  number = g_strdup_printf("%d", i);

  pixmap = gc_pixmap_load("gcompris/misc/cloud.png");

  itemgroup = \
    gnome_canvas_item_new (parent,
			   gnome_canvas_group_get_type (),
			   "x", (double) gcomprisBoard->width,
			   "y", (double)(g_random_int()%(gcomprisBoard->height-
						 (guint)(gdk_pixbuf_get_height(pixmap)*
							 imageZoom))),
			   NULL);


  gnome_canvas_item_new (GNOME_CANVAS_GROUP(itemgroup),
			 gnome_canvas_pixbuf_get_type (),
			 "pixbuf", pixmap,
			 "x", (double) -gdk_pixbuf_get_width(pixmap)*imageZoom/2,
			 "y", (double) -gdk_pixbuf_get_height(pixmap)*imageZoom/2,
			 "width", (double) gdk_pixbuf_get_width(pixmap)*imageZoom,
			 "height", (double) gdk_pixbuf_get_height(pixmap)*imageZoom,
			 "width_set", TRUE,
			 "height_set", TRUE,
			 NULL);
  gdk_pixbuf_unref(pixmap);


  gnome_canvas_item_new (GNOME_CANVAS_GROUP(itemgroup),
			 gnome_canvas_text_get_type (),
			 "text", number,
			 "font", gc_skin_font_board_big,
			 "x", (double) 0,
			 "y", (double) 0,
			 "fill_color", "red",
			 NULL);

  /* The plane is always on top */
  gnome_canvas_item_raise_to_top(planeitem);

  clouditem = g_malloc(sizeof(CloudItem));
  clouditem->rootitem = itemgroup;
  clouditem->number   = i;

  item_list = g_list_append (item_list, clouditem);

  g_free (number);

  return (itemgroup);
}

static void planegame_add_new_item()
{
  setup_item (planegame_create_item(gnome_canvas_root(gcomprisBoard->canvas)));
}

/*
 * This is called on a low frequency and is used to drop new items
 *
 */
static gint planegame_drop_items (GtkWidget *widget, gpointer data)
{
  planegame_add_new_item();

  drop_items_id = gtk_timeout_add (fallSpeed,
  				   (GtkFunction) planegame_drop_items, NULL);
  return (FALSE);
}

static gint
item_event(GnomeCanvasItem *item, GdkEvent *event, gpointer data)
{
   static double x, y;
   double new_x, new_y;
   GdkCursor *fleur;
   static int dragging;
   double item_x, item_y;

  if(!gcomprisBoard)
    return FALSE;

   item_x = event->button.x;
   item_y = event->button.y;
   gnome_canvas_item_w2i(item->parent, &item_x, &item_y);

   switch (event->type)
     {
     case GDK_BUTTON_PRESS:
       switch(event->button.button)
         {
         case 1:
           if (event->button.state & GDK_SHIFT_MASK)
             {
               x = item_x;
               y = item_y;

               fleur = gdk_cursor_new(GDK_FLEUR);
               gc_canvas_item_grab(item,
                                      GDK_POINTER_MOTION_MASK |
                                      GDK_BUTTON_RELEASE_MASK,
                                      fleur,
                                      event->button.time);
               gdk_cursor_destroy(fleur);
               dragging = TRUE;
             }
           break;

         default:
           break;
         }
       break;

     case GDK_MOTION_NOTIFY:
       if (dragging && (event->motion.state & GDK_BUTTON1_MASK))
         {
           new_x = item_x;
           new_y = item_y;

           gnome_canvas_item_move(item, new_x - x, new_y - y);
           x = new_x;
           y = new_y;
         }
       break;

     case GDK_BUTTON_RELEASE:
       if(dragging)
	 {
	   gc_canvas_item_ungrab(item, event->button.time);
	   dragging = FALSE;
	 }
       break;

     default:
       break;
     }

   return FALSE;
 }

static void
setup_item(GnomeCanvasItem *item)
{
  gtk_signal_connect(GTK_OBJECT(item), "event",
		     (GtkSignalFunc) item_event,
		     NULL);
}
