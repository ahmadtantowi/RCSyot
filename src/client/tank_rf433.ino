#include <RH_ASK.h>
#include <SPI.h>

// uncomment to enable print out debug to uart
// #define COM_DEBUG

// data type to hold PS 2 value
struct PS2_DATA {
  unsigned int Button;
  byte Left_X;
  byte Left_Y;
  byte Right_Y;
  byte Right_X;
};

RH_ASK _rf_driver;
PS2_DATA *_ps2_data;

void setup() {
#ifdef COM_DEBUG
    Serial.begin(57600);
#endif

    _rf_driver.init();
}

void loop() {
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (_rf_driver.recv(buf, &buflen)) {
        _ps2_data = (PS2_DATA *)buf;

#ifdef COM_DEBUG
        Serial.print(_ps2_data->Button, HEX);
        Serial.print(" : ");
        Serial.print(_ps2_data->Left_X, HEX);
        Serial.print(" : ");
        Serial.print(_ps2_data->Left_Y, HEX);
        Serial.print(" : ");
        Serial.print(_ps2_data->Right_X, HEX);
        Serial.print(" : ");
        Serial.print(_ps2_data->Right_Y, HEX);
        Serial.println();
    }
#endif
}
