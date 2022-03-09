# TBS_MAMBO_RESEARCH

Some info about TBS MAMBO:

main cpu - stm32f407
using two mlx90393 chips for each gimbal - 3d hall sensors

tbs mambo using spi2 for mlx chips
cs for first mlx90393 chip = GPIOD 7
cs for second mlx90393 chip = GPIOE 8

interrupt for first mlx90393 chip = GPIOC 5
interrupt for second mlx90393 chip = GPIOB 9

tx with sx1281 chip

PA - SKY65383-11
https://store.skyworksinc.com/datasheets/skyworks/sky65383-11%20datasheet.pdf

pc13 - reset sx1281
pe10 - busy sx1281
pe11 - dio1 sx1281
pe12 - dio2 sx1281
pe13 - dio3 sx1281
pe3 - css sx1281
pe14 - CRX - SKY65383-11
pe6 - CTX - SKY65383-11
pe15 - ??? CSD?? SKY65383-11
PB10 - clk spi2
PC2/PC3 - spi2 


SPI2 using for sx1281 and for two mlx chips with different cs pins!!!!!! 

tbs using this settings for mlx90393 chips:

	OSR	0						
	OSR2	0						
	DIG_FILT	1						
	BURST_DATA_RATE	0						
								
  TXYZ MEASURED?				
  yes	yes	yes	yes
        
	Typical	            IDLE	  STBY	  CONV_T	CONV_X	CONV_Y	CONV_Z	TOTAL
	Period Time   (ms)	0,000	  0,500	  0,192	  0,256	  0,256	  0,256	  1,460
	Current (mA)	      0,002	  1,600	  1,600	  2,290	  2,290	  2,960	  2,080
	Charge (uC)	        0,000	  0,800	  0,307	  0,586	  0,586	  0,758	  3,037
	Avg Current (uA)	  0,000	  547,9	  210,4	  401,5	  401,5	  519,0	  2080,4
								
	ODR	684,93	Hz					
	DutyCycle	100,00	%					

RESX, RESY, RESZ = 1;
OFFSETS X, Y, Z = 32768 (0x8000);

And hex values for some registers:

reg 0x0 = 0
reg 0x1 = 0x8400
reg 0x2 = 0x2A4
reg 0x4 = 0x8000
reg 0x5 = 0x8000
reg 0x6 = 0x8000

This all setting tbs using for mlx90393 chips.

I'm have added simple driver for opentx which can writing and reading regs for mlx90393 chips in tbs mambo - i'm not adding spi2 init function because crossfire fw initialising spi2 for us..








