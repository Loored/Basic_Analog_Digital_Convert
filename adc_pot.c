#include <18F4620.h>
#device adc = 10 
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#use fast_io(b)   
#use fast_io(c)   
#use fast_io(d)   
#use fast_io(e)

int lecturaPot1 = 0, lecturaPot2 = 0;
int leerPot(int valorLeido);
void barraPot1(int ledPot1);
void barraPot2(int ledPot2);
void ISR_AD(void);

setup_adc(ADC_CLOCK_DIV_32); //Configurar el uso del reloj interno 
setup_adc_ports(AN0_TO_AN1); //Iniciamos puertos AN0 y AN1 como puertos ADC
enable_interrupts(INT_AD);
enable_interrupts(GLOBAL);

set_tris_b(0x00); //Declaramos nuestros puertos en modo salida
set_tris_c(0x00); //Declaramos nuestros puertos en modo salida 
set_tris_d(0x00); //Declaramos nuestros puertos en modo salida
set_tris_e(0x00);
set_tris_a(0xFF);

#int_AD //Habilitamos las interrupciones AD

void main(void)
{
   int pot1 = 0, pot2 = 0, valorCalculado = 0; 
   //int conversionUno = 0, conversionDos = 0; //Variables a usar como rangos(OSC_16MHZ); //Configuramos nuestro oscillador a 16MHZ
   while(1)
   {
      set_adc_channel(0); //Puerto AN0 como transmisor
      delay_ms(20);//un momentito pa' que se active
      pot1 = read_adc(); //Leemos el valor en AN0
      delay_ms(20);//otro momentito pa' que amarre
      valorCalculado = leerPot(pot1);//guardo en una variable el valor obtenido de calcular el rango del por1
      barraPot1(valorCalculado);
      set_adc_channel(1); //Puerto AN1 como transmisor
      delay_ms(20);
      valorCalculado = 0;
      pot2 = read_adc(); //Leemos el valor en AN1
      delay_ms(20);
      valorCalculado = leerPot(pot2);
      ledEncencido(valorCalculado);
   }
}

int leerPot(int valorLeido){
	int rango = 0;
	if(valorLeido > 0 && valorLeido <= 100)
	{
		rango = 1;
	}
	if(valorLeido > 100 && valorLeido <= 200)
	{
		rango = 2;
	}
	if(valorLeido > 200 && valorLeido <= 300)
	{
		rango = 4;
	}
	if(valorLeido > 300 && valorLeido <= 400)
	{
		rango = 8;
	}
	if(valorLeido > 400 && valorLeido <= 500)
	{
		rango = 16;
	}
	if(valorLeido > 50 && valorLeido <= 600)
	{
		rango = 32;
	}
	if(valorLeido > 600 && valorLeido <= 700)
	{
		rango = 64;
	}
	if(valorLeido > 700 && valorLeido <= 800)
	{
		rango = 128;
	}
	if(valorLeido > 800 && valorLeido <= 900)
	{
		rango = 256;
	}	
	if(valorLeido > 900 && valorLeido <= 1000)
	{
		rango = 512;
	}
	if(valorLeido > 1000 && valorLeido <= 1023)
	{
		rango = 1024;
	}
	return rango;
	break;
}

int barraPot1(int ledPot1)
{
	output_b(ledPot1);
	output_c(ledPot1 >> 8);	
	break;
}

int barraPot2(int ledPot2)
{
	output_d(ledPot2);
	output_e(ledPot2 >> 8);	
	break;
}


//}
