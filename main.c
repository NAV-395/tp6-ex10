#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
cyhal_pwm_t pwm_obj;
int main(void)
{
    cy_rslt_t result;

    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    __enable_irq();

    cyhal_gpio_init (CYBSP_USER_LED , CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG , 1);
    cyhal_gpio_init (P9_1 , CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, 0);
  //  cyhal_gpio_init (P9_2 , CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, 0);
    cyhal_gpio_init(CYBSP_USER_BTN, CYHAL_GPIO_DIR_INPUT,CYHAL_GPIO_DRIVE_PULLUP, CYBSP_BTN_OFF);
    cyhal_gpio_init(P9_4, CYHAL_GPIO_DIR_INPUT,CYHAL_GPIO_DRIVE_PULLUP, 1);
    cyhal_gpio_init(P9_7, CYHAL_GPIO_DIR_INPUT,CYHAL_GPIO_DRIVE_PULLUP, 1);
    cyhal_pwm_init(&pwm_obj, P9_2, NULL);

    for (;;)
    {

    	if(cyhal_gpio_read(CYBSP_USER_BTN)==0){
    	 cyhal_system_delay_ms(250);
    	 cyhal_gpio_toggle(CYBSP_USER_LED);
    	}

    	if(cyhal_gpio_read(P9_4)==0){
    		cyhal_system_delay_ms(250);
    		for(int i=0;i<5;i++){
    			cyhal_gpio_write(P9_1, 1);
    			cyhal_system_delay_ms(250);
    			cyhal_gpio_write(P9_1, 0);
    			cyhal_system_delay_ms(250);
    		}
    	}
    	if(cyhal_gpio_read(P9_7)==0){
    		cyhal_system_delay_ms(250);
    		int x=100;
    		while(x!=-20){
    		   cyhal_pwm_set_duty_cycle(&pwm_obj,x,5000);
    		   cyhal_pwm_start(&pwm_obj);
    		   cyhal_system_delay_ms(200);
    		   x-=20;
    		}
    		 cyhal_pwm_stop(&pwm_obj);
    	}
    }
}

