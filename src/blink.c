#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned int estado;
int boton;

int main(void)
{
  DDRB = 0x08; //Configuracion del puerto. B3 como salida
  DDRA = 0X00;

  estado = 0x00; //Alto

  boton = 0;

  int tiempo = 0;

  GIMSK |= (1 << INT0); 

  MCUCR |= (1 << ISC00); 
  
  MCUCR |= (1 << ISC01);

  MCUCR |= (1 << PUD);

  sei();
  
  
  //Parpadear
  while (1) {
    PORTB = estado; 
    _delay_ms(1000);
    if(boton == 1){
      estado = 0x08;
      //PORTB = 0x08; _delay_ms(1000);
    }
  }
}

ISR(INT0_vect){
    boton = 1; 
}