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

#ifndef GBGOFFICE_DEFAULTS_H
#define GBGOFFICE_DEFAULTS_H

#include "config.h"


#ifdef DATA_DIR_CONFIG
static const char FILES_DIR[] = DATA_DIR_CONFIG;
#else
static const char FILES_DIR[] = "/usr/local/share/bgoffice/";
#endif


#ifdef USE_USER_LOCAL
static const char DICT_DIR[] = "/usr/local/share/bgoffice/";
#else
static const char DICT_DIR[] = DATA_DIR_CONFIG;
#endif

#ifdef USE_LIGHT
#define ENABLE_LIGHT_VERSION
#else
#undef ENABLE_LIGHT_VERSION
#endif

/* Name of the configuration file */
#define CONF_FILENAME		".gbgoffice"

/* Default values for configuration parameters */
#define CONF_MAX_WORD_LEN	128
#define CONF_WORDS_IN_LIST	50
#define CONF_WORDS_IN_HISTORY	50


#define CMD_HELP	"\nOptions: \n" \
	"  -d, --dump-data-dir           print data directory\n" \
	"  -l, --language=[bg/en]        sets language to Bulgarian or English\n" \
	"  -h, --help                    print this help\n" \
	"  -v, --version                 print version\n\n" \
	"For more information visit http://gbgoffice.info\n "


#endif	// GBGOFFICE_CONFIG_H
