#include <18F4620.h>
#device adc = 10 //Usamos 10 bits para que su rango sea de 0 a 1,024
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#use fast_io(b)   //Se emplea la directiva de Fast_io
#use fast_io(c)   //Se emplea la directiva de Fast_io
#use fast_io(d)   //Se emplea la directiva de Fast_io


int resultadoUno = 0, resultadoDos = 0; //Variables a usar en nuestros puertos
int conversionUno = 0, conversionDos = 0; //Variables a usar como rangos
int rangoFinal (int rango); //Prototipo de funcion para validar los LEDs	
#int_AD //Habilitamos las interrupciones AD
void interrupcion_AD(void) //Funcion de nuestra interrupcion
{
	if(conversionUno == 1) 
	{
		resultadoUno = read_adc(ADC_READ_ONLY); //Se lee el resultado 
	}
	if(conversionDos == 1)
	{
		resultadoDos = read_adcc(ADC_READ_ONLY);
	}
	read_adc(ADC_START_ONLY); //Configuracion para leer valores adc 
}


void main(void) //Programa principal
{
   setup_oscillator(OSC_16MHZ); //Configuramos nuestro oscillador a 16MHZ
   setup_adc(ADC_CLOCK_DIV_32); //Configurar el uso del reloj interno 
   setup_adc_ports(AN0_TO_AN1); //Iniciamos puertos AN0 y AN1 como puertos ADC
   enable_interrupts(INT_AD);
   enable_interrupts(GLOBAL);
   set_tris_b(0x00); //Declaramos nuestros puertos en modo salida
   set_tris_c(0x00); //Declaramos nuestros puertos en modo salida 
   set_tris_d(0x00); //Declaramos nuestros puertos en modo salida
   while(1) //Abrimos un ciclo infinito
   {
      set_adc_channel(0); //Puerto AN0 como transmisor
      conversionUno = read_adc(); //Leemos el valor en AN0
      set_adc_channel(1); //Puerto AN1 como transmisor
      conversioDos = read_adc(); //Leemos el valor en AN1
	  output_b(rango);
	  output_c(rango);
	  output_d(rango);
   }
}

int rangoFinal (int rango)
{
	if(rango >= 0 && rango <= 100)
	{
		rango = 1;
	}
	if(rango >= 101 && rango <= 200)
	{
		rango = 2;
	}
	if(rango >= 201 && rango <= 300)
	{
		rango = 4;
	}
	if(rango >= 301 && rango <= 400)
	{
		rango = 8;
	}
	if(rango >= 401 && rango <= 500)
	{
		rango = 16;
	}
	if(rango >= 501 && rango <= 600)
	{
		rango = 32;
	}
	if(rango >= 601 && rango <= 700)
	{
		rango = 64;
	}
	if(rango >= 701 && rango <= 800)
	{
		rango = 128;
	}
	if(rango >= 800 && rango <= 899)
	{
		rango = 256;
	}
	if(rango >= 990 && rango <= 1023)
	{
		rango = 512;
	}
	return rango;
}