#include "Mouse.h"
#include <hiduniversal.h>
#include "hidmouserptparser.h"
#include "Keyboard.h"

USB Usb;
HIDUniversal Hid(&Usb);
HIDMouseReportParser Mou(nullptr);

void setup()
{
	Mouse.begin();
  Keyboard.begin();
	Serial.begin(115200);
	Serial.println("Start");

	if (Usb.Init() == -1)
  {
		Serial.println("OSC did not start.");
  }
	
	delay(200);

	if (!Hid.SetReportParser(0, &Mou))
  {
		ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
  }
}

void loop()
{
  	Usb.Task();

    if (Serial.available() > 0)
    {
        String command = Serial.readStringUntil('\n');
        ParseSerialCommand(command);
    }
}

void ParseSerialCommand(const String& command)
{
    if (command == "c")
    {
        Mouse.click();
    }
    else if (command == "r")
    {
        Mouse.release();
    }
    else if (command == "p")
    {
        Mouse.press();
    }
    else if (command.startsWith("m"))
    {
        ExecuteMouseMoveCommand(command);
    }
}

void ExecuteMouseMoveCommand(const String& command)
{
    String moveCommand = command;
    moveCommand.replace("m", "");

    int commaIndex = moveCommand.indexOf(',');
    int x = moveCommand.substring(0, commaIndex).toInt();
    int y = moveCommand.substring(commaIndex + 1).toInt();

    Mouse.move(x, y, 0);
}

void onButtonDown(uint16_t buttonId)
{
    switch(buttonId)
    {
        case MOUSE_LEFT:
            Mouse.press(MOUSE_LEFT);
            break;
        case MOUSE_RIGHT:
            Mouse.press(MOUSE_RIGHT);
            break;
        case MOUSE_MIDDLE:
            Mouse.press(MOUSE_MIDDLE);
            break;
        case MOUSE_PREV:
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press(KEY_LEFT_ARROW);
            break;
        case MOUSE_NEXT: 
            Keyboard.press(KEY_LEFT_ALT);
            Keyboard.press(KEY_RIGHT_ARROW);
            break;
        default:
            break;
    }
}

void onButtonUp(uint16_t buttonId)
{
    switch(buttonId)
    {
        case MOUSE_LEFT:
            Mouse.release(MOUSE_LEFT);
            break;
        case MOUSE_RIGHT:
            Mouse.release(MOUSE_RIGHT);
            break;
        case MOUSE_MIDDLE:
            Mouse.release(MOUSE_MIDDLE);
            break;
        case MOUSE_PREV:
            Keyboard.release(KEY_LEFT_ALT);
            Keyboard.release(KEY_LEFT_ARROW);
            break;
        case MOUSE_NEXT:
            Keyboard.release(KEY_LEFT_ALT);
            Keyboard.release(KEY_RIGHT_ARROW);
            break;
        default:
            break;
    }
}

void onTiltPress(int8_t tiltValue)
{
	Serial.print("Tilt pressed: ");
	Serial.println(tiltValue);
}

void onMouseMove(int16_t x, int16_t y, int8_t wheel)
{
    Mouse.move(x, y, wheel);
}

void onScroll(int8_t scrollValue)
{
    Mouse.move(0, 0, scrollValue);
}