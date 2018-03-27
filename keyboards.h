#include <stdint.h>
#include "Energia.h"
#include "SPI.h"
#include "Screen_K35_SPI.h"

uint16_t charColour, bgColour;

bool caps = false;
bool special_ch = false;

void keyboard_init(Screen_K35_SPI myScreen) 
{

  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);  

  charColour = myScreen.calculateColour(170, 170, 170);
  bgColour = myScreen.calculateColour(245, 245, 245);

  myScreen.setFontSize(2);

  myScreen.dRectangle(0, 50, 320, 190, bgColour);

  // Printing the numbers
  myScreen.gText(7, 60, "1", charColour);  
  myScreen.gText(40, 60, "2", charColour);  
  myScreen.gText(75, 60, "3", charColour);  
  myScreen.gText(105, 60, "4", charColour);  
  myScreen.gText(132, 60, "5", charColour);  
  myScreen.gText(165, 60, "6", charColour);  
  myScreen.gText(197, 60, "7", charColour);  
  myScreen.gText(230, 60, "8", charColour);  
  myScreen.gText(262, 60, "9", charColour);  
  myScreen.gText(292, 60, "0", charColour);

  
  myScreen.gText(7, 99, "q", charColour);
  myScreen.gText(40, 99, "w", charColour);
  myScreen.gText(75, 99, "e", charColour);
  myScreen.gText(105, 99, "r", charColour);
  myScreen.gText(132, 99, "t", charColour);
  myScreen.gText(165, 99, "y", charColour);  
  myScreen.gText(197, 99, "u", charColour);
  myScreen.gText(230, 99, "i", charColour);
  myScreen.gText(262, 99, "o", charColour);
  myScreen.gText(292, 99, "p", charColour);

  myScreen.gText(23, 137, "a", charColour);
  myScreen.gText(55, 137, "s", charColour);
  myScreen.gText(89, 137, "d", charColour);
  myScreen.gText(124, 137, "f", charColour);
  myScreen.gText(154, 137, "g", charColour);
  myScreen.gText(189, 137, "h", charColour);
  myScreen.gText(219, 137, "j", charColour);
  myScreen.gText(249, 137, "k", charColour);
  myScreen.gText(283, 137, "l", charColour);

  myScreen.setFontSize(1);
  myScreen.gText(8, 174, "CAPS", charColour);  
  myScreen.setFontSize(2);
  myScreen.gText(55, 170, "z", charColour);  
  myScreen.gText(89, 170, "x", charColour);  
  myScreen.gText(124, 170, "c", charColour);  
  myScreen.gText(154, 170, "v", charColour);
  myScreen.gText(189, 170, "b", charColour);
  myScreen.gText(219, 170, "n", charColour);
  myScreen.gText(249, 170, "m", charColour);  
  myScreen.setFontSize(1);
  myScreen.gText(281, 174, "DEL", charColour);
  
  myScreen.gText(7, 213, "?@#", charColour);
  myScreen.setFontSize(2);
  myScreen.gText(54, 207, ",", charColour);
  myScreen.dRectangle(87, 205, 145, 30, myScreen.calculateColour(230, 230, 230));
  myScreen.gText(249, 207, ".", charColour);
  myScreen.setFontSize(1);
  myScreen.gText(281, 213, "DONE", charColour);
    
}


void updateKeyboard(Screen_K35_SPI myScreen, bool caps, bool special_ch) {

  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false);

  String ch;      

  myScreen.setFontSize(2);  


  // Printing characters or special characters
  myScreen.dRectangle(1, 92, 30, 33, bgColour);
  ch = special_ch ? "!" : (caps ? "Q" : "q");
  myScreen.gText(7, 99, ch, charColour);
  myScreen.dRectangle(31, 92, 35, 33, bgColour);
  ch = special_ch ? "@" : (caps ? "W" : "w");
  myScreen.gText(40, 99, ch, charColour);
  myScreen.dRectangle(66, 92, 30, 33, bgColour);
  ch = special_ch ? "#" : (caps ? "E" : "e");
  myScreen.gText(75, 99, ch, charColour);
  myScreen.dRectangle(96, 92, 30, 33, bgColour);
  ch = special_ch ? "$" : (caps ? "R" : "r");
  myScreen.gText(105, 99, ch, charColour);
  myScreen.dRectangle(126, 92, 30, 33, bgColour);
  ch = special_ch ? "%" : (caps ? "T" : "t");
  myScreen.gText(132, 99, ch, charColour);
  myScreen.dRectangle(156, 92, 35, 33, bgColour);
  ch = special_ch ? "^" : (caps ? "Y" : "y");
  myScreen.gText(165, 99, ch, charColour);  
  myScreen.dRectangle(191, 92, 30, 33, bgColour);  
  ch = special_ch ? "&" : (caps ? "U" : "u");
  myScreen.gText(197, 99, ch, charColour);
  myScreen.dRectangle(221, 92, 35, 33, bgColour);
  ch = special_ch ? "\\" : (caps ? "I" : "i");
  myScreen.gText(230, 99, ch, charColour);
  myScreen.dRectangle(256, 92, 30, 33, bgColour);
  ch = special_ch ? "(" : (caps ? "O" : "o");
  myScreen.gText(262, 99, ch, charColour);
  myScreen.dRectangle(286, 92, 34, 33, bgColour); 
  ch = special_ch ? ")" : (caps ? "P" : "p");
  myScreen.gText(292, 99, ch, charColour);

  myScreen.dRectangle(15, 128, 30, 33, bgColour);
  ch = special_ch ? "?" : (caps ? "A" : "a");
  myScreen.gText(23, 137, ch, charColour);
  myScreen.dRectangle(46, 128, 35, 33, bgColour);
  ch = special_ch ? "~" : (caps ? "S" : "s");
  myScreen.gText(55, 137, ch, charColour);
  myScreen.dRectangle(80, 128, 35, 33, bgColour);
  ch = special_ch ? "|" : (caps ? "D" : "d");
  myScreen.gText(89, 137, ch, charColour);
  myScreen.dRectangle(115, 128, 30, 33, bgColour);
  ch = special_ch ? "_" : (caps ? "F" : "f");
  myScreen.gText(124, 137, ch, charColour);
  myScreen.dRectangle(145, 128, 35, 33, bgColour);
  ch = special_ch ? "-" : (caps ? "G" : "g");
  myScreen.gText(154, 137, ch, charColour);
  myScreen.dRectangle(180, 128, 30, 33, bgColour);  
  ch = special_ch ? "+" : (caps ? "H" : "h");
  myScreen.gText(189, 137, ch, charColour);
  myScreen.dRectangle(210, 128, 30, 33, bgColour);  
  ch = special_ch ? "*" : (caps ? "J" : "j");
  myScreen.gText(219, 137, ch, charColour);
  myScreen.dRectangle(240, 128, 33, 33, bgColour);
  ch = special_ch ? "/" : (caps ? "K" : "k");
  myScreen.gText(249, 137, ch, charColour);
  myScreen.dRectangle(274, 128, 35, 33, bgColour);
  ch = special_ch ? "=" : (caps ? "L" : "l");
  myScreen.gText(283, 137, ch, charColour);

  myScreen.dRectangle(5, 164, 40, 33, bgColour);
  if(special_ch) 
  {
    myScreen.gText(7, 170, "<", charColour);
  }
  else 
  {
    myScreen.setFontSize(1);    
    myScreen.gText(8, 174, "CAPS", charColour);
  }
  myScreen.dRectangle(46, 164, 35, 33, bgColour);
  myScreen.setFontSize(2);
  ch = special_ch ? ">" : (caps ? "Z" : "z");
  myScreen.gText(55, 170, ch, charColour);
  myScreen.dRectangle(80, 164, 35, 33, bgColour);
  ch = special_ch ? ":" : (caps ? "X" : "x");
  myScreen.gText(89, 170, ch, charColour);
  myScreen.dRectangle(115, 164, 30, 33, bgColour);
  ch = special_ch ? ";" : (caps ? "C" : "c");
  myScreen.gText(124, 170, ch, charColour);
  myScreen.dRectangle(145, 164, 35, 33, bgColour);
  ch = special_ch ? "\"" : (caps ? "V" : "v");
  myScreen.gText(154, 170, ch, charColour);
  myScreen.dRectangle(180, 164, 30, 33, bgColour);  
  ch = special_ch ? "\'" : (caps ? "B" : "b");
  myScreen.gText(189, 170, ch, charColour);
  myScreen.dRectangle(210, 164, 30, 33, bgColour);  
  ch = special_ch ? "{" : (caps ? "N" : "n");
  myScreen.gText(219, 170, ch, charColour);
  myScreen.dRectangle(240, 164, 35, 33, bgColour);
  ch = special_ch ? "}" : (caps ? "M" : "m");
  myScreen.gText(249, 170, ch, charColour);


  myScreen.setFontSize(1);
  myScreen.gText(281, 174, "DEL", charColour);

  myScreen.dRectangle(1, 200, 35, 39, bgColour);
  String mode = (!special_ch) ? "?@#" : "Abc";
  myScreen.gText(7, 213, mode, charColour);    
  
}

void updateInputArea(Screen_K35_SPI myScreen, char input[], int i)
{
  myScreen.setPenSolid(true);
  myScreen.setFontSolid(false); 
  myScreen.setFontSize(2);
  myScreen.dRectangle(5, 5, 314, 40, whiteColour);
  for(int j = 0; j <= i; j++)
    myScreen.gText(10 + myScreen.fontSizeX() * j, 15, String(input[j]), redColour);
}

String getCharacter(int x, int y, bool caps, bool special_ch)
{
        // Touch events on numbers
        if((x >= 1 && x <= 30) && (y >= 50 && y <= 85))
        {
          //Serial.println("1");
          return "1";
          delay(1000);
        }
        else if((x >= 31 && x <= 65) && (y >= 50 && y <= 85))
        {
          //Serial.println("2");
          return "2";
          delay(1000);
        }
        else if((x >= 66 && x <= 95) && (y >= 50 && y <= 85))
        {
          //Serial.println("3");
          return "3";
          delay(1000);
        }
        else if((x >= 96 && x <= 125) && (y >= 50 && y <= 85))
        {
          //Serial.println("4");
          return "4";
          delay(1000);
        }
        else if((x >= 126 && x <= 155) && (y >= 50 && y <= 85))
        {
          //Serial.println("5");
          return "5";
          delay(1000);
        }
        else if((x >= 156 && x <= 190) && (y >= 50 && y <= 85))
        {
          //Serial.println("6");
          return "6";
          delay(1000);
        }
        else if((x >= 191 && x <= 220) && (y >= 50 && y <= 85))
        {
          //Serial.println("7");
          return "7";
          delay(1000);
        }
        else if((x >= 221 && x <= 255) && (y >= 50 && y <= 85))
        {
          //Serial.println("8");
          return "8";
          delay(1000);
        }
        else if((x >= 256 && x <= 285) && (y >= 50 && y <= 85))
        {
          //Serial.println("9");
          return "9";
          delay(1000);
        }
        else if((x >= 286 && x <= 319) && (y >= 50 && y <= 87))
        {
          //Serial.println("0");
          return "0";
          delay(1000);
        }

        // Touch events on characters
        if((x >= 1 && x <= 30) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("!");
            return "!";
          }
          else if(caps)          
          {
            //Serial.println("Q");
            return "Q";
          }
          else 
          {
            //Serial.println("q");
            return "q";  
          }
          delay(1000);
        }
        else if((x >= 31 && x <= 65) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("@");
            return "@";
          }
          else if(caps)          
          {
            //Serial.println("W");
            return "W";
          }
          else 
          {
            //Serial.println("w");
            return "w";  
          }
          delay(1000);
        }
        else if((x >= 66 && x <= 95) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("#");
            return "#";
          }
          else if(caps)          
          {
            //Serial.println("E");
            return "E";
          }
          else 
          {
            //Serial.println("e");
            return "e";  
          }
          delay(1000);
        }
        else if((x >= 96 && x <= 125) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("$");
            return "$";
          }
          else if(caps)          
          {
            //Serial.println("R");
            return "R";
          }
          else 
          {
            //Serial.println("r");
            return "r";  
          }
          delay(1000);
        }
        else if((x >= 126 && x <= 155) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("%");
            return "%";
          }
          else if(caps)          
          {
            //Serial.println("T");
            return "T";
          }
          else 
          {
            //Serial.println("t");
            return "t";  
          }
          delay(1000);
        }
        else if((x >= 156 && x <= 190) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("^");
            return "^";
          }
          else if(caps)          
          {
            //Serial.println("Y");
            return "Y";
          }
          else 
          {
            //Serial.println("y");
            return "y";  
          }
          delay(1000);
        }
        else if((x >= 191 && x <= 220) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("&");
            return "&";
          }
          else if(caps)          
          {
            //Serial.println("U");
            return "U";
          }
          else 
          {
            //Serial.println("u");
            return "u";  
          }
          delay(1000);
        }
        else if((x >= 221 && x <= 255) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("\\");
            return "\\";
          }
          else if(caps)          
          {
            //Serial.println("I");
            return "I";
          }
          else 
          {
            //Serial.println("i");
            return "i";  
          }
          delay(1000);
        }
        else if((x >= 256 && x <= 285) && (y >= 92 && y <= 124))
        {
          if(special_ch)
          {
            //Serial.println("(");
            return "(";
          }
          else if(caps)          
          {
            //Serial.println("O");
            return "O";
          }
          else 
          {
            //Serial.println("o");
            return "o";  
          }
          delay(1000);
        }
        else if((x >= 286 && x <= 314) && (y >= 92 && y <= 122))
        {
          if(special_ch)
          {
            //Serial.println(")");
            return ")";
          }
          else if(caps)          
          {
            //Serial.println("P");
            return "P";
          }
          else 
          {
            //Serial.println("p");
            return "p";  
          }
          delay(1000);
        }
        else if((x >= 15 && x <= 45) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("?");
            return "?";
          }
          else if(caps)          
          {
            //Serial.println("A");
            return "A";
          }
          else 
          {
            //Serial.println("a");
            return "a";  
          }
          delay(1000);
        }
        else if((x >= 46 && x <= 80) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("~");
            return "~";
          }
          else if(caps)          
          {
            //Serial.println("S");
            return "S";
          }
          else 
          {
            //Serial.println("s");
            return "s";  
          }
          delay(1000);
        }
        else if((x >= 81 && x <= 115) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("|");
            return "|";
          }
          else if(caps)          
          {
            //Serial.println("D");
            return "D";
          }
          else 
          {
            //Serial.println("d");
            return "d";  
          }
          delay(1000);
        }
        else if((x >= 116 && x <= 145) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("_");
            return "_";
          }
          else if(caps)          
          {
            //Serial.println("F");
            return "F";
          }
          else 
          {
            //Serial.println("f");
            return "f";  
          }
          delay(1000);
        }
        else if((x >= 146 && x <= 180) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("-");
            return "-";
          }
          else if(caps)          
          {
            //Serial.println("G");
            return "G";
          }
          else 
          {
            //Serial.println("g");
            return "g";  
          }
          delay(1000);
        }
        else if((x >= 181 && x <= 210) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("+");
            return "+";
          }
          else if(caps)          
          {
            //Serial.println("H");
            return "H";
          }
          else 
          {
            //Serial.println("h");
            return "h";  
          }
          delay(1000);
        }
        else if((x >= 211 && x <= 240) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("*");
            return "*";
          }
          else if(caps)          
          {
            //Serial.println("J");
            return "J";
          }
          else 
          {
            //Serial.println("j");
            return "j";  
          }
          delay(1000);
        }
        else if((x >= 241 && x <= 274) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("/");
            return "/";
          }
          else if(caps)          
          {
            //Serial.println("K");
            return "K";
          }
          else 
          {
            //Serial.println("k");
            return "k";  
          }
          delay(1000);
        }
        else if((x >= 275 && x <= 310) && (y >= 123 && y <= 153))
        {
          if(special_ch)
          {
            //Serial.println("=");
            return "=";
          }
          else if(caps)          
          {
            //Serial.println("L");
            return "L";
          }
          else 
          {
            //Serial.println("l");
            return "l";  
          }
          delay(1000);
        }
        else if((x >= 46 && x <= 80) && (y >= 155 && y <= 183))
        {
          if(special_ch)
          {
            //Serial.println(">");
            return ">";
          }
          else if(caps)          
          {
            //Serial.println("Z");
            return "Z";
          }
          else 
          {
            //Serial.println("z");
            return "z";  
          }
          delay(1000);
        }
        else if((x >= 81 && x <= 115) && (y >= 155 && y <= 183))
        {
          if(special_ch)
          {
            //Serial.println(":");
            return ":";
          }
          else if(caps)          
          {
            //Serial.println("X");
            return "X";
          }
          else 
          {
            //Serial.println("x");
            return "x";  
          }
          delay(1000);
        }
        else if((x >= 116 && x <= 145) && (y >= 155 && y <= 183))
        {
          if(special_ch)
          {
            //Serial.println(";");
            return ";";
          }
          else if(caps)          
          {
            //Serial.println("C");
            return "C";
          }
          else 
          {
            //Serial.println("c");
            return "c";  
          }
          delay(1000);
        }
        else if((x >= 146 && x <= 180) && (y >= 155 && y <= 183))
        {
          if(special_ch)
          {
            //Serial.println("\"");
            return "\"";
          }
          else if(caps)          
          {
            //Serial.println("V");
            return "V";
          }
          else 
          {
            //Serial.println("v");
            return "v";  
          }
          delay(1000);
        }
        else if((x >= 181 && x <= 210) && (y >= 155 && y <= 183))
        {
          if(special_ch)
          {
            //Serial.println("\'");
            return "\'";
          }
          else if(caps)          
          {
            //Serial.println("B");
            return "B";
          }
          else 
          {
            //Serial.println("b");
            return "b";  
          }
          delay(1000);
        }
        else if((x >= 211 && x <= 240) && (y >= 155 && y <= 183))
        {
          if(special_ch)
          {
            //Serial.println("{");
            return "{";
          }
          else if(caps)          
          {
            //Serial.println("N");
            return "N";
          }
          else 
          {
            //Serial.println("n");
            return "n";  
          }
          delay(1000);
        }
        else if((x >= 241 && x <= 275) && (y >= 155 && y <= 183))
        {
          if(special_ch)
          {
            //Serial.println("}");
            return "}";
          }
          else if(caps)          
          {
            //Serial.println("M");
            return "M";
          }
          else 
          {
            //Serial.println("m");
            return "m";  
          }
          delay(1000);
        }        
        else if((x >= 46 && x <= 80) && (y >= 190 && y <= 220))
        {
          //Serial.println(",");
          return ",";
          delay(1000);
        }
        else if((x >= 83 && x <= 235) && (y >= 190 && y <= 220))
        {
          //Serial.println("Space");
          return " ";
          delay(1000);
        }
        else if((x >= 240 && x <= 275) && (y >= 190 && y <= 220))
        {
          //Serial.println(".");
          return ".";
          delay(1000);
        }  
        else 
        {
          return "\0";  
        }
}


void keypad(Screen_K35_SPI myScreen, char input[])
{
  // Page Title  
  myScreen.clear(whiteColour);

  keyboard_init(myScreen);  

  int i = -1;  

  while(true)
  {
    
    if(myScreen.isTouch() > 0)
    {
      uint16_t  x, y, z;
      myScreen.getTouch(x, y, z);      

      //Serial.println("x: " + String(x) + "y: " + String(y) + "z: " + String(z));

      // Detect touch event, condition for button pressed
      if(z > 500 && y >= 50)      
      {          

        if((x >= 276 && x <= 319) && (y >= 155 && y <= 183))
        {
          //Serial.println("DEL");               
          updateInputArea(myScreen, input, --i);
          delay(1000);
        }
        else if((x >= 290 && x <= 310) && (y >= 190 && y <= 210))
        {
          //Serial.println("DONE");   
          input[++i] = '\0';
          return;
          //Serial.println(input);             
          //delay(1000);
        }
        else if((x >= 5 && x <= 45) && (y >= 155 && y <= 185))
        {
          //Serial.println("CAPS ON");     
          caps = !caps;
          updateKeyboard(myScreen, caps, special_ch);               
          delay(1000);
        }
        else if((x >= 1 && x <= 35) && (y >= 190 && y <= 215))
        {
          //Serial.println("SPECIAL ON");     
          special_ch = !special_ch;
          updateKeyboard(myScreen, caps, special_ch);               
          delay(1000);
        }
        else 
        {
            String ch = getCharacter(x, y, caps, special_ch);
            if(ch != "\0")
            {
              //Serial.println(ch);  
              input[++i] = ch[0];
              updateInputArea(myScreen, input, i);
              
            }
            delay(1000);  
        }
        
      }
    }
  } 
  
}



/*
void drawKeyboard()
{    
    uint16_t c;
    int k = 0;
    
    for (uint16_t i=51; i<240; i++) {
        for (uint16_t j=0; j<320; j++) {            
                c = lowercaseKeyboard[k++];                
                myScreen.point(j, i, c);            
        }        
    }
}
*/


/*
  uint16_t charColour = myScreen.calculateColour(170, 170, 170);



  myScreen.dRectangle(0, 50, 320, 190, myScreen.calculateColour(245, 245, 245));


  //myScreen.dRectangle(1, 50, 30, 33, blueColour);    
  myScreen.gText(7, 60, "1", charColour);
  //myScreen.dRectangle(31, 50, 35, 33, blueColour);
  myScreen.gText(40, 60, "2", charColour);
  //myScreen.dRectangle(66, 50, 30, 33, blueColour);
  myScreen.gText(75, 60, "3", charColour);
  //myScreen.dRectangle(96, 50, 30, 33, blueColour);
  myScreen.gText(105, 60, "4", charColour);
  //myScreen.dRectangle(126, 50, 30, 33, blueColour);
  myScreen.gText(132, 60, "5", charColour);
  //myScreen.dRectangle(156, 50, 35, 33, blueColour);  
  myScreen.gText(165, 60, "6", charColour);
  //myScreen.dRectangle(191, 50, 30, 33, blueColour);  
  myScreen.gText(197, 60, "7", charColour);
  //myScreen.dRectangle(221, 50, 35, 33, blueColour);
  myScreen.gText(230, 60, "8", charColour);
  //myScreen.dRectangle(256, 50, 30, 33, blueColour);
  myScreen.gText(262, 60, "9", charColour);
  //myScreen.dRectangle(286, 50, 34, 33, blueColour);  
  myScreen.gText(292, 60, "0", charColour);

  //myScreen.setPenSolid(false);

  

  
  //myScreen.dRectangle(1, 92, 30, 33, blueColour);
  myScreen.gText(7, 99, "q", charColour);
  //myScreen.dRectangle(31, 92, 35, 33, blueColour);
  myScreen.gText(40, 99, "w", charColour);
  //myScreen.dRectangle(66, 92, 30, 33, blueColour);
  myScreen.gText(75, 99, "e", charColour);
  //myScreen.dRectangle(96, 92, 30, 33, blueColour);
  myScreen.gText(105, 99, "r", charColour);
  //myScreen.dRectangle(126, 92, 30, 33, blueColour);
  myScreen.gText(132, 99, "t", charColour);
  //myScreen.dRectangle(156, 92, 35, 33, blueColour);
  myScreen.gText(165, 99, "y", charColour);  
  //myScreen.dRectangle(191, 92, 30, 33, blueColour);  
  myScreen.gText(197, 99, "u", charColour);
  //myScreen.dRectangle(221, 92, 35, 33, blueColour);
  myScreen.gText(230, 99, "i", charColour);
  //myScreen.dRectangle(256, 92, 30, 33, blueColour);
  myScreen.gText(262, 99, "o", charColour);
  //myScreen.dRectangle(286, 92, 34, 33, blueColour); 
  myScreen.gText(292, 99, "p", charColour);

  //myScreen.dRectangle(15, 128, 30, 33, blueColour);
  myScreen.gText(23, 137, "a", charColour);
  //myScreen.dRectangle(46, 128, 35, 33, blueColour);
  myScreen.gText(55, 137, "s", charColour);
  //myScreen.dRectangle(80, 128, 35, 33, blueColour);
  myScreen.gText(89, 137, "d", charColour);
  //myScreen.dRectangle(115, 128, 30, 33, blueColour);
  myScreen.gText(124, 137, "f", charColour);
  //myScreen.dRectangle(145, 128, 35, 33, blueColour);
  myScreen.gText(154, 137, "g", charColour);
  //myScreen.dRectangle(180, 128, 30, 33, blueColour);  
  myScreen.gText(189, 137, "h", charColour);
  //myScreen.dRectangle(210, 128, 30, 33, blueColour);  
  myScreen.gText(219, 137, "j", charColour);
  //myScreen.dRectangle(240, 128, 33, 33, blueColour);
  myScreen.gText(249, 137, "k", charColour);
  //myScreen.dRectangle(274, 128, 35, 33, blueColour);
  myScreen.gText(283, 137, "l", charColour);

  //myScreen.dRectangle(5, 164, 40, 33, blueColour);
  myScreen.setFontSize(1);
  myScreen.gText(8, 174, "CAPS", charColour);
  //myScreen.dRectangle(46, 164, 35, 33, blueColour);
  myScreen.setFontSize(2);
  myScreen.gText(55, 170, "z", charColour);
  //myScreen.dRectangle(80, 164, 35, 33, blueColour);
  myScreen.gText(89, 170, "x", charColour);
  //myScreen.dRectangle(115, 164, 30, 33, blueColour);
  myScreen.gText(124, 170, "c", charColour);
  //myScreen.dRectangle(145, 164, 35, 33, blueColour);
  myScreen.gText(154, 170, "v", charColour);
  //myScreen.dRectangle(180, 164, 30, 33, blueColour);  
  myScreen.gText(189, 170, "b", charColour);
  //myScreen.dRectangle(210, 164, 30, 33, blueColour);  
  myScreen.gText(219, 170, "n", charColour);
  //myScreen.dRectangle(240, 164, 35, 33, blueColour);
  myScreen.gText(249, 170, "m", charColour);  

  
  
  //myScreen.dRectangle(275, 164, 40, 33, blueColour);
  myScreen.setFontSize(1);
  myScreen.gText(281, 174, "BACK", charColour);

  //myScreen.dRectangle(1, 200, 35, 39, blueColour);
  myScreen.gText(7, 213, "?@#", charColour);
  //myScreen.dRectangle(46, 200, 35, 39, blueColour);
  myScreen.setFontSize(2);
  myScreen.gText(54, 207, ",", charColour);
  //myScreen.dRectangle(83, 200, 155, 39, blueColour);  
  myScreen.dRectangle(87, 205, 145, 30, myScreen.calculateColour(230, 230, 230));
  //myScreen.dRectangle(240, 200, 35, 39, blueColour);
  myScreen.gText(249, 207, ".", charColour);
  //myScreen.dRectangle(275, 200, 44, 39, blueColour);
  myScreen.setFontSize(1);
  myScreen.gText(281, 213, "DONE", charColour);
  */









