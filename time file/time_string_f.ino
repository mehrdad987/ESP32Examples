#include <Wire.h>
#include "RTClib.h"


RTC_DS3231 rtc;

char buffey[300];

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () 
{
  Serial.begin(115200);
  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
}

void loop () 
{
    DateTime now = rtc.now();
    
    Serial.println("Current Date & Time: ");
    String a = String(now.year());
    String b = String(".");
    String c = String(now.month());
    String d = String(".");
    String e = String(now.day());
    String f = String("."); 
    String i = String(now.hour());
    String j = String(".");
    String k = String(now.minute());
    String l = String(".");
    String m = String(now.second());
    String timefolder = (a+b+c+d+e+f+i+j+k+l+m);
    Serial.println(timefolder);
    
    delay(1000);
}
