#include "as5600.h"

#define abs(x) ((x)>0?(x):-(x))


static float angle_data_prev; //�ϴ�λ��
static float full_rotation_offset; //ת������Ȧ��

void bsp_as5600Init(void) {
  /* init i2c interface */
  
  /* init var */
  full_rotation_offset = 0;
  angle_data_prev = bsp_as5600GetRawAngle();
}

static int i2cWrite(uint8_t dev_addr, uint8_t *pData, uint32_t count) {
  int status;
  int i2c_time_out = I2C_TIME_OUT_BASE + count * I2C_TIME_OUT_BYTE;
  
  status = HAL_I2C_Master_Transmit(&AS5600_I2C_HANDLE, dev_addr, pData, count, i2c_time_out);
  return status;
}

static int i2cRead(uint8_t dev_addr, uint8_t *pData, uint32_t count) {
  int status;
  int i2c_time_out = I2C_TIME_OUT_BASE + count * I2C_TIME_OUT_BYTE;
  
  status = HAL_I2C_Master_Receive(&AS5600_I2C_HANDLE, (dev_addr | 1), pData, count, i2c_time_out);
  return status;
}

uint16_t bsp_as5600GetRawAngle(void) {
  uint16_t raw_angle;
  uint8_t buffer[2] = {0};
  uint8_t raw_angle_register = AS5600_RAW_ANGLE_REGISTER;
  
  i2cWrite(AS5600_ADDR, &raw_angle_register, 1);
  i2cRead(AS5600_ADDR, buffer, 2);
  raw_angle = ((uint16_t)buffer[0] << 8) | (uint16_t)buffer[1];
  return raw_angle;
}

float bsp_as5600GetAngle(void) {
  float angle_data = bsp_as5600GetRawAngle();
  
  return (angle_data *360/AS5600_RESOLUTION);
}

