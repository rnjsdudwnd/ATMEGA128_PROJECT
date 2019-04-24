#include <avr/io.h> //The header file for Input&OutPut in AVR
#include <util/delay.h> // The header file for Delay Function
#include "lcd.h" //The header file for Text LCD
#define M1_Forward 0x10
#define M1_Reverse 0x20
#define M1_Enable 0x20

//The function for Voltage which use output in LCD
void printf_2dot1(uint16_t _temp); 


int main(void)
{
	unsigned char LED_Data =0x00;
	DDRC=0x0F;
	unsigned char FND_DATA_TBL []={0x3F,0X06,0X5B,0X4F,0X66,0X6D,0x7C,0X07};		DDRA=0xFF;
//----------------------------------------------------------------------
	unsigned int DoReMi[8] = {523,587, 659, 698, 783, 1046};
	unsigned int AdData =0; //10bit variable for 'ADC'
	float v_temp; //Variable for Value of Voltage
	lcdInit(); //Resetting Text LCD
	ADMUX=0x01; // ACD Multiplexer Selection Register, 0000 0001, Chose ADC1
	
	ADCSRA=0x87; // A/D Converter Control and Status Register A, 1000 0111
	//permit 'ADC', Prescaler at 128
//----------------------------------------------------------------------
	
	//DDRB =0x80; // PWM OUTPUT, OCR1C
	TCCR1A |= 0x8A;
	TCCR1B |= 0x19;
	TCCR1C =0x00;
	TCNT1 =0x0000;
//----------------------------------------------------------------------
	DDRD =0x30;
	DDRB = 0xA0;
//----------------------------------------------------------------------
	
	
	PORTD=M1_Forward;

    while (1) 
    {//----------------------------------------------------------------------		PORTC=LED_Data;
		LED_Data++;
		if(LED_Data >0x0F) LED_Data=0;
		
//----------------------------------------------------------------------
		//Read 'ADC' through ADC1
		ADCSRA |= 0x40;	// 0100 0000
		while((ADCSRA & 0x10)==0x00); //ADIF AD
		AdData=ADC;
		v_temp = (float)AdData *33 /1023;
		printf_2dot1(v_temp);

		if(AdData<=128)
		{

			PORTA=FND_DATA_TBL[0];
			ICR1= 0;
			PORTD|=0x30;
			//
			LED_Data=0x00;
			PORTC=LED_Data;
		}
		else if(AdData<=256)
		{
			
			PORTA=FND_DATA_TBL[1];
			ICR1= 14745600/DoReMi[0];
			OCR1C=ICR1/2; //Duty Ratio 50% PIEZO
			OCR1A=ICR1/7; //Duty Ratio 50% MOTOR
			PORTD=M1_Reverse;
			//----------------------------------------------------------------------			PORTC=LED_Data;
			LED_Data++;
			if(LED_Data >0x0F) LED_Data=0;
			_delay_ms(1000);
			
		}
		else if(AdData<=400)
		{
			PORTA=FND_DATA_TBL[2];
			ICR1= 14745600/DoReMi[1];
			OCR1C=ICR1/2; //Duty Ratio 50%
			OCR1A=ICR1/7; //Duty Ratio 50%
			PORTD=M1_Reverse;
			//----------------------------------------------------------------------			PORTC=LED_Data;
			LED_Data++;
			if(LED_Data >0x0F) LED_Data=0;
			_delay_ms(800);
		}
		else if(AdData<=512)
		{
			PORTA=FND_DATA_TBL[3];
			ICR1= 14745600/DoReMi[2];
			OCR1C=ICR1/2; //Duty Ratio 50%
			OCR1A=ICR1/4; //Duty Ratio 50%
			PORTD=M1_Reverse;
			//----------------------------------------------------------------------			PORTC=LED_Data;
			LED_Data++;
			if(LED_Data >0x0F) LED_Data=0;
			_delay_ms(600);
			
		}
		else if(AdData<=640)
		{
			PORTA=FND_DATA_TBL[4];
			ICR1= 14745600/DoReMi[3];
			OCR1C=ICR1/2; //Duty Ratio 50%
			OCR1A=ICR1/4; //Duty Ratio 50%
			PORTD=M1_Reverse;
			//----------------------------------------------------------------------			PORTC=LED_Data;
			LED_Data++;
			if(LED_Data >0x0F) LED_Data=0;
			_delay_ms(400);
		}
		else if(AdData<=768)
		{
			PORTA=FND_DATA_TBL[5];
			ICR1= 14745600/DoReMi[4];
			OCR1C=ICR1/2; //Duty Ratio 50%
			OCR1A=ICR1/2; //Duty Ratio 50%
			PORTD=M1_Reverse;
			//----------------------------------------------------------------------			PORTC=LED_Data;
			LED_Data++;
			if(LED_Data >0x0F) LED_Data=0;
			_delay_ms(200);
			
		}
		else if(AdData<=896)
		{
			PORTA=FND_DATA_TBL[6];
			ICR1= 14745600/DoReMi[5];
			OCR1C=ICR1/2; //Duty Ratio 50%
			OCR1A=ICR1/2; //Duty Ratio 50%
			PORTD=M1_Reverse;
			//----------------------------------------------------------------------			PORTC=LED_Data;
			LED_Data++;
			if(LED_Data >0x0F) LED_Data=0;
			_delay_ms(100);
			
		}
		else if(AdData<=1024)
		{
			PORTA=FND_DATA_TBL[7];
			ICR1= 14745600/DoReMi[6];
			OCR1C=ICR1/2; //Duty Ratio 50%
			OCR1A=ICR1; //Duty Ratio 50%
			PORTD=M1_Reverse;
			//----------------------------------------------------------------------			PORTC=LED_Data;
			LED_Data++;
			if(LED_Data >0x0F) LED_Data=0;
			_delay_ms(10);
			
		}
//----------------------------------------------------------------------
		
//----------------------------------------------------------------------
		_delay_ms(10);		
    }
}

void printf_2dot1(uint16_t _temp) {
	uint8_t s100,s10;
	lcdGotoXY(0,0); 
	lcdPrintData("WIND",4);
	s100 = _temp/100; 
	if(s100> 0) lcdDataWrite(s100+'0'); 
	else lcdPrintData(" ",1); 
	s10 = _temp%100; 
	lcdDataWrite((s10/10)+'0'); 
	lcdPrintData(".",1); 
	lcdDataWrite((s10%10)+'0'); 
	lcdPrintData("NOTE",4);
}

