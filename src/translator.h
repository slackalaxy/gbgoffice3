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


#ifndef BGO_A_CORE_TRANSLATOR_H
#define BGO_A_CORE_TRANSLATOR_H

#include "database.h"

/*
* $Id: translator.h,v 1.2 2004/06/06 14:03:07 radnev Exp $
*/

class Translator {

public:
	Translator(const int type);
	~Translator();
	bool init(const int type, const char *fileName, const long fixedLastWordPointer = 0);
	bool findWord(const char *word, char **result);
	bool goToNextWord();
	char *getWord(const bool toUpper = false);
	char *getResult();
	bool testWord(const char *word);
	char *getNextRandomWord();
	void setTestParameters(const int level);
	bool setAdvancedSearchText(const char *word);
	bool searchNextWord();
	char *extractText(const char *text);
	char *countWords();

	static const int DUAL;
	static const int EN_BG;
	static const int BG_EN;

	bool separateMeanings;
	bool boldDecoration;
	bool htmlOutput;

	bool tryWithoutSuffix;

	bool advancedSearchState;
	bool advancedSearchHighlight;
	bool advancedSearchWholeWord;
	bool advancedSearchExactPhrase;

private:
	static const int  MAX_DATA_LEN;
	static const int  MAX_WORD_LEN;
	static const int  MAX_WORD_NUM;

	static const char EN_SUFFIXES[];
	static const char BOLD_START[];
	static const char BOLD_END[];
	static const char TRANSCRIPTION_START[];
	static const char TRANSCRIPTION_END[];
	static const char A_S_HL_HTML_START[];
	static const char A_S_HL_HTML_END[];
	static const char A_S_HL_NORMAL_START[];
	static const char A_S_HL_NORMAL_END[];
	static const char BREAK_LINE[];
	static const char DELIMITER;
	static const char TRANSCRIPTION_UNICODE[10][8];
	static const char TRANSCRIPTION_ANSI[];

	int dictionaryType;

	Database *dictEnBg;
	Database *dictBgEn;
	Database *currentDict;

	char *dataBuffer;
	char *wordBuffer;
	char *tempBuffer;
	char *dataBuffer2;
	char *wordBuffer2;
	bool *wordPlus;

	int wordNumber;

	int testLevel;

	bool firstTimeAdvancedSearch;
	bool firstDataBaseAdvancedSearch;

	char *toLowerCase(const char *word, char *buf);
	char *toUpperCase(const char *word, char *buf);
	char *toLegalDictionaryWord(const char *word, char *buf);
	char *trimWord(const char *word, char *buf);
	bool isEnglishWordWithoutSuffix(const char *word, char *buf);
	char *transformResult(const char *result);
	int appendString(const char *data, const int currentPointer);
	bool setCurrentDictionary(const char c, const bool opposite = false);
	char *search(char *text, const char *word, const bool exactSearch);
	bool isAlphaChar(const char c);

};

#endif
