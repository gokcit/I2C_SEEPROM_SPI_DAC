/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ128GA010
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef _PIN_MANAGER_H
#define _PIN_MANAGER_H
/**
    Section: Includes
*/
#include <xc.h>

/**
    Section: Device Pin Macros
*/
/**
  @Summary
    Sets the GPIO pin, RA0, high using LATA0.

  @Description
    Sets the GPIO pin, RA0, high using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 high (1)
    LED_SetHigh();
    </code>

*/
#define LED_SetHigh()          (_LATA0 = 1)
/**
  @Summary
    Sets the GPIO pin, RA0, low using LATA0.

  @Description
    Sets the GPIO pin, RA0, low using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RA0 low (0)
    LED_SetLow();
    </code>

*/
#define LED_SetLow()           (_LATA0 = 0)
/**
  @Summary
    Toggles the GPIO pin, RA0, using LATA0.

  @Description
    Toggles the GPIO pin, RA0, using LATA0.

  @Preconditions
    The RA0 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RA0
    LED_Toggle();
    </code>

*/
#define LED_Toggle()           (_LATA0 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RA0.

  @Description
    Reads the value of the GPIO pin, RA0.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RA0
    postValue = LED_GetValue();
    </code>

*/
#define LED_GetValue()         _RA0
/**
  @Summary
    Configures the GPIO pin, RA0, as an input.

  @Description
    Configures the GPIO pin, RA0, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an input
    LED_SetDigitalInput();
    </code>

*/
#define LED_SetDigitalInput()  (_TRISA0 = 1)
/**
  @Summary
    Configures the GPIO pin, RA0, as an output.

  @Description
    Configures the GPIO pin, RA0, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RA0 as an output
    LED_SetDigitalOutput();
    </code>

*/
#define LED_SetDigitalOutput() (_TRISA0 = 0)
/**
  @Summary
    Sets the GPIO pin, RB1, high using LATB1.

  @Description
    Sets the GPIO pin, RB1, high using LATB1.

  @Preconditions
    The RB1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB1 high (1)
    nCS_DAC_SetHigh();
    </code>

*/
#define nCS_DAC_SetHigh()          (_LATB1 = 1)
/**
  @Summary
    Sets the GPIO pin, RB1, low using LATB1.

  @Description
    Sets the GPIO pin, RB1, low using LATB1.

  @Preconditions
    The RB1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RB1 low (0)
    nCS_DAC_SetLow();
    </code>

*/
#define nCS_DAC_SetLow()           (_LATB1 = 0)
/**
  @Summary
    Toggles the GPIO pin, RB1, using LATB1.

  @Description
    Toggles the GPIO pin, RB1, using LATB1.

  @Preconditions
    The RB1 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RB1
    nCS_DAC_Toggle();
    </code>

*/
#define nCS_DAC_Toggle()           (_LATB1 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RB1.

  @Description
    Reads the value of the GPIO pin, RB1.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RB1
    postValue = nCS_DAC_GetValue();
    </code>

*/
#define nCS_DAC_GetValue()         _RB1
/**
  @Summary
    Configures the GPIO pin, RB1, as an input.

  @Description
    Configures the GPIO pin, RB1, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB1 as an input
    nCS_DAC_SetDigitalInput();
    </code>

*/
#define nCS_DAC_SetDigitalInput()  (_TRISB1 = 1)
/**
  @Summary
    Configures the GPIO pin, RB1, as an output.

  @Description
    Configures the GPIO pin, RB1, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RB1 as an output
    nCS_DAC_SetDigitalOutput();
    </code>

*/
#define nCS_DAC_SetDigitalOutput() (_TRISB1 = 0)
/**
  @Summary
    Sets the GPIO pin, RF6, high using LATF6.

  @Description
    Sets the GPIO pin, RF6, high using LATF6.

  @Preconditions
    The RF6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF6 high (1)
    SCK1_SetHigh();
    </code>

*/
#define SCK1_SetHigh()          (_LATF6 = 1)
/**
  @Summary
    Sets the GPIO pin, RF6, low using LATF6.

  @Description
    Sets the GPIO pin, RF6, low using LATF6.

  @Preconditions
    The RF6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF6 low (0)
    SCK1_SetLow();
    </code>

*/
#define SCK1_SetLow()           (_LATF6 = 0)
/**
  @Summary
    Toggles the GPIO pin, RF6, using LATF6.

  @Description
    Toggles the GPIO pin, RF6, using LATF6.

  @Preconditions
    The RF6 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF6
    SCK1_Toggle();
    </code>

*/
#define SCK1_Toggle()           (_LATF6 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RF6.

  @Description
    Reads the value of the GPIO pin, RF6.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF6
    postValue = SCK1_GetValue();
    </code>

*/
#define SCK1_GetValue()         _RF6
/**
  @Summary
    Configures the GPIO pin, RF6, as an input.

  @Description
    Configures the GPIO pin, RF6, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF6 as an input
    SCK1_SetDigitalInput();
    </code>

*/
#define SCK1_SetDigitalInput()  (_TRISF6 = 1)
/**
  @Summary
    Configures the GPIO pin, RF6, as an output.

  @Description
    Configures the GPIO pin, RF6, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF6 as an output
    SCK1_SetDigitalOutput();
    </code>

*/
#define SCK1_SetDigitalOutput() (_TRISF6 = 0)
/**
  @Summary
    Sets the GPIO pin, RF8, high using LATF8.

  @Description
    Sets the GPIO pin, RF8, high using LATF8.

  @Preconditions
    The RF8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF8 high (1)
    SDO1_SetHigh();
    </code>

*/
#define SDO1_SetHigh()          (_LATF8 = 1)
/**
  @Summary
    Sets the GPIO pin, RF8, low using LATF8.

  @Description
    Sets the GPIO pin, RF8, low using LATF8.

  @Preconditions
    The RF8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Set RF8 low (0)
    SDO1_SetLow();
    </code>

*/
#define SDO1_SetLow()           (_LATF8 = 0)
/**
  @Summary
    Toggles the GPIO pin, RF8, using LATF8.

  @Description
    Toggles the GPIO pin, RF8, using LATF8.

  @Preconditions
    The RF8 must be set to an output.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Toggle RF8
    SDO1_Toggle();
    </code>

*/
#define SDO1_Toggle()           (_LATF8 ^= 1)
/**
  @Summary
    Reads the value of the GPIO pin, RF8.

  @Description
    Reads the value of the GPIO pin, RF8.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    uint16_t portValue;

    // Read RF8
    postValue = SDO1_GetValue();
    </code>

*/
#define SDO1_GetValue()         _RF8
/**
  @Summary
    Configures the GPIO pin, RF8, as an input.

  @Description
    Configures the GPIO pin, RF8, as an input.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF8 as an input
    SDO1_SetDigitalInput();
    </code>

*/
#define SDO1_SetDigitalInput()  (_TRISF8 = 1)
/**
  @Summary
    Configures the GPIO pin, RF8, as an output.

  @Description
    Configures the GPIO pin, RF8, as an output.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    // Sets the RF8 as an output
    SDO1_SetDigitalOutput();
    </code>

*/
#define SDO1_SetDigitalOutput() (_TRISF8 = 0)

/**
    Section: Function Prototypes
*/
/**
  @Summary
    Configures the pin settings of the PIC24FJ128GA010

  @Description
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        PIN_MANAGER_Initialize();
    }
    </code>

*/
void PIN_MANAGER_Initialize (void);



#endif
