/*************************************************************************
*
* Gbgoffice
* Copyright (C) 2004-2005 Miroslav Yordanov <mironcho@linux-bg.org>
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

#ifndef GBGOFFICE_WORK_HELPER_H
#define GBGOFFICE_WORK_HELPER_H

#ifndef ENABLE_LIGHT_VERSION

#include <gtkmm.h>


class WorkHelper: public Gtk::Dialog
{

public:
	WorkHelper();
	~WorkHelper();
	
	void show_help();
	void hide_help();
	void init(Gtk::Window &win, Glib::RefPtr<Gtk::TextBuffer> tbuf);
	void init_tray(Glib::RefPtr<Gtk::StatusIcon> icon, Glib::RefPtr<Gtk::TextBuffer> tbuf);
	void set_win(Gtk::Window &win);
	void set_textbuf(Glib::RefPtr<Gtk::TextBuffer> tbuf);
	void set_hide_timeout(unsigned int);
	unsigned int get_hide_timeout();
	
	bool is_ok();
	void set_state(bool state);
	
private:
	virtual bool on_wait_timeout();
	virtual bool on_my_enter_notify_event(GdkEventCrossing* event);
	virtual bool on_my_leave_notify_event(GdkEventCrossing* event);
	virtual bool on_my_motion_notify_event(GdkEventProperty* event);
	void waiting_connect();
	void waiting_disconnect();
	bool helper_reset_size();
	
	Gtk::Window *opw;
	Glib::RefPtr<Gtk::StatusIcon> status_icon;
	Gtk::Box *vbox;
	Gtk::TextView textarea;
	Gtk::ScrolledWindow scwin;
	sigc::connection con_wait;
	
	unsigned int hide_timeout;
	unsigned int sizex, sizey;
	
	bool ok;

};

#endif	/* ENABLE_LIGHT_VERSION */

#endif	/* GBGOFFICE_WORK_HELPER_H */
