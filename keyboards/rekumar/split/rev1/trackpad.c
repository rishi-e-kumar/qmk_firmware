#include "trackpad.h"
#include <print.h>
#include <inttypes.h>
#include <stdio.h>
#include "quantum.h"

bool isScrollMode = false;

// Convenient way to store and access measurements
typedef struct _relData
{
  uint8_t buttons;
  int8_t xDelta;
  int8_t yDelta;
  bool xNegative;
  bool yNegative;
  int8_t wheelCount;
} relData_t;

relData_t touchData;

void writeregister(uint8_t address, uint8_t data) {
  uint8_t cmdByte = WRITE_MASK | address; //Form the WRITE command byte

  TP_CS_LO;

  SPI_TransferByte(cmdByte); // Signal a write to register at <address>
  SPI_TransferByte(data); // Send <value> to be written to register

  TP_CS_HI;
}

void readregister(uint8_t address, uint8_t * data, uint8_t count) {
  uint8_t cmdByte = READ_MASK | address; //Form the READ command byte

  TP_CS_LO;

  // Read the data
  SPI_TransferByte(cmdByte);
  SPI_TransferByte(FILLER);
  SPI_TransferByte(FILLER);
  for(uint8_t i = 0; i < count; i++){
    data[i] = SPI_TransferByte(FILLER);
  }

  TP_CS_HI;
}

void pinnacle_clearflags(void){
  writeregister(0x02, 0x00);
  wait_us(50);
}

void pinnacle_getrelative(relData_t * result){
  uint8_t data[3] = { 0,0,0 };
  readregister(0x12, data, 3);

  pinnacle_clearflags();

  result->buttons = data[0] & 0x05;
  result->xDelta = (int8_t)data[1];
  result->xNegative = data[0] & (1<<3);
  // if (result->xDelta < 0){
  //   result->xDelta = -(128 + result->xDelta);
  // }
  result->yDelta = (int8_t)data[2];
  result->yNegative = data[0] & (1<<4);

  // if (result->yDelta < 0){
  //   result->yDelta = -(128 + result->yDelta);
  // }
}

void pinnacle_clip(relData_t * result){
  // if ((result->xDelta > 100) || (result->xDelta < -100)){
  //   result->xDelta = 0;
  // } 

  // if ((result->yDelta > 100) || (result->yDelta < -100)){
  //   result->yDelta = 0;
  // } 
  // if ((result->xDelta < 0)){result->xDelta /= 2;}
  // if ((result->yDelta < 0)){result->yDelta /= 2;}
}

// bool pinnacle_touchdown(void){
//   if (ztotal/MOVING_AVERAGE_WINDOW <= pinnacle_Z_THRESHOLD) { return false;}
//   if (touchData.xDelta == 0) { return false;}
//   if (ytotal/MOVING_AVERAGE_WINDOW == 0) { return false;}
//   return true;
// }

// Enables or disables feed of touch data
void pinnacle_enableFeed(bool feedEnable)
{
  uint8_t temp;

  readregister(FEEDCONFIG_1, &temp, 1);  // Store contents of FeedConfig1 register

  if(feedEnable)
  {
    temp |= 0x01;                 // Set Feed Enable bit
    writeregister(FEEDCONFIG_1, temp);
  }
  else
  {
    temp &= ~0x01;                // Clear Feed Enable bit
    writeregister(FEEDCONFIG_1, temp);
  }
}

// Writes a byte, <data>, to an extended register at <address> (16-bit address)
void ERA_writeByte(uint16_t address, uint8_t data)
{
  // uint8_t ERAControlValue = 0xFF;

  pinnacle_enableFeed(false); // Disable feed

  writeregister(ERA_VALUE, data);      // Send data byte to be written

  writeregister(ERA_HIGH_BYTE, (uint8_t)(address >> 8));     // Upper byte of ERA address
  writeregister(ERA_LOW_BYTE, (uint8_t)(address & 0x00FF)); // Lower byte of ERA address

  writeregister(ERA_CONTROL, 0x02);  // Signal an ERA-write to pinnacle

  // Wait for status register 0x1E to clear
  // do
  // {
  //   readregister(ERA_CONTROL, &ERAControlValue, 1);
  // } while(ERAControlValue != 0x00);

  pinnacle_clearflags();
}

// pinnacle includes a feature that allows it to automatically detect when SPI data is
// transitioning on falling edges (rather than rising edges, as it should be). In this case,
// pinnacle can automatically switch the clock phase of the SPI module to accommodate.
// NOTE: if your SPI signals have excessive ringing and/or glitches, this feature may be triggered
// in error. To disable the feature, call this function immediately after SPI is setup.
void pinnacle_disableAutoEdgeDetect(void)
{
  ERA_writeByte(0xDA, 0x81);
  pinnacle_enableFeed(true);
}

void pointing_device_init(void){
  SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_SCK_LEAD_RISING | SPI_SAMPLE_TRAILING | SPI_ORDER_MSB_FIRST | SPI_MODE_MASTER); //SPI_ORDER_MSB_FIRST

  TP_CS_INIT;
  TP_DR_INIT;

  TP_CS_HI;

  pinnacle_clearflags();

  // pinnacle_disableAutoEdgeDetect();
  writeregister(0x03, SYSCONFIG_1);
  writeregister(0x05, FEEDCONFIG_2);
  writeregister(0x04, 0x01);
  writeregister(0x0A, Z_IDLE_COUNT);
  // pinnacle_enableFeed(true);


}

void pointing_device_task(void){
  // Motion has occurred on the trackpad
  if (TP_DR_READ) {
    pinnacle_getrelative(&touchData);
    pinnacle_clip(&touchData);
    if (true){
      int8_t dx, dy;
  

      dx = touchData.xDelta;
      dy = -touchData.yDelta;

      if (IS_LAYER_ON(5)){ //pretty ghetto, need to link to keymap.c. had compile issues though
        isScrollMode = true;
      }else{
        isScrollMode = false;
      }


      report_mouse_t currentReport = pointing_device_get_report();
      if (isScrollMode)
      {
        currentReport.h = -dx * SCROLL_SPEED_MULTIPLIER;
        currentReport.v = dy * SCROLL_SPEED_MULTIPLIER;
        if (touchData.buttons & (1<<0)){
          currentReport.buttons |= MOUSE_BTN2;
        }else{
          currentReport.buttons &= ~MOUSE_BTN2;
        }
      }
      else
      {
        currentReport.x = dx * POINTER_SPEED_MULTIPLIER;
        currentReport.y = dy * POINTER_SPEED_MULTIPLIER;
        if (touchData.buttons & (1<<0)){
          currentReport.buttons |= MOUSE_BTN1;
        }else{
          currentReport.buttons &= ~MOUSE_BTN1;
        }
      }
      pointing_device_set_report(currentReport);
      pointing_device_send();

    } 
  }
}
