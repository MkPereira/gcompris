#  gcompris - doubleclick
#
# Copyright (C) 2008 Bruno Coudoin
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, see <http://www.gnu.org/licenses/>.
#

import gobject
import gnomecanvas
import gcompris
import gcompris.utils
import gcompris.skin
import gcompris.bonus
import gcompris.sound
import gtk
import gtk.gdk
from gcompris import gcompris_gettext as _

# ----------------------------------------
# Double click in a timely fashion to goal against Tux

class Gcompris_doubleclick:
  """double click goal"""


  def __init__(self, gcomprisBoard):
    self.gcomprisBoard = gcomprisBoard

    self.gcomprisBoard.disable_im_context = True

    # These are used to let us restart only after the bonus is displayed.
    # When the bonus is displayed, it call us first with pause(1) and then with pause(0)
    self.board_paused  = 0
    self.gamewon       = 0
    self.timer_indic   = 0
    self.timerinc      = 10

  def start(self):
    self.gcomprisBoard.level=1
    self.gcomprisBoard.maxlevel=9
    self.gcomprisBoard.sublevel=1
    self.gcomprisBoard.number_of_sublevel=1
    gcompris.bar_set(gcompris.BAR_LEVEL)
    gcompris.set_background(self.gcomprisBoard.canvas.root(),
                            "images/penalty_bg.png")
    gcompris.bar_set_level(self.gcomprisBoard)


    self.ballinc = 20        # Event loop timer for the ball move

    # Create our rootitem. We put each canvas item in it so at the end we
    # only have to kill it. The canvas deletes all the items it contains automaticaly.
    self.rootitem = self.gcomprisBoard.canvas.root().add(
      gnomecanvas.CanvasGroup,
      x=0.0,
      y=0.0
      )

    # Help
    self.help_item = self.rootitem.add(
      gnomecanvas.CanvasText,
      font = gcompris.skin.get_font("gcompris/board/medium"),
      x = gcompris.BOARD_WIDTH / 2,
      y = gcompris.BOARD_HEIGHT - 170,
      anchor=gtk.ANCHOR_CENTER,
      fill_color = "white"
      )
    self.help_item.hide()

    # Tux
    pixbuf = gcompris.utils.load_pixmap("gcompris/misc/tux.png")
    item = self.rootitem.add(
      gnomecanvas.CanvasPixbuf,
      pixbuf = pixbuf,
      x=gcompris.BOARD_WIDTH/2 - pixbuf.get_width()/2,
      y=195.0
      )
    item.connect("event", self.help)

    # The activity help
    item = self.rootitem.add(
      gnomecanvas.CanvasPixbuf,
      pixbuf = gcompris.utils.load_pixmap("images/doubleclick.png"),
      x = gcompris.BOARD_WIDTH  - 150,
      y = gcompris.BOARD_HEIGHT - 100
      )
    item.connect("event", self.help)

    # The click indicator
    indicator_h = 30
    indicator_w = 10
    y_ref = 107

    self.indicator = []
    self.indicator.append(
      Indicator(self.rootitem,
                gcompris.BOARD_WIDTH/2 - 350,
                y_ref,
                indicator_w,
                indicator_h,
                0,
                200)
      )
    self.indicator.append(
      Indicator(self.rootitem,
                gcompris.BOARD_WIDTH/2,
                y_ref - 80,
                indicator_h,
                indicator_w,
                1,
                100)
      )
    self.indicator.append(
      Indicator(self.rootitem,
                gcompris.BOARD_WIDTH/2 + 350,
                y_ref,
                indicator_w,
                indicator_h,
                2,
                200)
      )

    self.balloon = Balloon(self, 10, 10)
    self.balloon.item.connect("event", self.shoot_item_event)

    self.next_level()


  def end(self):

    self.balloon.reset()

    if self.timer_indic:
      gobject.source_remove(self.timer_indic)
    self.timer_indic = 0

    # Remove the root item removes all the others inside it
    self.rootitem.destroy()

  def ok(self):
    pass


  def repeat(self):
    pass


  def config(self):
    pass


  def key_press(self, keyval, commit_str, preedit_str):
    return False

  # Called by gcompris core
  def pause(self, pause):

    self.board_paused = pause

    # When the bonus is displayed, it call us first with pause(1) and then with pause(0)
    # the game is won
    if(pause == 0):
      self.next_level()
      self.gamewon = 0

    return


  # Called by gcompris when the user click on the level icon
  def set_level(self, level):
    self.gcomprisBoard.level=level
    self.gcomprisBoard.sublevel=1
    self.next_level()

  # End of Initialisation
  # ---------------------

  def next_level(self):

    # Set the level in the control bar
    gcompris.bar_set_level(self.gcomprisBoard);
    self.balloon.reset()

    if self.timer_indic:
      gobject.source_remove(self.timer_indic)
    self.timer_indic = 0

    if(self.gcomprisBoard.level == 1):
      winlimit = 1000
    elif(self.gcomprisBoard.level == 2):
      winlimit = 800
    elif(self.gcomprisBoard.level == 3):
      winlimit = 600
    elif(self.gcomprisBoard.level == 4):
      winlimit = 400
    elif(self.gcomprisBoard.level == 5):
      winlimit = 250
    elif(self.gcomprisBoard.level == 6):
      winlimit = 200
    elif(self.gcomprisBoard.level == 7):
      winlimit = 180
    elif(self.gcomprisBoard.level == 8):
      winlimit = 170
    elif(self.gcomprisBoard.level == 9):
      winlimit = 160

    self.counter = [0, 0, 0]
    for i in self.indicator:
      i.reset()
      i.winlimit = winlimit


  # Code that increments the sublevel and level
  # And bail out if no more levels are available
  # return 1 if continue, 0 if bail out
  def increment_level(self):
    self.gcomprisBoard.sublevel += 1

    if(self.gcomprisBoard.sublevel>self.gcomprisBoard.number_of_sublevel):
      # Try the next level
      self.gcomprisBoard.sublevel=1
      self.gcomprisBoard.level += 1
      if(self.gcomprisBoard.level>self.gcomprisBoard.maxlevel):
        self.gcomprisBoard.level = self.gcomprisBoard.maxlevel

    return 1

  # Update the counter and return true if click action
  # is compteted
  def update_counter(self, button, time):

    if self.counter[button] == 0:
      # FIRST CLICK
      # Check we are not already running
      for i in range(3):
        if self.counter[i] != 0:
          return False

      self.counter[button] = time
      self.indicator[button].start()
      self.timer_indic  = gobject.timeout_add(self.timerinc,
                                              self.indicator[button].refresh,
                                              self.timerinc)
      gcompris.sound.play_ogg("sounds/flip.wav")
      return False
    elif self.counter[button] != 0:
      # SECOND CLICK
      self.counter[button] = abs(self.counter[button] - time)
      self.counter[button] = 0
      self.balloon.move_to(self.indicator[button].stop())
      return True

  def shoot_item_event(self, widget, event=None):
    if event.type == gtk.gdk.BUTTON_PRESS:
      if event.button <= 3:
        if self.balloon.need_reset:
          self.balloon.reset()
          for i in range(3):
            self.counter[i] = 0
            self.indicator[i].reset()
        else:
          self.update_counter(event.button - 1,
                              event.time)

    return False

  #
  # Display an info string when the user clicks
  # on the wrong item
  def help(self, widget, event=None):
    if event.type == gtk.gdk.BUTTON_PRESS:
      if self.balloon.need_reset:
        text=_("Click on the balloon to place it again.")
      else:
        text=_("Click twice on the balloon to shoot it.")

      self.help_item.set(text = text)
      self.help_item.show()

    return False

class Indicator:
  winlimit = 0
  color_init = 0x1212CCC0
  color_done = 0x000012C0
  item = 0
  orientation = 0
  counter = 0
  stopped = True
  # orientation = 0 : horizontal, left assigned
  #             = 1 : vertical, top assigned
  #             = 2 : horizontal, right assigned
  #
  def __init__(self, rootitem, x, y, w, h,
               orientation, max):
    self.x = x
    self.y = y
    self.w = w
    self.h = h
    self.max = max
    self.orientation = orientation
    self.item = \
        rootitem.add(gnomecanvas.CanvasRect,
                     outline_color_rgba=0xFFFFFFFFL,
                     width_units = 1)
    self.reset()

  def reset(self):
    self.item.set(
      x1 = self.x,
      y1 = self.y,
      x2 = self.x + self.w,
      y2 = self.y + self.h,
      fill_color_rgba = self.color_init)
    self.stopped = True

  #
  # Return the calculated coordinate of the ballon
  # return: (win, X, Y) with win = True or False
  #
  def stop(self):
    self.stopped = True

    return (self.counter <= self.winlimit,
            self.target_x,
            self.target_y)


  def start(self):
    self.stopped = False
    self.counter = 0

  def refresh(self, timerinc):
    self.counter += timerinc
    self.update(self.counter)

    if self.stopped:
      return False
    return True

  def update(self, counter):
    length = min( (counter * self.max) / self.winlimit,
                  self.max)

    if self.orientation == 0:
      x2 = self.x + length
      self.item.set(x2 = x2)
      self.target_x = x2
      self.target_y = self.y
    elif self.orientation == 1:
      y2 = self.y + length
      self.item.set(y2 = y2)
      self.target_x = self.x
      self.target_y = y2
    elif self.orientation == 2:
      x1 = (self.x + self.w) - length
      self.item.set(x1 = x1)
      self.target_x = x1
      self.target_y = self.y

    # Calc a proportional red and green color
    color = 0L
    if counter <= self.winlimit:
      cg = 0xFF - min( 0xFF,
                       (counter * 0xFF) / self.winlimit)
      cg = max(cg, 0x50)
      cr = 0x12
    else:
      cg = 0x12
      cr = min( 0xFF,
                ((counter - self.winlimit) * 0xFF) / self.winlimit)
      cr += 0x90
      cr = min(0xFF, cr)

    color = self.color_done | (cg<<16) | (cr<<24)

    self.item.set(fill_color_rgba = color)

#
# The balloon display and it's motion
#
class Balloon:
  x = 0
  y = 0
  size = 0
  stopped = True
  item = 0
  timerinc = 20
  timer = 0
  need_reset = False

  def __init__(self, doubleclick, x, y):

    self.doubleclick = doubleclick
    self.rootitem = doubleclick.rootitem
    self.x = x
    self.y = y

    # Balloon shadow
    self.shadow = self.rootitem.add(
      gnomecanvas.CanvasPixbuf,
      pixbuf = gcompris.utils.load_pixmap("images/foot_shadow.png"),
      )

    # Balloon
    self.item = self.rootitem.add(
      gnomecanvas.CanvasPixbuf,
      pixbuf = gcompris.utils.load_pixmap("images/foot.png"),
      )
    # This item is clickeable and it must be seen
    self.item.connect("event", gcompris.utils.item_event_focus)

    bounds = self.item.get_bounds()
    self.size = bounds[2] - bounds[1]

  def reset(self):
    self.need_reset = False
    self.x = gcompris.BOARD_WIDTH/2
    self.y = gcompris.BOARD_HEIGHT - 115

    self.item.set(
      x = self.x - self.size/2,
      y = self.y - self.size/2,
      )

    self.shadow.set(
      x = self.x - self.size/2,
      y = self.y + self.size/2 - 5,
      )

    if self.timer:
      gobject.source_remove(self.timer)
    self.timer = 0


  def move_step(self):
    self.x -= self.dx
    self.y -= self.dy
    self.item.set(
      x = self.x - self.size/2,
      y = self.y - self.size/2,
      )
    self.step -= 1

    if self.step == 0:
      if self.win:
        gcompris.sound.play_ogg("sounds/bonus.wav")
        self.doubleclick.increment_level()
        self.doubleclick.next_level()
      else:
        gcompris.sound.play_ogg("sounds/tuxok.wav")

      return False

    return True


  # target: (win, X, Y) with win = True or False
  def move_to(self, target):
    if self.timer != 0:
      return

    self.need_reset = True
    gcompris.sound.play_ogg("sounds/brick.wav")

    self.win = target[0]
    target_x = target[1]
    target_y = target[2]
    if target[0] == False:
      target_x = gcompris.BOARD_WIDTH / 2
      target_y = 260

    self.step = 100.0
    self.dx = (self.x - target_x) / self.step
    self.dy = (self.y - target_y) / self.step

    self.timer  = gobject.timeout_add(self.timerinc,
                                      self.move_step)

