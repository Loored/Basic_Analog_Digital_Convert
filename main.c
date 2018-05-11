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
float valorDecimal = 0, valorDecimal2 = 0; //Variables a usar en nuestros puertos
float rangoDecimal = 0, rangoDecimal2 = 0; //Variables a usar como rangos
float rango = 0; //Variable usada para definir rango
float rangoFinal(float rango); //Prototipo de funcion de calcular rango final
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
      //Imprimimos valores a partir de las variaciones presentadas
      //printf("Valores %f, %f \r\n", (float)valorDecimal, (float)valorDecimal2);
      //el valor de nuestros puertos se multiplica por 5 (voltaje) y se divide
      //entre 2^10(1024)
      rangoDecimal = (valorDecimal*5)/1024; 
      rangoDecimal2 = (valorDecimal2*5)/1024;
      //Imprimimos los valores de nuestros rangos
      //printf("Valor uno: %f, Valor dos: %f \r\n", (float)rangoDecimal, (float)rangoDecimal2);
      //Rango sera igual a la funcion con el valor de nuestro rango decimal
      rango = rangoFinal(rangoDecimal);
      printf("Rango es igual a: %f \r\n", rango);
      //rango = rangoFinal(rangoDecimal2);
      //printf("Rango es igual a: %.0f \r\n", rango);
   }
}

float rangoFinal(float rango) //Iniciamos funcion rangoFinal
{
   if(rango >= 0 && rango <= 0.4) //Si nuestro rango es mayor o igual a 0
   {                             //Y menor a 0.5
      rango = 1;                //Nuestro rango es 1
   }
   if(rango >= 0.5 && rango <= 0.9)
   {
      rango = 2;
   }
   if(rango >= 1.0 && rango <= 1.4)
   {
      rango = 3;
   }
   if(rango >= 1.5 && rango <= 1.9)
   {
      rango = 4;
   }
   if(rango >= 2.0 && rango <= 2.4)
   {
      rango = 5;
   }
   if(rango >= 2.5 && rango <= 2.9)
   {
      rango = 6;
   }
   if(rango >= 3.0 && rango <= 3.4)
   {
      rango = 7;
   }
   if(rango >= 3.5 && rango <= 3.9)
   {
      rango = 8;
   }
   if(rango >= 4.0 && rango <= 4.4)
   {
      rango = 9;
   }
   if(rango >= 4.5 && rango <= 5.0)
   {
      rango = 10;
   }
   return rango; //Retornamos el valor de rango
}
