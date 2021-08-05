#include <RH_ASK.h>
#include <SPI.h>
#include <MX1508.h>

// uncomment to enable print out debug to uart
// #define COM_DEBUG

// RF433 pin
#define RF_SPEED    2000
#define RF_RX       4
#define RF_TX       7
#define RF_PTT      8

// MX1508 pin
#define MOTOR_A1    11
#define MOTOR_A2    6
#define MOTOR_B1    3
#define MOTOR_B2    5

// buzzer pin
#define BUZZER  2

// PS 2 controller button
#define PSB_SELECT      0x0001
#define PSB_L3          0x0002
#define PSB_R3          0x0004
#define PSB_START       0x0008
#define PSB_PAD_UP      0x0010
#define PSB_PAD_RIGHT   0x0020
#define PSB_PAD_DOWN    0x0040
#define PSB_PAD_LEFT    0x0080
#define PSB_L2          0x0100
#define PSB_R2          0x0200
#define PSB_L1          0x0400
#define PSB_R1          0x0800
#define PSB_GREEN       0x1000
#define PSB_RED         0x2000
#define PSB_BLUE        0x4000
#define PSB_PINK        0x8000
#define PSB_TRIANGLE    0x1000
#define PSB_CIRCLE      0x2000
#define PSB_CROSS       0x4000
#define PSB_SQUARE      0x8000

// data type to hold PS 2 value
struct PS2_DATA {
  unsigned int Button;
  byte Left_X;
  byte Left_Y;
  byte Right_Y;
  byte Right_X;
};

RH_ASK _rf_driver(RF_SPEED, RF_RX, RF_TX, RF_PTT);
MX1508 _motor_a(MOTOR_A1, MOTOR_A2, FAST_DECAY, PWM_2PIN);
MX1508 _motor_b(MOTOR_B1, MOTOR_B2, FAST_DECAY, PWM_2PIN);

PS2_DATA *_ps2_data;
int _current_pwm = 100;
int _min_pwm = 40;
int _max_pwm = 1023;

void setup() {
#ifdef COM_DEBUG
    Serial.begin(57600);
#endif

    if (_rf_driver.init()) {
        tone(BUZZER, 500, 100);
    }
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
#endif

        // drive left motor with left analog
        if (_ps2_data->Left_Y != 0x7B) {
            int left_analog = map(_ps2_data->Left_Y, 0, 255, _current_pwm, -_current_pwm);
            _motor_a.motorGo(left_analog);
        }
        else {
            _motor_a.stopMotor();
        }

        // drive right motor with right analog
        if (_ps2_data->Right_Y != 0x7B) {
            int right_analog = map(_ps2_data->Right_Y, 0, 255, _current_pwm, -_current_pwm);
            _motor_b.motorGo(right_analog);
        }
        else {
            _motor_b.stopMotor();
        }

        // drive with dpad
        if (IsPressed(PSB_PAD_UP)) {
            _motor_a.motorGo(_current_pwm);
            _motor_b.motorGo(_current_pwm);
        }
        else if (IsPressed(PSB_PAD_DOWN)) {
            _motor_a.motorGo(-_current_pwm);
            _motor_b.motorGo(-_current_pwm);
        }
        else if (IsPressed(PSB_PAD_LEFT)) {
            _motor_a.motorGo(-_current_pwm);
            _motor_b.motorGo(_current_pwm);
        }
        else if (IsPressed(PSB_PAD_RIGHT)) {
            _motor_a.motorGo(_current_pwm);
            _motor_b.motorGo(-_current_pwm);
        }

        // stop when square pressed
        if (IsPressed(PSB_SQUARE)) {
            _motor_a.stopMotor();
            _motor_b.stopMotor();
        }

        // increase/decrease pwm speed with L1/R1
        if (IsPressed(PSB_L1) && _current_pwm >= _min_pwm) {
            _current_pwm -= 5;
            tone(BUZZER, 250, 50);
        }
        if (IsPressed(PSB_R1) && _current_pwm <= _max_pwm) {
            _current_pwm += 5;
            tone(BUZZER, 500, 50);
        }
    }
}

boolean IsPressed(uint16_t ps2_button) {
    return ((_ps2_data->Button & ps2_button) > 0);
}
