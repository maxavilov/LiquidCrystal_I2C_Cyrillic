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

#include "LiquidCrystal_I2C_Cyrillic.h"

void LiquidCrystal_I2C_Cyrillic::printCyrillic(const char* str, int x, int y) {
  for (int i = 0; str[i] != 0; i++) {
    if ((uint8_t) str[i] < 0x80) {
      setCursor(x + i, y);
      write(str[i]);
    } else if ((uint8_t) str[i] >= 0x80 + CYRILLIC_FONT_CHAR_COUNT) {
      writeOtherChar(str[i], x + i, y);
    } else {
      uint8_t charFont[8] = {0, 0, 0, 0, 0, 0, 0, 0};
      makeCharFont(charFont, CyrFont + (((uint8_t) str[i]) - 0x80) * 5);
      uint8_t customC = putChar((uint8_t) str[i]);
      createChar(customC, charFont);
      setCursor(x + i, y);
      write(customC);
    }
  }
}

void LiquidCrystal_I2C_Cyrillic::writeOtherChar(uint8_t otherChar, int x, int y) {
  setCursor(x, y);
  write(otherChar);
};

void LiquidCrystal_I2C_Cyrillic::makeCharFont(uint8_t* charFont, const void * charFontSrc) {
  uint8_t fontCols[5];
  memcpy_P(fontCols, charFontSrc, 5);
  register uint8_t fontCol0 = fontCols[0];
  register uint8_t fontCol1 = fontCols[1];
  register uint8_t fontCol2 = fontCols[2];
  register uint8_t fontCol3 = fontCols[3];
  register uint8_t fontCol4 = fontCols[4];
  uint8_t i = 0;
  while (1) {
    register uint8_t buf = 0;
    asm volatile(
      "bst %1, 0 \n\t"
      "bld %0, 0 \n\t"
      "bst %2, 0 \n\t"
      "bld %0, 1 \n\t"
      "bst %3, 0 \n\t"
      "bld %0, 2 \n\t"
      "bst %4, 0 \n\t"
      "bld %0, 3 \n\t"
      "bst %5, 0 \n\t"
      "bld %0, 4 \n\t"
      : "=r" (buf)
      : "r" (fontCol0),
      "r" (fontCol1),
      "r" (fontCol2),
      "r" (fontCol3),
      "r" (fontCol4));
    charFont[7 - i] = buf;
    if (i == 7) return;
    i++;
    fontCol0 >>= 1;
    fontCol1 >>= 1;
    fontCol2 >>= 1;
    fontCol3 >>= 1;
    fontCol4 >>= 1;
  }
}

uint8_t LiquidCrystal_I2C_Cyrillic::putChar(uint8_t customC) {
  for (int i = 0; i < 8; i++) {
    if (customChars_[i] == customC) {
      return i;
    } else if (i == customCharsFirstFree_) {
      customChars_[i] = customC;
      customCharsFirstFree_++;
      customCharsFirstFree_ %= 8;
      return i;
    }
  }
  uint8_t result = customCharsFirstFree_;
  customChars_[result] = customC;
  customCharsFirstFree_++;
  customCharsFirstFree_ %= 8;
  return result;
}
