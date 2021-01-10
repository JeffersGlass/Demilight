#include <Servo.h>
#include <Conceptinetics.h>

#define DMX_SLAVE_CHANNELS 512

// Configure a DMX slave controller
DMX_Slave dmx_slave ( DMX_SLAVE_CHANNELS );

const int ledPin = 3;
const int panPin = 5;
const int tiltPin = 6;

Servo panServo;
Servo tiltServo;

// the setup routine runs once when you press reset:
void setup() {

  dmx_slave.enable ();
  dmx_slave.setStartAddress (1);

  // Set led pin as output pin
  pinMode(ledPin, OUTPUT );
  analogWrite(ledPin, 0);

  pinMode(4, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, LOW); //turn on receive
  digitalWrite(10, LOW); //turn off transmit

  panServo.attach(panPin);
  tiltServo.attach(tiltPin);
  delay(100);
  panServo.write(90);
  tiltServo.write(90);
  delay(2000);
}

// the loop routine runs over and over again forever:
void loop()
{

  // getChannelValue is relative to the configured startaddress

  analogWrite(ledPin, int(dmx_slave.getChannelValue(1)*.8));
  panServo.write(map(dmx_slave.getChannelValue(2), 0, 255, 0, 180));
  tiltServo.write(map(dmx_slave.getChannelValue(3), 0, 255, 0, 180));

}
