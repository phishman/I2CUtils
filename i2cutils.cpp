/*
* Arduino Library for I2C Utilities
*
* Copyright (C) 2015 RF Designs. All rights reserved.
*
* Author: Bob Frady <rfdesigns@live.com>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public
* License v2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public
* License along with this program; if not, write to the
* Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 021110-1307, USA.
*
* If you can't comply with GPLv2, alternative licensing terms may be
* arranged. Please contact RF Designs <rfdesigns@live.com> for proprietary
* alternative licensing inquiries.
*/


#include <wire.h>

#include <i2cutils.h>



I2CUTIL::I2CUTIL() :
{
}

void I2CUTIL::begin(void)
{
  Wire.begin();
}


void I2CUTIL::dump_reg(uint8_t address, uint8_t START, uint8_t END) {
  byte error;
  
  Serial.println("\nI2C Dump Reg");
  
  Wire.beginTransmission((uint8_t)address);
  //Wire.write((uint8_t)0x00);
  error = Wire.endTransmission();
  
  if(error) {
    Serial.print("*** Error from device at address:");
    Serial.print(address, HEX);
    Serial.println(" ***");
  }
  
  for(int x=START;x <= END;x++) {
    Wire.requestFrom((uint8_t)address, (uint8_t) 0x01);
    data = Wire.read();
    Serial.print(x, HEX);
    Serial.print(":");
    Serial.print(data, HEX);
    Serial.print(" ");
    if(((x % 0x0F) == 0) && (x > 0)) {
      Serial.print("\n"); 
    }
  }
  Serial.print("\n");
  Serial.println("...END...");
}