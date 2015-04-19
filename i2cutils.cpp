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


void I2CUTIL::Scan(void) {
  Scan((uint8_t) 0x01, (uint8_t) 0x7F);
}

void I2CUTIL::Scan(uint8_t start, uint8_t end) {
  
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = start; address < end; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

}