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

#ifndef GBGOFFICE_TOOLS_H
#define GBGOFFICE_TOOLS_H

#include <gtkmm.h>
#include "translator_manager.h"


Glib::ustring& operator<<(Glib::ustring& str, int i);
Glib::ustring& operator<<(Glib::ustring& str, double f);
Glib::ustring& operator<<(Glib::ustring& str, const char *s);
Glib::ustring& operator<<(Glib::ustring& str, Glib::ustring s);

// Replacement for the Gtk::Table::attach(child, left, right, top, bottom,
// xoptions, yoptions, xpadding, ypadding) calls: Gtk::Table is deprecated,
// Gtk::Grid is its successor. hexpand/hfill mirror Gtk::EXPAND / Gtk::FILL.
void grid_attach(Gtk::Grid &grid, Gtk::Widget &child, int left, int right,
		int top, int bottom, bool hexpand, bool hfill, int pad = 3);


class GbgofficeTools
{

public:
	GbgofficeTools();
	virtual ~GbgofficeTools();

	const char *to_cp1251(Glib::ustring str);
	const Glib::ustring to_utf8(char *str);
	const Glib::ustring to_utf8(std::string str);

	// menu helpers (gtkmm 3 has no Menu_Helpers / Menu::items() any more)
	Gtk::MenuItem *append_stock_item(Gtk::MenuShell &menu, const Gtk::StockID &id,
			const sigc::slot<void> &slot);
	Gtk::MenuItem *append_item(Gtk::MenuShell &menu, const Glib::ustring &label,
			const sigc::slot<void> &slot);
	Gtk::MenuItem *append_submenu(Gtk::MenuShell &menu, const Glib::ustring &label,
			Gtk::Menu &submenu);
	void append_separator(Gtk::MenuShell &menu);

	Glib::RefPtr<Gdk::Pixbuf> smile_ok;
	Glib::RefPtr<Gdk::Pixbuf> smile_nok;
	Glib::RefPtr<Gdk::Pixbuf> smile_neok;

private:
	std::string cp1251_buf;	// storage for to_cp1251() result
	
};	


#endif	// GBGOFFICE_TOOLS_H
