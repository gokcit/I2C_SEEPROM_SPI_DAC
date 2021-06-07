/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/spi1.h"
   
volatile uint16_t FIFO_0[256];
volatile uint16_t FIFO_1[256];

volatile uint16_t counter = 0;
volatile uint16_t dataOut;

volatile uint16_t *BackBuffer;
volatile uint16_t *ForeBuffer;

volatile bool ForeBuffer_Is_Empty;
volatile bool BackBuffer_Is_Empty;

volatile bool FIFO_0_Is_Empty = true; // delete if not used!
volatile bool FIFO_1_Is_Empty = true;

volatile uint16_t ForeBufferPtr = 0;     // for swapping the buffers

volatile uint8_t addrLow, addrHigh, addrUpper, ctrlByteWr, ctrlByteRd;

volatile bool DAC_FIFO_InUse_Now = false; // check if sending data to DAC
volatile bool endOfFile = false;          // True when we reach the end of file

volatile uint16_t data;
volatile uint16_t counterDAC = 0;       // 8-bit address count
volatile uint16_t dummy_1;

volatile uint32_t addr = 0x00000000;

volatile uint8_t testLED = 0;

void I2C_Initialize(){
    
    // initialize the I2C hardware
    // Baud Rate Generator Value: I2CBRG 19;   
    I2C1BRG = 0x9;
    // ACKEN disabled; STREN disabled; GCEN disabled; SMEN disabled; DISSLW enabled; I2CSIDL disabled; ACKDT Sends ACK; SCLREL Holds; RSEN disabled; IPMIEN disabled; A10M 7 Bit; PEN disabled; RCEN disabled; SEN disabled; I2CEN enabled; 
    I2C1CON = 0x8000;
    // P disabled; S disabled; I2COV disabled; IWCOL disabled; 
    I2C1STAT = 0x00;
}


void I2C_InterruptEnable(){
    // clear the master interrupt flag
    IFS1bits.MI2C1IF = 0;
    // enable the master interrupt
    IEC1bits.MI2C1IE = 1;
}

void Initialize_PPBuffer(){
    ForeBufferPtr = 0;
    ForeBuffer = FIFO_0;
    BackBuffer = FIFO_1;
}

void I2C_clearIF(void)
{
    IFS1bits.MI2C1IF = 0;
}

void I2C_Start_Master(){
    // Start   
    I2C1CONbits.SEN = 1;                // Start Enable
    while(!IFS1bits.MI2C1IF){};         // Wait till Master Interrupt
    I2C_clearIF();                      // Clear IF
    while(I2C1CONbits.SEN){};           // check if SEN is cleared
    // Start complete
}

void I2C_Restart_Master(){
    
    I2C1CONbits.RSEN = 1;                 // RSEN bit set
    while(!IFS1bits.MI2C1IF){};           // Wait till Master Interrupt
    I2C_clearIF();                        // Clear IF
    while(I2C1CONbits.RSEN);              // check if RSEN is cleared
}

void I2C_Stop(){
    //while(!(I2C1CON && 0b11111 == 0x0000)){}; // Wait till The five Least Significant bits of I2CxCON are ?0?
    I2C1CONbits.PEN = 1;
    while(!IFS1bits.MI2C1IF){};             // Wait till Master Interrupt
    I2C_clearIF();                          // Clear IF
    while(I2C1CONbits.PEN);                 // Check if PEN is cleared
}

void I2C_SendOneByte(uint16_t oneByte){
    I2C1TRN = oneByte;                      // Send Device Address Byte
    while(!IFS1bits.MI2C1IF){};             // Wait till Master Interrupt
    I2C_clearIF();                          // Clear IF
    while(I2C1STATbits.ACKSTAT){};          // Wait till receive ACK from the slave 
}

uint16_t I2C_ReceiveOneByte(){
    I2C1CONbits.RCEN = 1;                   // Receive Enable
    while(!IFS1bits.MI2C1IF){};             // Wait till Master Interrupt
    I2C_clearIF();                          // Clear IF
    while(I2C1CONbits.RCEN){};              // Check if RCEN is cleared
    while(!I2C1STATbits.RBF)                // Check if RBF is set
    while(!IFS1bits.MI2C1IF){};             // Wait till Master Interrupt
    I2C_clearIF();                          // Clear IF
    data = I2C1RCV;
    while(I2C1STATbits.RBF)                 // Check if RBF is cleared
        
    return data;
}

uint16_t I2C_CurrentRead(){
    
    I2C_Start_Master();                     // Initiate current address read
    
    I2C_SendOneByte(ctrlByteRd);            // Send Device Address Byte with a read indication
    
    data = I2C_ReceiveOneByte();            // Read the first byte
    
    I2C_Stop();
    
    return data;
}

uint16_t I2C_ReceiveOneByte_ACK(){
    I2C1CONbits.RCEN = 1;                   // Receive Enable
    //while(!IFS1bits.MI2C1IF){};             // Wait till Master Interrupt
    //I2C_clearIF();                          // Clear IF
    while(I2C1CONbits.RCEN){};              // Check if RCEN is cleared
    while(!I2C1STATbits.RBF)                // Check if RBF is set
    while(!IFS1bits.MI2C1IF){};             // Wait till Master Interrupt
    I2C_clearIF();                          // Clear IF
    data = I2C1RCV;
    while(I2C1STATbits.RBF)                 // Check if RBF is cleared
    I2C1CONbits.ACKDT = 0;                  // NACK from master
    I2C1CONbits.ACKEN = 1;
                    
    while(I2C1CONbits.ACKEN){};             // Check if ACKEN is cleared
    //while(!IFS1bits.MI2C1IF){};             // Wait till Master Interrupt
    //I2C_clearIF();                          // Clear IF
    return data;
}

void I2C_ForeBuffer_Fill(){ // Page read - Sequential Read Initiated by a Current Read
    counterDAC = 0;
    // AT24CM02 page 22: Sequential reads are initiated by either a current address read or a random read
    //ForeBuffer[0] = I2C_CurrentRead();
    LED_SetHigh();
    dummy_1 = I2C_CurrentRead();
    LED_SetLow();
    I2C_Start_Master();
    I2C_SendOneByte(ctrlByteRd);                // Send Device Address Byte with a read indication
    counter = 0;
    while(counter <= 0xFF){                     // Read the next 256 bytes
        data = I2C_ReceiveOneByte_ACK() << 4;   // shift 8 data bits to the middle
        //data = counter << 4;    
        LED_Toggle();
                                                // MCP4802 datasheet page 22:
                                                // 0 ? GA SHDN D7 D6 D5 D4 D3 D2 D1 D0 x x x x
                                                // bit15                                     bit0
        ForeBuffer[counter] = data;    // Configuration bits and the 8 data bits
        counter++;
    }
    Nop();
    dummy_1 = I2C_ReceiveOneByte();       // Read the last byte
    LED_SetLow();    
    I2C_Stop();   
//    if(*ForeBuffer == 0x0FF0){
////        endOfFile = true;
//        asm ("RESET");
//    }
    //ForeBuffer_Is_Empty = false;
}

uint16_t I2C_Read_RandomAddress(){           // read address 0x00000000
    
    I2C_Start_Master();                     // Initiate one random address read
       
    I2C_SendOneByte(ctrlByteWr);            // Send Device Address Byte with a write indication    
    
    I2C_SendOneByte(addrHigh);              // Send EEPROM Address High Byte
            
    I2C_SendOneByte(addrLow);               // Send EEPROM Address Low Byte
    
    I2C_Restart_Master();                   // Restart
    
    I2C_SendOneByte(ctrlByteRd);            // Send Device Address Byte with a read indication 
    
    data = I2C_ReceiveOneByte();       // Receive one byte and stop
            
    I2C_Stop();
    
    return data;
}

void SwapBuffers(){ 
    // BackBuffer is emptied in the interrupt handler
    // Then swapped here.
    if(ForeBufferPtr == 0){
        ForeBufferPtr = 1;
        ForeBuffer = FIFO_1;
        BackBuffer = FIFO_0;
    }else{
        ForeBufferPtr = 0;
        ForeBuffer = FIFO_0;
        BackBuffer = FIFO_1;
    }
    ForeBuffer_Is_Empty = true; 
    I2C_ForeBuffer_Fill();
}
/*
                         Main application
 */
int main(void)
{
    
    I2C1CONbits.I2CEN = 0;                  // close the bus first - for debugging reset
    SPI1STATbits.SPIEN = 0;                 // close the bus
    endOfFile = false;
    // initialize the device
    SYSTEM_Initialize();
    //INTERRUPT_Initialize();
    
//    
//    IFS0bits.T1IF = 0; // Clear the Timer1 interrupt status flag
//    IEC0bits.T1IE = 1; // Enable Timer1 interrupts
    
    I2C_Initialize();
    Initialize_PPBuffer();
    //SPI_Reinitialize();                     // Enhanced Buffer Mode disabled
    
    I2C_InterruptEnable();
    //SPI_InterruptEnable();
    
    // Variables
    addrLow   = (addr >> 0 ) & 0x000000FF; //mask out the low order addr bits
    addrHigh  = (addr >> 8 ) & 0x000000FF; //mask out the high order addr bits
    addrUpper = (addr >> 16) & 0x00000003; //mask out the 2 upper addr bits

    ctrlByteWr = addrUpper << 1;            //construct the control byte w/write bit
    ctrlByteWr = 0xA8 | ctrlByteWr;         // see AT24CM02 data sheet p. 17

    ctrlByteRd = addrUpper << 1;            //construct the control byte w/read bit
    ctrlByteRd = 0xA9 | ctrlByteRd;         // see AT24CM02 data sheet p. 17
        
    data = I2C_Read_RandomAddress();        // read the first byte
    
    I2C_ForeBuffer_Fill();                       // Load FIFO_0
    SwapBuffers();
    I2C_ForeBuffer_Fill();                       // Load FIFO_1
    ForeBuffer_Is_Empty = false;                //ForeBuffer = FIFO_1
    BackBuffer_Is_Empty = false;                //BackBuffer = FIFO_0
    
    TMR1_Initialize();
    // Start the Timer
    
    nCS_DAC_SetDigitalOutput();
    
    while (1)
    {
    }

    return 1;
}
/**
 End of File
*/

