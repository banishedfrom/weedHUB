


#include <LiquidCrystal_I2C.h>
///////////////////////////LCD///////////////////////////////////

///////////////////////////HumedadEnSuelo///////////////////////////////////
#define sensorHumedadEnSuelo A2 // Se declaró en el A2
///////////////////////////HumedadEnSuelo///////////////////////////////////
//////////////////////////DHT11////////////////////////////////////
#include <DHT.h>
 //////////////////////////DHT11////////////////////////////////////
// Definimos el pin digital donde se conecta el sensor ( PIN 2)
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
 
// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

///////////////////////////LCD///////////////////////////////////

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display  //
///////////////////////////LCD///////////////////////////////////
//////////////////////////////DHT11////////////////////////////////

//////////////////////////////NivelDeAgua////////////////////////////////
 // Declaramos la variable para almacenar los valores del sensor. ( PIN A0 PERO SE DECLARA EN EL LOOP)
 int sensorNivelAgua;
//////////////////////////////NivelDeAgua////////////////////////////////

///////////////////////////UltraSonido///////////////////////////////////
const int Trigger = 3;   //Pin digital 2 para el Trigger del sensor
const int Echo = 4;   //Pin digital 3 para el Echo del sensor
///////////////////////////UltraSonido///////////////////////////////////




////////////////RELAYS/////////////
String data = "";
const int rele1 = 8;
const int rele2 = 9;
const int rele3 = 10;
const int rele4 = 11;
const int rele5 = 12;
const int rele6 = 13;
////////////////RELAYS/////////////
void setup() {
  // Inicializamos comunicación serie
  Serial.begin(9600); 
  // Comenzamos el sensor DHT
  dht.begin();
  //Continuamos con el sensor UltraSonido
  pinMode(Trigger, OUTPUT); //pin como salida
  pinMode(Echo, INPUT);  //pin como entrada
  digitalWrite(Trigger, LOW);//Inicializamos el pin con 0

  //sensorHumedadEnSuelo
  pinMode(sensorHumedadEnSuelo, INPUT);


  ///////////////////////////LCD///////////////////////////////////
 lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  //lcd.setCursor(1,0);
 // lcd.print("hello everyone");
 // lcd.setCursor(1,1);
 // lcd.print("konichiwaa");
  //delay(1000);
 // lcd.setCursor(1,1);


 //////////////////////////RELAYS////////////////////////
   
   pinMode(rele1,OUTPUT);
   pinMode(rele2,OUTPUT);
   pinMode(rele3,OUTPUT);
   pinMode(rele4,OUTPUT);
   pinMode(rele5,OUTPUT);
   pinMode(rele6,OUTPUT);

   
}
 
void loop() {
    // Esperamos 5 segundos entre medidas
  //delay(1000);
 /////////////////////////////////////////DHT11///////////////////////////////////////////////
  // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float T = dht.readTemperature();
  // Leemos la temperatura en grados Fahreheit
  float f = dht.readTemperature(true);
 
  // Comprobamos si ha habido algún error en la lectura
  //if (isnan(h) || isnan(T) || isnan(f)) {
    //Serial.println("Error obteniendo los datos del sensor DHT11");
    //return;
  //}
 
  // Calcular el índice de calor en Fahreheit
  float hif = dht.computeHeatIndex(f, h);
  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(T, h, false);
 ////////////////////////////////////////////DHT11////////////////////////////////////////////////
  ////////////////////////////////////////////NivelAgua////////////////////////////////////////////////


// Rescatamos los valores del sensor.
  sensorNivelAgua = analogRead(0);
 
  
  ////////////////////////////////////////////NivelAgua////////////////////////////////////////////////
  ///////////////////////////UltraSonido///////////////////////////////////
 long t; //timepo que demora en llegar el eco
 long d; //distancia en centimetros

  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = 33-(t/59);             //escalamos el tiempo a una distancia en cm
  ///////////////////////////UltraSonido///////////////////////////////////

///////////////////////////HumedadSuelo///////////////////////////////////
  int valorHumedadSuelo = map(analogRead(sensorHumedadEnSuelo), 0, 1023, 100, 0);
  ///////////////////////////HumedadSuelo///////////////////////////////////

 //Humedad
  //Serial.print("Humedad: ");
  Serial.print(h);
  
  //Serial.print(" %\t");
  //Serial.print(" Temperatura: ");
  Serial.print(T);
  
  //Serial.print(" *C ");
  //Serial.print(f);
  //Serial.print(" *F\t");
  //Serial.print("Índice de calor: ");
  //Serial.print(hic);
  //Serial.print(" *C ");
  //Serial.print(hif);
  //Serial.print(" *F ");
   //Humedad//
   
   // Nivel de Agua.//
  //Serial.print(" Nivel de Agua: ");
  //Serial.print(sensorNivelAgua);
   // Nivel de Agua.
   
   //UltraSonido//
   //Serial.print(" Distancia: ");
  Serial.print(d);
 //Enviamos serialmente el valor de la distancia
  //Serial.print("cm");
  
//UltraSonido//
//HumedadSuelo
  //Serial.print(" HumedadSuelo: ");
  Serial.println(valorHumedadSuelo);
//HumedadSuelo  
//Serial.println();

///////Escribiendo en el LCD////
lcd.setCursor(0,0);
lcd.print("T:");
lcd.print(T);
lcd.print(" H2O:");
lcd.print(sensorNivelAgua);

// Evita que sobre escriba la pantalla
if(sensorNivelAgua<10){
  lcd.print("   ");
}else{
 if(sensorNivelAgua<100){
  lcd.print("  ");
}else{
 lcd.print(" ");
}
}

lcd.setCursor(0,1);
lcd.print("D:");
lcd.print(d);

// Evita que sobre escriba la pantalla
if(d<10){
  lcd.print("   HSuelo:");
}else{
 if(d<100){
  lcd.print("  HSuelo:");
}else{
 lcd.print(" HSuelo:");
}
}


lcd.print(valorHumedadSuelo);
if(valorHumedadSuelo<10){
  lcd.print("  ");
}else{
 if(valorHumedadSuelo<100){
  lcd.print(" ");
  }
}
lcd.setCursor(15,1);






//int tamano = strlen(" Temperatura: ");
//Serial.print(tamano);
  
  //lcd.scrollDisplayLeft();
  delay(5000);
//lcd.clear();

//////////////////////////RELAYS////////////////////////////////
//////////////////////////RELAYS////////////////////////////////   
//////////////////////////RELAYS////////////////////////////////
//Usaremos la "convencion" de lectura por Serial: donde se escribirá re(# de rele)-(ON/OFF) ejemplo: re1-ON/re1-OFF
   while (Serial.available())
   {
      char character = Serial.read();
      if (character != '\n')
      {
         data.concat(character);
         
      }
      else
      {
        //Serial.print(data);         
         
         //Hay que colocar algun tipo de excepcion en caso para la entrada de esta función

         //La variable tamano obtiene el tamaño del string de entrada serial
         int tamano = data.length();

         
         //Una vez lee el string, lee los ultimos 3/2 caracteres (OFF)/(ON) para ejecutar la acción en cada pin

         
         if( data.charAt(tamano-3)=='O' && data.charAt(tamano-2)=='F' && data.charAt(tamano-1)=='F'){
            
           switch(data.charAt(2)){

               case '1': digitalWrite(rele1, HIGH);
               break;

               case '2': digitalWrite(rele2, HIGH);
               break;

               case '3': digitalWrite(rele3, HIGH);
               break;

               case '4': digitalWrite(rele4, HIGH);
               break;

               case '5': digitalWrite(rele5, HIGH);
               break;

               case '6': digitalWrite(rele6, HIGH);
               break;
              
              }
          }
          else{
            if( data.charAt(tamano-2)=='O' && data.charAt(tamano-1)=='N'){
              switch(data.charAt(2)){

               case '1': digitalWrite(rele1, LOW);
               break;

               case '2': digitalWrite(rele2, LOW);
               break;

               case '3': digitalWrite(rele3, LOW);
               break;

               case '4': digitalWrite(rele4, LOW);
               break;

               case '5': digitalWrite(rele5, LOW);
               break;

               case '6': digitalWrite(rele6, LOW);
               break;
              }
          }
          }
            data = "";
          }
         
      }
//////////////////////////RELAYS////////////////////////////////
//////////////////////////RELAYS////////////////////////////////  
//////////////////////////RELAYS////////////////////////////////
//////////////////////////RELAYS////////////////////////////////
if (Serial.available() > 0) {
char pl = Serial.read();
 if (pl=="pgl")
  
 
  
   digitalWrite(rele3, LOW);
      {
         if(T>30)
         {
          digitalWrite(rele4, LOW);
          digitalWrite(rele5,LOW);
          digitalWrite(rele6,LOW);
          digitalWrite(rele1,HIGH);
          digitalWrite(rele2,LOW);
          
         }
         if(T<25)
         {
          digitalWrite(rele4, HIGH);
          digitalWrite(rele5,HIGH);
          digitalWrite(rele6,HIGH);
          digitalWrite(rele1,LOW);
           digitalWrite(rele1,HIGH);
          
         }

          if(h>65)
         {
          digitalWrite(rele4, LOW);
          digitalWrite(rele5,LOW);
          digitalWrite(rele6,LOW);
          digitalWrite(rele1,HIGH);
          digitalWrite(rele2,LOW);
          
         }
         if(h<50)
         {
          digitalWrite(rele4, HIGH);
          digitalWrite(rele5,HIGH);
          digitalWrite(rele6,HIGH);
          digitalWrite(rele1,LOW);
           digitalWrite(rele1,HIGH);
          
         }
           
           if(valorHumedadSuelo<60)
         {
          
          
         }
          
         
         
      }
}  
   
}
