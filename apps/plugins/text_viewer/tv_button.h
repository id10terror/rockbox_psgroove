/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Gilles Roux
 *               2003 Garrett Derner
 *               2010 Yoshihisa Uchida
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/
#ifndef PLUGIN_TEXT_VIEWER_BUTTON_H
#define PLUGIN_TEXT_VIEWER_BUTTON_H

/* variable button definitions */

/*
 * [required]
 * TV_QUIT           exit txit viewer
 * TV_SCROLL_UP      scroll up
 * TV_SCROLL_DOWN    scroll down
 * TV_SCREEN_LEFT    scroll left (when wide mode)/scroll previous page (when narrow mode)
 * TV_SCREEN_RIGHT   scroll right (when wide mode)/scroll next page (when narrow mode)
 * TV_MENU           enter menu
 * TV_AUTOSCROLL     toggle autoscroll
 * TV_BOOKMARK       set/reset bookmark
 *
 * [optional]
 * TV_RC_QUIT        exit text plugin (remote key only)
 * TV_LINE_UP        one line up
 * TV_LINE_DOWN      one line down
 * TV_COLUMN_LEFT    one column left
 * TV_COLUMN_RIGHT   one column right
 */

/* Recorder keys */
#if CONFIG_KEYPAD == RECORDER_PAD
#define TV_QUIT         BUTTON_OFF
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_F1
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_LINE_UP      (BUTTON_ON | BUTTON_UP)
#define TV_LINE_DOWN    (BUTTON_ON | BUTTON_DOWN)
#define TV_COLUMN_LEFT  (BUTTON_ON | BUTTON_LEFT)
#define TV_COLUMN_RIGHT (BUTTON_ON | BUTTON_RIGHT)
#define TV_BOOKMARK     BUTTON_F2

/* Archos AV300 keys */
#elif CONFIG_KEYPAD == ARCHOS_AV300_PAD
#define TV_QUIT         BUTTON_OFF
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_F1
#define TV_AUTOSCROLL   BUTTON_SELECT
#define TV_LINE_UP      (BUTTON_ON | BUTTON_UP)
#define TV_LINE_DOWN    (BUTTON_ON | BUTTON_DOWN)
#define TV_COLUMN_LEFT  (BUTTON_ON | BUTTON_LEFT)
#define TV_COLUMN_RIGHT (BUTTON_ON | BUTTON_RIGHT)
#define TV_BOOKMARK     BUTTON_F2

/* Ondio keys */
#elif CONFIG_KEYPAD == ONDIO_PAD
#define TV_QUIT           BUTTON_OFF
#define TV_SCROLL_UP      BUTTON_UP
#define TV_SCROLL_DOWN    BUTTON_DOWN
#define TV_SCREEN_LEFT    BUTTON_LEFT
#define TV_SCREEN_RIGHT   BUTTON_RIGHT
#define TV_MENU           (BUTTON_MENU|BUTTON_REPEAT)
#define TV_AUTOSCROLL_PRE BUTTON_MENU
#define TV_AUTOSCROLL     (BUTTON_MENU|BUTTON_REL)
#define TV_BOOKMARK       (BUTTON_MENU|BUTTON_OFF)

/* Player keys */
#elif CONFIG_KEYPAD == PLAYER_PAD
#define TV_QUIT         BUTTON_STOP
#define TV_SCROLL_UP    BUTTON_LEFT
#define TV_SCROLL_DOWN  BUTTON_RIGHT
#define TV_SCREEN_LEFT  (BUTTON_ON|BUTTON_LEFT)
#define TV_SCREEN_RIGHT (BUTTON_ON|BUTTON_RIGHT)
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_BOOKMARK     BUTTON_ON

/* iRiver H1x0 && H3x0 keys */
#elif (CONFIG_KEYPAD == IRIVER_H100_PAD) || \
      (CONFIG_KEYPAD == IRIVER_H300_PAD)
#define TV_QUIT         BUTTON_OFF
#define TV_RC_QUIT      BUTTON_RC_STOP
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_MODE
#define TV_AUTOSCROLL   BUTTON_SELECT
#define TV_LINE_UP      (BUTTON_ON | BUTTON_UP)
#define TV_LINE_DOWN    (BUTTON_ON | BUTTON_DOWN)
#define TV_COLUMN_LEFT  (BUTTON_ON | BUTTON_LEFT)
#define TV_COLUMN_RIGHT (BUTTON_ON | BUTTON_RIGHT)
#define TV_BOOKMARK     (BUTTON_ON | BUTTON_SELECT)

/* iPods */
#elif (CONFIG_KEYPAD == IPOD_4G_PAD) || \
      (CONFIG_KEYPAD == IPOD_3G_PAD) || \
      (CONFIG_KEYPAD == IPOD_1G2G_PAD)
#define TV_QUIT_PRE     BUTTON_SELECT
#define TV_QUIT         (BUTTON_SELECT | BUTTON_MENU)
#define TV_SCROLL_UP    BUTTON_SCROLL_BACK
#define TV_SCROLL_DOWN  BUTTON_SCROLL_FWD
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_BOOKMARK     BUTTON_SELECT

/* iFP7xx keys */
#elif CONFIG_KEYPAD == IRIVER_IFP7XX_PAD
#define TV_QUIT         BUTTON_PLAY
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_MODE
#define TV_AUTOSCROLL   BUTTON_SELECT
#define TV_BOOKMARK     (BUTTON_LEFT|BUTTON_SELECT)

/* iAudio X5 keys */
#elif CONFIG_KEYPAD == IAUDIO_X5M5_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_SELECT
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_BOOKMARK     BUTTON_REC

/* GIGABEAT keys */
#elif CONFIG_KEYPAD == GIGABEAT_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL_PRE BUTTON_A
#define TV_AUTOSCROLL   (BUTTON_A|BUTTON_REL)
#define TV_LINE_UP      (BUTTON_A|BUTTON_UP)
#define TV_LINE_DOWN    (BUTTON_A|BUTTON_DOWN)
#define TV_COLUMN_LEFT  (BUTTON_A|BUTTON_LEFT)
#define TV_COLUMN_RIGHT (BUTTON_A|BUTTON_RIGHT)
#define TV_BOOKMARK     BUTTON_SELECT

/* Sansa E200 keys */
#elif CONFIG_KEYPAD == SANSA_E200_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_SELECT
#define TV_AUTOSCROLL   BUTTON_REC
#define TV_LINE_UP      BUTTON_SCROLL_BACK
#define TV_LINE_DOWN    BUTTON_SCROLL_FWD
#define TV_BOOKMARK     (BUTTON_DOWN|BUTTON_SELECT)

/* Sansa Fuze keys */
#elif CONFIG_KEYPAD == SANSA_FUZE_PAD
#define TV_QUIT         (BUTTON_HOME|BUTTON_REPEAT)
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_SELECT|BUTTON_REPEAT
#define TV_AUTOSCROLL   BUTTON_SELECT|BUTTON_DOWN
#define TV_LINE_UP      BUTTON_SCROLL_BACK
#define TV_LINE_DOWN    BUTTON_SCROLL_FWD
#define TV_BOOKMARK     BUTTON_SELECT

/* Sansa C200 keys */
#elif CONFIG_KEYPAD == SANSA_C200_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_VOL_UP
#define TV_SCROLL_DOWN  BUTTON_VOL_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_SELECT
#define TV_AUTOSCROLL   BUTTON_REC
#define TV_LINE_UP      BUTTON_UP
#define TV_LINE_DOWN    BUTTON_DOWN
#define TV_BOOKMARK     (BUTTON_DOWN | BUTTON_SELECT)

/* Sansa Clip keys */
#elif CONFIG_KEYPAD == SANSA_CLIP_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_VOL_UP
#define TV_SCROLL_DOWN  BUTTON_VOL_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_SELECT
#define TV_AUTOSCROLL   BUTTON_HOME
#define TV_LINE_UP      BUTTON_UP
#define TV_LINE_DOWN    BUTTON_DOWN
#define TV_BOOKMARK     (BUTTON_DOWN|BUTTON_SELECT)

/* Sansa M200 keys */
#elif CONFIG_KEYPAD == SANSA_M200_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_VOL_UP
#define TV_SCROLL_DOWN  BUTTON_VOL_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         (BUTTON_SELECT | BUTTON_UP)
#define TV_AUTOSCROLL   (BUTTON_SELECT | BUTTON_REL)
#define TV_LINE_UP      BUTTON_UP
#define TV_LINE_DOWN    BUTTON_DOWN
#define TV_BOOKMARK     (BUTTON_DOWN|BUTTON_SELECT)

/* iriver H10 keys */
#elif CONFIG_KEYPAD == IRIVER_H10_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_SCROLL_UP
#define TV_SCROLL_DOWN  BUTTON_SCROLL_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_REW
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_BOOKMARK     BUTTON_FF

/*M-Robe 500 keys */
#elif CONFIG_KEYPAD == MROBE500_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_RC_PLAY
#define TV_SCROLL_DOWN  BUTTON_RC_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_RC_HEART
#define TV_AUTOSCROLL   BUTTON_RC_MODE
#define TV_BOOKMARK     BUTTON_CENTER

/*Gigabeat S keys */
#elif CONFIG_KEYPAD == GIGABEAT_S_PAD
#define TV_QUIT           BUTTON_BACK
#define TV_SCROLL_UP      BUTTON_PREV
#define TV_SCROLL_DOWN    BUTTON_NEXT
#define TV_SCREEN_LEFT    (BUTTON_PLAY | BUTTON_LEFT)
#define TV_SCREEN_RIGHT   (BUTTON_PLAY | BUTTON_RIGHT)
#define TV_MENU           BUTTON_MENU
#define TV_AUTOSCROLL_PRE BUTTON_PLAY
#define TV_AUTOSCROLL     (BUTTON_PLAY|BUTTON_REL)
#define TV_LINE_UP        BUTTON_UP
#define TV_LINE_DOWN      BUTTON_DOWN
#define TV_COLUMN_LEFT    BUTTON_LEFT
#define TV_COLUMN_RIGHT   BUTTON_RIGHT
#define TV_BOOKMARK       BUTTON_SELECT

/*M-Robe 100 keys */
#elif CONFIG_KEYPAD == MROBE100_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL   BUTTON_DISPLAY
#define TV_BOOKMARK     BUTTON_SELECT

/* iAUdio M3 keys */
#elif CONFIG_KEYPAD == IAUDIO_M3_PAD
#define TV_QUIT         BUTTON_REC
#define TV_RC_QUIT      BUTTON_RC_REC
#define TV_SCROLL_UP    BUTTON_RC_VOL_UP
#define TV_SCROLL_DOWN  BUTTON_RC_VOL_DOWN
#define TV_SCREEN_LEFT  BUTTON_RC_REW
#define TV_SCREEN_RIGHT BUTTON_RC_FF
#define TV_MENU         BUTTON_RC_MENU
#define TV_AUTOSCROLL   BUTTON_RC_MODE
#define TV_BOOKMARK     BUTTON_RC_PLAY

/* Cowon D2 keys */
#elif CONFIG_KEYPAD == COWON_D2_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_MENU         BUTTON_MENU
#define TV_SCROLL_UP    BUTTON_MINUS
#define TV_SCROLL_DOWN  BUTTON_PLUS
#define TV_BOOKMARK     (BUTTON_MENU|BUTTON_PLUS)

#elif CONFIG_KEYPAD == IAUDIO67_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_VOLUP
#define TV_SCROLL_DOWN  BUTTON_VOLDOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_RC_QUIT      BUTTON_STOP
#define TV_BOOKMARK     (BUTTON_LEFT|BUTTON_PLAY)

/* Creative Zen Vision:M keys */
#elif CONFIG_KEYPAD == CREATIVEZVM_PAD
#define TV_QUIT         BUTTON_BACK
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL   BUTTON_SELECT
#define TV_BOOKMARK     BUTTON_PLAY

/* Philips HDD1630 keys */
#elif CONFIG_KEYPAD == PHILIPS_HDD1630_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL   BUTTON_VIEW
#define TV_BOOKMARK     BUTTON_SELECT

/* Philips SA9200 keys */
#elif CONFIG_KEYPAD == PHILIPS_SA9200_PAD
#define TV_QUIT         BUTTON_POWER
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_PREV
#define TV_SCREEN_RIGHT BUTTON_NEXT
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_BOOKMARK     BUTTON_RIGHT

/* Onda VX747 keys */
#elif CONFIG_KEYPAD == ONDAVX747_PAD
#define TV_QUIT BUTTON_POWER
#define TV_MENU BUTTON_MENU
#define TV_BOOKMARK (BUTTON_RIGHT|BUTTON_POWER)

/* Onda VX777 keys */
#elif CONFIG_KEYPAD == ONDAVX777_PAD
#define TV_QUIT BUTTON_POWER
#define TV_BOOKMARK (BUTTON_RIGHT|BUTTON_POWER)

/* SAMSUNG YH-820 / YH-920 / YH-925 keys */
#elif CONFIG_KEYPAD == SAMSUNG_YH_PAD
#define TV_QUIT         BUTTON_REC
#define TV_SCROLL_UP    BUTTON_UP
#define TV_SCROLL_DOWN  BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_LEFT
#define TV_SCREEN_RIGHT BUTTON_RIGHT
#define TV_MENU         BUTTON_PLAY
#define TV_AUTOSCROLL   BUTTON_REW
#define TV_BOOKMARK     BUTTON_FFWD

/* Packard Bell Vibe 500 keys */
#elif CONFIG_KEYPAD == PBELL_VIBE500_PAD
#define TV_QUIT         BUTTON_REC
#define TV_SCROLL_UP    BUTTON_OK
#define TV_SCROLL_DOWN  BUTTON_CANCEL
#define TV_LINE_UP      BUTTON_UP
#define TV_LINE_DOWN    BUTTON_DOWN
#define TV_SCREEN_LEFT  BUTTON_PREV
#define TV_SCREEN_RIGHT BUTTON_NEXT
#define TV_MENU         BUTTON_MENU
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_BOOKMARK     BUTTON_POWER

/* MPIO HD200 keys */
#elif CONFIG_KEYPAD == MPIO_HD200_PAD
#define TV_QUIT         (BUTTON_REC | BUTTON_PLAY)
#define TV_SCROLL_UP    BUTTON_PREV
#define TV_SCROLL_DOWN  BUTTON_NEXT
#define TV_SCREEN_LEFT  BUTTON_VOL_DOWN
#define TV_SCREEN_RIGHT BUTTON_VOL_UP
#define TV_MENU         BUTTON_SELECT
#define TV_AUTOSCROLL   BUTTON_PLAY
#define TV_BOOKMARK     BUTTON_REC

#else
#error No keymap defined!
#endif

#ifdef HAVE_TOUCHSCREEN
#ifdef TV_QUIT
#define TV_QUIT2        BUTTON_TOPLEFT
#else
#define TV_QUIT         BUTTON_TOPLEFT
#endif
#ifdef TV_SCROLL_UP
#define TV_SCROLL_UP2   BUTTON_TOPMIDDLE
#else
#define TV_SCROLL_UP    BUTTON_TOPMIDDLE
#endif
#ifdef TV_SCROLL_DOWN
#define TV_SCROLL_DOWN2 BUTTON_BOTTOMMIDDLE
#else
#define TV_SCROLL_DOWN  BUTTON_BOTTOMMIDDLE
#endif
#ifndef TV_SCREEN_LEFT
#define TV_SCREEN_LEFT  BUTTON_MIDLEFT
#endif
#ifndef TV_SCREEN_RIGHT
#define TV_SCREEN_RIGHT BUTTON_MIDRIGHT
#endif
#ifdef TV_MENU
#define TV_MENU2        BUTTON_TOPRIGHT
#else
#define TV_MENU         BUTTON_TOPRIGHT
#endif
#ifndef TV_AUTOSCROLL
#define TV_AUTOSCROLL   BUTTON_CENTER
#endif
#endif

#endif
