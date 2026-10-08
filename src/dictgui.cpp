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

#include "dictgui.h"
#include "properties.h"
#include "prefsdialog.h"
#include "exam.h"
#include "defaults.h"
#include <iostream>
#include <cstring>

#ifndef ENABLE_LIGHT_VERSION
#include "splash.h"
#endif


#define FEDORA_FILE_CHECK	"/etc/fedora-release"


extern Properties *cfg;
extern bool lang;

DictGui::DictGui(int argc, char **argv, const char *dir)
#ifndef ENABLE_LIGHT_VERSION
:	add_to_history(true),
	mainvbox(Gtk::ORIENTATION_VERTICAL),
	boxup(Gtk::ORIENTATION_VERTICAL),
	boxdown(Gtk::ORIENTATION_HORIZONTAL),
	boxup_e(Gtk::ORIENTATION_HORIZONTAL),
	spacer(" "),
	button_clear(Gtk::Stock::CLEAR),
	button_next(Gtk::Stock::GO_FORWARD),
	button_prev(Gtk::Stock::GO_BACK)
#else
:	mainvbox(Gtk::ORIENTATION_VERTICAL),
	boxup(Gtk::ORIENTATION_VERTICAL),
	boxdown(Gtk::ORIENTATION_HORIZONTAL),
	boxup_e(Gtk::ORIENTATION_HORIZONTAL)
#endif

{
	dataDir = dir;
	use_tray = cfg->getBool("UseTray", true);
	use_tray_close = cfg->getBool("UseTrayClose", false);
	tray_hide_os = cfg->getBool("TrayHideOnStart", false);
	words_in_list = cfg->getInt("WordsInList", CONF_WORDS_IN_LIST);
	use_clipboard = cfg->getBool("UseClipboard", false);


#ifndef ENABLE_LIGHT_VERSION
	// First, loading splash window
	SplashScreen *splash = new SplashScreen();
	splash->show_now();			// show splash window NOW
	splash->flush_queue();		// needed only once
	
	history = new History(CONF_WORDS_IN_HISTORY, CONF_MAX_WORD_LEN);

	splash->set_step(0.2);
#endif
	dict = new TranslatorManager((char*) dataDir);
	if (!dict->init()) {
#ifndef ENABLE_LIGHT_VERSION
		delete splash;
#endif
		if (isFedora()) {
			errorDialog(LT_(DATA_MISSING_FEDORA));
		} else {
			errorDialog(LT_(DATA_MISSING));
		}
		exit(1);
	}
	num_of_dicts = dict->sizeOfDictionaries();	
	dict->setBoldDecoration(false);
	dict->setHTMLOutput(false);
	dict->setCurrentDictionary(0);

#ifndef ENABLE_LIGHT_VERSION	
	// OK - going to create GUI
	// setting default window size and position#ifndef ENABLE_LIGHT_VERSION
	splash->set_step(0.4);
#endif

	win.set_default_size(600, 370);	// sorry, no config for this yet
	win.set_position(Gtk::WIN_POS_CENTER);	// center the window

	// adding main vbox to the window 
	win.add(mainvbox);

	// adding main boxes to the main vbox 
	mainvbox.pack_start(boxup, false, false, 2);
	mainvbox.pack_start(boxdown);
	mainvbox.pack_start(status, false, false, 2);

	// setting statusbar (the resize grip is gone in GTK 3)
	set_statusbar();

	// Creating menus
	// File menu items
	append_stock_item(menu_file, Gtk::Stock::QUIT,
			sigc::mem_fun(*this, &DictGui::on_menu_quit));

	// Edit menu items
	append_stock_item(menu_edit, Gtk::Stock::COPY,
			sigc::mem_fun(*this, &DictGui::on_button_copy));
	append_stock_item(menu_edit, Gtk::Stock::PASTE,
			sigc::mem_fun(*this, &DictGui::on_button_paste));

#ifndef ENABLE_LIGHT_VERSION
	append_separator(menu_edit);

	append_stock_item(menu_edit, Gtk::Stock::GO_FORWARD,
			sigc::mem_fun(*this, &DictGui::history_next));
	append_stock_item(menu_edit, Gtk::Stock::GO_BACK,
			sigc::mem_fun(*this, &DictGui::history_prev));

	/*
	append_separator(menu_edit);
	append_item(menu_edit, LT_(GUI_VIEW_HISTORY),
			sigc::mem_fun(*this, &DictGui::on_menu_history));
	*/

	splash->set_step(0.6);
#endif

	// Dictionaries menu items
	{
		Gtk::RadioMenuItem::Group RadioGroup;

		for (int i = 0; i < num_of_dicts; i++) {
			struct Dictionary temp = dict->getDictionary(i);
			Gtk::RadioMenuItem *ritem = Gtk::manage(new Gtk::RadioMenuItem(
					RadioGroup,
					Glib::convert(temp.name, "UTF-8", "WINDOWS-1251")));
			ritem->signal_activate().connect(
					sigc::bind<int, const char*> (sigc::mem_fun(*this, &DictGui::on_menu_dict),
						i, temp.name.c_str()));
			menu_dict.append(*ritem);
			ritem->show();
		}

#ifndef ENABLE_LIGHT_VERSION
		append_separator(menu_dict);
		append_item(menu_dict, LT_(GUI_EXAM_MENU),
				sigc::mem_fun(*this, &DictGui::on_menu_exam));
#endif
	}

	// Settings menu items
	append_stock_item(menu_settings, Gtk::Stock::PREFERENCES,
			sigc::mem_fun(*this, &DictGui::on_menu_preferences));

	// Help menu items
	append_stock_item(menu_help, Gtk::Stock::HELP,
			sigc::mem_fun(*this, &DictGui::on_menu_help));
	append_stock_item(menu_help, Gtk::Stock::DIALOG_INFO,
			sigc::mem_fun(*this, &DictGui::on_menu_info));


	menubar = new Gtk::MenuBar();
	append_submenu(*menubar, LT_(GUI_MENU_FILE), menu_file);
	append_submenu(*menubar, LT_(GUI_MENU_EDIT), menu_edit);
	append_submenu(*menubar, LT_(GUI_MENU_DICTS), menu_dict);
	append_submenu(*menubar, LT_(GUI_MENU_SETTINGS), menu_settings);
	append_submenu(*menubar, LT_(GUI_MENU_HELP), menu_help);


	// packing widgets to main boxes 
	boxup.pack_start(*menubar, Gtk::PACK_SHRINK);	// packing menus
	boxup.pack_start(boxup_e, false, false, 1);	// packing the hbox boxup_e
	boxdown.pack_start(sctree, false, false, 2);	// packing treeview
	boxdown.pack_start(scwin, true, true, 2);	// packing textview


#ifndef ENABLE_LIGHT_VERSION
	button_prev.set_sensitive(false);
	button_next.set_sensitive(false);
	
	button_clear.set_relief(Gtk::RELIEF_HALF);
	button_prev.set_relief(Gtk::RELIEF_HALF);
	button_next.set_relief(Gtk::RELIEF_HALF);
#endif

	entry.set_max_length(CONF_MAX_WORD_LEN - 1);	// fixes buffer overflow

	// packing widgets to boxup_e 
	boxup_e.pack_start(entry, false, false, 1);
#ifndef ENABLE_LIGHT_VERSION
	boxup_e.pack_start(button_clear, false, false, 1);
	boxup_e.pack_start(spacer, false, false, 10);		// spacer
	boxup_e.pack_start(button_prev, false, false, 1);
	boxup_e.pack_start(button_next, false, false, 1);
	boxup_e.pack_end(emotion, false, false, 2);

	emotion.set(smile_ok);
#endif

	// creating treemodel and related stuff
	refmc = Gtk::ListStore::create(mc);
	refmcsel = wlist.get_selection();
	wlist.set_model(refmc);
	wlist.append_column(LT_(GUI_NEXT_WORDS), mc.col_name);
	sctree.add(wlist);
	sctree.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	sctree.set_size_request(150);
	// a frame gives the column header / scrollbar corner clean edges in GTK3 themes
	sctree.set_shadow_type(Gtk::SHADOW_IN);

	// creating textbuffer/scrolled window.. 
	tbuf = Gtk::TextBuffer::create();
	tbuf->set_text(LT_(WELLCOME_MESSAGE));
	textarea.set_buffer(tbuf);
	textarea.set_editable(false);
	textarea.set_wrap_mode(Gtk::WRAP_WORD);
	textarea.set_indent(4);
	scwin.add(textarea);
	scwin.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);


	// create tags for buffer
	create_buffer_tags();

	// connecting all signals
#ifndef ENABLE_LIGHT_VERSION
	splash->set_step(0.8);
#endif
	
	con_entry = entry.signal_changed().connect(sigc::mem_fun(*this, &DictGui::on_entry_changed));
	entry.signal_activate().connect(sigc::mem_fun(*this, &DictGui::on_entry_activated));
	refmcsel->signal_changed().connect(sigc::mem_fun(*this, &DictGui::get_selected_word));

#ifndef ENABLE_LIGHT_VERSION
	button_clear.signal_clicked().connect(sigc::mem_fun(*this, &DictGui::clear_entry));
	button_prev.signal_clicked().connect(sigc::mem_fun(*this, &DictGui::history_prev));
	button_next.signal_clicked().connect(sigc::mem_fun(*this, &DictGui::history_next));


	// hiding splash
	splash->set_step(1.0);
	delete splash;
#endif

	// getting clipboard and watching for new words
	clp = Gtk::Clipboard::get();
	if (use_clipboard) {
		clipboard_connect();
	}
	
#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	// tray icon
	if (use_tray) {
		tric = new TrayIcon(this);
		if (NULL == tric) {
			errorDialog(LT_(ERROR_INIT_TRAYICON));
			exit(1);
		}
		
		if (use_tray_close) {
			win.signal_hide().connect(sigc::mem_fun(*this, &DictGui::on_menu_quit));
		}
		
		helper.init_tray(tric->getStatusIcon(), tbuf);
	}
#endif

#ifndef ENABLE_LIGHT_VERSION
	if (!helper.is_ok()) {
		helper.init(win, tbuf);
	}
	
	helper.set_hide_timeout(cfg->getInt("WHSeconds", 4));
	helper.set_state(cfg->getBool("UseWH", true));
#endif
	
	// showing everything
	win.show_all_children();

#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	if (use_tray && tray_hide_os) {
		win.hide();
	} else {
		win.show();
	}
#else
	win.show();

#endif

}

// destructor
DictGui::~DictGui()
{
#ifndef ENABLE_LIGHT_VERSION
	delete history;
#endif
	// preventing segfault in libsigc (probaly some old version)
	entry_disconnect();
	clipboard_disconnect();
	
	std::cout << "see you!" << std::endl;
}

inline bool DictGui::showNextWords()
{
	refmc->clear();	// clear liststore
	for (int i = 0; i < words_in_list; i++) {
		(Gtk::TreeModel::Row (*(refmc->append())))[mc.col_name] = to_utf8(dict->getWord(false));
		
		// going to next word in dictionary
		if (!dict->goToNextWord()) {
			break;	// there aren't more words
		}
	}

	return true;
}


void DictGui::on_entry_changed()
{
	searchCurrentWord();
	showNextWords();
}

void DictGui::on_entry_activated()
{
	entry.select_region(0, entry.get_text().size());
}



void DictGui::get_selected_word()
{
	Gtk::TreeModel::iterator iter = refmcsel->get_selected();

	if (iter) {
		entry_disconnect();
		
		Gtk::TreeModel::Row row = *iter;
		entry.set_text(row[mc.col_name]);
		searchCurrentWord();
		
		entry_connect();
	}
}


// creating tags for text buffer
bool DictGui::create_buffer_tags()
{
	Glib::RefPtr<Gtk::TextBuffer::TagTable> tag_table = tbuf->get_tag_table();
	
	// blue tag
	Glib::RefPtr<Gtk::TextBuffer::Tag> tag_blue = Gtk::TextBuffer::Tag::create("bluetag");
	tag_blue->property_foreground() = "blue";
	tag_table->add(tag_blue);

	// bold tag
	Glib::RefPtr<Gtk::TextBuffer::Tag> tag_bold = Gtk::TextBuffer::Tag::create("boldtag");
	tag_bold->property_weight() = Pango::WEIGHT_BOLD;
	tag_table->add(tag_bold);

	return true;
}


// searching for word and viewing the results
// in main texview widget
inline void DictGui::searchCurrentWord()
{
	bool ok = false;
	char *nw = NULL;
	Glib::ustring w = entry.get_text();
	
	if (w.length() >= CONF_MAX_WORD_LEN) {
		// this never should happen...
		return;
	}
	
	ok = dict->findWord(to_cp1251(w), &nw);
	tbuf->set_text(to_utf8(nw));

	// first line - bold, second line - blue (the transcription)
	tbuf->apply_tag_by_name("boldtag", tbuf->get_iter_at_line(0), tbuf->get_iter_at_line(1));
	tbuf->apply_tag_by_name("bluetag", tbuf->get_iter_at_line(1), tbuf->get_iter_at_line(2));
	
	
#ifndef ENABLE_LIGHT_VERSION
	if (ok && (w.length() > 0)) {
		
		if (!strncasecmp(dict->getWord(), to_cp1251(w), strlen(dict->getWord()))) {
			emotion.set(smile_ok);
		} else {
			emotion.set(smile_neok);
		}
		
		if (add_to_history) {
			// adding history item and setting history buttons
			history->addItem(to_cp1251(w));
			button_prev.set_sensitive();
			button_next.set_sensitive(false);
		}
	} else {
		emotion.set(smile_nok);
	}
#endif
}

// menu widgets functions
void DictGui::on_menu_info()
{
	Gtk::MessageDialog dialog(LT_(ABOUT_MESSAGE));
	dialog.run();
}

void DictGui::on_menu_help()
{
	tbuf->set_text(LT_(HELP_MESSAGE));
}

void DictGui::on_menu_quit()
{
#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	if (use_tray) {
		// there is no tray window to hide any more, just leave the main loop
		Gtk::Main::quit();
	} else {
		win.hide();
	}
#else
	win.hide();
#endif
}


void DictGui::on_menu_history()
{
#ifndef ENABLE_LIGHT_VERSION
	add_to_history = false;
	int size = history->getCurrentSize();
	
	if (size > 0) {
		while (!history->isFirst()) {
			history->prev();
		}
		
		refmc->clear();
		for ( ; size > 0; history->prev(), size--) {
			(Gtk::TreeModel::Row (*(refmc->append())))[mc.col_name] = to_utf8(history->getCurrentItem());
			std::cout << history->getCurrentItem() << std::endl;
			if (history->isLast()) {
				break;
			}
		}
	}
	add_to_history = true;
#endif
}

// viewing preferences dialog and adjusting some
// variables after that
void DictGui::on_menu_preferences()
{
	GbgofficePrefs dialog;
	
	words_in_list = cfg->getInt("WordsInList", CONF_WORDS_IN_LIST);
	
	use_clipboard = cfg->getBool("UseClipboard", false);
	if (use_clipboard) {
		if(con_timer.connected()) {
			clipboard_disconnect();
		}
		clipboard_connect();
		
	} else {
		if (con_timer.connected()) {
			clipboard_disconnect();
		}
	}
	
#ifndef ENABLE_LIGHT_VERSION
	helper.set_hide_timeout(cfg->getInt("WHSeconds", 4));
	helper.set_state(cfg->getBool("UseWH", true));
#endif
}

// exam window...
void DictGui::on_menu_exam()
{
	GbgofficeExam exam(dict);
}

// copy,paste signal handlers
void DictGui::on_button_copy()
{
	Gtk::TextBuffer::iterator r_begin, r_end;

	if (entry.has_focus()) {
		clp->set_text(entry.get_text());
	} else {
		tbuf->get_selection_bounds(r_begin, r_end);
		if (r_begin == r_end) {
			clp->set_text(tbuf->get_text(false));
		} else {
			clp->set_text(tbuf->get_text(r_begin, r_end, false));
		}
	}
}

void DictGui::on_button_paste()
{
	// because textview is not editable, we will set only entry
	if (entry.has_focus()) {
		entry.set_text(clp->wait_for_text());
	} 
}

// setting current ductinary
void DictGui::on_menu_dict(int index, const char *name)
{
	dict->setCurrentDictionary(index);
	set_statusbar();
	on_entry_changed();
}

// clearing entry box
void DictGui::clear_entry()
{
	entry_disconnect();
	entry.set_text("");
	entry.grab_focus();
	entry_connect();
}


// some connect-disconnect helper functions
inline void DictGui::entry_connect()
{
	con_entry = entry.signal_changed().connect(sigc::mem_fun(*this, &DictGui::on_entry_changed));
}

inline void DictGui::entry_disconnect()
{
	con_entry.disconnect();
}

// also for clipboard function
inline void DictGui::clipboard_connect()
{
	con_timer = Glib::signal_timeout().connect(sigc::mem_fun(*this, &DictGui::lookup_clipboard), 500);
}

inline void DictGui::clipboard_disconnect()
{
	con_timer.disconnect();
}

#ifndef ENABLE_LIGHT_VERSION
// two similar functions for history manipulation
void DictGui::history_prev()
{
	if (!button_prev.is_sensitive()) {
		return;
	}
	add_to_history = false;
	
	history->prev();
	if (!entry.get_text().compare(history->getCurrentItem())) {
		history->prev();
	}
	entry.set_text(to_utf8(history->getCurrentItem()));
		
	button_next.set_sensitive();
	if (history->isLast() && (history->getCurrentSize() > 1)) {
		button_prev.set_sensitive(false);
	}
	
	add_to_history = true;
}

void DictGui::history_next()
{
	if (!button_next.is_sensitive()) {
		return;
	}
	add_to_history = false;

	history->next();
	entry.set_text(to_utf8(history->getCurrentItem()));
	
	button_prev.set_sensitive();
	if (history->isFirst()) {
		button_next.set_sensitive(false);
	}
	
	add_to_history = true;
}
#endif

// status bar message
void DictGui::set_statusbar()
{
	struct Dictionary d = dict->getDictionary(dict->getCurrentDictionary());
	Glib::ustring m(LT_(GUI_CURRENT_DICT));

	status.push(m + to_utf8(d.name));
}

// error dialog implementation
void DictGui::errorDialog(Glib::ustring message)
{
	Gtk::MessageDialog dlg(message, Gtk::MESSAGE_ERROR);
	dlg.run();
}

// check if we are runnig fedora
bool DictGui::isFedora()
{
	return Glib::file_test(FEDORA_FILE_CHECK, Glib::FILE_TEST_EXISTS);
}


// timer function - looking for new words in clipboard
bool DictGui::lookup_clipboard()
{
	static Glib::ustring last_clp_word;
	Glib::ustring tmp(""), buf("");

	if (clp->wait_is_text_available()) {
		tmp = clp->wait_for_text();

		if (!tmp.length()) {
			return true;
		}
		
		// now, lets check the buffer
		Glib::ustring::iterator it = tmp.begin();
		for (int i = 0; (it != tmp.end()) && (i < 20); it++, i++) {
			// catch only alphabets and return on anything else
			if (Glib::Unicode::isalpha(*it)) {
				buf += *it;
			} else {
				return true;
			}
		}

		// search the word if it's not the same..
		if (buf != last_clp_word) {
			entry.set_text(buf);
			last_clp_word = buf;

#ifndef ENABLE_LIGHT_VERSION			
			helper.show_help();
#endif
		}
	}

	// returns true to continue..
	return true;
}


