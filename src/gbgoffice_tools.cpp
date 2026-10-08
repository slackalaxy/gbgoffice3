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

#include "gbgoffice_tools.h"
#include "defaults.h"
#include <iostream>
#include <cstdio>

#define TMP_STR_SIZE	20


GbgofficeTools::GbgofficeTools()
{
	try {
		smile_ok = Gdk::Pixbuf::create_from_file(std::string(FILES_DIR) + "gbgoffice-smile.png");
		smile_neok = Gdk::Pixbuf::create_from_file(std::string(FILES_DIR) + "gbgoffice-neutral.png");
		smile_nok = Gdk::Pixbuf::create_from_file(std::string(FILES_DIR) + "gbgoffice-sad.png");
	}
	catch (Glib::FileError er) {
		switch (er.code()) {
			case Glib::FileError::NO_SUCH_ENTITY:
				std::cout << "Some important files are missing!" << std::endl;
				std::cout << "Did you type 'make install' before running gbgoffice?" << std::endl;
				break;
			default:
				std::cout << "Some important files are missing or unaccessible!" << std::endl;
		}
		exit(1);
	}

}

GbgofficeTools::~GbgofficeTools()
{
}


const char *GbgofficeTools::to_cp1251(Glib::ustring str)
{
	// keep the converted string alive: returning c_str() of a temporary
	// would hand the caller a dangling pointer
	cp1251_buf = Glib::convert(str, "WINDOWS-1251", "UTF-8");
	return cp1251_buf.c_str();
}

const Glib::ustring GbgofficeTools::to_utf8(char *str)
{
	return Glib::convert(str, "UTF-8", "WINDOWS-1251");
}

const Glib::ustring GbgofficeTools::to_utf8(std::string str)
{
	return Glib::convert(str, "UTF-8", "WINDOWS-1251");
}


Gtk::MenuItem *GbgofficeTools::append_stock_item(Gtk::MenuShell &menu, const Gtk::StockID &id,
		const sigc::slot<void> &slot)
{
	Gtk::MenuItem *item = Gtk::manage(new Gtk::ImageMenuItem(id));
	item->signal_activate().connect(slot);
	menu.append(*item);
	item->show();
	return item;
}

Gtk::MenuItem *GbgofficeTools::append_item(Gtk::MenuShell &menu, const Glib::ustring &label,
		const sigc::slot<void> &slot)
{
	Gtk::MenuItem *item = Gtk::manage(new Gtk::MenuItem(label, true));
	item->signal_activate().connect(slot);
	menu.append(*item);
	item->show();
	return item;
}

Gtk::MenuItem *GbgofficeTools::append_submenu(Gtk::MenuShell &menu, const Glib::ustring &label,
		Gtk::Menu &submenu)
{
	Gtk::MenuItem *item = Gtk::manage(new Gtk::MenuItem(label, true));
	item->set_submenu(submenu);
	menu.append(*item);
	item->show();
	return item;
}

void GbgofficeTools::append_separator(Gtk::MenuShell &menu)
{
	Gtk::SeparatorMenuItem *sep = Gtk::manage(new Gtk::SeparatorMenuItem());
	menu.append(*sep);
	sep->show();
}


void grid_attach(Gtk::Grid &grid, Gtk::Widget &child, int left, int right,
		int top, int bottom, bool hexpand, bool hfill, int pad)
{
	child.set_margin_start(pad);
	child.set_margin_end(pad);
	child.set_margin_top(pad);
	child.set_margin_bottom(pad);
	child.set_hexpand(hexpand);
	// a Gtk::Table child without FILL is centered in its cell
	child.set_halign(hfill ? Gtk::ALIGN_FILL : Gtk::ALIGN_CENTER);
	grid.attach(child, left, top, right - left, bottom - top);
}


Glib::ustring& operator<<(Glib::ustring& str, int i)
{
	char s[TMP_STR_SIZE];
	snprintf(s, TMP_STR_SIZE - 1, "%d", i);
	str += s;
	return str;	
}

Glib::ustring& operator<<(Glib::ustring& str, double f)
{
	char s[TMP_STR_SIZE];
	snprintf(s, TMP_STR_SIZE - 1, "%f", f);
	str += s;	
	return str;	
}

Glib::ustring& operator<<(Glib::ustring& str, const char *s)
{
	str += s;	
	return str;
}

Glib::ustring& operator<<(Glib::ustring& str, Glib::ustring s)
{
	str += s;	
	return str;
}
