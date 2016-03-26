# GenuiLib
Generic User Interface Library for Arduino
I developped this library because I wanted to make a device for a sailboat that would basicaly :
-Help the sailor underway
  - Display the bearing (magnetic ou true) (real or average)
  - Display the speed (true and toward the destination)(real or average)
  - Display the distance to the destination
  - Store some selected nmea sentences on a sd card
-At the anchorage
  -Graphical anchoring alarm

And more.

I succeed a first release in pure C. I first used a screen ILI9341 with an Arduino Mega and a Bluetooth dongle HC05 to listen a GPS NMEA flow broadcasted with Bluetooth. To manage the screen, I used the graphic library UTFT.

When I decided to develop alarms to alert the sailor that the speed is too low, or even more important, the bearing is off course, I faced some difficulties. The code was getting too complex for my taste. So I decided to re-develop the whole system in C++.
Being a developper OOP, it was obvious that C++ could make the system easier to maintain and to evolve.

I developped first a graphic library of a higher level than UTFT for all the graphic component I needed :
-Menus
-Compass
-Label
-Dynamic label
-Graphic to display data in real time at different scales
-Layouts to position graphic in the screen
-etc.
For this first release of my graphic library, I wrapped the UTFT library wich is under Creative Commons (CC BY-NC-SA 3.0) licence.

After that, I started developping the framework for the different applications of my navigational device in C++ as well. The work is still in progress and now in stand by for some reasons. That is an other subject ...

In parallel, I developped a graphical weather station with an other screen (ST7920) by using my graphic library. However the screen ST7920 wasn't compatible with UTFT library. Because I wrapped UTFT, it was easy to wrap the library U8glib that manages my new screen ST7920.
I modified a bit my graphic library to be able to use all of the graphics component I developped previously with either library. And it works.

So, the goal of this graphic library for Arduino is to make available some graphic components for the Arduino developer. It should make the developpement of user interface a lot faster.
This graphic library should work with all the screens managed by UTFT and U8glib. However, I did test only with ILI9341 (UTFT) and with ST7920 (U8glib).


  
