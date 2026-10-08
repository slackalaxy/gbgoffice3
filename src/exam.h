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

#ifndef GBGOFFICE_EXAM_H
#define GBGOFFICE_EXAM_H

#ifndef ENABLE_LIGHT_VERSION

#include <gtkmm.h>
#include <gtkmm/stock.h>
#include <gtkmm/dialog.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

#include "gbgoffice_tools.h"
#include "translator_manager.h"


class GbgofficeExam : public GbgofficeTools, public Gtk::Dialog
{

public:
	GbgofficeExam(TranslatorManager *manager);
	virtual ~GbgofficeExam();

protected:

	// Signal handlers
	virtual void on_new_button();
	virtual void on_help_button();
	virtual void answer_given();

	void reset();
	
	// Child widgets
	Gtk::Box *vbox;
	Gtk::Box hbox1, hbox2, hbox3, hbox4;	// horizontal by default
	Gtk::Button *button_close, *button_help, *button_new;
	Gtk::Label question, result;
	Gtk::ProgressBar pbar;
	Gtk::Entry answer;
	Gtk::TextView ta;
	Gtk::ScrolledWindow ta_win;
	Gtk::Image emotion;

	Glib::RefPtr<Gtk::TextBuffer> tbuf;

	TranslatorManager *trm;
	Translator *dict;


	bool translate;
	int current;
	int correct;
	int num;

};	

#endif

#endif	// GBGOFFICE_EXAM_H

