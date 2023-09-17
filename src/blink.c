#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//estados
#define PasoVehi 0 //auto detenido luz roja
#define ParpadeoVehi 1 //auto detenido luz parpadea
#define AltoVehi 2 //auto en movimiento luz verde
#define PasoPeaton 3 //peaton en movimiento luz verde
#define ParpadeoPeaton 4 //peaton detenido luz parpadea
#define AltoPeaton 5 //peaton detenido luz roja
unsigned int estado;
unsigned int boton;
int main(void)
{
  DDRB = 0x3F; //Configuracion del puerto. B3 como salida
  PORTB = 0x00;
  estado = 0; //Alto
  boton = 0;
  //int tiempo = 0;
  GIMSK |= (1 << INT0); 
  MCUCR |= (1 << ISC00); 
  MCUCR |= (1 << ISC01);
  GIMSK |= (1 << INT1); 
  MCUCR |= (1 << ISC10); 
  MCUCR |= (1 << ISC11);
  MCUCR |= (1 << PUD);
  sei();
  while (1) {
    if(estado == 0){
      if(boton == 0){
        estado = 0;
        PORTB = 0x1A;
      }
      else{
        estado = 1;         
      }
    }  
    else if(estado == 1){
        estado = 2; 
        PORTB = 0x1A;
        _delay_ms(5000);
        PORTB = 0x0A;
        _delay_ms(5000);
        PORTB = 0x1A;
        _delay_ms(5000);
        PORTB = 0x0A;
        _delay_ms(5000);
      }
      else if(estado == 2){
        estado = 3;
        PORTB = 0x2A;
        _delay_ms(10000);
      }
      else if(estado == 3){
        estado = 4;
        PORTB = 0x25;
        _delay_ms(50000);
      }
      else if(estado == 4){
        estado = 5;
        PORTB = 0x25;
        _delay_ms(5000);
        PORTB = 0x20;
        _delay_ms(5000);
        PORTB = 0x25;
        _delay_ms(5000);
        PORTB = 0x20;
        _delay_ms(5000); 
      }      
      else if(estado == 5){
        estado = 0;
        boton = 0;
        PORTB = 0x2A;
        _delay_ms(10000);
      }
  }
}
ISR(INT0_vect){
  boton = 1;

}
ISR (INT1_vect, ISR_ALIASOF (INT0_vect));
