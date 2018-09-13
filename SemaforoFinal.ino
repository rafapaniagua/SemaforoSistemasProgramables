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
int tiempo;
int minimo = 0;

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
  //Se enciende fijamente el verde del semaforo y el rojo del peaton
  digitalWrite(led_verde,HIGH);
  digitalWrite(led_peat_rojo,HIGH);
  //Se aumenta la variable del tiempo minimo para alcanzar los 10000 y haga efecto el boton
  minimo += 10;
  Serial.println(minimo);
  //Si se presiona el boton despues del tiempo minimo entrara a la condicional
  if((digitalRead(boton) == LOW) && (minimo > 10000)){
    //El potenciometro controla el tiempo del verde del peaton
    valorPot = analogRead(pot);
    segundos = valorPot*20;
    tiempo = segundos/1000;
    Serial.println("Se presiono");
    Serial.print("Esperará ");
    Serial.print(tiempo);
    Serial.println(" segundos");
    //Se ejecuta el metodo de cambio de estados del semaforo
    cambio();
    //Se reinicia el contador del tiempo minimo para que haga efecto el boton
    minimo = 0;
  }
}

void cambio(){
  //Metodo para hacer las transiciones entre los estados del semaforo
  verde();
  amarillo();
  rojo();
}

void verde(){
  //Una vez presionado el boton parpadea 3 veces y se mantiene apagado
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
  //Se enciende el rojo del semaforo, el verde del peaton y suena el buzzer, espera el numero de segundos asignado por el potenciometro
  tone(buzzer,400);
  digitalWrite(led_rojo,HIGH);
  digitalWrite(led_peat_verde,HIGH);
  delay(segundos);
  //Se apaga el rojo del semaforo, el verde del peaton y el buzzer deja de sonar
  noTone(buzzer);
  digitalWrite(led_peat_verde,LOW);
  delay(500);
  //Parpadea y suena 3 veces antes de volver a su estado original
  for(int x=0;x<3;x++){
    tone(buzzer,400);
    digitalWrite(led_rojo,HIGH);
    digitalWrite(led_peat_verde,HIGH);
    delay(500);
    noTone(buzzer);
    digitalWrite(led_peat_verde,LOW);
    delay(500);
  }
  digitalWrite(led_rojo,LOW);
}
