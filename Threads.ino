 /* O programa a seguir utiliza o timer 1 do ATmega328P para criar um sistema de threads,
  *permitindo assim que sejam realizadas multiplas tarefas que devem ser executadas em tempos diferentes. 
  * No exemplo foram utilizados 3 threads no timer 1, com o objetivo de cada thread sendo inverter
  *o estado de um pino com uma frequência diferente cada pino.
  */
 
 void setup() {
  DDRD |= (1<<2)|(1<<3)|(1<<4); //Define os pinos 2, 3 e 4 do conjunto D como saídas
  PORTD &= 0x00; //Coloca as saídas em nível baixo
  
  noInterrupts(); //Desabilita interrupções
  TCCR1A = 0x00; //Operar o timer no modo normal
  TCCR1B = 0x01; //Define o prescaler (atraso) do timer em 1 ciclo de clock
  TCNT1 = 49536; //Valor inicial do Timer 1

  //Tempo de contagem = 62,5nS x 1 x (65536-49536) = 1mS

  TIMSK1 = 0x01; //Interrupção do estouro do timer habilitada
  interrupts(); //Habilita interrupções
}

ISR(TIMER1_OVF_vect) //Quando o timer estourar o seguinte será executado
{
  TCNT1 = 49536; //Carrega novamente o valor inicial no timer
  
  static int td1=0, td2=0, td3=0; //Declara as três threads do exemplo

  td1++; //Incrementa as threads a cada estouro do timer
  td2++;
  td3++;

  if(td1==50) //Quando a thread 1 alcançar o tempo definido para ser executado (50 x 1mS) será invertido o pino relacionado a thread
  {
    PORTD ^= (1<<PD2); //Inverte o pino PD2
    td1=0;
  }

  if(td2==500) //Quando a thread 2 alcançar o tempo definido para ser executado (500 x 1mS) será invertido o pino relacionado a thread
  {
    PORTD ^= (1<<PD3); //Inverte o pino PD3
    td2=0;
  }

  if(td3==1000) //Quando a thread 3 alcançar o tempo definido para ser executado (1000 x 1mS) será invertido o pino relacionado a thread
  {
    PORTD ^= (1<<PD4); //Inverte o pino PD4
    td3=0;
  } 
}

void loop() {
 //Aqui você poderá colocar funções menos prioritárias para o seu código
}
