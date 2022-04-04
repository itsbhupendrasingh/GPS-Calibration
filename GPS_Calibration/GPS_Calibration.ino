/*
 * 
 * Tested dated 1/4/2022
 * By Bhupendra Singh
 * SME Dehradun
 * 
 */
#include <TinyGPS.h>
#include <SoftwareSerial.h>
TinyGPS gps;

SoftwareSerial gps_port(2,3);

char sz[32];
int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
void setup()
{
  Serial.begin(9600);
  gps_port.begin(9600);
  delay(2000);
}

void getgps(TinyGPS &gps)
{
 float latitude, longitude;
 gps.f_get_position(&latitude, &longitude);
 Serial.print("GPS Location: ");
 Serial.print("http://www.google.com/maps/place/");      
 Serial.print(latitude,6);
 Serial.print(",");
 Serial.print(longitude,6); 
 Serial.println(",");

 Serial.print("Speed: ");
 Serial.print(gps.f_speed_kmph());
 Serial.print(", ");
 Serial.print("Current Date & Time: ");
 gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
 sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",month, day, year, hour, minute, second);
 Serial.println(sz);
 delay(1000);
}
void loop()
{
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (gps_port.available())
    {
      char a = gps_port.read();
//       Serial.print(a); 
      if(gps.encode(a)) 
       {
        getgps(gps); 
       }
    }
  }
} 
