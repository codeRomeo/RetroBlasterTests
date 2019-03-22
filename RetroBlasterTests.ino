
#include <TVout.h>
#include <fontALL.h>

TVout TV;

int x;
int y;
int r;

int score = 50;
const int SW_pin = 2;
int fastmode = 5;

int u = 0;
int l = 0;
int rnd = 0;

  int sensorPin1 = A0;    // select the input pin for the potentiometer
  int sensorPin2 = A1;
  int r_in = 0;
  int l_in = 0;
  int paddle = 1;
  int l_paddle =1;
  
int counter = 0;

void setup() {

 // Serial.begin(9600);
  
  TV.begin(NTSC,136,104);
  TV.select_font(font8x8);
  TV.clear_screen();
  TV.print(16,52,"Retro Blaster");
  make_sound(800,100,65);
  TV.delay(3000);
  TV.clear_screen();
  randomSeed(analogRead(3));
  
}

void loop() {
/*
r_in = analogRead(sensorPin);
r_in = map(r_in, 600, 900, -40, 150);
Serial.println(r_in);
*/

  TV.clear_screen();
  TV.draw_rect(0,0,135,103,WHITE);
  x = random(5,130);
  y = random(8,56); 
    
  TV.print(1,1,score);
  rnd = random(1,5); 

  for (r=y; r<96; r+=rnd) {  

      TV.print(96,1,counter);
      TV.draw_circle(x,r,4,WHITE,WHITE);
      TV.delay(score/2);   
      
          r_in = analogRead(sensorPin2);
          //paddle = map(r_in, 0, 1024, 118, 1);
            //TV.print(1,35,r_in);
          if (r_in < 520) {
          paddle += fastmode;
          }
          if (r_in > 520) {
            paddle -= fastmode;
          } 
 
       if (paddle >= 118) {
        paddle = 118;
      }
      if (paddle <= 1) {
        paddle = 1;
      }
            
      // (r_in != l_in) {
        TV.draw_rect(l_paddle,99,16,2,BLACK,BLACK);
        TV.draw_rect(paddle,99,16,2,WHITE,WHITE);
        l_in = r_in;
        l_paddle = paddle;
       //}
       TV.draw_circle(x,r,4,BLACK, BLACK); 
       counter++;    
   }
     l = paddle;
     u = paddle+16;
     if ( x>=l &&  x<=u ) { 
       score++;
       make_sound(400,300,25);   
     } else { 
      score--;
      make_low_sound(300,100,25); 
      }

     if ( score<= 0 ) {
      TV.clear_screen();
      TV.print(31,51,"Game Over");
      make_sound(500,300,25);
      TV.print(48,68,counter);
      score = 50;
      TV.delay(4000);
      counter = 0;
     }

}

void make_sound(int high, int low, int duration)
{
          int freq = low;
          while (freq < high)
          {
            TV.tone(freq,duration);
            TV.delay(duration);
            freq += duration;
          }
          
      TV.noTone();
  return;
}

void make_low_sound(int high, int low, int duration)
{
          int freq = high;
          while (freq > low)
          {
            TV.tone(freq,duration);
            TV.delay(duration);
            freq -= duration;
          }
          
      TV.noTone();
  return;
}

