/*
 * File:   newmain.c
 * Author: thilakram
 *
 * Created on 23 March, 2021, 10:00 AM
 */
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include"Declarations.h"
void initializer(void);
void viewMenu();
void editMenu(void);
void editValues(void);
void dataPass(uint8_t data);
void display1(uint32_t data);
void display2(uint32_t data);
void led(void);
void displayString(const uint8_t* string);
uint8_t enterSwitch(void);
uint8_t upSwitch(void);
uint8_t menuSwitch(void);
uint8_t selectSwitch(void);
uint8_t resetSwitch(void);
uint32_t displayChange(uint32_t);
uint32_t increment(uint32_t value);
int32_t countPlus(void);
int32_t countMinus(void);
void eepromRead(void);
void encoder(void);

void main(void) {
    initializer();
    eepromRead();
    while(1){
        editMenu();
        editValues();
        
        if(resetSwitch()){
            if(viewMenuPointer == 0){
                if(currentClothLength){
                    previousCurrentClothLength = currentClothLength;
                    eeprom_write(0x11,previousCurrentClothLength/UINT32_C(10000));
                    eeprom_write(0x12,(previousCurrentClothLength/100)%100);
                    eeprom_write(0x13,previousCurrentClothLength%100);
                }
                resetCounter += 1;
                eeprom_write(0x14,resetCounter/UINT32_C(10000));
                eeprom_write(0x15,(resetCounter/100)%100);
                eeprom_write(0x16,resetCounter%100);
                currentClothLength = 0;
                metrePerMin = 0;
                currentClothLengthBalanceMinus = 0;
                currentClothLengthBalancePlus = 0;
            }
            else if(viewMenuPointer == 2){
                resetCounter = 0;
            }
            else if(viewMenuPointer == 3){
                hourMeter = 0;
            }
        }
        
        if(currentClothLength >= (actualClothLength * 100)){
            relay1 = 1;
        }
        else{
            relay1 = 0;
        }
        if(currentClothLength >= (warningClothLength * 100)){
            relay2 = 1;
        }
        else{
            relay2 = 0;
        }
        
        if(skipCount >= 200){
            editMenuPointer = 0;
            viewMenuPointer = 0;
            editValue = 0;
            currentDisplay = 0;
            skipCount = 0;
        }
        
        if(encoderSkipCount >= 200){
            metrePerMinCounter = 0;
            metrePerMin = 0;
        }
        
        if(metrePerMinCounter >= pulse){
            metrePerMin = (12 * circumference) / timerCount;
            metrePerMinCounter = 0;
            timerCount = 0;
            if(metrePerMin > 999)metrePerMin = 999;
        }
        if(hourMeterCounter >= 7200){
            hourMeter += 1;
            hourMeterCounter = 0;
        }
        viewMenu();
        if(changed){
            if(count == 1){
                currentClothLength+=countingPulse;
                metrePerMinCounter += 1;
                encoderSkipCount = 0;
            }
            if(count == 2){
                currentClothLength-=countingPulse;
                metrePerMinCounter += 1;
                encoderSkipCount = 0;
            }     
            changed = 0;
        }
        encoder();
    }
    return;
}
void initializer(void){
    
//    CMCON = 0X07;
//    ADCON0 = 0x00;
//    ADCON1 = 0x06;
    ANSEL = 0;
    ANSELH = 0;
    nRBPU = 0;
    INTEDG = 1;
    GIE=1;          //Enable Global Interrupt
    PEIE=1;         //Enable the Peripheral Interrupt
    INTE = 1;       //Enable RB0 as external Interrupt pin
    INTF=0;
    RBIE = 1;
    RBIF = 0;
    WPUB = 0xF1;
    IOCB = 0xC0;    
    T1CON = 0x20; // Timer0 with external freq and 8 as prescalar
    TMR1H=0x0B;     // Load the time value(0xBDC) for 100ms delay
    TMR1L=0xE5; 
    TMR1IE=1;   
    TMR1ON = 1;
    TRISA = 0xF0;
    TRISB = 0xF1;
    TRISC = 0xFF;
    TRISD = 0xFF;
    TRISE = 0x01;
    
}

void eepromRead(void){
    
    actualClothLength = (unsigned int)eeprom_read(0x00)*UINT32_C(10000) + (unsigned int)eeprom_read(0x01)*100 + (unsigned int)eeprom_read(0x02);
    warningClothLength = (unsigned int)eeprom_read(0x03)*UINT32_C(10000) + (unsigned int)eeprom_read(0x04)*100 + (unsigned int)eeprom_read(0x05);
    circumference = (unsigned int)eeprom_read(0x06)*UINT32_C(10000) + (unsigned int)eeprom_read(0x07)*100 + (unsigned int)eeprom_read(0x08);
    pulse = (unsigned int)eeprom_read(0x09)*UINT32_C(10000) + (unsigned int)eeprom_read(0x0A)*100 + (unsigned int)eeprom_read(0x0B);
    
    currentClothLength = (unsigned int)eeprom_read(0x0C)* UINT32_C(10000) + (unsigned int)eeprom_read(0x0D)*100 + (unsigned int)eeprom_read(0x0E);
    previousCurrentClothLength = (unsigned int)eeprom_read(0x11)* UINT32_C(10000) + (unsigned int)eeprom_read(0x12)*100 + (unsigned int)eeprom_read(0x13);

    resetCounter = (unsigned int)eeprom_read(0x14)* UINT32_C(10000) + (unsigned int)eeprom_read(0x15)*100 + (unsigned int)eeprom_read(0x16);
    hourMeter = (unsigned int)eeprom_read(0x17)* UINT32_C(10000) + (unsigned int)eeprom_read(0x18)*100 + (unsigned int)eeprom_read(0x19);
    
    if(currentClothLength > UINT32_C(999999)){
        currentClothLength = 100;
    }
    if(previousCurrentClothLength > UINT32_C(999999)){
        previousCurrentClothLength = 100;
    }
    if(actualClothLength > UINT32_C(9999)){
        actualClothLength = 999;
    }
    if(warningClothLength > UINT32_C(9999)){
        warningClothLength = 989;
    }
    if(resetCounter > UINT32_C(99999)){
        resetCounter = 100;
    }
    if(hourMeter > UINT32_C(99999)){
        hourMeter = 100;
    }
    if(circumference > UINT32_C(9999)){
        circumference = 500;
    }
    if(pulse > UINT32_C(9999)){
        pulse = 4;
    }
    
    countingPulse = (circumference)/pulse;
    metrePerMinCounter = 0;
}

void __interrupt(high_priority) highISR()
{
    
    if(RBIF == 1){
        if(!encoderA && !encoderB){
            encoderFlag = 1;
        }
        if(encoderFlag && !encoderA && encoderB){count=1;changed = 1;}
        if(encoderFlag && encoderA && !encoderB){count=2;changed = 1;}
        if(encoderA && encoderB)encoderFlag = 0;
    }
    if(TMR1IF==1){
        timerCount += 1;
        skipCount += 1;
        TMR1H=0x0B;     // Load the time value(0xBDC) for 100ms delay
        TMR1L=0xE5; 
        TMR1IF=0;  
        if(encoderSkipCount){
            hourMeterCounter += 1;
        }
        encoderSkipCount += 1;
    }
    if (INTF == 1) {//External Interrupt detected
        
            eeprom_write(0x0C,currentClothLength/UINT32_C(10000));
            eeprom_write(0x0D,(currentClothLength/100)%100);
            eeprom_write(0x0E,currentClothLength%100);
            eeprom_write(0x17,hourMeter/UINT32_C(10000));
            eeprom_write(0x18,(hourMeter/100)%100);
            eeprom_write(0x19,hourMeter%100);
            GIE = 0;
    }
    

    INTF = 0; 
    RBIF = 0;// clear the interrupt flag after done with it
}

void viewMenu(){
    
    if(viewMenuPointer == 0  && editMenuPointer == 0){
        display1(currentClothLength/10);
    }
    if(viewMenuPointer == 1  && editMenuPointer == 0){
        display1(previousCurrentClothLength/10);
    }
    if(viewMenuPointer == 2  && editMenuPointer == 0){
        display1(resetCounter);
    }
    if(viewMenuPointer == 3  && editMenuPointer == 0){
        display1(hourMeter);
    }
    display2(metrePerMin);
    led();
    
    if(editMenuPointer == 0 && upSwitch()){
        viewMenuPointer += 1; 
    }
    if(viewMenuPointer == 4){
        viewMenuPointer = 0;
    }
}

void editMenu(void){
    
    if(editMenuPointer == 1){
        if(editValue == 1){
            display1(actualClothLength);
            actualClothLength = displayChange(actualClothLength);
        }
        else{
            displayString("F Set");
        }
    }
    else if(editMenuPointer == 2){
        if(editValue == 2){
            display1(warningClothLength);
            warningClothLength = displayChange(warningClothLength);
        }
        else{
            displayString("P Set");
        }
    }
    else if(editMenuPointer == 3){
        if(editValue == 3){
            display1(password);
            password = displayChange(password);
        }
        else{
            displayString("PASS ");
        }
    }
    else if(editMenuPointer == 4){
        if(editValue == 4){
            display1(circumference);
            circumference = displayChange(circumference);
        }
        else{
            displayString("Circu");
        }
    }
    else if(editMenuPointer == 5){
        if(editValue == 5){
            display1(pulse); 
            pulse = displayChange(pulse);
        }
        else{
            displayString("PuLSe");
        }
    }
    
    if(menuSwitch() == 1 && editValue == 0){
        if(editMenuPointer != 3){
            editMenuPointer += 1;
        }
        else if(password == tk_password){
            editMenuPointer += 1;
        }
        else{
            editMenuPointer = 0;
        }
    }
    if(editMenuPointer == 6){
        editMenuPointer = 0;
        password = 0;
    }
}

void editValues(void){
    if(editMenuPointer && enterSwitch()){
        if(editValue){
            
            if(editValue == 3 && password != tk_password){
                editMenuPointer = 0;
                editValue = 0;
                currentDisplay = 0;
                password = 0;
                return;
            }
            
        if(actualClothLength == 0){
            actualClothLength = 999;
        }
        if(warningClothLength == 0){
            warningClothLength = 989;
        }
        if(circumference == 0){
            circumference = 500;
        }
        if(pulse == 0){
            pulse = 4;
        }
            
            editValue = 0;
            currentDisplay = 0;
            
            eeprom_write(0x00,actualClothLength/UINT32_C(10000));
            eeprom_write(0x01,(actualClothLength/100)%100);
            eeprom_write(0x02,actualClothLength%100);
            
            eeprom_write(0x03,warningClothLength/UINT32_C(10000));
            eeprom_write(0x04,(warningClothLength/100)%100);
            eeprom_write(0x05,warningClothLength%100);
            
            eeprom_write(0x06,circumference/UINT32_C(10000));
            eeprom_write(0x07,(circumference/100)%100);
            eeprom_write(0x08,circumference%100);
            
            eeprom_write(0x09,pulse/UINT32_C(10000));
            eeprom_write(0x0A,(pulse/100)%100);
            eeprom_write(0x0B,pulse%100);
            
            editMenuPointer += 1;
            
            countingPulse = (circumference)/pulse;
            
        }
        else if(editValue == 0){
            editValue = editMenuPointer;
            currentDisplay = 1;
        }
    }
}

void dataPass(uint8_t data){
    for (uint8_t i=0 ; i<8 ; i++){
        DATA = (data >> i) & 0x01;
        CLK = 1;
        CLK = 0;
    }
    STROBE = 1;
    STROBE = 0;
}

void display1(uint32_t value){
    
    if(value/10000 == 0){
        if(viewMenuPointer == 0 && editMenuPointer == 0){
            dataPass(FONT_DEFAULT[44] | 0x20);
        }
        else if(viewMenuPointer == 1 && editMenuPointer == 0){
            dataPass(FONT_DEFAULT[82] | 0x20);
        }
        else if(viewMenuPointer == 2 && editMenuPointer == 0){
            dataPass(FONT_DEFAULT['d' - 32] | 0x20);
        }
        else if(viewMenuPointer == 3 && editMenuPointer == 0){
            dataPass(FONT_DEFAULT['H' - 32] | 0x20);
        }
        else if(editMenuPointer == 1){
            dataPass(FONT_DEFAULT['F' - 32] | 0x20);
        }
        else if(editMenuPointer == 2){
            dataPass(FONT_DEFAULT['P'- 32] | 0x20);
        }
        else if(editMenuPointer == 3){
            dataPass(FONT_DEFAULT['P'- 32] | 0x20);
        }
        else if(editMenuPointer == 4){
            dataPass(FONT_DEFAULT['C'- 32] | 0x20);
        }
        else if(editMenuPointer == 5){
            dataPass(FONT_DEFAULT['P'- 32] | 0x20);
        }
    }
    else{
        dataPass(segCode[value/10000]);
    }
    A = 0;
    B = 0;
    C = 1;
    D = 1;
    __delay_ms(dispDelay);
      
    if(currentDisplay == 1 && blinkValue > 10){
        dataPass (0x00);
    }
    else{
        dataPass(segCode[(value/1000)%10]);
    }
    A = 0;
    B = 0;
    C = 1;
    D = 0;
    __delay_ms(dispDelay);

    if(currentDisplay == 2 && blinkValue > 10){
        dataPass (0x00);
    }
    else{
        uint8_t dot = 0;
        if(viewMenuPointer == 1 || viewMenuPointer == 0){
            dot = 0x20;
        }
        if(editMenuPointer){
            dot = 0;
        }
        dataPass(segCode[(value/100)%10] | dot);
    }
    A = 0;
    B = 0;
    C = 0;
    D = 1;
    __delay_ms(dispDelay);
    
    if(currentDisplay == 3 && blinkValue > 10){
        dataPass (0x00);
    }
    else{
        uint8_t dot1 = 0;
        if(editMenuPointer == 1 || editMenuPointer == 2 || viewMenuPointer == 3){
            dot1 = 0x20;
        }
        dataPass(segCode[(value/10)%10] | dot1);
    }
    A = 0;
    B = 0;
    C = 0;
    D = 0;
    __delay_ms(dispDelay);
    
    if(currentDisplay == 4   && blinkValue > 10){
        dataPass (0x00);
    }
    else{
        dataPass(segCode[value%10]);
    }
    A = 1;
    B = 1;
    C = 0;
    D = 1;
    __delay_ms(dispDelay);
    
    blinkValue += 1;
    if(blinkValue > 20){
        blinkValue = 0;
    }

}

void display2(uint32_t value){
    
    dataPass(segCode[value/100]);
    A = 0;
    B = 1;
    C = 0;
    D = 1;
    __delay_ms(dispDelay);
      
    dataPass(segCode[(value/10)%10] | 0x20);
    A = 1;
    B = 0;
    C = 0;
    D = 1;
    __delay_ms(dispDelay);

    dataPass(segCode[value%10]);
    A = 1;
    B = 0;
    C = 0;
    D = 0;
    __delay_ms(dispDelay);

}

void led(){
    uint8_t value = 0;
//            EDC
    if(relay1){
        value += 128;
    }
    if(relay2){
        value += 32;
    }
    if(encoderFlag){
        value += 8;
    }
    dataPass(value);
    A = 1;
    B = 1;
    C = 0;
    D = 0;
    __delay_ms(dispDelay);
}


void displayString(const uint8_t* string){
    dataPass(FONT_DEFAULT[string[0]-32]);
    A = 0;
    B = 0;
    C = 1;
    D = 1;
    __delay_ms(dispDelay);
    
    dataPass(FONT_DEFAULT[string[1]-32]);
    A = 0;
    B = 0;
    C = 1;
    D = 0;
    __delay_ms(dispDelay);
    
    dataPass(FONT_DEFAULT[string[2]-32]);
    A = 0;
    B = 0;
    C = 0;
    D = 1;
    __delay_ms(dispDelay);
    
    
    dataPass(FONT_DEFAULT[string[3]-32]);
    A = 0;
    B = 0;
    C = 0;
    D = 0;
    __delay_ms(dispDelay);
    
    dataPass(FONT_DEFAULT[string[4]-32]);
    A = 1;
    B = 1;
    C = 0;
    D = 1;
    __delay_ms(dispDelay);
}    


uint8_t enterSwitch(void){

    if(enter == 1 && enterFlag == 1){
        enterFlag = 0;
        return 1;
    }
    if(enter == 0){
        enterFlag = 1;
        skipCount = 0;
    }
    return 0;
}

uint8_t selectSwitch(void){

    if(select == 1 && selectFlag == 1){
        selectFlag = 0;
        return 1;
    }
    if(select == 0){
        selectFlag = 1;
        skipCount = 0;
    }
    return 0;
}

uint8_t upSwitch(void){

    if(up == 1 && upFlag == 1){
        upFlag = 0;
        return 1;
    }
    if(up == 0){
        upFlag = 1;
        skipCount = 0;
    }
    return 0;
}

uint8_t menuSwitch(void){

    if(menu == 1 && menuFlag == 1){
        menuFlag = 0;
        return 1;
    }
    if(menu == 0){
        menuFlag = 1;
        skipCount = 0;
    }
    return 0;
}

uint8_t resetSwitch(void){

    if(reset == 1 && resetFlag == 1){
        resetFlag = 0;
        return 1;
    }
    if(reset == 0){
        resetFlag = 1;
        skipCount = 0;
    }
    return 0;
}

uint32_t displayChange(uint32_t value){
    if(selectSwitch() == 1){
        currentDisplay += 1;
        if(currentDisplay == 5){
        currentDisplay = 1;}
    }
    if(upSwitch() == 1){
       value =  increment(value);
    }
    return value;
}

uint32_t increment(uint32_t value){
    
//    if(currentDisplay == 1){
//        if(value%100000>=90000){
//            value-=90000;
//        }
//        else{
//            value += 10000;
//        }}
    
    if(currentDisplay == 1){
        if(value%10000>=9000){ 
            value -= 9000;
        }
        else{
            value += 1000;
        }
    }
    
    if(currentDisplay == 2){
        if(value%1000>=900){
            value -= 900;
        }
        else{
            value += 100;
        }
    }
    
    if(currentDisplay == 3){
        if(value%100>=90){ 
            value -= 90;
        }
        else{
            value += 10;
        }
    }
    
    if(currentDisplay == 4){
        if(value%10>=9){
            value -= 9;
        }
        else{
            value += 1;
        }
    }
    return value;
}

int32_t countPlus(void){
    int32_t value = countingPulse + currentClothLengthBalancePlus;
    currentClothLengthBalancePlus = value % 100;
    return value/100;
}

int32_t countMinus(void){
    int32_t value = currentClothLengthBalanceMinus - countingPulse;
    currentClothLengthBalanceMinus = value % 100;
    return value/100;
}

void encoder(void){
    
//    if(changed){
//            if(count == 1){
//                currentClothLength+=countPlus();
//                metrePerMinCounter += 1;
//                encoderSkipCount = 0;
//            }
//            if(count == 2){
//                currentClothLength+=countMinus();
//                metrePerMinCounter += 1;
//                encoderSkipCount = 0;
//            }     
//            changed = 0;
//    }
    
    if(currentClothLength > UINT32_C(1000010)){
        currentClothLength = 0;
    }
    if(currentClothLength > UINT32_C(999999)){
        currentClothLength = UINT32_C(999999);
    }
}
