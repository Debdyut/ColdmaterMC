#include "Energia.h"
#include "SPI.h"
#include "Screen_K35_SPI.h"
#include <WiFi.h>
#include "keyboards.h"

/* Global variables declaration */
Screen_K35_SPI myScreen;  // Declaring a new screen object

void setup() {

  Serial.begin(9600);  
  
  // Initialize screen
  screen_init();

  //keypad();

  //while(true);

  // Displays the welcome screen
  displayLandingPageDisplay();  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}

void screen_init() 
{
  
  myScreen.begin();
  myScreen.clear(whiteColour);    
}

void displayLandingPageDisplay()
{
  // Title
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(myScreen.fontMax() - 1);    
  myScreen.gText(100, 20, "COLDMATER", myScreen.calculateColour(255, 0, 0));

  // Draw button
  myScreen.dRectangle(80, 20 + myScreen.fontSizeY() * 3, 140, 40, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(95, 45  + myScreen.fontSizeY() * 3, "CONFIGURE WiFi", whiteColour);

  // Wait for touch event
  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      // Detect touch event, condition for button pressed
      if(z > 500 && (x >= 80 && x <= 220) && (y >= 68 && y <= 84))
      {        
          // Display screen to configure Wifi
          configureWifi();  
      }
      
    } // end of if    
  } // end of while
} // end of function

String ssid = "SSID: None provided";

void configureWifi()
{
  // Page Title
  myScreen.clear(whiteColour);
  myScreen.setFontSize(myScreen.fontMax() - 1); 
  myScreen.gText(25, 10, "List of available WiFi", redColour);
  myScreen.setFontSize(1); 

  // Initialize WiFi
  WiFi.init();

  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {    
    myScreen.gText(30, 35, "Couldn't get a wifi connection", blackColour);  
  }
  
  // print the list of networks seen:  
  String str = "Number of available networks: " + String(numSsid);
  myScreen.gText(30, 35, str, blackColour);    

  int pages = numSsid / 3;
  if(numSsid % 3 > 0) pages++;
  int currentPage = 0;

  // print the network number and name for each network found:  
  listNetworks(currentPage, numSsid);

  // Next page button
  updateButtons(currentPage, pages);

  // Refresh button to rescan for available wifi
  myScreen.dRectangle(70, 200, 140, 30, greenColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(110, 210, "Refresh", blueColour);

  // Wait for touch event
  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      // Serial.println("x: " + String(x) + "y: " + String(y) + "z: " + String(z));
    
      // Detect touch event, condition for button pressed
      if(z > 500)      
      {          

          if((x >= 70 && x <= 210) && (y >= 200 && y <= 230))
          {
            // Display screen to configure Wifi
            configureWifi();  
          }
          else if((x >= 285 && x <= 315) && (y >= 105 && y <= 135))
          {
            Serial.println("Next");    
            if(currentPage < (pages-1))         
              listNetworks(++currentPage, numSsid);
            updateButtons(currentPage, pages);
          }
          else if((x >= 25 && x <= 55) && (y >= 105 && y <= 135))
          {
            Serial.println("Previous"); 
            if(currentPage > 0)
              listNetworks(--currentPage, numSsid);  
            updateButtons(currentPage, pages);
          }
          else if( (x >= 70 && x <= 210) && (y >= 80 && y <= 110) )
          {
            //Serial.println("Button 1");
            ssid = WiFi.SSID(0 + currentPage * 3);
            wpa2form(currentPage, 0);              
          }
          else if( (x >= 70 && x <= 210) && (y >= 111 && y <= 140) )
          {
            Serial.println("Button 2");
            ssid = WiFi.SSID(1 + currentPage * 3);
            wpa2form(currentPage, 1);  
          }
          else if( (x >= 70 && x <= 210) && (y >= 150 && y <= 175) )
          {
            Serial.println("Button 3");
            ssid = WiFi.SSID(2 + currentPage * 3);
            wpa2form(currentPage, 2);  
          }
          
      }
      
    } // end of if    
  } // end of while
        
}

void updateButtons(int currentPage, int pages)
{
  uint16_t colour;
  if(currentPage < (pages-1))
    colour = redColour;
  else 
    colour = myScreen.calculateColour(170, 170, 170);
    
  // Next page button
  myScreen.circle (290, 125, 20, colour);
  myScreen.setFontSize(myScreen.fontMax() - 1);  
  myScreen.gText(285, 120, ">", whiteColour);

  if(currentPage == 0)
    colour = myScreen.calculateColour(170, 170, 170);
  else 
    colour = redColour;

  // Prev page button
  myScreen.circle (30, 125, 20, colour);
  myScreen.setFontSize(myScreen.fontMax() - 1);  
  myScreen.gText(25, 120, "<", whiteColour);
}

void listNetworks(int currentPage, int numSsid) {

  // Clear the area of the list
  myScreen.dRectangle(65, 75, 150, 115, whiteColour); 

  // print the network number and name for each network found:
  for (int thisNet = 0; (thisNet + currentPage * 3) < numSsid && thisNet < 3; thisNet++) {
    myScreen.dRectangle(70, 80 + myScreen.fontSizeY() * 3 * thisNet, 140, 30, redColour); 
    myScreen.setFontSize(1);  
    myScreen.gText(90, 90  + myScreen.fontSizeY() * 3 * thisNet, WiFi.SSID(thisNet + currentPage * 3), whiteColour);
    //printEncryptionType(WiFi.encryptionType(thisNet));
  }
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
  case ENC_TYPE_WEP:
    Serial.println("WEP");
    break;
  case ENC_TYPE_TKIP:
    Serial.println("WPA");
    break;
  case ENC_TYPE_CCMP:
    Serial.println("WPA2");
    break;
  case ENC_TYPE_NONE:
    Serial.println("None");
    break;
  case ENC_TYPE_AUTO:
    Serial.println("Auto");
    break;
  }
}


char password[20];
String pwdState = "Enter Password";

void wpa2form(int currentPage, int thisNet)
{  
  
  // Page Title
  myScreen.clear(whiteColour);
  myScreen.setFontSize(myScreen.fontMax() - 1); 
  myScreen.gText(60, 20, "WPA2 Credentials", redColour);

  // SSID  
  myScreen.setFontSize(2);  
  myScreen.gText(20, 63, "SSID: ", redColour);
  myScreen.setFontSize(1);  
  myScreen.gText(85, 65, ssid, blackColour);

  // Password 
  myScreen.setFontSize(2);  
  myScreen.gText(20, 83, "Password: ", redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(130, 85, password, blackColour); 
  

  // Enter Password button
  myScreen.dRectangle(25, 107, 140, 30, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(35, 115, pwdState, whiteColour);

  if(pwdState == "Change password")
  {
    myScreen.dRectangle(160, 170, 140, 30, greenColour); 
    myScreen.setFontSize(1);  
    myScreen.gText(195, 180, "Connect", blackColour);
  }

  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      Serial.println("x: " + String(x) + "y: " + String(y) + "z: " + String(z));
    
      // Detect touch event, condition for button pressed
      if(z > 500)      
      {          
        if((x >= 30 && x <= 170) && (y >= 107 && y <= 137))
        {
          // Display screen to configure Wifi
          keypad(myScreen, password);            
          pwdState = "Change password";                   
          wpa2form(currentPage, thisNet);          
        }
        if((x >= 160 && x <= 300) && (y >= 160 && y <= 190))
        {
          loginPage();
        }
      }
    }
  }
  
}


void loginPage()
{
    // Page Title
    myScreen.clear(whiteColour);
    myScreen.setFontSize(myScreen.fontMax() - 1); 
    myScreen.gText(60, 20, "Waiting to connect", redColour);
}





