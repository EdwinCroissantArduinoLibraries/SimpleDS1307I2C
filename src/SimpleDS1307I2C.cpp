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

#include <SimpleDS1307I2C.h>

SimpleDS1307I2C::SimpleDS1307I2C() {
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	minute = 0;
	second = 0;
}

bool SimpleDS1307I2C::readClock() {
	uint8_t temp;
	I2c.read(I2Caddr, RegStart, 8);
	temp = I2c.receive();
	if (temp > 0xEF) // bit 7 set, clock halted
		return false;
	second = (temp & 0x0F) + ((temp >> 4) * 10);
	temp = I2c.receive();
	minute = (temp & 0x0F) + ((temp >> 4) * 10);
	temp = I2c.receive();
	hour = (temp & 0x0F) + ((temp >> 4) * 10);
	I2c.receive(); // day number
	temp = I2c.receive();
	day = (temp & 0x0F) + ((temp >> 4) * 10);
	temp = I2c.receive();
	month = (temp & 0x0F) + ((temp >> 4) * 10);
	temp = I2c.receive();
	year = (temp & 0x0F) + ((temp >> 4) * 10);
	return true;
}

void SimpleDS1307I2C::setClock() {
	I2c.start();
	I2c.sendAddress(SLA_W(I2Caddr));
	I2c.sendByte(RegStart);
	I2c.sendByte(((second % 10) | ((second / 10) << 4)) & 0x7F);
	I2c.sendByte(((minute % 10) | ((minute / 10) << 4)) & 0x7F);
	I2c.sendByte(((hour % 10) | ((hour / 10) << 4)) & 0x3F); // force 24h mode
	I2c.sendByte(1);
	I2c.sendByte(((day % 10) | ((day / 10) << 4)) & 0x3F);
	I2c.sendByte(((month % 10) | ((month / 10) << 4)) & 0x1F);
	I2c.sendByte((year % 10) | ((year / 10) << 4));
	I2c.stop();
}

void SimpleDS1307I2C::writeRam(uint8_t memLoc, uint8_t* source,
		uint8_t quantity) {
	I2c.write(I2Caddr, memLoc + RamStart, source, quantity);
}

void SimpleDS1307I2C::readRam(uint8_t memLoc, uint8_t quantity,
		uint8_t* destination) {
	I2c.read(I2Caddr, memLoc + RamStart, quantity, destination);
}

void SimpleDS1307I2C::clearRam() {
	I2c.start();
	I2c.sendAddress(SLA_W(I2Caddr));
	I2c.sendByte(RamStart);
	for (int i = 0; i < RamSize; ++i) {
		I2c.sendByte(0);
	};
	I2c.stop();
}

SimpleDS1307I2C rtc = SimpleDS1307I2C();


