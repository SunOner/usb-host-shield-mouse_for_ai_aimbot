#include "hidmouserptparser.h"
#include "Mouse.h"

HIDMouseReportParser::HIDMouseReportParser(void *) : previousButtonsState(0) {};

void HIDMouseReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    uint16_t buttonsState = buf[0] | (buf[1] << 8);

    for (uint16_t buttonId = 1; buttonId <= MOUSE_ALL; buttonId <<= 1)
    {
        if (buttonsState & buttonId)
        {
            if (!(previousButtonsState & buttonId))
            {
              onButtonDown(buttonId);
            }
        }
        else
        {
            if (previousButtonsState & buttonId)
            {
              onButtonUp(buttonId);
            }
        }
    }
    previousButtonsState = buttonsState;
  
    int16_t xMovement = (int16_t)((buf[3] << 8) | buf[2]);
    int16_t yMovement = (int16_t)((buf[5] << 8) | buf[4]);
    int8_t scrollValue = (int8_t)buf[6];
  
    if (xMovement != 0 || yMovement != 0 || scrollValue != 0)
    {
        onMouseMove(xMovement, yMovement, 0);
        
        if (scrollValue != 0)
        {
            onScroll(scrollValue);
        }
    }
}