  /**
    ******************************************************************************
    * @file UART1_Interrupt\main.c
    * @brief This file contains the main function for a basic communication between UART1 and UART3 using interrupts.
    * @author  MCD Application Team
    * @version V2.0.4
    * @date     26-April-2018
    ******************************************************************************
    * @attention
    *
    * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
    *
    * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
    * You may not use this file except in compliance with the License.
    * You may obtain a copy of the License at:
    *
    *        http://www.st.com/software_license_agreement_liberty_v2
    *
    * Unless required by applicable law or agreed to in writing, software 
    * distributed under the License is distributed on an "AS IS" BASIS, 
    * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    * See the License for the specific language governing permissions and
    * limitations under the License.
    *
    ******************************************************************************
    */ 

  /* Includes ------------------------------------------------------------------*/
  #include "stm8l15x.h"
  #include "stm8l15x_it.h"    /* SDCC patch: required by SDCC for interrupts */
  #include "main.h"
  #include "stdio.h"
  /**
    * @addtogroup UART1_Interrupt
    * @{
    */
  /* Private typedef -----------------------------------------------------------*/
  /* Private variables ---------------------------------------------------------*/


  /* Private function prototypes -----------------------------------------------*/
  static void CLK_Config(void);
  static void UART_Config(void);
  #define PUTCHAR_PROTOTYPE int putchar (int c)
  #define GETCHAR_PROTOTYPE int getchar (void)
  /**
    * @brief  Main program.
    * @param  None
    * @retval None
    */
  void main(void)
  {
    char ans;
    /* CLK configuration -----------------------------------------*/
    CLK_Config();

    /* UART configuration -----------------------------------------*/
    UART_Config();  

    printf("\n\rUSART Example: retarget the C library printf()\getchar() functions to the USART\n\r");
    printf("\n\rEnter Text\n\r");

    while (1)
    {
      ans = getchar();
      printf("#%c#", ans);
    }
  }

  /**
    * @brief  Configure system clock to run at 16Mhz
    * @param  None
    * @retval None
    */
  static void CLK_Config(void)
  {
      /* Initialization of the clock */
      /* Clock divider to HSI/1 */
    // CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
      CLK_DeInit();
      CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

      // GPIO_ExternalPullUpConfig(GPIOE, GPIO_Pin_6, ENABLE);
      // GPIO_ExternalPullUpConfig(GPIOE, GPIO_Pin_7, ENABLE);

  }

  /**
    * @brief  UART1 and UART3 Configuration for interrupt communication
    * @param  None
    * @retval None
    */
  static void UART_Config(void)
  {
    /* Deinitializes the UART1 and UART3 peripheral */
      /* UART1 and UART3 configuration -------------------------------------------------*/
      /* UART1 and UART3 configured as follow:
            - BaudRate = 9600 baud  
            - Word Length = 8 Bits
            - One Stop Bit
            - No parity
            - Receive and transmit enabled
            - UART1 Clock disabled
      */
     USART_DeInit(USART2);
    CLK_PeripheralClockConfig(CLK_Peripheral_USART2, ENABLE);
    GPIO_ExternalPullUpConfig(GPIOE, GPIO_Pin_3, ENABLE);
    GPIO_ExternalPullUpConfig(GPIOE, GPIO_Pin_4, ENABLE);

      /* Configure the UART1 */
    USART_Init(USART2, (uint32_t)115200, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No,
              (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
    
  }
  PUTCHAR_PROTOTYPE
  {
    /* Write a character to the USART */
    USART_SendData8(USART2, c);
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);

    return (c);
  }
  /**
    * @brief Retargets the C library scanf function to the USART.
    * @param[in] None
    * @retval char Character to Read
    * @par Required preconditions:
    * - None
    */
  GETCHAR_PROTOTYPE
  {
    int c = 0;
    /* Loop until the Read data register flag is SET */
    while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData8(USART2);
  }

  #ifdef USE_FULL_ASSERT

  /**
    * @brief  Reports the name of the source file and the source line number
    *   where the assert_param error has occurred.
    * @param file: pointer to the source file name
    * @param line: assert_param error line source number
    * @retval None
    */
  void assert_failed(uint8_t* file, uint32_t line)
  { 
    /* User can add his own implementation to report the file name and line number,
      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
  }
  #endif

  /**
    * @}
    */


  /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
