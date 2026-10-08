/*************************************************************************
*
* Gbgoffice
* Copyright (C) 2004 Miroslav Yordanov <mironcho@linux-bg.org>
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

#ifndef GBGOFFICE_TRAY_ICON_H
#define GBGOFFICE_TRAY_ICON_H

#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)

#include <gtkmm.h>
#include "gbgoffice_tools.h"
#include "language_tools.h"

class DictGui;

// The tray icon is now a Gtk::StatusIcon. The old EggTrayIcon (a GtkPlug
// speaking the X11 system tray protocol directly) cannot be built with GTK 3.
class TrayIcon: public GbgofficeTools
{

public:
	TrayIcon(DictGui *win);
	~TrayIcon();

	Glib::RefPtr<Gtk::StatusIcon> getStatusIcon();

private:
	void on_activate();
	void on_popup_menu(guint button, guint32 activate_time);
	virtual void on_menu_quit();
	virtual void on_menu_preferences();
	virtual void on_menu_help();
	virtual void on_menu_info();


	DictGui *mainwin;
	Glib::RefPtr<Gtk::StatusIcon> icon;
	Gtk::Menu popupmenu;

};

#endif

#endif	/* GBGOFFICE_TRAY_ICON_H */
