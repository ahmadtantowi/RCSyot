#include <RH_ASK.h>
#include <SPI.h>
#include <PS2X_lib.h>

// uncomment to enable print out debug to uart
// #define COM_DEBUG

// RF433 pin
#define RF_SPEED 2000
#define RF_RX 8
#define RF_TX 9
#define RF_PTT 7

// PS 2 controller pin (via SPI)
#define PS2_DAT 12
#define PS2_CMD 11
#define PS2_SEL 10
#define PS2_CLK 13

// buzzer pin
#define BUZZER 6

// data type to hold PS 2 value
struct PS2_DATA
{
  unsigned int Button;
  byte Left_X;
  byte Left_Y;
  byte Right_Y;
  byte Right_X;
};

RH_ASK _rf_driver(RF_SPEED, RF_RX, RF_TX, RF_PTT);
PS2X _ps2x;

PS2_DATA _ps2_data;
int _ps2_error;

void setup()
{
#ifdef COM_DEBUG
    Serial.begin(57600);
#endif

    if (_rf_driver.init()) {
        tone(BUZZER, 1000, 100);
    }

    // add delay to give PS 2 controller time to startup
    delay(300);

    _ps2_error = _ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);
    if (_ps2_error == 0) {
        tone(BUZZER, 1000, 200);
    }
}

void loop()
{
    if (_ps2_error == 0) {
        // read PS 2 analog and button value
        _ps2x.read_gamepad();
        _ps2_data.Button = _ps2x.ButtonDataByte();
        _ps2_data.Left_X = _ps2x.Analog(PSS_LX);
        _ps2_data.Left_Y = _ps2x.Analog(PSS_LY);
        _ps2_data.Right_X = _ps2x.Analog(PSS_RX);
        _ps2_data.Right_Y = _ps2x.Analog(PSS_RY);

#ifdef COM_DEBUG
        Serial.print(_ps2_data.Button, HEX);
        Serial.print(" : ");
        Serial.print(_ps2_data.Left_X, HEX);
        Serial.print(" : ");
        Serial.print(_ps2_data.Left_Y, HEX);
        Serial.print(" : ");
        Serial.print(_ps2_data.Right_X, HEX);
        Serial.print(" : ");
        Serial.print(_ps2_data.Right_Y, HEX);
        Serial.println();
#endif

        // send PS 2 data via RF433
        if (_rf_driver.send((uint8_t *)&_ps2_data, sizeof(PS2_DATA))) {
            _rf_driver.waitPacketSent();
        }
    }
}
