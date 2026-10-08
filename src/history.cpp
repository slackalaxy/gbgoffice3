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


#include <string.h>

#include "history.h"


/*
* This class represents History object.
* It holds entered words and serves navigation
*
* $Id: history.cpp,v 1.1.1.1 2004/04/13 14:37:19 radnev Exp $
*/


History::History(const int items, const int length) {
	buf = NULL;
	len = length;
	setMaxSize(items);
}


History::~History() {
	delete [] buf;
}

void History::setMaxSize(const int items) {
	if (buf == NULL) {
		buf = new char[items*(len + 1)];
		currentSize = 0;
		current = 0;
		size = items;
	} else {
		char *b;
		int i;
		i = (size < items ? size : items);
		b = new char[items*(len + 1)];
		memcpy(b, buf, i*(len + 1));
		delete [] buf;
		buf = b;
		currentSize = i;
		if (current > currentSize - 1) {
			current = currentSize - 1;
		}
		size = items;
	}
}


int History::getMaxSize() {
	return size;
}


int History::getCurrentSize() {
	return currentSize;
}


void History::addItem(const char *item) {
	if (((currentSize > 0) && (strcmp(buf, item) != 0)) || (currentSize == 0)) {
		memmove(buf + len + 1, buf, (size - 1)*(len + 1));
		if ((signed)strlen(item) <= len) {
			strcpy(buf, item);
		} else {
			strncpy(buf, item, len);
			buf[len] = '\0';
		}
		if (currentSize < size) {
			currentSize++;
		}
		current = -1;
	}
}


char *History::getCurrentItem() {
	return (buf + current*(len + 1));
}


void History::prev() {
	if (current < currentSize - 1) {
		current++;
	}
}


void History::next() {
	if (current > 0) {
		current--;
	}
}


bool History::isFirst() {
	return (current == 0);
}


bool History::isLast() {
	return (current == (currentSize - 1));
}


bool History::isNew() {
	return (current == -1);
}
