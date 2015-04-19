#ifndef I2CUTILS_H
#define I2CUTILS_H

#define I2CUTILSVER 1.0


/* Retro-compatibility with arduino 0023 and previous version */
#if ARDUINO >= 100
#include "Arduino.h"
#define I2CWRITE(x) Wire.write(x)
#define I2CREAD() Wire.read()
#else
#include "WProgram.h"
#define I2CWRITE(x) Wire.send(x)
#define I2CREAD() Wire.receive()
#define INPUT_PULLUP 2
#endif

#include <inttypes.h>

class I2CUTIL {
public:
  I2CUTIL();
  void begin(void);
  void dump_reg(uint8_t address, uint8_t START, uint8_t END);
  void Scan(void);
  void Scan(uint8_t start, uint8_t end);
  
protected:

private:

};

#endif