#include <18F4620.h>
#device adc = 10 //Usamos 10 bits para que su rango sea de 0 a 1,024
#fuses HS, NOFCMEN, NOIESO, PUT, NOBROWNOUT, NOWDT
#fuses NOPBADEN, NOMCLR, STVREN, NOLVP, NODEBUG
#use delay(clock=16000000)

#use fast_io(b)   //Se emplea la directiva de Fast_io
#use fast_io(c)   //Se emplea la directiva de Fast_io
#use fast_io(d)   //Se emplea la directiva de Fast_io


#define TX_232        PIN_C6 
#define RX_232        PIN_C7
#use RS232(BAUD=9600, XMIT=TX_232, RCV=RX_232, BITS=8, PARITY=N, STOP=1)
long valorDecimal = 0, valorDecimal2 = 0; //Variables a usar en nuestros puertos
void main(void) //Programa principal
{
   setup_oscillator(OSC_16MHZ); //Configuramos nuestro oscillador a 16MHZ
   setup_adc(ADC_CLOCK_INTERNAL); //Configurar el uso del reloj interno 
   set_tris_b(0x00); //Declaramos nuestros puertos en modo salida
   set_tris_c(0x00); //Declaramos nuestros puertos en modo salida 
   set_tris_d(0x00); //Declaramos nuestros puertos en modo salida
   setup_adc_ports(AN0_TO_AN1); //Iniciamos puertos AN0 y AN1 como puertos ADC
   while(1) //Abrimos un ciclo infinito
   {
      set_adc_channel(0); //Puerto AN0 como transmisor
      valorDecimal = read_adc(); //Leemos el valor en AN0
      set_adc_channel(1); //Puerto AN1 como transmisor
      valorDecimal2 = read_adc(); //Leemos el valor en AN1
      printf("Valores %f, %f", (float)valorDecimal, (float)valorDecimal2);
   }
}