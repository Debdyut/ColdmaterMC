#include "Energia.h"
#include "SPI.h"
#include "Screen_K35_SPI.h"
#include <WiFi.h>
#include "keyboards.h"
#include <Adafruit_Fingerprint.h>

// For fingerprint scanner
#define mySerial Serial1
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


/* Global variables declaration */
Screen_K35_SPI myScreen;  // Declaring a new screen object

void setup() {

  String machineid = "CMM0000001";

  Serial.begin(9600);      

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  // Initialize screen
  screen_init();

  //while(true);
  //Dashboard();
  // Displays the welcome screen
  //displayLandingPageDisplay();  

  Dashboard();
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}

void screen_init() 
{
  
  myScreen.begin();
  myScreen.clear(whiteColour);   
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false); 
  myScreen.setFontSize(myScreen.fontMax() - 1);
}

void displayLandingPageDisplay()
{
  myScreen.clear(whiteColour);
  // Title
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(myScreen.fontMax() - 1);    
  myScreen.gText(100, 20, "COLDMATER", myScreen.calculateColour(255, 0, 0));

  myScreen.setFontSize(1);  
  myScreen.gText(20, 40, "Choose a method for authentication", blackColour);

  // Draw button
  myScreen.dRectangle(80, 20 + myScreen.fontSizeY() * 3, 140, 40, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(95, 70, "Internet", whiteColour);

  // Draw button
  myScreen.dRectangle(80, 120, 140, 40, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(95, 135, "Fingerprint", whiteColour);

  // Wait for touch event
  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      // Detect touch event, condition for button pressed
      if(z > 500) { 
        if ((x >= 80 && x <= 220) && (y >= 68 && y <= 84))
        {        
            // Display screen to configure Wifi
            configureWifi();  
        }
        else if ((x >= 80 && x <= 220) && (y >= 120 && y <= 160))
        {
          fingerprintAuth();  
        }
      }
      
    } // end of if    
  } // end of while
} // end of function

String ssid = "SSID: None provided";

void fingerprintAuth() {
  
  myScreen.clear(whiteColour);
  myScreen.setFontSize(myScreen.fontMax() - 1); 
  myScreen.gText(10, 10, "Fingerprint Authenticator", redColour);
  myScreen.setFontSize(1); 

  
  if (finger.verifyPassword()) {        
    myScreen.gText(50, 117, "Waiting for valid finger...", blackColour);

    while(1) {
      
      if(getFingerprintIDez() != -1) {
        myScreen.dRectangle(40, 110, 240, 30, whiteColour); 
        myScreen.gText(50, 117, "Authentication Successful!", blackColour);
        delay(1000);
        Dashboard();
      }        
      delay(50);            //don't need to run this at full speed.        
    }
    
  } 
  else {
    myScreen.gText(10, 10, "Fingerprint sensor not responsive!", redColour);
    myScreen.gText(10, 10, "Try internet login", redColour);    
  }  

}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);  
  
  return finger.fingerID; 
  
}



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

      //Serial.println("x: " + String(x) + "y: " + String(y) + "z: " + String(z));
    
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
    myScreen.gText(35, 20, "Waiting to connect to ", redColour);
    myScreen.gText(90, 60, ssid, redColour);

    Serial.print("Attempting to connect to Network named: ");
    // print the network name (SSID);
    Serial.println(ssid);

    char ssid_char[20];

    ssid.toCharArray(ssid_char, 20);

    WiFi.begin(ssid_char, password);

    while ( WiFi.status() != WL_CONNECTED) {
      // print dots while we wait to connect
      Serial.print(".");
      delay(300);
    }
  
    while (WiFi.localIP() == INADDR_NONE) {
      // print dots while we wait for an ip addresss
      Serial.print(".");
      delay(300);
    }

    Serial.println("\nIP Address obtained");
    printWifiStatus();

    if ( WiFi.status() == WL_CONNECTED && WiFi.localIP() != INADDR_NONE) {
      //Notify user connection is successful
      myScreen.clear(whiteColour);
      myScreen.setFontSize(myScreen.fontMax() - 1);
      myScreen.gText(60, 20, "Connected to Wifi", redColour);
      myScreen.gText(80, 50, "Successfully!", redColour);

      delay(1000);

      loginForm();
    }
}

char username[20];
char userpwd[20];

String username_state = "Enter Username";
String userpwd_state = "Enter Password";


void loginForm()  {

  //Title of Login Page
  myScreen.clear(whiteColour);
  myScreen.setFontSize(myScreen.fontMax() - 0);
  myScreen.gText(90, 20, "LOGIN PAGE", redColour);

  //User Id Button
  myScreen.dRectangle(80, 100, 140, 30, redColour); 
  myScreen.setFontSize(1);  

  if(username_state != "Enter Username")  {
    myScreen.gText(80, 80, "Username: " + String(username), blackColour);      
  }
  myScreen.gText(90, 110, username_state, whiteColour);  

  //Password Button
  myScreen.dRectangle(80, 160, 140, 30, redColour); 
  myScreen.setFontSize(1);  
  if(userpwd_state != "Enter Password")  {
    myScreen.gText(80, 140, "Password: " + String(userpwd), blackColour);      
  }
  myScreen.gText(90, 170, userpwd_state, whiteColour);

  if(userpwd_state == "Change Password" && username_state == "Change Username")
  {
    Serial.println("OK");
    
    myScreen.dRectangle(80, 200, 140, 30, greenColour); 
    myScreen.setFontSize(1);  
    myScreen.gText(120, 210, "Connect", blackColour);
  }

  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      //Serial.println("x: " + String(x) + "y: " + String(y) + "z: " + String(z));
    
      // Detect touch event, condition for button pressed
      if(z > 500)      
      {          
        if((x >= 80 && x <= 225) && (y >= 95 && y <= 125))
        {          
          keypad(myScreen, username);                      
          username_state = "Change Username";
          loginForm();
        }
        else if((x >= 80 && x <= 225) && (y >= 155 && y <= 185))
        {
          keypad(myScreen, userpwd);                      
          userpwd_state = "Change Password";
          loginForm();
        }
        else if((x >= 80 && x <= 225) && (y >= 190 && y <= 215) && userpwd_state == "Change Password" && username_state == "Change Username")
        {          
          login_attempt();
        }
      }
    }
  }
  
}


char server[] = "http://coldmaterweb.herokuapp.com";   

WiFiClient client;
bool client_connected = false;

void login_attempt() {

  myScreen.clear(whiteColour);
  myScreen.setFontSize(myScreen.fontMax() - 0);
  myScreen.gText(90, 20, "LOGIN Attempt", redColour);

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    client_connected = true;
    // Make a HTTP request:
    client.println("GET https://coldmaterweb.herokuapp.com/user/username%3D" + String(username) + "&password%3D" + String(userpwd) + "/ HTTP/1.1");
    client.println("Accept: application/json");
    client.println("Host: coldmaterweb.herokuapp.com");
    client.println("Cache-Control: no-cache");
    client.println("Connection: close");
    client.println();    
  }
  else {
    Serial.println("Server not found!");  
  }

  String resp;

  while(true) {
    while (client.available()) {
      resp += char(client.read());
      //Serial.write(c);
    }  
  
    resp = resp.substring(resp.indexOf('{') + 1, resp.lastIndexOf('}'));
    Serial.println(resp);    

      
    // if the server's disconnected, stop the client:
    
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();
      client_connected = false;
      break;
    }
    

    // Todo login auth

    delay(1000);
    Dashboard();
    
  }
  // Todo cannot login at the moment
  
}

String getTemp() {
    Serial.println("\nStarting connection to server...");
    // if you get a connection, report back via serial:    
    if(client_connected) {
      client.stop();
      delay(1000);
    }
    if (client.connect(server, 80)) {
      Serial.println("connected to server");
      // Make a HTTP request:
      client.println("GET https://coldmaterweb.herokuapp.com/machine_info/CMM0000001/15/23 HTTP/1.1");
      client.println("Accept: application/json");
      client.println("Host: coldmaterweb.herokuapp.com");
      client.println("Cache-Control: no-cache");
      client.println("Connection: close");
      client.println();
    }
    else {
      Serial.println("Server not found!");  
    }

    String resp1;

    while(true) {
      while (client.available()) {
        resp1 += char(client.read());
        //Serial.write(c);
    }  
  
    resp1 = resp1.substring(resp1.indexOf('{') + 1, resp1.lastIndexOf('}'));    

    // if the server's disconnected, stop the client:    
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting from server.");
      client.stop();

      break;
    }    
      
  }

  return resp1;
}

void Dashboard() {
  //Title of Page
  myScreen.clear(whiteColour);
  myScreen.setFontSize(myScreen.fontMax() - 0);
  myScreen.gText(100, 20, "Dashboard", redColour);  

  Serial.println(getTemp());

  //Temp Control
  myScreen.setFontSize(1);
  myScreen.gText(10, 60, "Ambient Temperature: 35 &deg;C", blueColour);

  // + button
  myScreen.circle (290, 140, 20, redColour);
  myScreen.setFontSize(myScreen.fontMax() - 1);  
  myScreen.gText(285, 133, "+", whiteColour);
  
  // - button 
  myScreen.circle (30, 140, 20, redColour);
  myScreen.setFontSize(myScreen.fontMax() - 1);  
  myScreen.gText(24, 133, "-", whiteColour);

  // Control 2
  myScreen.setFontSize(myScreen.fontMax() - 0);
  myScreen.gText(87, 130, "Control 2", blueColour);

  // Add user button
  myScreen.dRectangle(10, 200, 140, 30, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(25, 210, "Settings", whiteColour);

  // Add user button
  myScreen.dRectangle(170, 200, 140, 30, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(185, 210, "Logout", whiteColour);

  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      //Serial.println("x: " + String(x) + "y: " + String(y) + "z: " + String(z));
    
      // Detect touch event, condition for button pressed
      if(z > 500)      
      {          
        if((x >= 10 && x <= 150) && (y >= 185 && y <= 210))
        {          
          settingsPage();
        }
        else if((x >= 170 && x <= 310) && (y >= 185 && y <= 210))
        {          
          displayLandingPageDisplay();
        }        
      }
    }
  }
  
}

void settingsPage() {
  // Title
  myScreen.clear(whiteColour);
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(myScreen.fontMax() - 1);    
  myScreen.gText(100, 20, "Settings", myScreen.calculateColour(255, 0, 0));

  // Draw button
  myScreen.dRectangle(70, 50, 160, 30, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(75, 60, "Manage Fingerprints", whiteColour);

  // Back button
  drawBackButton();  

  // Wait for touch event
  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      // Detect touch event, condition for button pressed
      if(z > 500) { 
        if ((x >= 70 && x <= 230) && (y >= 50 && y <= 80))
        {        
            // Display screen to configure Wifi
            fingerPrintSettings();
        }  
        else if ((x >= 275 && x <= 310) && (y >= 180 && y <= 215))
        {        
            // Display screen to configure Wifi
            Dashboard();
        }       
      }
      
    } // end of if    
  } // end of while
  
}

void fingerPrintSettings() {
  // Title
  myScreen.clear(whiteColour);
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(myScreen.fontMax() - 1);    
  myScreen.gText(100, 20, "Settings", myScreen.calculateColour(255, 0, 0));

  // Draw button
  myScreen.dRectangle(70, 50, 160, 30, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(75, 60, "Add User", whiteColour);

  // Draw button
  myScreen.dRectangle(70, 90, 160, 30, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(75, 100, "Clean DB", whiteColour);

   // Back button
  drawBackButton();  

  // Wait for touch event
  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      // Detect touch event, condition for button pressed
      if(z > 500) { 
        if ((x >= 70 && x <= 230) && (y >= 50 && y <= 80))
        {        
            // Display screen to configure Wifi
            addUser();
        }  
        else if ((x >= 70 && x <= 230) && (y >= 90 && y <= 120))
        {        
            // Display screen to configure Wifi
            cleanDB();
        }
        else if ((x >= 275 && x <= 310) && (y >= 180 && y <= 215))
        {        
            // Display screen to configure Wifi
            settingsPage();
        }       
      }
      
    } // end of if    
  } // end of while
  
}

void cleanDB() {
  finger.emptyDatabase();  
}

void addUser() {
  // Title
  myScreen.clear(whiteColour);
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(myScreen.fontMax() - 1);    
  myScreen.gText(100, 20, "Add User", myScreen.calculateColour(255, 0, 0));

  myScreen.setFontSize(1);  
  myScreen.gText(50, 40, "Choose a method for login", blackColour);

  // Draw button
  myScreen.dRectangle(80, 20 + myScreen.fontSizeY() * 3, 140, 40, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(95, 70, "Internet", whiteColour);

  // Draw button
  myScreen.dRectangle(80, 120, 140, 40, redColour); 
  myScreen.setFontSize(1);  
  myScreen.gText(95, 135, "Fingerprint", whiteColour);

  // Back button
  drawBackButton();  

  // Wait for touch event
  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      // Detect touch event, condition for button pressed
      if(z > 500) { 
        if ((x >= 80 && x <= 220) && (y >= 68 && y <= 84))
        {        
            // Display screen to configure Wifi
            addUserInternet();
        }
        else if ((x >= 80 && x <= 220) && (y >= 120 && y <= 160))
        {
          addUserFingerPrint();  
        }
        else if ((x >= 275 && x <= 310) && (y >= 180 && y <= 215))
        {        
            // Display screen to configure Wifi
            fingerPrintSettings();
        } 
      }
      
    } // end of if    
  } // end of while
}

void addUserInternet() {
  myScreen.clear(whiteColour);
  // Title
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(myScreen.fontMax() - 1);    
  myScreen.gText(70, 20, "Add User Internet", myScreen.calculateColour(255, 0, 0));

  drawBackButton();  

  while(true)
  {
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      
      
      Serial.println("x: " + String(x) + "y: " + String(y) + "z: " + String(z));

      // Detect touch event, condition for button pressed
      if(z > 500) { 
        if ((x >= 275 && x <= 310) && (y >= 180 && y <= 215))
        {        
            // Display screen to configure Wifi
            addUser();
        }        
      }
      
    } // end of if  
  } 
  
}

uint8_t id;

void addUserFingerPrint() {
  myScreen.clear(whiteColour);
  // Title
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);
  myScreen.setFontSize(myScreen.fontMax() - 1);    
  myScreen.gText(20, 20, "Add User Fingerprint", myScreen.calculateColour(255, 0, 0));  

  finger.getTemplateCount();
  id = finger.templateCount + 1;  

  while (!  getFingerprintEnroll() );
  
}

// Function to add a fingerprint for a new user
uint8_t getFingerprintEnroll() {

  int p = -1;
  myScreen.setFontSize(1);    
  myScreen.dRectangle(40, 110, 240, 30, whiteColour); 
  myScreen.gText(15, 117, "Waiting for valid finger to enroll", blackColour);  
  String new_id_msg = "ID: " + String(id);
  myScreen.gText(80, 133, new_id_msg, blackColour);  
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      myScreen.dRectangle(0, 110, 319, 60, whiteColour); 
      myScreen.gText(80, 117, "Image taken", blackColour);        
      break;
    case FINGERPRINT_NOFINGER:      
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      myScreen.gText(80, 135, "Image converted", blackColour);              
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  myScreen.gText(80, 155, "Remove finger", blackColour);                
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  myScreen.dRectangle(0, 110, 319, 80, whiteColour); 
  myScreen.gText(60, 100, "Place same finger again", blackColour);                   
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      myScreen.gText(80, 120, "Image taken", blackColour);                         
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      myScreen.gText(80, 140, "Image converted", blackColour);                               
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    myScreen.gText(80, 160, "Prints matched!", blackColour);       
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    myScreen.gText(100, 180, "Stored!", blackColour);    
    delay(1000);
    displayLandingPageDisplay();   
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
} // end of function


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void drawBackButton() {
  // Back button
  myScreen.circle (290, 215, 20, redColour);
  myScreen.setFontSize(myScreen.fontMax() - 1);  
  myScreen.gText(285, 208, "<", whiteColour);  
}


