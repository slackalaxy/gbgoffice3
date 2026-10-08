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

#ifndef ENABLE_LIGHT_VERSION

#include "exam.h"
#include "properties.h"
#include "defaults.h"
#include "language_tools.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


//extern Properties *cfg;
extern bool lang;

GbgofficeExam::GbgofficeExam(TranslatorManager *manager)
{
	trm = manager;


	set_default_size(400, 300);
	
	// getting the vbox from dialog
	vbox = get_content_area();
	vbox->pack_start(hbox1, false, false, 3);
	vbox->pack_start(hbox2, false, false, 3);
	vbox->pack_start(hbox3, true, true, 3);
	vbox->pack_start(hbox4, false, false, 3);
	
	// adding buttons to action area
	button_new = add_button(Gtk::Stock::NEW, Gtk::RESPONSE_NONE);
	button_help = add_button(Gtk::Stock::HELP, Gtk::RESPONSE_NONE);
	button_close = add_button(Gtk::Stock::CLOSE, Gtk::RESPONSE_CLOSE);


	question.set_markup(LT_(GUI_EXAM_TESTNOTSTARTED));

	//status.set_has_resize_grip(false);
	
	tbuf = Gtk::TextBuffer::create();
	tbuf->set_text(LT_(GUI_EXAM_NEWTEST));
	ta.set_buffer(tbuf);
	ta.set_editable(false);
	ta.set_wrap_mode(Gtk::WRAP_WORD);
	ta.set_indent(4);
	ta_win.add(ta);
	ta_win.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);

	// packing widgets 
	hbox1.pack_start(question, false, false, 5);
	hbox2.pack_start(answer, false, false, 5);
	hbox2.pack_end(emotion, false, false, 5);
	hbox2.pack_end(result, false, false, 5);
	hbox3.pack_start(ta_win, true, true, 5);
	hbox4.pack_end(pbar, true, true, 5);

	// connecting all signals
	button_help->signal_clicked().connect(sigc::mem_fun(*this, &GbgofficeExam::on_help_button));
	button_new->signal_clicked().connect(sigc::mem_fun(*this, &GbgofficeExam::on_new_button));
	answer.signal_activate().connect(sigc::mem_fun(*this, &GbgofficeExam::answer_given));

	reset();
	dict = trm->getTestDictionaryObject(0, 0);
	dict->separateMeanings = true;
	dict->boldDecoration = false;
	dict->htmlOutput = false;


	show_all_children();
	run();
}

// destructor
GbgofficeExam::~GbgofficeExam()
{
}


void GbgofficeExam::reset()
{
	current = 0;
	correct = 0;
	num = 0;
	translate = false;
}

void GbgofficeExam::on_new_button()
{
	Gtk::Dialog ne;
	
	ne.set_default_size(300, 200);
	
	Gtk::Grid tbl;
	Gtk::Box *vx = ne.get_content_area();
	vx->pack_start(tbl, true, true, 3);
	
	Gtk::ComboBoxText combo1;
	for (int i = 0; i < trm->sizeOfTestDictionaries(); i++) {
		combo1.insert(i, to_utf8(trm->getTestDictionary(i).name.c_str()));
	}
	combo1.set_active(0);
	
	Gtk::ComboBoxText combo2;
	combo2.insert(0, LT_(GUI_EXAM_NEW_LEVEL1));
	combo2.insert(1, LT_(GUI_EXAM_NEW_LEVEL2));
	combo2.insert(2, LT_(GUI_EXAM_NEW_LEVEL3));
	combo2.insert(3, LT_(GUI_EXAM_NEW_LEVEL4));
	combo2.insert(4, LT_(GUI_EXAM_NEW_LEVEL5));
	combo2.set_active(0);
	
	Gtk::Label l1(LT_(GUI_EXAM_TRANSLATION));
	l1.set_justify(Gtk::JUSTIFY_RIGHT);
	grid_attach(tbl, l1, 0, 1, 0, 1, false, false);
	grid_attach(tbl, combo1, 1, 2, 0, 1, true, true);
	
	Gtk::Label l2(LT_(GUI_EXAM_DIFFICULTY));
	l2.set_justify(Gtk::JUSTIFY_RIGHT);
	grid_attach(tbl, l2, 0, 1, 1, 2, false, false);
	grid_attach(tbl, combo2, 1, 2, 1, 2, true, true);
	
	Glib::RefPtr<Gtk::Adjustment> adj1 = Gtk::Adjustment::create(0.0, 0.0, 1000.0, 1.0, 5.0, 0.0);
	Gtk::SpinButton sp1(adj1);
	Gtk::Label l3(LT_(GUI_EXAM_NUMTEST));
	grid_attach(tbl, l3, 0, 1, 2, 3, false, false);
	grid_attach(tbl, sp1, 1, 2, 2, 3, true, false);
	
	
	Glib::RefPtr<Gtk::Adjustment> adj2 = Gtk::Adjustment::create(100.0, 10.0, 1000.0, 10.0, 50.0, 0.0);
	Gtk::SpinButton sp2(adj2);
	Gtk::Label l4(LT_(GUI_EXAM_NUMQUEST));
	grid_attach(tbl, l4, 0, 1, 3, 4, false, false);
	grid_attach(tbl, sp2, 1, 2, 3, 4, true, false);
	
	
	ne.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	ne.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	
	ne.show_all_children();
	if (ne.run() == Gtk::RESPONSE_OK) {
		translate = true;
		current = correct = 0;
		num = sp2.get_value_as_int() - 1;		
		
		if (dict != NULL) {
			delete dict;
		}
		dict = trm->getTestDictionaryObject(combo1.get_active_row_number(), 
				combo2.get_active_row_number());
		dict->separateMeanings = true;
		dict->boldDecoration = false;
		dict->htmlOutput = false;
		
		pbar.set_fraction(0.0);
		pbar.set_text("");
		answer.set_text("");
		result.set_text("");
		tbuf->set_text("");
		emotion.clear();
		
		srand(time(NULL));
		question.set_text(to_utf8(dict->getNextRandomWord()));
		set_focus(answer);
		
	} else {
		translate = false;
	}
	ne.hide();
	
	run();
}

void GbgofficeExam::on_help_button()
{
	tbuf->set_text(LT_(GUI_EXAM_NEWTEST));
	run();
}

void GbgofficeExam::answer_given()
{
	if (translate) {
		if (dict->testWord(to_cp1251(answer.get_text()))) {
			correct++;
			tbuf->set_text(to_utf8(dict->getResult()));
			result.set_markup("<b>" + (LT_(GUI_EXAM_CORRECT)) + "</b>");
			emotion.set(smile_ok);
		} else {
			tbuf->set_text(to_utf8(dict->getResult()));
			result.set_markup("<b>" + (LT_(GUI_EXAM_INCORRECT)) + "</b>");
			emotion.set(smile_nok);
		}
		
		float step = (float)(1.0 / num) * current;
		step = (step > 1.0) ? 1.0: step;
		step = (step < 0.0) ? 0.0: step;
		pbar.set_fraction(step);
		
		current++;
		Glib::ustring s;
		s << current << " / " << (num + 1) << " (" << correct;
		s << " " << (LT_(GUI_EXAM_CORRECT_ANSWERS)) << ")";
		pbar.set_text(s);
		
		if (current > num) {
			question.set_text(LT_(GUI_EXAM_ENDOFTEST));
			translate = false;
		} else {
			question.set_text(to_utf8(dict->getNextRandomWord()));
			answer.set_text("");
		}
		
	} else {
		tbuf->set_text(LT_(GUI_EXAM_NEWTEST));
	}
}

#endif
