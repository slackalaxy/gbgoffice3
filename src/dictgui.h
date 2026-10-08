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

#ifndef GBGOFFICE_DICT_GUI_H
#define GBGOFFICE_DICT_GUI_H

#include <gtkmm.h>
#include "translator_manager.h"
#include "gbgoffice_tools.h"
#include "language_tools.h"
#include "trayicon.h"

#ifndef ENABLE_LIGHT_VERSION
#include "workhelper.h"
#include "history.h"
#endif


class DictGui : public GbgofficeTools
{
	
public:
	DictGui(int argc, char **argv, const char *dir);
	virtual ~DictGui();

	void run();
	bool showNextWords();
	void searchCurrentWord();
	void errorDialog(Glib::ustring message);
	bool isFedora();
	
#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	TrayIcon *tric;
#endif
	Gtk::Window win;

	virtual void on_menu_preferences();
	virtual void on_menu_help();
	virtual void on_menu_info();

protected:
	// our data directory
	const char *dataDir;

	// number of words in list (treeview widget)
	// this will not be taken from cfg, for faster access
	int words_in_list;
	int num_of_dicts;

	// use clipboard?
	bool use_clipboard;
	
	// use trayicon?
	bool use_tray;
	bool use_tray_close;
	bool tray_hide_os;

#ifndef ENABLE_LIGHT_VERSION
	bool add_to_history;
#endif

	// Signal handlers
	virtual void on_entry_changed();
	virtual void on_entry_activated();
	virtual void clear_entry();
	virtual void entry_connect();
	virtual void entry_disconnect();
	virtual void clipboard_connect();
	virtual void clipboard_disconnect();

#ifndef ENABLE_LIGHT_VERSION
	void history_prev();
	void history_next();
#endif
	
	virtual void get_selected_word();
	virtual void set_statusbar();
	virtual void on_menu_quit();
	virtual void on_menu_history();
	virtual void on_menu_exam();
	virtual void on_menu_dict(int index, const char *name);

	// handlers for copy/paste functionality
	virtual void on_button_copy();
	virtual void on_button_paste();

	// timer function
	bool lookup_clipboard();

	// buffer tags function
	bool create_buffer_tags();

	// Treemodel stuff for treeview... blabla... this is so slowly :((
	// I'll write a faster widget later
	class ModelColumn : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumn() { add(col_name); }
		Gtk::TreeModelColumn<Glib::ustring> col_name;
	};
	ModelColumn mc;
	Gtk::TreeView wlist;
	Glib::RefPtr<Gtk::ListStore> refmc;
	Glib::RefPtr<Gtk::TreeSelection> refmcsel;
	Gtk::ScrolledWindow sctree;

	// Widgets
	Gtk::Box mainvbox, boxup;
	Gtk::Box boxdown, boxup_e;
	Gtk::Entry entry;
	Gtk::TextView textarea;
	Gtk::ScrolledWindow scwin;
	Gtk::Label spacer;
	Gtk::Statusbar status;
	//Gtk::Image simage;

#ifndef ENABLE_LIGHT_VERSION
	// Buttons
	Gtk::Button button_clear, button_next, button_prev;
	Gtk::Image emotion;
#endif

	// Menus
	Gtk::Menu menu_file, menu_edit, menu_dict, menu_settings, menu_help;
	Gtk::MenuBar *menubar;

	Glib::RefPtr<Gtk::TextBuffer> tbuf;

	sigc::connection con_entry;
	sigc::connection con_timer;

	Glib::RefPtr<Gtk::Clipboard> clp;

	// Translator manager
	TranslatorManager *dict;
	
#ifndef ENABLE_LIGHT_VERSION
	// Work Helper
	WorkHelper helper;
	
	// History
	History *history;
#endif

};


#endif  // GBGOFFICE_DICT_GUI_H

