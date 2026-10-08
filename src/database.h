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


#ifndef BGO_A_CORE_DATABASE_H
#define BGO_A_CORE_DATABASE_H

#include <stdio.h>

/*
* $Id: database.h,v 1.1.1.1 2004/04/13 14:37:04 radnev Exp $
*/

class Database {

public:
	Database();
	~Database();
	bool init(const char *fileName, const long fixedLastWordPointer = 0);
	bool findWord(const char *word);
	char *getWord();
	char *getResult();
	char *getNextRandomWord();
	bool goToNextWord();
	void goToFirstWord();
	void goToLastWord();

private:
	static const int  MAX_WORD_LEN;
	static const int  MAX_DATA_LEN;
	static const char WORD_SEPARATOR;
	static const char DATA_SEPARATOR;

	FILE *dataFile;
	char *dataBuffer;
	char *wordBuffer;
	char *compBuffer;
	long firstWordPointer;
	long lastWordPointer;
	long lastSearchWordPointer;
	long currentWordPointer;

	void toLegalDictionaryWord(const char *word);
	void readData();

};

#endif
