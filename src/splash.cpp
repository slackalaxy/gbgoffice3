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

#include "splash.h"
#include "defaults.h"


#ifndef ENABLE_LIGHT_VERSION

SplashScreen::SplashScreen()
:	vbox(Gtk::ORIENTATION_VERTICAL)
{
	Glib::ustring s(FILES_DIR);
	image.set(s + "gbgoffice-splash.png");

	// getting started with the magic ;)
	context = Glib::MainContext::get_default();

	// removing decoration and setting some stuff...
	set_decorated(false);
	set_type_hint(Gdk::WINDOW_TYPE_HINT_SPLASHSCREEN);
	set_role("splash");
	set_position(Gtk::WIN_POS_CENTER);

	// adding and paccking widgets
	add(vbox);
	vbox.pack_start(image, true, true, 0);
	vbox.pack_start(pbar, false, false, 0);

	show_all_children();
	flush_queue();
}


SplashScreen::~SplashScreen()
{
	usleep(50000);
	hide();
}


void SplashScreen::set_step(float step)
{
	if ((step > 1.0) || (step < 0.0)) {
		step = 1.0;
	}

	pbar.set_fraction(step);
	flush_queue();
	usleep(SPLASH_SLEEP_USEC);
}

// the most important function in this class
// actualy showing splashscreen widgets here!
void SplashScreen::flush_queue()
{
	while (context->pending()) {
		context->iteration(true);
	}
}

#endif

