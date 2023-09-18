#include <avr/io.h>
#include <avr/interrupt.h>
int counterTemp1, counterTemp2, counterTemp3, counterTemp4, estado, boton;
void resetCounterT1();
void resetCounter();
int main(void)
{
  DDRB = 0x3F; //Configuracion del puerto. B3 como salida
  PORTB = 0x00;
  estado = 0; //Alto
  boton = 0;
  MCUCR |= (1 << ISC00) | (1 << ISC01) | (1 << ISC10) | (1 << ISC11) | (1 << PUD); 
  GIMSK |= (1 << INT1) | (1 << INT0); 
  TCCR0B |= (1 << CS00) | (1 << CS02);//Periodo de CLKio/1024
  TIMSK |= (1 << TOIE0);
  resetCounterT1();
  resetCounter();
  sei();
  while (1) {
    switch(estado){
       case 0:
        if(boton == 0 || counterTemp4 < 700){
          estado = 0;
          PORTB = 0x1A;
          break;
        }
        else if(boton == 1 && counterTemp4 >= 700){
          estado = 1;
          resetCounter();
          resetCounterT1();
          break;         
        }
      case 1:
        if(counterTemp3 < 210){
          if(counterTemp1 < 35){
            PORTB = 0x1A;
          }
          else if(counterTemp1 >= 35 && counterTemp1 < 70){
            PORTB = 0x0A;
          }
          else{
            resetCounterT1();
          }
          break;        
        }
        else if(counterTemp2 >= 210){
          estado = 2;
          resetCounterT1();
          resetCounter(); 
          break;
        }
      case 2:
        if(counterTemp2 < 70){
          PORTB = 0x2A;
          break;
        }
        else if(counterTemp2 >= 70){
          estado = 3;
          resetCounterT1();
          resetCounter();
          break;
        }
      case 3:
        if(counterTemp4 < 700){
          PORTB = 0x25;
          break;
        }
        else if(counterTemp4 >= 700){
          estado = 4;
          resetCounterT1();
          resetCounter();
          break;
        }
      case 4:
        if(counterTemp3 < 210){
          if(counterTemp1 < 35){
            PORTB = 0x25;
          }
          else if(counterTemp1 >= 35 && counterTemp1 < 70){
            PORTB = 0x20;
          }
          else{
            resetCounterT1();
          }
          break;        
        }
        else if(counterTemp2 >= 210){
          estado = 5;
          resetCounterT1();
          resetCounter(); 
          break;
        }
      case 5:
        if(counterTemp2 < 70){
          PORTB = 0x2A;
          break;
        }
        else if(counterTemp2 >= 70){
          estado = 0;
          boton = 0;
          resetCounterT1();
          resetCounter();
          break;
        }
    }
  }
}
ISR(TIMER0_OVF_vect){
  counterTemp1 += 1;
  counterTemp2 += 1;
  counterTemp3 += 1;
  counterTemp4 += 1;
}
ISR(INT0_vect){
  boton = 1;
}
ISR(INT1_vect, ISR_ALIASOF(INT0_vect));
void resetCounterT1(){
  counterTemp1 = 0;
}
void resetCounter(){
  counterTemp2 = 0;
  counterTemp3 = 0;
  counterTemp4 = 0;
}