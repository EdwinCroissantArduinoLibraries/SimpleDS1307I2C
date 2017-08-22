/*
 * Very simple library for the DS1307 RTC.
 *
 * uses the I2C library from Wayne Truchsess
 *
 * Copyright (C) 2017 Edwin Croissant
 *
 *  This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See the README.md file for additional information.
 */

#ifndef SIMPLEDS1307I2C_H_
#define SIMPLEDS1307I2C_H_

#include <I2C.h>

class SimpleDS1307I2C {
public:
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	SimpleDS1307I2C(void);
	bool readClock(void);
	void setClock(void);
	void writeRam(uint8_t memLoc, uint8_t* source, uint8_t quantity);
	void readRam(uint8_t memLoc, uint8_t quantity, uint8_t* destination);
	void clearRam();
private:
	enum MCP23017 {
		I2Caddr = 0x68,
		RegStart = 0x00,
		RamStart = 0x08,
		RamSize = (0x3F - 0x08)
	};
};

extern SimpleDS1307I2C rtc;

#endif /* SIMPLEDS1307I2C_H_ */
