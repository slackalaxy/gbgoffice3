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

#ifndef GBGOFFICE_PREFS_DIALOG_H
#define GBGOFFICE_PREFS_DIALOG_H

#include <gtkmm/stock.h>
#include <gtkmm/grid.h>
#include <gtkmm/notebook.h>
#include <gtkmm/dialog.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>


class GbgofficePrefs : public Gtk::Dialog
{

public:
	GbgofficePrefs();
	virtual ~GbgofficePrefs();

protected:
	// Signal handlers
	virtual void on_save_button();
	virtual void something_changed();
	virtual void use_tray_changed();
	virtual void use_clip_changed();
	
	// Child widgets
	Gtk::Box *vbox;
	Gtk::Grid tbl1, tbl2;
	Gtk::Notebook notebook;
	Gtk::Button *button_close, *button_save;
	Gtk::Label lbl1, spacer;
	Glib::RefPtr<Gtk::Adjustment> words_num_a;
	Gtk::SpinButton words_num;
	Gtk::CheckButton use_clp;
	
#ifndef ENABLE_LIGHT_VERSION
	Gtk::Label lbl2;
	Gtk::CheckButton use_wh;
	Glib::RefPtr<Gtk::Adjustment> wh_seconds_a;
	Gtk::SpinButton wh_seconds;
#endif
	
#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	Gtk::Label helpmsg;
	Gtk::CheckButton use_tr;
	Gtk::CheckButton use_tr_close;
	Gtk::CheckButton tr_hide_os;
#endif

};


#endif	// GBGOFFICE_PREFS_DIALOG_H
