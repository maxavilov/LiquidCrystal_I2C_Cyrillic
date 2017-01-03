/*
 *  Copyright (C) 2016 Maxim Avilov (maxim.avilov@gmail.com)
 *
 *  This file is part of LiquidCrystal_I2C_Cyrillic.
 *
 *  LiquidCrystal_I2C_Cyrillic is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  LiquidCrystal_I2C_Cyrillic is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser Public License
 *  along with LiquidCrystal_I2C_Cyrillic.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  (Этот файл — часть LiquidCrystal_I2C_Cyrillic.
 *
 *  LiquidCrystal_I2C_Cyrillic - свободная программа: вы можете перераспространять ее и/или
 *  изменять ее на условиях Меньшей общественной лицензии GNU в том виде,
 *  в каком она была опубликована Фондом свободного программного обеспечения;
 *  либо версии 3 лицензии, либо (по вашему выбору) любой более поздней
 *  версии.
 *
 *  LiquidCrystal_I2C_Cyrillic распространяется в надежде, что она будет полезной,
 *  но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 *  или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Меньшей
 *  общественной лицензии GNU.
 *
 *  Вы должны были получить копию Меньшей общественной лицензии GNU
 *  вместе с этой программой. Если это не так, см.
 *  <http://www.gnu.org/licenses/>.)
 *
 * +++++++++++++[>+>+++++>+++++++++>++++++++>++>++++++<<<<<<-]>>.>.-.>.<-----.++
 * +.<-------.>>>++++++.>-.<<-------.<++++++.>++++++++.++++.>.<<<+++++++.>--.>--
 * --.+++.+++.<.<<---.
 */
#ifndef LiquidCrystal_I2C_Cyrillic_h
#define LiquidCrystal_I2C_Cyrillic_h

#include "Arduino.h"
#include <LiquidCrystal_I2C.h>
#include "LC_Cyrillic_Font_Compact.h"

class LiquidCrystal_I2C_Cyrillic : public LiquidCrystal_I2C {
  public:
    LiquidCrystal_I2C_Cyrillic(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows) {};
    void printCyrillic(const char* str, int x, int y);
  protected:
    virtual void writeOtherChar(uint8_t otherChar, int x, int y);
    uint8_t putChar(uint8_t customC);
    void makeCharFont(uint8_t* charFont, const void * charFontSrc);
  private:
    uint8_t customChars_[8];
    uint8_t customCharsFirstFree_ = 0;
};
#endif