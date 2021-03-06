/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2007 by Jonathan Gordon
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

/* This file contains the code to draw the list widget on BITMAP LCDs. */

#include "config.h"
#include "lcd.h"
#include "font.h"
#include "button.h"
#include "string.h"
#include "settings.h"
#include "kernel.h"
#include "system.h"
#include "file.h"

#include "action.h"
#include "screen_access.h"
#include "list.h"
#include "scrollbar.h"
#include "lang.h"
#include "sound.h"
#include "misc.h"
#include "viewport.h"
#include "statusbar-skinned.h"
#include "debug.h"

#define ICON_PADDING 1

/* these are static to make scrolling work */
static struct viewport list_text[NB_SCREENS], title_text[NB_SCREENS];

#ifdef HAVE_TOUCHSCREEN
static enum {
    SCROLL_NONE,    /* no scrolling */
    SCROLL_BAR,     /* scroll by using the scrollbar */
    SCROLL_SWIPE,   /* scroll by wiping over the screen */
} scroll_mode;
#endif

int gui_list_get_item_offset(struct gui_synclist * gui_list, int item_width,
                             int text_pos, struct screen * display,
                             struct viewport *vp);
bool list_display_title(struct gui_synclist *list, enum screen_type screen);

void gui_synclist_scroll_stop(struct gui_synclist *lists)
{
    int i;
    FOR_NB_SCREENS(i)
    {
        screens[i].scroll_stop(&list_text[i]);
        screens[i].scroll_stop(&title_text[i]);
        screens[i].scroll_stop(lists->parent[i]);
    }
}

/* Draw the list...
    internal screen layout:
        -----------------
        |TI|  title     |   TI is title icon
        -----------------
        | | |            |
        |S|I|            |   S - scrollbar
        | | | items      |   I - icons
        | | |            |
        ------------------

        Note: This image is flipped horizontally when the language is a
        right-to-left one (Hebrew, Arabic)
*/
static bool draw_title(struct screen *display, struct gui_synclist *list)
{
    const int screen = display->screen_type;
    int style = STYLE_DEFAULT;
    struct viewport *title_text_vp = &title_text[screen];

    if (sb_set_title_text(list->title, list->title_icon, screen))
        return false; /* the sbs is handling the title */
    display->scroll_stop(title_text_vp);
    if (!list_display_title(list, screen))
        return false;
    *title_text_vp = *(list->parent[screen]);
    title_text_vp->height = font_get(title_text_vp->font)->height;

    if (list->title_icon != Icon_NOICON && global_settings.show_icons)
    {
        struct viewport title_icon = *title_text_vp;

        title_icon.width = get_icon_width(screen) + ICON_PADDING * 2;
        if (VP_IS_RTL(&title_icon))
        {
            title_icon.x += title_text_vp->width - title_icon.width;
        }
        else
        {
            title_text_vp->x += title_icon.width;
        }
        title_text_vp->width -= title_icon.width;

        display->set_viewport(&title_icon);
        screen_put_icon(display, 0, 0, list->title_icon);
    }
#ifdef HAVE_LCD_COLOR
    if (list->title_color >= 0)
    {
        style |= (STYLE_COLORED|list->title_color);
    }
#endif
    display->set_viewport(title_text_vp);
    display->puts_scroll_style(0, 0, list->title, style);
    return true;
}

void list_draw(struct screen *display, struct gui_synclist *list)
{
    struct viewport list_icons;
    int start, end, line_height, style, i;
    const int screen = display->screen_type;
    const int list_start_item = list->start_item[screen];
    const int icon_width = get_icon_width(screen) + ICON_PADDING;
    const bool scrollbar_in_left = (global_settings.scrollbar == SCROLLBAR_LEFT);
    const bool show_cursor = !global_settings.cursor_style &&
                        list->show_selection_marker;
    struct viewport *parent = (list->parent[screen]);
#ifdef HAVE_LCD_COLOR
    unsigned char cur_line = 0;
#endif
    int item_offset;
    bool show_title;
    struct viewport *list_text_vp = &list_text[screen];

    line_height = font_get(parent->font)->height;
    display->set_viewport(parent);
    display->clear_viewport();
    display->scroll_stop(list_text_vp);
    *list_text_vp = *parent;
    if ((show_title = draw_title(display, list)))
    {
        list_text_vp->y += line_height;
        list_text_vp->height -= line_height;
    }

    start = list_start_item;
    end = start + viewport_get_nb_lines(list_text_vp);

    /* draw the scrollbar if its needed */
    if (global_settings.scrollbar &&
        viewport_get_nb_lines(list_text_vp) < list->nb_items)
    {
        struct viewport vp;
        vp = *list_text_vp;
        vp.width = SCROLLBAR_WIDTH;
        vp.height = line_height * viewport_get_nb_lines(list_text_vp);
        vp.x = parent->x;
        list_text_vp->width -= SCROLLBAR_WIDTH;
        if (scrollbar_in_left)
            list_text_vp->x += SCROLLBAR_WIDTH;
        else
            vp.x += list_text_vp->width;
        display->set_viewport(&vp);
        gui_scrollbar_draw(display,
                (scrollbar_in_left? 0: 1), 0, SCROLLBAR_WIDTH-1, vp.height,
                list->nb_items, list_start_item, list_start_item + end-start,
                VERTICAL);
    }
    else if (show_title)
    {
        /* shift everything a bit in relation to the title... */
        if (!VP_IS_RTL(list_text_vp) && scrollbar_in_left)
        {
            list_text_vp->width -= SCROLLBAR_WIDTH;
            list_text_vp->x += SCROLLBAR_WIDTH;
        }
        else if (VP_IS_RTL(list_text_vp) && !scrollbar_in_left)
        {
            list_text_vp->width -= SCROLLBAR_WIDTH;
        }
    }

    /* setup icon placement */
    list_icons = *list_text_vp;
    int icon_count = (list->callback_get_item_icon != NULL) ? 1 : 0;
    if (show_cursor)
        icon_count++;
    if (icon_count)
    {
        list_icons.width = icon_width * icon_count;
        list_text_vp->width -= list_icons.width + ICON_PADDING;
        if (VP_IS_RTL(&list_icons))
            list_icons.x += list_text_vp->width + ICON_PADDING;
        else
            list_text_vp->x += list_icons.width + ICON_PADDING;
    }

    for (i=start; i<end && i<list->nb_items; i++)
    {
        /* do the text */
        unsigned const char *s;
        char entry_buffer[MAX_PATH];
        unsigned char *entry_name;
        int text_pos = 0;
        s = list->callback_get_item_name(i, list->data, entry_buffer,
                                         sizeof(entry_buffer));
        entry_name = P2STR(s);
        display->set_viewport(list_text_vp);
        style = STYLE_DEFAULT;
        /* position the string at the correct offset place */
        int item_width,h;
        display->getstringsize(entry_name, &item_width, &h);
        item_offset = gui_list_get_item_offset(list, item_width, text_pos,
                display, list_text_vp);

#ifdef HAVE_LCD_COLOR
        /* if the list has a color callback */
        if (list->callback_get_item_color)
        {
            int color = list->callback_get_item_color(i, list->data);
            /* if color selected */
            if (color >= 0)
            {
                style |= STYLE_COLORED|color;
            }
        }
#endif
        /* draw the selected line */
        if(
#ifdef HAVE_TOUCHSCREEN
            /* don't draw it during scrolling */
            scroll_mode == SCROLL_NONE &&
#endif
                i >= list->selected_item
                && i <  list->selected_item + list->selected_size
                && list->show_selection_marker)
        {/* The selected item must be displayed scrolling */
            if (global_settings.cursor_style == 1
#ifdef HAVE_REMOTE_LCD
                    /* the global_settings.cursor_style check is here to make
                    * sure if they want the cursor instead of bar it will work
                    */
                    || (display->depth < 16 && global_settings.cursor_style)
#endif
            )
            {
                /* Display inverted-line-style */
                style = STYLE_INVERT;
            }
#ifdef HAVE_LCD_COLOR
            else if (global_settings.cursor_style == 2)
            {
                /* Display colour line selector */
                style = STYLE_COLORBAR;
            }
            else if (global_settings.cursor_style == 3)
            {
                /* Display gradient line selector */
                style = STYLE_GRADIENT;

                /* Make the lcd driver know how many lines the gradient should
                   cover and current line number */
                /* number of selected lines */
                style |= NUMLN_PACK(list->selected_size);
                /* current line number, zero based */
                style |= CURLN_PACK(cur_line);
                cur_line++;
            }
#endif
            /* if the text is smaller than the viewport size */
            if (item_offset> item_width - (list_text_vp->width - text_pos))
            {
                /* don't scroll */
                display->puts_style_offset(0, i-start, entry_name,
                        style, item_offset);
            }
            else
            {
                display->puts_scroll_style_offset(0, i-start, entry_name,
                        style, item_offset);
            }
        }
        else
        {
            if (list->scroll_all)
                display->puts_scroll_style_offset(0, i-start, entry_name,
                        style, item_offset);
            else
                display->puts_style_offset(0, i-start, entry_name,
                        style, item_offset);
        }
        /* do the icon */
        display->set_viewport(&list_icons);
        if (list->callback_get_item_icon && global_settings.show_icons)
        {
            screen_put_icon_with_offset(display, show_cursor?1:0,
                                    (i-start),show_cursor?ICON_PADDING:0,0,
                                    list->callback_get_item_icon(i, list->data));
        }
        if (show_cursor && i >= list->selected_item &&
                i <  list->selected_item + list->selected_size)
        {
            screen_put_icon(display, 0, i-start, Icon_Cursor);
        }
    }
    display->set_viewport(parent);
    display->update_viewport();
    display->set_viewport(NULL);
}

#if defined(HAVE_TOUCHSCREEN)
/* This needs to be fixed if we ever get more than 1 touchscreen on a target. */

static bool released = false;

/* Used for kinetic scrolling as we need to know the last position to
 * recognize the scroll direction.
 * This gets reset to 0 at the end of scrolling
 */
static int last_position=0;


static int gui_synclist_touchscreen_scrollbar(struct gui_synclist * gui_list,
                                              int y)
{
    const int screen = screens[SCREEN_MAIN].screen_type;
    const int nb_lines = viewport_get_nb_lines(&list_text[screen]);

    if (nb_lines <  gui_list->nb_items)
    {
        scroll_mode = SCROLL_BAR;
        int scrollbar_size = nb_lines*
            font_get(gui_list->parent[screen]->font)->height;
        int actual_y = y - list_text[screen].y;

        int new_selection = (actual_y * gui_list->nb_items)
                / scrollbar_size;

        int start_item = new_selection - nb_lines/2;
        if(start_item < 0)
            start_item = 0;
        else if(start_item > gui_list->nb_items - nb_lines)
            start_item = gui_list->nb_items - nb_lines;

        gui_list->start_item[screen] = start_item;

        return ACTION_REDRAW;
    }

    return ACTION_NONE;
}

/*
 * returns the number of scrolled items since the last call
 **/
static int gui_synclist_touchscreen_scrolling(struct gui_synclist * gui_list, int position)
{
    const int screen = screens[SCREEN_MAIN].screen_type;
    const int difference = position - last_position;
    const int nb_lines = viewport_get_nb_lines(&list_text[screen]);
    if(nb_lines < gui_list->nb_items && difference != 0) /* only scroll if needed */
    {
        int new_start_item;
        new_start_item = gui_list->start_item[screen] - difference;
        /* check if new_start_item is bigger than list item count */
        if(new_start_item > gui_list->nb_items - nb_lines)
            new_start_item = gui_list->nb_items - nb_lines;
        /* set new_start_item to 0 if it's negative */
        if(new_start_item < 0)
            new_start_item = 0;
        gui_list->start_item[screen] = new_start_item;
    }
    return difference;
}

unsigned gui_synclist_do_touchscreen(struct gui_synclist * gui_list)
{
    short x, y;
    const int button = action_get_touchscreen_press(&x, &y);
    const int screen = SCREEN_MAIN;
    const int list_start_item = gui_list->start_item[screen];
    const struct viewport *list_text_vp = &list_text[screen];
    const bool old_released = released;
    int line, list_width = list_text_vp->width;

    /* make sure it is inside the UI viewport */    
    if (!viewport_point_within_vp(sb_skin_get_info_vp(screen), x, y))
        return BUTTON_NONE;

    released = (button&BUTTON_REL) != 0;

    if (global_settings.scrollbar == SCROLLBAR_RIGHT)
        list_width += SCROLLBAR_WIDTH;

    if (button == BUTTON_NONE)
        return ACTION_NONE;

    if (x > list_text_vp->x + list_width)
        return ACTION_NONE;

    if (list_display_title(gui_list, screen) &&
        viewport_point_within_vp(&title_text[screen], x, y) && 
        button == BUTTON_REL && scroll_mode == SCROLL_NONE)
        return ACTION_STD_CANCEL;

    if (x < list_text_vp->x)
    {
        /* Top left corner is GO_TO_ROOT */
        if (y<list_text[SCREEN_MAIN].y)
        {
            if (button == BUTTON_REL)
                return ACTION_STD_MENU;
            else if (button == (BUTTON_REPEAT|BUTTON_REL))
                return ACTION_STD_CONTEXT;
            else
                return ACTION_NONE;
        }
        /* Scroll bar */
        else if(global_settings.scrollbar == SCROLLBAR_LEFT)
            return gui_synclist_touchscreen_scrollbar(gui_list, y);
    }
    else
    {
        int line_height = font_get(gui_list->parent[screen]->font)->height;
        /* add a small margin to prevent accidental selection */
        int x_end = list_text_vp->x + list_text_vp->width - line_height;

        /* conditions for scrollbar scrolling:
         *    * pen is on the scrollbar (x > x_end-scrollbar width)
         *      AND scrollbar is on the right (left case is handled above)
         * OR * pen is in the somewhere else but we did scrollbar scrolling before
         *
         * scrollbar scrolling must end if the pen is released
         * scrollbar scrolling must not happen if we're currently scrolling
         * via swiping the screen
         **/

        if (!released && scroll_mode != SCROLL_SWIPE
            && ((scroll_mode == SCROLL_BAR
                || (x > x_end && global_settings.scrollbar == SCROLLBAR_RIGHT))))
        {
            return gui_synclist_touchscreen_scrollbar(gui_list, y);
        }

        /* |--------------------------------------------------------|
         * | Description of the touchscreen list interface:         |
         * |--------------------------------------------------------|
         * | Pressing an item will select it and "enter" it.        |
         * |                                                        |
         * | Pressing and holding your pen down will scroll through |
         * | the list of items.                                     |
         * |                                                        |
         * | Pressing and holding your pen down on a single item    |
         * | will bring up the context menu of it.                  |
         * |--------------------------------------------------------|
         */
        if (y > list_text_vp->y || button & BUTTON_REPEAT)
        {
            int actual_y;

            actual_y = y - list_text_vp->y;
            line = actual_y / line_height;
            
            /* Pressed below the list*/
            if (list_start_item + line >= gui_list->nb_items)
                return ACTION_NONE;
            
            /* Pressed a border */
            if(UNLIKELY(actual_y % line_height == 0))
                return ACTION_NONE;

            if (released)
            {
                /* Pen was released anywhere on the screen */
                last_position = 0;
                if (scroll_mode == SCROLL_NONE)
                {
                    gui_synclist_select_item(gui_list, list_start_item + line);
                    /* If BUTTON_REPEAT is set, then the pen was hold on
                     * the same line for some time
                     *  -> context menu
                     * otherwise,
                     *  -> select
                     **/
                    if (button & BUTTON_REPEAT)
                        return ACTION_STD_CONTEXT;
                    return ACTION_STD_OK;
                }
                else
                {
                    /* we were scrolling
                     *  -> reset scrolling but do nothing else */
                    scroll_mode = SCROLL_NONE;
                    return ACTION_NONE;
                }
            }
            else
            {   /* pen is on the screen */
                int result = 0;
                bool redraw = false;

                /* beginning of list interaction denoted by release in
                 * the previous call */
                if (old_released)
                {
                    scroll_mode = SCROLL_NONE;
                    redraw = true;
                }
                
                /* select current item */
                gui_synclist_select_item(gui_list, list_start_item+line);
                if (last_position == 0)
                    last_position = line;
                else
                    result = gui_synclist_touchscreen_scrolling(gui_list, line);

                /* Start scrolling once the pen is moved without
                 * releasing it inbetween */
                if (result)
                {
                    redraw = true;
                    scroll_mode = SCROLL_SWIPE;
                }

                last_position = line;

                return redraw ? ACTION_REDRAW:ACTION_NONE;
            }
        }
    }
    return ACTION_NONE;
}
#endif
