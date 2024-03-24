#include <Mouse.h>
#include <hiduniversal.h>
#include "hidmouserptparser.h"

USB Usb;
HIDUniversal Hid(&Usb);
HIDMouseReportParser Mou(nullptr);

void setup() {
	Mouse.begin();
	Serial.begin(115200);
	Serial.println("Start");

	if (Usb.Init() == -1)
		Serial.println("OSC did not start.");
	
	delay(200);

	if (!Hid.SetReportParser(0, &Mou))
		ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
}

void loop() {
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

void onButtonDown(uint16_t buttonId) {
	Mouse.press(buttonId);
	// Serial.print("Button ");
	switch (buttonId)
  {
		case MOUSE_LEFT:
			Mouse.press(1);
			break;

		case MOUSE_RIGHT:
			Mouse.press(2);
			break;
		
		case MOUSE_MIDDLE:
			Mouse.press(4);
			break;

		case MOUSE_BUTTON4:
			// Serial.print("MOUSE_BUTTON4");
			break;

		case MOUSE_BUTTON5:
			// Serial.print("MOUSE_BUTTON5");
			break;
		default:
			// Serial.print("OTHER_BUTTON");
			break;
	}
	// Serial.println(" pressed");
}

void onButtonUp(uint16_t buttonId) {
	Mouse.release(buttonId);
	// Serial.print("Button ");
	switch (buttonId)
  {
		case MOUSE_LEFT:
			Mouse.release(1);
			break;

		case MOUSE_RIGHT:
			Mouse.release(2);
			break;
		
		case MOUSE_MIDDLE:
			Mouse.release(4);
			break;

		case MOUSE_BUTTON4:
			// Serial.print("MOUSE_BUTTON4");
			break;

		case MOUSE_BUTTON5:
			// Serial.print("MOUSE_BUTTON5");
			break;
		default:
			// Serial.print("OTHER_BUTTON");
			break;
	}
	// Serial.println(" released");
}

void onTiltPress(int8_t tiltValue) {
	Serial.print("Tilt pressed: ");
	Serial.println(tiltValue);
}

void onMouseMove(int8_t xMovement, int8_t yMovement, int8_t scrollValue) {
  Mouse.move(xMovement, yMovement, scrollValue);
}
