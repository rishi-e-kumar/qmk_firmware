#include "trackpad.h"
#include <print.h>
#include <inttypes.h>
#include <stdio.h>

bool isScrollMode = false;

// Convenient way to store and access measurements
typedef struct _absData
{
  uint16_t xValue;
  uint16_t yValue;
  uint16_t zValue;
  uint8_t buttonFlags;
  bool touchDown;
} absData_t;

absData_t touchData;

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

void pinnacle_getrelative(absData_t * result){
  uint8_t data[6] = { 0,0,0,0 };
  readregister(0x12, data, 4);

  pinnacle_clearflags();

  result->buttonFlags = data[0] & 0x3F;
  result->xValue = data[1];
  if (data[0] & 0x08){
    result->xValue *= -1
  }
  result->yValue = data[2];
  if (data[0] & 0x10){
    result->yValue *= -1
  }

  result->touchDown = result->xValue != 0;
}

void pinnacle_scale(absData_t * result){
  result->xValue -= PINNACLE_X_LOWER;
  result->xValue /= PINNACLE_X_RANGE/512;

  result->yValue -= PINNACLE_Y_LOWER;
  result->yValue /= PINNACLE_Y_RANGE/512;
}

// bool pinnacle_touchdown(void){
//   if (ztotal/MOVING_AVERAGE_WINDOW <= PINNACLE_Z_THRESHOLD) { return false;}
//   if (touchData.xValue == 0) { return false;}
//   if (ytotal/MOVING_AVERAGE_WINDOW == 0) { return false;}
//   return true;
// }

void pointing_device_init(void){
  SPI_Init(SPI_SPEED_FCPU_DIV_8 | SPI_ORDER_MSB_FIRST | SPI_MODE_MASTER);

  TP_CS_INIT;
  TP_DR_INIT;

  TP_CS_HI;

  pinnacle_clearflags();
  writeregister(0x03, SYSCONFIG_1);
  writeregister(0x05, FEEDCONFIG_2);
  writeregister(0x04, 0x01);
  writeregister(0x0A, MOVING_AVERAGE_WINDOW);

  for (int i = 0; i < MOVING_AVERAGE_WINDOW; i++){
    x[i] = 0;
    y[i] = 0;
    z[i] = 0;
  }

}

void pointing_device_task(void){
  // Motion has occurred on the trackpad
  if (TP_DR_READ) {
    pinnacle_getrelative(&touchData);
    uprintf("x:%" PRIu16 ", y:%" PRIu16 ", z:%" PRIu16 "\n", touchData.xValue, touchData.yValue);

    if (pinnacle_touchdown()){
      int8_t dx, dy;
      // wait_ms(10);

      dx = touchData.xValue;
      dy = touchData.yValue;
      // uprintf("dx, dy: (%d, %d)\n\n\n", dx, dy);
      // dz = touchData->zValue - touchData_prev->zValue;

      report_mouse_t currentReport = pointing_device_get_report();
      if (isScrollMode)
      {
        currentReport.h = dx * SCROLL_SPEED_MULTIPLIER;
        currentReport.v = dy * SCROLL_SPEED_MULTIPLIER;
      }
      else
      {
        currentReport.x = dx * POINTER_SPEED_MULTIPLIER;
        currentReport.y = dy * POINTER_SPEED_MULTIPLIER;
      }

      pointing_device_set_report(currentReport);
      pointing_device_send();

    } 
  }
}
