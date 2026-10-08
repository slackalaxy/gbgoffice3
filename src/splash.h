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

#ifndef GBGOFFICE_SPLASH_H
#define GBGOFFICE_SPLASH_H


#ifndef ENABLE_LIGHT_VERSION

#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/box.h>
#include <glibmm.h>
#include <unistd.h>



#define SPLASH_SLEEP_USEC	250000


class SplashScreen : public Gtk::Window
{

public:
	SplashScreen();
	virtual ~SplashScreen();
	
	void set_step(float step);
	void flush_queue();
	
private:
	
	Gtk::Box  vbox;
	Gtk::Image image;
	Gtk::ProgressBar pbar;

	Glib::RefPtr<Glib::MainContext> context;
};


#endif

#endif	/* GBGOFFICE_SPLASH_H */
