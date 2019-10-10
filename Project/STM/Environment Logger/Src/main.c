/* USER CODE BEGIN Header */

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/**
 * @brief			A holding structure for a decimal separated number.
 * @param 			ones The decimal ones of the number.
 * @param 			tens The decimal tens of the number.
 */
typedef struct {
	uint8_t ones;
	uint8_t tens;
} decimalSeperatedValue;

/**
 * @brief			A holding structure for all parameters tracked by the MCP7940 RTC.
 */
typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t weekday;
	uint8_t date;
	uint8_t month;
	uint8_t year;
} time;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ADC_Channels 3
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */
void writeDACVoltage(float);
void writeDAC(uint16_t *);

float readADC		(uint8_t);
float readADCMean(uint8_t);

void setRTCTime(time);
void setRTCSeconds(uint8_t);
void setRTCMinutes(uint8_t);
void setRTCHours(uint8_t);
void setRTCWeekday(uint8_t);
void setRTCDate(uint8_t);
void setRTCMonth(uint8_t, uint8_t);
void setRTCYear(uint8_t);

time 	getRTCTime();
uint8_t getRTCSeconds();
uint8_t getRTCMinutes();
uint8_t getRTCHours();
uint8_t getRTCWeekday();
uint8_t getRTCDate();
uint8_t getRTCMonth();
uint8_t getRTCYear();

uint8_t startRTC();
uint8_t stopRTC();
uint8_t getRTCOscillatorStatus();

uint8_t mean(uint16_t *);
float   meanf(float    *);

decimalSeperatedValue seperateDecimalValues(uint8_t);
uint8_t mergeDecimalSeperatedValue(decimalSeperatedValue);
decimalSeperatedValue extractRegisterValues(uint8_t, uint8_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static uint8_t UARTbuffer[1];

static time t = {
		  .seconds = 50,
		  .minutes = 59,
		  .hours   = 23,
		  .weekday = 7,
		  .date	   = 10,
		  .month   = 10,
		  .year	   = 19
};

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, UARTbuffer, sizeof(UARTbuffer));

  writeDACVoltage(2.1);



  setRTCTime(t);
  startRTC();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    t = getRTCTime();
	HAL_Delay(1000);

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DAC_GPIO_Port, DAC_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED0_Pin|LED1_Pin|LED3_Pin|LED3B3_Pin 
                          |LED4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ADC_GPIO_Port, ADC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SW0_Pin SW1_Pin SW2_Pin SW3_Pin */
  GPIO_InitStruct.Pin = SW0_Pin|SW1_Pin|SW2_Pin|SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : DAC_Pin */
  GPIO_InitStruct.Pin = DAC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(DAC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED0_Pin LED1_Pin LED3_Pin LED3B3_Pin 
                           LED4_Pin */
  GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin|LED3_Pin|LED3B3_Pin 
                          |LED4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ADC_Pin */
  GPIO_InitStruct.Pin = ADC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ADC_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_3_IRQn);

}

/* USER CODE BEGIN 4 */

/**
 * @brief Transmit a 10-bit value to the external MCP4911 DAC.
 * The command assembles a transmitting stream and transmits it to the DAC.
 * Configure bits are hard coded by the coefficients in the summing line to predefined bit values.
 * @param n: The 10-bit DAC value. Bits 15-10 are nulled to 0 by default.
 * @retval None
 */
void writeDACNumber(uint16_t n){
	uint8_t data[2];

	data[1] = (1*BUF + 1*GA + 1*SHDN);							// Set configuration bits
	data[1] |=((n & 0x03FF) >> 6);								// Add 4 MSB to RHS
	data[0] = ((n * 0x003F) << 2);								// Add 6 LSb to LHS

	HAL_GPIO_WritePin(DAC_GPIO_Port, DAC_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, data, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(DAC_GPIO_Port, DAC_Pin, GPIO_PIN_SET);
}

/**
 * @brief Command the external MCP4911 DAC to output a set voltage between 0 and 3V3
 * If the input exceeds this range the output is set to 0V;
 * @param V: The desired voltage output. Set to 0 if out of 0-3V3 range.
 * @retval None
 */
void writeDACVoltage(float V){
	if(V < 0.0)
		V = 0.0;
	writeDACNumber((uint16_t) ( (V/3.3) * 0x3FF) & 0x3FF);
}

/**
 * @brief 	Read the mean value of channel on the external SPI MCP3008 ADC in single mode (not differential)
 * @Note 	This function takes 10 readings in quick succession and averages the result.
 * 			This reduces the effect of random errors and settling time.
 * 			Should only be used for low request frequencies.
 * @param channel: 	The channel of the ADC to read from (CH0-CH3)
 * @retval 			The value Voltage of the reading (3V3 reference assumed)
 */
float readADCMean(uint8_t channel){
	float ADC_Values[10];

	for(int i = 0; i<10; i++){
		ADC_Values[i] = readADC(channel);
	}

	float Mean_ADC_Voltage = meanf(ADC_Values);

	return Mean_ADC_Voltage;
}

/**
 * @brief 			Read a channel on the external SPI MCP3008 ADC in single mode (not differential)
 * @param channel: 	The channel of the ADC to read from (CH0-CH3)
 * @retval 			The value Voltage of the reading (3V3 reference assumed)
 */
float readADC(uint8_t channel){
	uint8_t ADC_Tx[3];
	uint8_t ADC_Rx[3];

	ADC_Tx[2] = 0x01;
	ADC_Tx[1] = SNGL + channel;
	ADC_Tx[0] = 0x00;

	HAL_GPIO_WritePin(ADC_GPIO_Port, ADC_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, ADC_Tx, ADC_Rx, 3, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(ADC_GPIO_Port, ADC_Pin, GPIO_PIN_SET);

	float ADC_Value = ( ( ((ADC_Rx[1] & 0x3) << 8) + ADC_Rx[0]) << 1) * 3.3/1024.0;

	return ADC_Value;
}

/**
 * @brief			Set all data fields of the MCP7940 RTC.
 * @param 			.
 * @retval			A time struct containing the current RTC information.
 */
void setRTCTime(time t){
	setRTCSeconds	(t.seconds);
	setRTCMinutes	(t.minutes);
	setRTCHours		(t.hours);
	setRTCWeekday	(t.weekday);
	setRTCMonth		(t.month, t.year);
	setRTCYear		(t.year);
}
void setRTCSeconds(uint8_t sec){
	sec %= 60;
	decimalSeperatedValue s = seperateDecimalValues(sec);
	uint8_t RTC_Tx[1] = {(s.tens<<4) | s.ones};
	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDR<<1, RTC_SEC_ADDR, 1, RTC_Tx, 1, HAL_MAX_DELAY);
}
void setRTCMinutes(uint8_t min){
	min %= 60;
	decimalSeperatedValue s = seperateDecimalValues(min);
	uint8_t RTC_Tx[1] = {(s.tens<<4) | s.ones};
	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDR<<1, RTC_MIN_ADDR, 1, RTC_Tx, 1, HAL_MAX_DELAY);
}
void setRTCHours(uint8_t hour){
	hour %= 24;
	decimalSeperatedValue s = seperateDecimalValues(hour);
	uint8_t RTC_Tx[1] = {~0x40 & ((s.tens<<4) | s.ones)};
	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDR<<1, RTC_HOUR_ADDR, 1, RTC_Tx, 1, HAL_MAX_DELAY);
}
void setRTCWeekday(uint8_t weekday){
	if(weekday > 7)
		weekday = 1;

	uint8_t RTC_Tx[1] = {weekday};
	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDR<<1, RTC_WEEKDAY_ADDR, 1, RTC_Tx, 1, HAL_MAX_DELAY);
}
void setRTCDate(uint8_t date){
	if(date > 31)
		date = 1;

	decimalSeperatedValue s = seperateDecimalValues(date);
	uint8_t RTC_Tx[1] = {(s.tens<<4) | s.ones};
	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDR<<1, RTC_DATE_ADDR, 1, RTC_Tx, 1, HAL_MAX_DELAY);
}
void setRTCMonth(uint8_t month, uint8_t year){
	if(month > 12)
		month = 1;
	decimalSeperatedValue s = seperateDecimalValues(month);

	uint8_t leapyear;
	if(year % 4 ==0){
		if(year % 100 != 0){
			if(year%400 == 0){
				leapyear = 0x20;
			}
			else{
				leapyear = 0x00;
			}
		}
		else{
			leapyear = 0x20;
		}
	}
	else{
		leapyear = 0x00;
	}

	uint8_t RTC_Tx[1] = {leapyear | (s.tens<<4) | s.ones};
	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDR<<1, RTC_MONTH_ADDR, 1, RTC_Tx, 1, HAL_MAX_DELAY);
}
void setRTCYear(uint8_t year){
	year %= 100;
	decimalSeperatedValue s = seperateDecimalValues(year);
	uint8_t RTC_Tx[1] = {(s.tens<<4) | s.ones};
	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDR<<1, RTC_YEAR_ADDR, 1, RTC_Tx, 1, HAL_MAX_DELAY);
}

/**
 * @brief			Read all data fields of the MCP7940 RTC.
 * @param 			None.
 * @retval			The current time set on the RTC.
 */
time 	getRTCTime(){
	time t;
	t.seconds = getRTCSeconds();
	t.minutes = getRTCMinutes();
	t.hours	  = getRTCHours();
	t.weekday = getRTCWeekday();
	t.date	  = getRTCDate();
	t.month	  = getRTCMonth();
	t.year	  = getRTCYear();
	return t;
}
uint8_t getRTCSeconds(){
	uint8_t RTC_Rx[1];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDR<<1, RTC_SEC_ADDR, 1, RTC_Rx, 1, HAL_MAX_DELAY);
	uint8_t sec = mergeDecimalSeperatedValue(extractRegisterValues(RTC_Rx[0], 3));
	return sec;
}
uint8_t getRTCMinutes(){
	uint8_t RTC_Rx[1];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDR<<1, RTC_MIN_ADDR, 1, RTC_Rx, 1, HAL_MAX_DELAY);
	uint8_t min = mergeDecimalSeperatedValue(extractRegisterValues(RTC_Rx[0], 3));
	return min;
}
uint8_t getRTCHours(){
	uint8_t RTC_Rx[1];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDR<<1, RTC_HOUR_ADDR, 1, RTC_Rx, 1, HAL_MAX_DELAY);
	uint8_t hour = mergeDecimalSeperatedValue(extractRegisterValues(RTC_Rx[0], 2));
	return hour;
}
uint8_t getRTCWeekday(){
	uint8_t RTC_Rx[1];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDR<<1, RTC_WEEKDAY_ADDR, 1, RTC_Rx, 1, HAL_MAX_DELAY);
	uint8_t weekday = RTC_Rx[0] & 0x07;
	return weekday;
}
uint8_t getRTCDate(){
	uint8_t RTC_Rx[1];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDR<<1, RTC_DATE_ADDR, 1, RTC_Rx, 1, HAL_MAX_DELAY);
	uint8_t date = mergeDecimalSeperatedValue(extractRegisterValues(RTC_Rx[0], 2));
	return date;
}
uint8_t getRTCMonth(){
	uint8_t RTC_Rx[1];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDR<<1, RTC_MONTH_ADDR, 1, RTC_Rx, 1, HAL_MAX_DELAY);
	uint8_t month = mergeDecimalSeperatedValue(extractRegisterValues(RTC_Rx[0], 1));
	return month;
}
uint8_t getRTCYear(){
	uint8_t RTC_Rx[1];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDR<<1, RTC_YEAR_ADDR, 1, RTC_Rx, 1, HAL_MAX_DELAY);
	uint8_t year = mergeDecimalSeperatedValue(extractRegisterValues(RTC_Rx[0], 4));
	return year;
}

/**
 * @brief			Start the MCP7940 RTC.
 * @param 			None.
 * @retval			The OSCRUN bit on the RTC. 1 = running, 0 = not running (oscillator failure).
 */
uint8_t startRTC(){
	decimalSeperatedValue s = seperateDecimalValues(getRTCSeconds());

	uint8_t RTC_Tx[1] = {0x80 | (s.tens<<4) | s.ones};

	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDR<<1, RTC_SEC_ADDR, 1, RTC_Tx, 1, HAL_MAX_DELAY);

	HAL_Delay(3);						// Delay by 3ms to give margin for ~1ms time for OSCRUN bit to set

	return getRTCOscillatorStatus();
}

/**
 * @brief			Stop the MCP7940 RTC.
 * @param 			None.
 * @retval			The OSCRUN bit on the RTC. 1 = running (failure to stop), 0 = not running (success)
 */
uint8_t stopRTC(){
	setRTCSeconds(getRTCSeconds());		// This effectively clears the ST bit while retaining the seconds value.
	HAL_Delay(3);						// ~1ms of no oscillator is required before the OSCRUN bit is changed
	return getRTCOscillatorStatus();
}

/**
 * @brief			Read the run status of the MCP7940 RTC.
 * @param 			None.
 * @retval			The OSCRUN bit on the RTC. 1 = running, 0 = not running (stopped or oscillator failure)
 */
uint8_t getRTCOscillatorStatus(){
	uint8_t RTC_Rx[1];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDR<<1, RTC_WEEKDAY_ADDR, 1, RTC_Rx, 1, HAL_MAX_DELAY);
	uint8_t oscStatus = (RTC_Rx[0] & 0x20) >> 5;
	return oscStatus;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);

	switch(GPIO_Pin){
		case SW0_Pin:

			break;
		case SW1_Pin:

			break;
		case SW2_Pin:

			break;
		case SW3_Pin:

			break;
		default:
			break;
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	HAL_UART_Transmit(&huart1, UARTbuffer, sizeof(UARTbuffer), HAL_MAX_DELAY);

	writeDACVoltage((float) (((UARTbuffer[0]-'0') * (3.3/10))));

	HAL_UART_Receive_IT(&huart1, UARTbuffer, sizeof(UARTbuffer));
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

}

uint8_t mean(uint16_t * a){
	uint8_t sum = 0;
	int n = (sizeof(a) / sizeof(a[0]));
	for(int i = 0 ; i< n ; i++){
		sum+=a[i];
	}
	return (uint8_t)(sum / n);
}
float meanf(float * a){
	float sum = 0.0;
	int n = (sizeof(a) / sizeof(a[0]));

	for(int i = 0 ; i< n ; i++){
		sum+=a[i];
	}
	return (float)(sum / n);
}

/**
 * @brief			Separate a binary number into the decimal tens and ones components.
 * @param 			n The number to be separated.
 * @retval			s The structure for a decimal separated number.
 */
decimalSeperatedValue seperateDecimalValues(uint8_t n){
	decimalSeperatedValue s;
	s.ones = n % 10;
	s.tens = (n - s.ones) / 10;

	return s;
}

/**
 * @brief			Recombine a decimal separated structure to the original number.
 * @param 			s The decimal separated number.
 * @retval			The numerical value of the decimal separated number.
 */
uint8_t mergeDecimalSeperatedValue(decimalSeperatedValue s){
	return s.tens*10 + s.ones;
}

/**
 * @brief			Extract the value of a register read from the MCP7940 RTC.
 * @note			The RTC follows the separated decimal value format.
 * @param 			reg The raw register value read.
 * @param			n_tens The number of bits that constitute tens decimal bits within reg.
 * @retval			s The separated tens and ones extracted from reg.
 */
decimalSeperatedValue extractRegisterValues(uint8_t reg, uint8_t n_tens){
	decimalSeperatedValue s;
	s.tens = (reg & ( (1<<n_tens) - 1)<<4) >> 4;
	s.ones = reg & 0x0F;

	return s;
}




/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
