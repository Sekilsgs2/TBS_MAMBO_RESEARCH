#include "opentx.h"
#include "mlx.h"

#define SPI_TIMEOUT                   10000000UL

#define MLX1_CS_HIGH()                 GPIOD->BSRRL = GPIO_Pin_7
#define MLX1_CS_LOW()                  GPIOD->BSRRH = GPIO_Pin_7
#define MLX2_CS_HIGH()                 GPIOE->BSRRL = GPIO_Pin_8
#define MLX2_CS_LOW()                  GPIOE->BSRRH = GPIO_Pin_8

void mlx_css1_or_css2(int mlx1_or_mlx2, int HIGH_OR_LOW)
{

  if ( mlx1_or_mlx2 )
  {
    if ( HIGH_OR_LOW )
      MLX2_CS_HIGH();
    else
      MLX2_CS_LOW();
  }
  else
  {
    if ( HIGH_OR_LOW )
      MLX1_CS_HIGH();
    else
      MLX1_CS_LOW();
  }
}

uint8_t spiWrite(uint8_t byte)
{

  while ((SPI2->SR & SPI_SR_TXE) == 0);

  SPI2->DR = byte;

  while ((SPI2->SR & SPI_SR_RXNE) == 0);

  return SPI2->DR;

}

MLX90393::MLX90393()
{
}

MLX90393::MLX90393(int mlx)
{
    mlx_num = mlx;
}

//*************************************** MAIN FUNCTIONS ***************************************

void MLX90393::EX(char *receiveBuffer, int mode)
{
    write_buffer[0] = 0x80;
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1);
    }
}

void MLX90393::SB(char *receiveBuffer, char zyxt, int mode)
{
    write_buffer[0] = (0x10)|(zyxt);
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1);
    }
}

void MLX90393::SWOC(char *receiveBuffer, char zyxt, int mode)
{
    write_buffer[0] = (0x20)|(zyxt);
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1);
    }
}

void MLX90393::SM(char *receiveBuffer, char zyxt, int mode)
{
    write_buffer[0] = (0x30)|(zyxt);
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1);
    }
}

void MLX90393::RM(char *receiveBuffer, char zyxt, int mode)
{
    write_buffer[0] = (0x40)|(zyxt);
    for(int i=0; i<2*count_set_bits(zyxt); i++) {
        write_buffer[i+2] = 0x00;
    }
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1+2*count_set_bits(zyxt));
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1+2*count_set_bits(zyxt));
    }
}

void MLX90393::RR(char *receiveBuffer, int address, int mode)
{
    write_buffer[0] = 0x50;
    write_buffer[1] = address << 2;
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 2, 3);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 2, 3);
    }
}

void MLX90393::WR(char *receiveBuffer, int address, int data, int mode)
{
    write_buffer[0] = 0x60;
    write_buffer[1] = (data&0xFF00)>>8;
    write_buffer[2] = data&0x00FF;
    write_buffer[3] = address << 2;
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 4, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 4, 1);
    }
}

void MLX90393::RT(char *receiveBuffer, int mode)
{
    write_buffer[0] = 0xF0;
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1);
    }
}

void MLX90393::NOP(char *receiveBuffer, int mode)
{
    write_buffer[0] = 0x00;
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1);
    }
}

void MLX90393::HR(char *receiveBuffer, int mode)
{
    write_buffer[0] = 0xD0;
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1);
    }
}

void MLX90393::HS(char *receiveBuffer, int mode)
{
    write_buffer[0] = 0xE0;
    if (mode == 1) {
        Send_SPI(receiveBuffer, write_buffer, 1, 1);
    } else {
        Send_I2C(receiveBuffer, write_buffer, 1, 1);
    }
}

//************************************* COMMUNICATION LEVEL ************************************

void MLX90393::Send_SPI(char *receiveBuffer, char *sendBuffer, int sendMessageLength, int receiveMessageLength)
{
    char* tempSendBuffer = sendBuffer;
    char* tempReceiveBuffer = receiveBuffer;
    mlx_css1_or_css2(mlx_num,0);
    for(int i=0; i<sendMessageLength; i++) {
        spiWrite(*tempSendBuffer);
        tempSendBuffer++;
    }
    for(int i=0; i<receiveMessageLength; i++) {
        *receiveBuffer = spiWrite(0x00);
        receiveBuffer++;
    }
    mlx_css1_or_css2(mlx_num,1);
    receiveBuffer = tempReceiveBuffer;
}

void MLX90393::Send_I2C(char *receiveBuffer, char *sendBuffer, int sendMessageLength, int receiveMessageLength)
{
}

//*************************************** EXTRA FUNCTIONS **************************************

int MLX90393::count_set_bits(int N)
{
    int result = 0;
    while(N) {
        result++;
        N &=N-1;
    }
    return result;
}



