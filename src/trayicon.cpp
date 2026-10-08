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

#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)

#include "trayicon.h"
#include "dictgui.h"
#include "defaults.h"
#include <iostream>


TrayIcon::TrayIcon(DictGui *win)
:	mainwin(win)
{
	icon = Gtk::StatusIcon::create_from_file(std::string(FILES_DIR) + "gbgoffice-tray.png");
	icon->set_tooltip_text("gbgoffice");
	
	// left click
	icon->signal_activate().connect(sigc::mem_fun(*this, &TrayIcon::on_activate));
	// right click
	icon->signal_popup_menu().connect(sigc::mem_fun(*this, &TrayIcon::on_popup_menu));
	icon->set_visible(true);
	
	// pop up menu
	append_stock_item(popupmenu, Gtk::Stock::PREFERENCES, 
			sigc::mem_fun(*this, &TrayIcon::on_menu_preferences));
	append_stock_item(popupmenu, Gtk::Stock::HELP, 
			sigc::mem_fun(*this, &TrayIcon::on_menu_help));
	append_stock_item(popupmenu, Gtk::Stock::DIALOG_INFO,
			sigc::mem_fun(*this, &TrayIcon::on_menu_info));
	
	append_separator(popupmenu);
	append_stock_item(popupmenu, Gtk::Stock::QUIT,
			sigc::mem_fun(*this, &TrayIcon::on_menu_quit));
}

TrayIcon::~TrayIcon()
{	
}

Glib::RefPtr<Gtk::StatusIcon> TrayIcon::getStatusIcon()
{
	return icon;
}

void TrayIcon::on_activate()
{
	if (mainwin->win.is_visible()) {
		mainwin->win.hide();
	} else {
		mainwin->win.show();
	}
}

void TrayIcon::on_popup_menu(guint button, guint32 activate_time)
{
	icon->popup_menu_at_position(popupmenu, button, activate_time);
}


void TrayIcon::on_menu_quit()
{
	// the tray icon used to be a window whose hiding ended the main loop
	Gtk::Main::quit();
}


void TrayIcon::on_menu_preferences()
{
	mainwin->on_menu_preferences();
}


void TrayIcon::on_menu_help()
{
	// show main window before put help into it
	mainwin->win.show();
	mainwin->on_menu_help();
}


void TrayIcon::on_menu_info()
{
	mainwin->on_menu_info();
}

#endif
