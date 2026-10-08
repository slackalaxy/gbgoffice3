/*************************************************************************
*
* Gbgoffice
* Copyright (C) 2004-2006 Miroslav Yordanov <mironcho@linux-bg.org>
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
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*************************************************************************/

#ifndef ENABLE_LIGHT_VERSION

#include "workhelper.h"
#include <iostream>


WorkHelper::WorkHelper()
:	opw(NULL),
	hide_timeout(4),
	sizex(250),
	sizey(150),
	ok(false)
{
	set_default_size(sizex, sizey);
	//set_position(Gtk::WIN_POS_CENTER_ON_PARENT);
	set_decorated(false);
	set_modal(false);
	//set_resize_mode(Gtk::RESIZE_PARENT);

	Gtk::Box *hba = get_action_area();

	add_events(Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK);
	
	vbox = get_content_area();
	vbox->add(scwin);
	
	textarea.set_editable(false);
	textarea.set_wrap_mode(Gtk::WRAP_WORD);
	textarea.set_indent(4);
	scwin.add(textarea);
	scwin.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
	

	//textarea.signal_enter_notify_event().connect(
	//		sigc::mem_fun(*this, &WorkHelper::on_my_enter_notify_event));
	//textarea.signal_leave_notify_event().connect(
	//		sigc::mem_fun(*this, &WorkHelper::on_my_leave_notify_event));
	


	signal_enter_notify_event().connect(
			sigc::mem_fun(*this, &WorkHelper::on_my_enter_notify_event));
	signal_leave_notify_event().connect(
			sigc::mem_fun(*this, &WorkHelper::on_my_leave_notify_event));

	scwin.signal_property_notify_event().connect(
			sigc::mem_fun(*this, &WorkHelper::on_my_motion_notify_event));


	show_all_children();
	hba->hide();
}

WorkHelper::~WorkHelper()
{	
}


void WorkHelper::show_help()
{
	int x, y;

	if (!ok) {
		// not running or disabled
		return;
	}
	
	hide_help();

	bool placed = false;

	if (status_icon) {
		// popup near the tray icon
		Glib::RefPtr<Gdk::Screen> screen;
		Gdk::Rectangle area;
		Gtk::Orientation orientation;

		if (status_icon->get_geometry(screen, area, orientation)) {
			set_position(Gtk::WIN_POS_NONE);
			move(area.get_x() - sizex, area.get_y() - sizey);
			placed = true;
		}
	} else if (opw) {
		opw->set_gravity(Gdk::GRAVITY_STATIC);
		opw->get_position(x, y);
		opw->set_gravity(Gdk::GRAVITY_NORTH_WEST);

		set_position(Gtk::WIN_POS_NONE);
		move(x - sizex, y - sizey);
		placed = true;
	}

	if (!placed) {
		// the tray did not tell us where it is (not embedded, no geometry)
		set_position(Gtk::WIN_POS_MOUSE);
	}
	
	waiting_connect();
	show_all_children();
	resize(sizex, sizey);
	present();
}

void WorkHelper::hide_help()
{
	waiting_disconnect();
	hide();
}

bool WorkHelper::is_ok()
{
	return ok;
}

void WorkHelper::set_state(bool state = true)
{
	ok = state;
}

void WorkHelper::init(Gtk::Window &win, Glib::RefPtr<Gtk::TextBuffer> tbuf)
{
	//set_transient_for(win);
	opw = &win;
	status_icon.reset();
	textarea.set_buffer(tbuf);
	
	ok = true;
}

// like init(), but the popup is positioned next to the tray icon
void WorkHelper::init_tray(Glib::RefPtr<Gtk::StatusIcon> icon, Glib::RefPtr<Gtk::TextBuffer> tbuf)
{
	opw = NULL;
	status_icon = icon;
	textarea.set_buffer(tbuf);
	
	ok = true;
}

void WorkHelper::set_win(Gtk::Window &win)
{
	set_transient_for(win);
}

void WorkHelper::set_textbuf(Glib::RefPtr<Gtk::TextBuffer> tbuf)
{
	textarea.set_buffer(tbuf);
}

inline void WorkHelper::waiting_connect()
{
	waiting_disconnect();
	con_wait = Glib::signal_timeout().connect(
			sigc::mem_fun(*this, &WorkHelper::on_wait_timeout), hide_timeout * 1000);
}

inline void WorkHelper::waiting_disconnect()
{
	if (con_wait.connected()) {
		con_wait.disconnect();
	}
}

void WorkHelper::set_hide_timeout(unsigned int i)
{
	hide_timeout = i;
}

unsigned int WorkHelper::get_hide_timeout()
{
	return hide_timeout;
}


bool WorkHelper::on_wait_timeout()
{
	hide_help(); 
	return false;
}

bool WorkHelper::on_my_enter_notify_event(GdkEventCrossing* event)
{
	waiting_disconnect();
	return false;
}

bool WorkHelper::on_my_leave_notify_event(GdkEventCrossing* event)
{
	waiting_connect();
	return false;
}

bool WorkHelper::on_my_motion_notify_event(GdkEventProperty* event)
{
	waiting_disconnect();
	return false;
}

bool WorkHelper::helper_reset_size()
{
	check_resize();
	return true;
}


#endif	/* ENABLE_LIGHT_VERSION */
