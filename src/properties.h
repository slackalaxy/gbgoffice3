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


#ifndef BGO_TOOLS_PROPERTIES_H
#define BGO_TOOLS_PROPERTIES_H

/*
* $Id: properties.h,v 1.1.1.1 2004/04/13 14:37:05 radnev Exp $
*/

class Properties {

public:
	Properties(const char *path, const char *file, const char *suffix = "~");
	~Properties();
	char *getString(const char *property, const char *defaultValue = "");
	int getInt(const char *property, const int defaultValue = 0);
	int getInt(const char *property, const int defaultValue, const int minValue, const int maxValue);
	bool getBool(const char *property, const bool defaultValue = false);
	bool setString(const char *property, const char *value);
	bool setInt(const char *property, const int value);
	bool setBool(const char *property, const bool value);

private:
	static const int MAX_LINE_LEN;
	static const int MAX_KEY_LEN;
	char *buf;
	char *sbuf;
	char *key;
	char *fileName;
	char *backupFileName;

};

#endif
