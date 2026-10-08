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

#ifndef GBGOFFICE_LANGUAGE_TOOLS_H
#define GBGOFFICE_LANGUAGE_TOOLS_H


// simple way for i18n without using gettext
#define LT_(x)	true == lang ? Glib::convert(x[1], "UTF-8", "CP1251"): x[0]


static const char *HELP_MESSAGE[] = {
	"Type a word (bulgarian or english) in entry box above",
	"Напишете дума (на български или английски) в полето по-горе"
};


static const char *WELLCOME_MESSAGE[] = {
	"Wellcome to GTK BG Office!",
	"Добре дошли в GTK БГ Офис. Приятно използване!"
};


static const char *ABOUT_MESSAGE[] = {
	"GTK BG Office assistant\n"
	"Official webpage - http://gbgoffice.info\n\n"
	"(C) 2004-2006 Miroslav Yordanov <mironcho@linux-bg.org>\n"
	"Gbgoffice is part from BG Office project  - http://bgoffice.sf.net\n\n"
	"Ported from GTK2 (gtkmm 2.4) to GTK3 (gtkmm 3.0) entirely\n"
	"by Claude, an AI assistant made by Anthropic.",

	"GTK БГ Офис помощник\n"
	"Официална страница - http://gbgoffice.info\n\n"
	"(C) 2004-2006 Мирослав Йорданов <mironcho@linux-bg.org>\n"
	"Gbgoffice е част от проекта БГ Офис - http://bgoffice.sf.net\n\n"
	"Портиран от GTK2 (gtkmm 2.4) към GTK3 (gtkmm 3.0) изцяло\n"
	"от Claude, AI асистент, създаден от Anthropic."
};

	
static const char *CONFIG_ERROR[] = {
	"The configuration could not be initialized\n"
	"This is fatal error and gbgoffice now will exit!",
	
	"Конфигурацията не може да бъде инициализирана\n"
	"Тази грешка е фатална!"
};


static const char *ERROR_INIT_TRAYICON[] = {
	"Error initializing trayicon module.\n"
	"This is fatal error and gbgoffice now will exit!",
	
	"Грешка при инициализирането на trayicon модула.\n"
	"Тази грешка е фатална!"
};


static const char *DATA_MISSING[] = {
	"Dicionary files are missing.\n"
	"Please check that you have installed them\n"
	"and if they are missing, visit\n"
	"http://bgoffice.sourceforge.net\n"
	"for information how to get and install them\n\n"
	"This error is fatal and gbgoffice now will exit!",
	
	"Речниците липсват.\n"
	"Моля проверете дали сте ги инсталирали\n"
	"и ако не сте, посетете сайта http://bgoffice.sf.net\n"
	"за повече информация от къде да ги изтеглите и как да ги инсталирате\n\n"
	"Тази грешка е фатална!"
};


static const char *DATA_MISSING_FEDORA[] = {
	"Dicionary files are missing.\n"
	"Please check that you have installed them\n"
	"and if they are missing, please use the supplied \n"
	"bgoffice-dicts.spec file to download and build a rpm file.\n"
	"For information how to get and install them please follow \n"
	"the instructions in the bgoffice-dicts.spec file.\n\n"
	"This error is fatal and gbgoffice now will exit!",
	
	"Речниците липсват.\n"
	"Моля проверете дали сте ги инсталирали\n"
	"и ако не сте, моля използвайте bgoffice-dicts.spec файла\n"
	"за да изтеглите и направите rpm пакет. За подробни указания,\n"
	"следвайте инструкциите в bgoffice-dicts.spec файла.\n\n"
	"Тази грешка е фатална!"
};



static const char *GUI_CURRENT_DICT[] = {
	"Current dictionary - ",
	"Текущ речник - "
};


static const char *GUI_NEXT_WORDS[] = {
	"next words",
	"следващи думи"
};


static const char *GUI_MENU_FILE[] = {
	"_File",
	"_Файл"
};


static const char *GUI_MENU_EDIT[] = {
	"_Edit",
	"Р_едактиране"
};


static const char *GUI_MENU_DICTS[] = {
	"_Dictionaries",
	"_Речници"
};


static const char *GUI_MENU_SETTINGS[] = {
	"_Settings",
	"_Настройки"
};


static const char *GUI_MENU_HELP[] = {
	"_Help",
	"_Помощ"
};


static const char *GUI_VIEW_HISTORY[] = {
	"View history",
	"Показва историята"
};


static const char *GUI_PREFS_NUM_WORDS[] = {
	" Number of words in list",
	" Брой думи в списъка"
};


static const char *GUI_PREFS_USE_CLIPBOARD[] = {
	" Watch clipboard for new words",
	" Наблюдавай клипборда за нови думи"
};


static const char *GUI_PREFS_TAB_GENERAL[] = {
	"General",
	"Основни"
};


static const char *GUI_PREFS_TAB_TRAY[] = {
	"Trayicon",
	"Trayicon"
};


static const char *GUI_PREFS_TAB_TRAY_HELP[] = {
	"<b>You must restart gbgoffice \nbefore these settings take effect</b>",
	"<b>Трябва да рестартирате gbgoffice \nза да влязат в сила тези настройки</b>"
};


static const char *GUI_PREFS_USE_TRAYICON[] = {
	" Use trayicon",
	" Използва trayicon"
};


static const char *GUI_PREFS_USE_TRAYICON_CLOSE[] = {
	" Closing main window,\n quits application",
	" Затварянето на основния прозорец,\n спира програмата"
};

static const char *GUI_PREFS_TRAYICON_HIDE_ON_START[] = {
	" Hide main window on startup",
	" Скрива основния прозорец при стартиране"
};


static const char *GUI_PREFS_USE_WH[] = {
	" Use helper",
	" Използва помощника"
};


static const char *GUI_PREFS_WH_SECONDS[] = {
	" time for showing helper\n (in seconds)",
	" време за показване на помощника\n (в секунди)"
};


static const char *GUI_EXAM_MENU[] = {
	"Make a test",
	"Проверка на знанията"
};


static const char *GUI_EXAM_CORRECT[] = {
	"correct",
	"правилно"
};

static const char *GUI_EXAM_INCORRECT[] = {
	"incorrect",
	"грешно"
};

static const char *GUI_EXAM_NEWTEST[] = {
	"Press button \"New\" for new test.",
	"Натиснете бутона \"Нов\" за нов тест."
};

static const char *GUI_EXAM_NEW_LEVEL1[] = {
	"Novice",
	"Начално"
};

static const char *GUI_EXAM_NEW_LEVEL2[] = {
	"Beginner",
	"Лесно"
};

static const char *GUI_EXAM_NEW_LEVEL3[] = {
	"Intermediate",
	"Средно"
};

static const char *GUI_EXAM_NEW_LEVEL4[] = {
	"Specialist",
	"Трудно"
};

static const char *GUI_EXAM_NEW_LEVEL5[] = {
	"Expert",
	"Експертно"
};

static const char *GUI_EXAM_TRANSLATION[] = {
	"Translation: ",
	"Превод: "
};

static const char *GUI_EXAM_DIFFICULTY[] = {
	"Difficulty: ",
	"Ниво: "
};

static const char *GUI_EXAM_NUMTEST[] = {
	"Test (0 = random): ",
	"Тест (0 = произволен): "
};

static const char *GUI_EXAM_NUMQUEST[] = {
	"Num of questions: ",
	"Брой въпроси: "
};

static const char *GUI_EXAM_ENDOFTEST[] = {
	"End of test.",
	"Край на теста."
};

static const char *GUI_EXAM_TESTNOTSTARTED[] = {
	"Test not started.",
	"Не е започнат тест."
};

static const char *GUI_EXAM_CORRECT_ANSWERS[] = {
	"correct",
	"правилни"
};


#endif	// GBGOFFICE_LANGUAGE_TOOLS_H

