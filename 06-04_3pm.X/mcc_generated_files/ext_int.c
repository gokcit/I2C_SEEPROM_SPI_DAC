/**
   Section: Includes
 */

#include "ext_int.h"
#include <stdbool.h>

extern bool ForeBuffer_Is_Empty;
//***User Area Begin->code: Add External Interrupt handler specific headers 

//***User Area End->code: Add External Interrupt handler specific headers

/**
   Section: External Interrupt Handlers
*/
 
 void __attribute__ ((weak)) EX_INT1_CallBack(void)
{
    // Add your custom callback code here
}

/**
  Interrupt Handler for EX_INT1 - INT1
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT1Interrupt(void)
{
    //***User Area Begin->code: INT1 - External Interrupt 1***
	
//    if(ForeBuffer_Is_Empty){
    SwapBuffers();          // Swap and I2C page read
    IFS1bits.INT1IF = 0;    // clear the interrupt flag
//    }
	//EX_INT1_CallBack();
    
	//***User Area End->code: INT1 - External Interrupt 1***
    //EX_INT1_InterruptFlagClear();
}
/**
    Section: External Interrupt Initializers
 */
/**
    void EXT_INT_Initialize(void)

    Initializer for the following external interrupts
    INT1
*/
void EXT_INT_Initialize(void)
{
    /*******
     * INT1
     * Clear the interrupt flag
     * Set the external interrupt edge detect
     * Enable the interrupt, if enabled in the UI. 
     ********/
    EX_INT1_InterruptFlagClear();   
    EX_INT1_PositiveEdgeSet();
    EX_INT1_InterruptEnable();
}
