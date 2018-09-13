//Declaracion de pines del Arduino para cada uno de los componentes
#define boton 2
#define led_rojo 4
#define led_ama 7
#define led_verde 8
#define led_peat_verde 12
#define led_peat_rojo 13
#define pot A0
#define buzzer 9

//Declaracion de variables para control del tiempo en base al potenciometro
int valorPot;
int segundos;

void setup() {
  //Declaracion de los leds y del buzzer como pines de salida
  pinMode(led_verde,OUTPUT);
  pinMode(led_ama,OUTPUT);
  pinMode(led_rojo,OUTPUT);
  pinMode(led_peat_verde,OUTPUT);
  pinMode(led_peat_rojo,OUTPUT);
  pinMode(buzzer,OUTPUT);
  //Declaracion del boton como pin de salida
  pinMode(boton,INPUT);
  //Iniciacion del puerto serial a 9600 baudios
  Serial.begin(9600);
}

void loop() {
  //Variable obtiene valor de acuerdo a la posicion del potenciometro
  valorPot = analogRead(pot);
  //Variable obtiene valor al multiplicar por 2 y dividir entre 100 el valor anterior
  //Sera el valor para determinar el numero de segundos que durara el semaforo
  segundos = (valorPot*2)/100;
  Serial.print("Segundos en verde: ");
  Serial.println(segundos);
  //Se inicia el metodo que controla el verde del semaforo
  verde();
  //Se inicia el metodo que controla el amarillo del semaforo
  amarillo();
  //Se inicia el metodo que controla el rojo del semaforo
  rojo();
}

void verde(){
  //Se enciende fijamente el verde del semaforo y el rojo del peaton
  digitalWrite(led_verde,HIGH);
  digitalWrite(led_peat_rojo,HIGH);
  //Se lleva a cabo un ciclo desde 0 hasta los x segundos obtenidos anteriormente
  for(int x=0;x<segundos;x++){
    //Esperamos un segundo
    delay(1000);
    //Comprobamos que no se haya pulsado el boton
    if(digitalRead(boton) == LOW){
      Serial.print("-----Se detuvo a los ");
      Serial.print(x+1);
      Serial.println(" segundos");
      //Si el boton fue pulsado, se detiene el ciclo
      x=segundos;
    }
  }
  //Una vez detenido el ciclo parpadea 3 veces y se mantiene apagado
  digitalWrite(led_verde,LOW);
  delay(500);
  for(int x=0;x<3;x++){
    digitalWrite(led_verde,HIGH);
    delay(500);
    digitalWrite(led_verde,LOW);
    delay(500);
  }
}

void amarillo(){
  //Prende el amarillo y espera 3 segundos
  digitalWrite(led_ama,HIGH);
  delay(3000);
  //Se apaga amarillo del semaforo y rojo del peaton
  digitalWrite(led_ama,LOW);
  digitalWrite(led_peat_rojo,LOW);
  delay(1000);
}

void rojo(){
  //Se enciende el rojo del semaforo, el verde del peaton y suena el buzzer, espera 4 segundos
  tone(buzzer,400);
  digitalWrite(led_rojo,HIGH);
  digitalWrite(led_peat_verde,HIGH);
  delay(4000);
  //Se apaga el rojo del semaforo, el verde del peaton y el buzzer deja de sonar
  noTone(buzzer);
  digitalWrite(led_rojo,LOW);
  digitalWrite(led_peat_verde,LOW);
  delay(1000);
}
