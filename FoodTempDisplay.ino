//created by SAYANTIKA BANIK
/*the code sample is written for the customized shield to detect the temperature 
 * of the food items and hence carry out the analysis. 
 * The room temperature is taken as 24 deg C (Ts)
 * The final temperature is taken as 30 deg C (Tf)
 * Newton law of cooling as derived in its native state is as follows-
 * time=ln((To-Ts)/(Tf-Ts))*k
 * 
 * 
 */
#include <U8glib.h> //for oled 
int  sensorPin= A0;// pin initialised

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);


void setup() 
{
  
  Serial.begin(9600);
  u8g.setFont(u8g_font_courB12);
  u8g.setColorIndex(2);
  Serial.println("LCD test with PWM contrast adjustment");
 
}

void loop() 
{
  
 int reading = analogRead(sensorPin);   
   // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 3.3;
 voltage /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = -(voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 float time1=log((temperatureC-24)/(30-24))*(1);//newtons law of cooling
 
 Serial.print(temperatureF); Serial.println(" degrees F");
 
 delay(1000);                   
  
Serial.print("temp degrees C->");
Serial.println(temperatureC);
Serial.print("temp degrees F->");
  Serial.println(temperatureF);
  //float timeOfCooling= newtonTime(temperatureC);
  Serial.print("Time Calculated->");
  Serial.println( time1*10);
  u8g.firstPage();
              do {  
                    
                    u8g.drawStr(50,20,"Mins");
                    
                    u8g.setPrintPos(10, 20);
                   
                   u8g.print(time1*10);
                   u8g.setPrintPos(40, 40);
                   u8g.drawStr(90,40,"C");
                   u8g.print(temperatureC);
                   
                   if (temperatureC>32){
                   u8g.drawStr(3,60,"PERFECT->DELIVER");
                    delay(100);
                  }
                    else
                    { 
                   u8g.drawStr(3,60,"CAN'T DELIVER");
                    delay(100);
                    }
           
                 
                 } while( u8g.nextPage() );
             
  delay(200);
}
 
/*int newtonTime(int temperature)
{
  int Tinitial;
  float time1=log((Tinitial-24)/(30-24))*(1);
  return time1;
}*/




