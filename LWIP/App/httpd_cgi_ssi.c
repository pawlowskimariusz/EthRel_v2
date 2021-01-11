/**
  ******************************************************************************
  * @file    LwIP/LwIP_HTTP_Server_Raw/Src/httpd_cg_ssi.c
  * @author  MCD Application Team
  * @brief   Webserver SSI and CGI handlers
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lwip/debug.h"
#include "lwip/tcp.h"
#include "lwip/apps/httpd.h"
#include "http_cgi_ssi.h"


#include <string.h>
#include <stdlib.h>


extern unsigned char ToggleButt;
/* we will use character "t" as tag for CGI */
char const* TAGCHAR="t";
char const** TAGS=&TAGCHAR;


/* CGI handler for LED control */
const char * LEDS_CGI_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

void httpd_cgi_init(void);

/* Html request for "/leds.cgi" will start LEDS_CGI_Handler */
const tCGI LEDS_CGI={"/", LEDS_CGI_Handler};

/* Cgi call table, only one CGI used */
tCGI CGI_TAB[1];


/**
  * @brief  CGI handler for LEDs control
  */
const char * LEDS_CGI_Handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
  uint32_t i=0;

  /* We have only one SSI handler iIndex = 0 */
  if (iIndex==0)
  {
    /* All LEDs off */

	 HAL_GPIO_WritePin(GPIOC, Rel0_Pin|Rel1_Pin|Rel2_Pin|Rel3_Pin, GPIO_PIN_SET);
    /* Check cgi parameter : application GET /leds.cgi?led=2&led=4 */
    for (i=0; i<iNumParams; i++)
    {
    	printf("Param[%d] %s\n\r",(int)i,pcParam[i]);

      /* check parameter "led" */

        /* Switch LED1 ON if 1 */
        if(strncmp(pcParam[i], "rel0",4) ==0)
        {
        	printf("Relay 0 - ON\n\r");
        	HAL_GPIO_WritePin(GPIOC, Rel0_Pin, GPIO_PIN_RESET);
        }
        /* Switch LED2 ON if 2 */
        else if(strncmp(pcParam[i], "rel1",4) ==0)
        {
        	printf("Relay 1 - ON\n\r");
        	HAL_GPIO_WritePin(GPIOC, Rel1_Pin, GPIO_PIN_RESET);
        }
        /* Switch LED3 ON if 3 */
        else if(strncmp(pcParam[i], "rel2",4) ==0)
        {
        	printf("Relay 2 - ON\n\r");
        	HAL_GPIO_WritePin(GPIOC, Rel2_Pin, GPIO_PIN_RESET);
        }

        /* Switch LED4 ON if 4 */
        else if(strncmp(pcParam[i], "rel3",4) ==0)
        {
        	printf("Relay 3 - ON\n\r");
        	HAL_GPIO_WritePin(GPIOC, Rel3_Pin, GPIO_PIN_RESET);
        }

    }
  }
  /* uri to send after cgi call*/
  return "/index.shtml";
}

/**
  * @brief  Http webserver Init
  */
void http_server_init(void)
{
  /* Httpd Init */
  httpd_init();



  /* configure CGI handlers (LEDs control CGI) */
  CGI_TAB[0] = LEDS_CGI;
  http_set_cgi_handlers(CGI_TAB, 1);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
