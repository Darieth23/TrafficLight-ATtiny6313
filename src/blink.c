#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
int estado;
int boton;
int main(void)
{
  DDRB = 0x3F; //Configuracion del puerto. B3 como salida
  PORTB = 0x00;
  estado = 0; //Alto
  boton = 0;
  //int tiempo = 0;
  MCUCR |= (1 << ISC00); 
  MCUCR |= (1 << ISC01);
  MCUCR |= (1 << ISC10); 
  MCUCR |= (1 << ISC11);
  MCUCR |= (1 << PUD);
  GIMSK |= (1 << INT1); 
  GIMSK |= (1 << INT0); 
  sei();
  while (1) {
    switch(estado){
      case 0:
        if(boton == 0){
          estado = 0;
          PORTB = 0x1A;
          break;
        }
        if(boton == 1){
          estado = 1;
          break;         
        }
      case 1:
        if(1){
          estado = 2; 
          PORTB = 0x1A;
          _delay_ms(5000);
          PORTB = 0x0A;
          _delay_ms(5000);
          PORTB = 0x1A;
          _delay_ms(5000);
          PORTB = 0x0A;
          _delay_ms(5000);
          break;        
        }
        else{
          break;
          //falta
        }
      case 2:
        if(1){
          estado = 3;
          PORTB = 0x2A;
          _delay_ms(10000);
          break; 
        }
        else{
          break;
          //falta
        }
      case 3:
        if(1){
          estado = 4;
          PORTB = 0x25;
          _delay_ms(50000);          
          break;
        }
        else{
          break;
          //falta
        }
      case 4:
        if(1){
          estado = 5;
          PORTB = 0x25;
          _delay_ms(5000);
          PORTB = 0x20;
          _delay_ms(5000);
          PORTB = 0x25;
          _delay_ms(5000);
          PORTB = 0x20;
          _delay_ms(5000);
          break;
        }
        else{
          break;
          //falta
        }
      case 5:
        if(1){
          estado = 0;
          boton = 0;
          PORTB = 0x2A;
          _delay_ms(10000);
          break;
        }
        else{
          break;
          //falta
        }        
    }
  }
}
ISR(INT0_vect){
  boton = 1;
}
ISR (INT1_vect, ISR_ALIASOF (INT0_vect));
