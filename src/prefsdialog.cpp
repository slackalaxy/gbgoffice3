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

#include "properties.h"
#include "defaults.h"
#include "language_tools.h"
#include "prefsdialog.h"
#include "gbgoffice_tools.h"


extern Properties *cfg;
extern bool lang;

GbgofficePrefs::GbgofficePrefs()
:	lbl1(LT_(GUI_PREFS_NUM_WORDS)),
	words_num_a(Gtk::Adjustment::create(1.0, 10.0, 500.0, 5.0, 5.0, 0.0)),
	words_num(words_num_a),
	spacer(" "),
#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	use_tr(LT_(GUI_PREFS_USE_TRAYICON)),
	use_tr_close(LT_(GUI_PREFS_USE_TRAYICON_CLOSE)),
	tr_hide_os(LT_(GUI_PREFS_TRAYICON_HIDE_ON_START)),
#endif
#ifndef ENABLE_LIGHT_VERSION
	lbl2(LT_(GUI_PREFS_WH_SECONDS)),
	use_wh(LT_(GUI_PREFS_USE_WH)),
	wh_seconds_a(Gtk::Adjustment::create(2.0, 1.0, 100.0, 1.0, 1.0, 0.0)),
	wh_seconds(wh_seconds_a),
#endif
	use_clp(LT_(GUI_PREFS_USE_CLIPBOARD))
	
{
	
	vbox = get_content_area();
	vbox->pack_start(notebook, true, true, 5);
	
	notebook.append_page(tbl1, LT_(GUI_PREFS_TAB_GENERAL));
	
	// adding buttons to action area
	button_save = add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_NONE);
	button_close = add_button(Gtk::Stock::CLOSE, Gtk::RESPONSE_CLOSE);

	// setting save button unsensitive
	set_response_sensitive(Gtk::RESPONSE_NONE, false);

	words_num_a->set_value(cfg->getInt("WordsInList", CONF_WORDS_IN_LIST));
	use_clp.set_active(cfg->getBool("UseClipboard", false));
	
	grid_attach(tbl1, words_num, 0, 1, 0, 1, true, true);
	grid_attach(tbl1, lbl1, 1, 2, 0, 1, true, true);
	grid_attach(tbl1, use_clp, 0, 2, 1, 2, true, true);
	
#ifndef ENABLE_LIGHT_VERSION

	use_wh.set_active(cfg->getBool("UseWH", true));
	wh_seconds.set_value(cfg->getInt("WHSeconds", 4));
	
	grid_attach(tbl1, use_wh, 0, 2, 2, 3, true, true);
	grid_attach(tbl1, wh_seconds, 0, 1, 3, 4, true, true);
	grid_attach(tbl1, lbl2, 1, 2, 3, 4, true, true);
	
	use_wh.signal_toggled().connect(sigc::mem_fun(*this, &GbgofficePrefs::something_changed));
	wh_seconds_a->signal_value_changed().connect(sigc::mem_fun(*this, &GbgofficePrefs::something_changed));

#endif
	
#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	
	notebook.append_page(tbl2, LT_(GUI_PREFS_TAB_TRAY));
	
	use_tr.set_active(cfg->getBool("UseTray", true));
	use_tr_close.set_active(cfg->getBool("UseTrayClose", false));
	tr_hide_os.set_active(cfg->getBool("TrayHideOnStart", false));
	helpmsg.set_markup(LT_(GUI_PREFS_TAB_TRAY_HELP));
	
	grid_attach(tbl2, use_tr, 0, 2, 0, 1, true, true);
	grid_attach(tbl2, use_tr_close, 0, 2, 1, 2, true, true);
	grid_attach(tbl2, tr_hide_os, 0, 2, 2, 3, true, true);
	grid_attach(tbl2, spacer, 0, 2, 3, 4, false, false);
	grid_attach(tbl2, helpmsg, 0, 2, 4, 5, false, false);
	
	use_tr.signal_toggled().connect(sigc::mem_fun(*this, &GbgofficePrefs::use_tray_changed));
	use_tr_close.signal_toggled().connect(sigc::mem_fun(*this, &GbgofficePrefs::something_changed));
	tr_hide_os.signal_toggled().connect(sigc::mem_fun(*this, &GbgofficePrefs::something_changed));
	
#endif

	button_save->signal_clicked().connect(sigc::mem_fun(*this, &GbgofficePrefs::on_save_button));
	words_num_a->signal_value_changed().connect(sigc::mem_fun(*this, &GbgofficePrefs::something_changed));
	use_clp.signal_toggled().connect(sigc::mem_fun(*this, &GbgofficePrefs::use_clip_changed));

	show_all_children();
	run();
}

// destructor
GbgofficePrefs::~GbgofficePrefs()
{
}

// saving new settings
void GbgofficePrefs::on_save_button()
{
	cfg->setInt("WordsInList", (int) words_num_a->get_value());
	cfg->setBool("UseClipboard", use_clp.get_active());

#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	cfg->setBool("UseTray", use_tr.get_active());
	cfg->setBool("UseTrayClose", use_tr_close.get_active());
	cfg->setBool("TrayHideOnStart", tr_hide_os.get_active());
#endif

#ifndef ENABLE_LIGHT_VERSION
	cfg->setInt("WHSeconds", (int) wh_seconds_a->get_value());
	cfg->setBool("UseWH", use_wh.get_active());
#endif
	
	set_response_sensitive(Gtk::RESPONSE_NONE, false);
	run();
}

// setting save button sensitive
void GbgofficePrefs::something_changed()
{
	set_response_sensitive(Gtk::RESPONSE_NONE, true);
}


void GbgofficePrefs::use_tray_changed()
{
#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	something_changed();
	
	if (use_tr.get_active()) {
		use_tr_close.set_sensitive(true);
		tr_hide_os.set_sensitive(true);
	} else {
		use_tr_close.set_sensitive(false);
		tr_hide_os.set_sensitive(false);
	}
#endif
}

void GbgofficePrefs::use_clip_changed()
{
#ifndef ENABLE_LIGHT_VERSION
	something_changed();
	
	if (use_clp.get_active()) {
		use_wh.set_sensitive(true);
		wh_seconds.set_sensitive(true);
		lbl2.set_sensitive(true);
	} else {
		use_wh.set_sensitive(false);
		wh_seconds.set_sensitive(false);
		lbl2.set_sensitive(false);
	}
#endif
}


