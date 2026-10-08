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

#include "dictgui.h"
#include "properties.h"
#include "defaults.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <gtkmm/main.h>
using namespace std;

extern char *optarg;
Properties *cfg;
bool lang = false;


int main(int argc, char **argv)
{
	char *env, *path, *dataDir;
	int ch;
	
	
	/* command line options descriptor */
	static struct option longopts[] = {
		{ "dump-data-dir",	no_argument, 	NULL, 'd' },
		{ "help",		no_argument, 	NULL, 'h' },
		{ "language",	required_argument, 	NULL, 'l' },
		{ "version",	no_argument, 	NULL, 'v' },
		{ NULL, 		0, 		NULL, 0 }
	};


	/* configuration init
	 * few lines copy-pasted from kbgoffice main.cpp 
	 * with some modifications
	 */
	cfg = new Properties(getenv("HOME"), CONF_FILENAME);
	path = cfg->getString("DataDir", DICT_DIR);
	dataDir = new char[strlen(path) + 2];
	strcpy(dataDir, path);
	if ((dataDir[0] != '\0') && (dataDir[strlen(dataDir) - 1] != '/')) {
		strcat(dataDir, "/");
	}
	
	
	/* parsing command line options */
	while ((ch = getopt_long(argc, argv, "dhl:v", longopts, NULL)) != -1) {
		switch (ch) {
			case 'v':
				cout << "\nGbgoffice version " << VERSION << "\n" << endl;
				return 0;
						
			case 'd':
				cout << dataDir << endl;
				return 0;
				
			case 'l':
				if (!strcasecmp(optarg, "bg")) {
					setenv("LANG", "bg_BG", 1);
					cout << "language set to Bulgarian" << endl;
					
					break;
					
				} else if (!strcasecmp(optarg, "en")) {
					setenv("LANG", "C", 1);
					cout << "language set to English" << endl;
					
					break;
				}
				
				cout << argv[0] << ": invalid language - " << optarg << endl;

			case ':':
			case '?':
			case 'h':
			default:
				cout << "\nUsage: " << argv[0] << " [OPTIONS...]" << endl;
				cout << CMD_HELP << endl;
				
				exit(1);
		}
		
	}
	
	
	/* 
	* Now we look only in LANG variable for language settings.
	* If it is bg_BG, then we will set everything to bg_BG (bg),
	* otherwise, everything will be set to C (en).
	*/
	env = getenv("LANG");
	if (env && (strlen(env) >= 5) && !strncmp(env, "bg_BG", 5)) {
		setenv("LANGUAGE", "bg", 1);
		lang = true;
	} else {
		setenv("LANGUAGE", "C", 1);
		setenv("LANG", "C", 1);
		lang = false;
	}
	
	
	bool use_tray = cfg->getBool("UseTray", true);
			
	// gtkmm init
	Gtk::Main kit(argc, argv);

	// gui init
	DictGui maindict(argc, argv, dataDir);
	
#if !defined(ENABLE_LIGHT_VERSION) && !defined(DISABLE_TRAY)
	if (use_tray) {
		// the tray icon is not a window any more; DictGui::on_menu_quit()
		// (and the tray menu) call Gtk::Main::quit() to end this loop
		kit.run();
	} else {
		kit.run(maindict.win);
	}
#else
	kit.run(maindict.win);
#endif

	return 0;
}

