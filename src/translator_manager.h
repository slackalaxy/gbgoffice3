/*************************************************************************
*
* BG Office Project
* Copyright (C) 2000-2004 Radostin Radnev <radnev@yahoo.com>
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


#ifndef BGO_A_CORE_TRANSLATOR_MANAGER_H
#define BGO_A_CORE_TRANSLATOR_MANAGER_H

#include <string>
#include <vector>

using namespace std;

#include "translator.h"

/*
* $Id: translator_manager.h,v 1.2 2004/09/16 16:14:26 radnev Exp $
*/


struct Dictionary {
	string file;
	string name;
	string icon;
	string version;
};

struct TestDictionary {
	string file;
	string name;
};


class TranslatorManager {

public:
	TranslatorManager(char *pDataDir);
	~TranslatorManager();
	bool init(const bool ignoreLANG = false);

	int sizeOfDictionaries();
	Dictionary getDictionary(const int index);
	void setCurrentDictionary(const int index);
	int getCurrentDictionary();

	int sizeOfTestDictionaries();
	TestDictionary getTestDictionary(const int index);
	Translator *getTestDictionaryObject(const int index, const int level);

	bool findWord(const char *word, char **result);
	bool goToNextWord();
	char *getWord(const bool toUpper = false);
	char *getResult();
	bool setAdvancedSearchText(const char *word);
	bool searchNextWord();
	char *countWords();

	bool getSeparateMeanings();
	bool getTryWithoutSuffix();
	bool getBoldDecoration();
	bool getHTMLOutput();
	bool getAdvancedSearchWholeWord();
	bool getAdvancedSearchExactPhrase();
	bool getAdvancedSearchHighlight();
	bool getAdvancedSearchState();

	void setSeparateMeanings(const bool val);
	void setTryWithoutSuffix(const bool val);
	void setBoldDecoration(const bool val);
	void setHTMLOutput(const bool val);
	void setAdvancedSearchWholeWord(const bool val);
	void setAdvancedSearchExactPhrase(const bool val);
	void setAdvancedSearchHighlight(const bool val);
	void setAdvancedSearchState(const bool val);


private:
	char *dataDir;

	vector<Dictionary> dictionaries;
	vector<TestDictionary> testDictionaries;
	vector<Translator*> translators;

	Translator *currentTranslator;
	int currentDict;

	vector<string> findFiles(const char *dir, const char *extension);

};

#endif
