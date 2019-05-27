// Adicionando as bibliotecas necessárias
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

// Atribuindo um ID para o sensor
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(199851);

void displaySensorDetails(void)
{
sensor_t sensor;
mag.getSensor(&sensor);
Serial.println("------------------------------------");
Serial.print ("Sensor: "); Serial.println(sensor.name);
Serial.print ("Versao do driver: "); Serial.println(sensor.version);
Serial.print ("ID do sensor: "); Serial.println(sensor.sensor_id);
Serial.print ("Valor maximo: "); Serial.print(sensor.max_value); 
Serial.print ("Valor Minimo: "); Serial.print(sensor.min_value); 
Serial.print ("Resolucao: "); Serial.print(sensor.resolution);
Serial.println("------------------------------------");
Serial.println("");
delay(500);
}

void setup(void) 
{
Serial.begin(9600);

// Inicializando o sensor
if(!mag.begin())
{
// Checando se não houve nenhum problema de conexão com o... 
//sensor HMC5883
Serial.println("Ooops, sensor nao detectado ... Verifique as conexoes!");
while(1);
}

// Mostra algumas informações básicas do sensor
displaySensorDetails();
}

void loop(void) 
{
// Obtem um novo evento do sensor 
sensors_event_t event; 
mag.getEvent(&event);

// Calculando a posição do eixo x e y 
float heading = atan2(event.magnetic.y, event.magnetic.x);

// Depois de ter sua posição, você deve em seguida, adicionar o seu... 
//'angulo de declincação', que é o 'erro' do campo magnético em... 
//sua localização.
// Localizar o seu aqui: http://www.magnetic-declination.com/
// O meu é: -20, que é ~ 20 graus, ou (o que nós precisamos) 0,34 radianos
// Se você não conseguiu encontrar a sua declinação, comente estas... 
//duas linhas, a bussola ficará um pouco defasada.

float declinationAngle = 0.34;
heading += declinationAngle;

// Faz a correção quandos os sinais estão invertidos
if(heading < 0)
heading += 2*PI;

// Verifica a adição de declinação
if(heading > 2*PI)
heading -= 2*PI;

// Converter radianos em graus para facilitar a leitura
float headingDegrees = heading * 180/M_PI; 

Serial.print("Posicao em graus: "); Serial.println(headingDegrees);

if (headingDegrees > 0 && headingDegrees <= 44.9)
{
Serial.println ("Norte");
}
else if (headingDegrees > 45 && headingDegrees <= 89.9)
{
Serial.println ("Nordeste");
}
else if (headingDegrees > 90 && headingDegrees <= 134.9)
{
Serial.println ("Leste");
}
else if (headingDegrees > 135 && headingDegrees <= 179.9)
{
Serial.println ("Sudeste");
}
else if (headingDegrees > 180 && headingDegrees <= 224.9)
{
Serial.println ("Sul");
}
else if (headingDegrees > 225 && headingDegrees <= 269.9)
{
Serial.println ("Suldoeste");
}
else if (headingDegrees > 270 && headingDegrees <= 314.9)
{
Serial.println ("Oeste");
}
else if (headingDegrees > 315 && headingDegrees <= 359.9)
{
Serial.println ("Noroeste");
}

delay(500);
}