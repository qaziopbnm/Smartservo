#include <SoftwareSerial.h>
#include "MeAuriga.h"

#define L1 12
#define L2 11
#define D1 3
#define panDown delay(100);servo_6_2.write(95);delay(100);
#define panUp   delay(100);servo_6_2.write(135);delay(100);

//  正方向往左
volatile double lastX = 0;
volatile double lastY = 12;
volatile double lastO1 = 0;
volatile double lastO2 = 0;

struct Vector2
{
  double o1;
  double o2;
};
MeSmartServo ss(PORT5);   //UART2 is on port 5
Servo servo_6_2;
MePort port_6(6);
float DEGS = 180.0/PI;
float RADS = PI/180.0;
float speed = 50, scal;
float records[2][361];
int i,poH;
Vector2 po;
void setup()
{
  Serial.begin(115200);
  ss.begin(115200);
  delay(5);
  panUp;
  ss.assignDevIdRequest();
  servo_6_2.attach(port_6.pin2());
  delay(50);
  Serial.println("setup!");
//  ss.setBreak(1,true);
//  ss.setBreak(2,true);
//  delay(5000);
//  ss.setZero(1);
//  ss.setZero(2);
  panUp;
  po = point2angle(0,12);
  moveTo(po.o1,po.o2);
  delay(500);
}

void drawMakeblock(){
  poH = 17;
  scal = 0.4;
  drawC(-8+2, poH, 'm', scal);
  drawC(-4+2, poH, 'a', scal);
  drawC(0+2, poH, 'k', scal);
  drawC(4+2, poH, 'e', scal);
  poH = 12;
  drawC(-8, poH, 'b', scal);
  drawC(-4, poH, 'l', scal);
  drawC(0, poH, 'o', scal);
  drawC(4, poH, 'c', scal);
  drawC(8, poH, 'k', scal);
  delay(500);
}

void loop()
{
//  drawMakeblock();
  poH = 0;
    scal = 0.2;
  Serial.println("first");
  number(2, poH, 1, scal);
    Serial.println("1");

  number(6, poH, 2, scal);
  Serial.println("2");

  number(10, poH, 3, scal);
  number(14, poH, 4, scal);
//  poH = 12;
//  number(-8, poH, 5, 0.2);
//  number(-4, poH, 6, 0.2);
//  number(0, poH, 7, 0.2);
//  number(4, poH, 8, 0.2);
//  number(8, poH, 9, 0.2);

//  number(0, 12, 3, 0.2);
  
  delay(500);
  while(1){
    ;
  }

}

void goTo(float x,float y){
  po = point2angle(x,y);
  moveTo(po.o1,po.o2);  
}
void moveTo(float angle1,float angle2){
  Serial.println("move Step");
  Serial.println(angle1);
  Serial.println(angle2);
  
  ss.moveTo(1,angle1,speed);
  ss.moveTo(2,angle2,speed);
////  delay(30);
//  while(abs(abs(ss.getAngleRequest(1)-angle1))>1||abs(abs(ss.getAngleRequest(2)-angle2))>1){
//   
//  }
}
Vector2 point2angle(double x,double y){
  y = 20 - y;
  x = 12 - x;  
  double angleLeft_0 = atan2((x + 3),y); 
  double angleLeft_1 = return_angle(return_distance_left(x,y), L1+D1, L2);  //Get left angle
  double angleLeft = angleLeft_1 - angleLeft_0;

  double angleTurn = return_angle(return_distance_left(x,y), L2, L1+D1);
  double angleDe = angleLeft_0 + angleTurn;
//  D1*cos(angleDe)
  x = x - D1*sin(angleDe);
  y = y - D1*cos(angleDe);
  double angleRight_0 = atan2((3 - x),y); 
  double angleRight_1 = return_angle(return_distance_right(x,y), L1, L2);
  double angleRight = angleRight_1 - angleRight_0;
//  lastX = x;
//  lastY = y;

  Vector2 a;
  a.o1 = - angleRight * DEGS;  
  a.o2 = angleLeft * DEGS;
  Serial.print("x:y ::");
  Serial.print(x);
  Serial.print(":");
  Serial.println(y);
  Serial.print("01:02 ::");
  Serial.print(a.o1);
  Serial.print(":");
  Serial.println(a.o2);
  return a; 
}
double return_angle(double a, double b, double c) {
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}
double return_distance_left(double x, double y){
  return sqrt((x+3)*(x+3)+y*y);
}
double return_distance_right(double x, double y){
  return sqrt((3-x)*(3-x)+y*y);
}

////////////////////////////////////////////////////////
void drawC(float bx, float by, char C, float scale){
  switch(C){
    case 'm':
      drawTo(bx + 0.5 * scale, by + 1 * scale);
      panDown;
      drawTo(bx + 2 * scale, by + 5 * scale);
      drawTo(bx + 3 * scale, by + 1.6 * scale);
      drawTo(bx + 4 * scale, by + 5 * scale);
      drawTo(bx + 5.5 * scale, by + 1 * scale);
      panUp;
      break;
    case 'a':
      drawTo(bx + 1.5 * scale, by + 1 * scale);
      panDown;
      drawTo(bx + 3 * scale, by + 5 * scale);
      drawTo(bx + 4.5 * scale, by + 1 * scale);
      panUp;
      drawTo(bx + 2.25 * scale, by + 2.4 * scale);
      panDown;
      delay(30);
      drawTo(bx + 3.75 * scale, by + 2.4 * scale);
      panUp;
      break;
    case 'k':
      drawTo(bx + 1.5 * scale, by + 5.5 * scale);
      panDown;
      drawTo(bx + 1.5 * scale, by + 1 * scale);
      panUp;
      drawTo(bx + 4.5 * scale, by + 5.5 * scale);
      panDown;
      delay(30);
      drawTo(bx + 1.5 * scale, by + 3 * scale);
      drawTo(bx + 4.5 * scale, by + 1 * scale);
      panUp;
      break;
    case 'e':
      drawTo(bx + 4.5 * scale, by + 5.5 * scale);
      panDown;
      drawTo(bx + 1.5 * scale, by + 5.5 * scale);
      drawTo(bx + 1.5 * scale, by + 0.5 * scale);
      drawTo(bx + 4.5 * scale, by + 0.5 * scale);
      panUp;
      drawTo(bx + 4.5 * scale, by + 3 * scale);
      panDown;
      drawTo(bx + 1.5 * scale, by + 3 * scale);
      panUp;
      break;
    case 'b':
      drawTo(bx + 1.5 * scale, by + 0.5 * scale);
      panDown;
      drawTo(bx + 1.5 * scale, by + 5.5 * scale);
      drawTo(bx + 3.5 * scale, by + 5.5 * scale);
      bogenUZS(bx + 3.5 * scale, by + 4.25 * scale, 1.25 * scale, PI/2, -PI/2, 1);
      drawTo(bx + 1.5 * scale, by + 3 * scale);
      panUp;
      drawTo(bx + 3.5 * scale, by + 3 * scale);
      panDown;
      bogenUZS(bx + 3.5 * scale, by + 1.75 * scale, 1.25 * scale, PI/2, -PI/2, 1);
      drawTo(bx + 1.5 * scale, by + 0.5 * scale);      
      panUp;
      break;
    case 'l':
      drawTo(bx + 1.5 * scale, by + 5.5 * scale);
      panDown;
      drawTo(bx + 1.5 * scale, by + 0.5 * scale);
      drawTo(bx + 4.5 * scale, by + 0.5 * scale);
      panUp;
      break;
    case 'o':
      drawTo(bx + 3 * scale, by + 0.5 * scale);
      panDown;
      bogenUZS(bx + 3 * scale, by + 3 * scale, 2.5 * scale, PI*2, -PI/2, 0.7);
      panUp;
      break;
    case 'c':
      drawTo( 2.5 * cos(PI/2-0.3) + bx+3*scale, 
              2.5 * sin(PI/2-0.3) + by+2*scale);
//      drawTo(bx + (3 + 2.5 * cos(PI/2-0.2) * 0.6) * scale, by + (3 + 2.5 * sin(PI/2-0.2)));
      panDown;
      bogenGZS(bx + 3 * scale, by + 3 * scale, 2.5 * scale, PI/2-0.3, PI*2, 0.6);
//      bogenGZS(bx + 3 * scale, by + 3 * scale, 2.5 * scale, PI*3/2-0.2, PI*5/2+0.2, 0.6);
      panUp;
      break;
    default:
      break;      
  }
}
void number(float bx, float by, int num, float scale) {

  switch (num) {

  case 0:
    drawTo(bx + 12 * scale, by + 6 * scale);
    panDown;
    bogenGZS(bx + 7 * scale, by + 10 * scale, 10 * scale, -0.8, 6.7, 0.5);
    panUp;
    break;
  case 1:

    drawTo(bx + 3 * scale, by + 15 * scale);
    panDown;
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 10 * scale, by + 0 * scale);
    panUp;
    break;
  case 2:
    drawTo(bx + 2 * scale, by + 12 * scale);
    panDown;
    bogenUZS(bx + 8 * scale, by + 14 * scale, 6 * scale, 3, -0.8, 1);
    Serial.print("x:y :: ");
    Serial.print(bx + 8 * scale);
    Serial.print(":");
    Serial.println( by + 14 * scale);
    
    drawTo(bx + 1 * scale, by + 0 * scale);
    drawTo(bx + 12 * scale, by + 0 * scale);
    panUp;
    break;
  case 3:
    drawTo(bx + 2 * scale, by + 17 * scale);
    panDown;
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 3, -2, 1);
    bogenUZS(bx + 5 * scale, by + 5 * scale, 5 * scale, 1.57, -3, 1);
    panUp;
    break;
  case 4:
    drawTo(bx + 10 * scale, by + 0 * scale);
    panDown;
    drawTo(bx + 10 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 6 * scale);
    drawTo(bx + 12 * scale, by + 6 * scale);
    panUp;
    break;
  case 5:
    drawTo(bx + 2 * scale, by + 5 * scale);
    panDown;
    bogenGZS(bx + 5 * scale, by + 6 * scale, 6 * scale, -2.5, 2, 1);
    drawTo(bx + 5 * scale, by + 20 * scale);
    drawTo(bx + 12 * scale, by + 20 * scale);
    panUp;
    break;
  case 6:
    drawTo(bx + 2 * scale, by + 10 * scale);
    panDown;
    bogenUZS(bx + 7 * scale, by + 6 * scale, 6 * scale, 2, -4.4, 1);
    drawTo(bx + 11 * scale, by + 20 * scale);
    panUp;
    break;
  case 7:
    drawTo(bx + 2 * scale, by + 20 * scale);
    panDown;
    drawTo(bx + 12 * scale, by + 20 * scale);
    drawTo(bx + 2 * scale, by + 0);
    panUp;
    break;
  case 8:
    drawTo(bx + 5 * scale, by + 10 * scale);
    panDown;
    bogenUZS(bx + 5 * scale, by + 15 * scale, 5 * scale, 4.7, -1.6, 1);
    bogenGZS(bx + 5 * scale, by + 5 * scale, 5 * scale, -4.7, 2, 1);
    panUp;
    break;

  case 9:
    drawTo(bx + 9 * scale, by + 11 * scale);
    panDown;
    bogenUZS(bx + 7 * scale, by + 15 * scale, 5 * scale, 4, -0.5, 1);
    drawTo(bx + 5 * scale, by + 0);
    panUp;
    break;

  case 111:

    panDown;
    drawTo(70, 46);
    drawTo(65, 43);

    drawTo(65, 49);
    drawTo(5, 49);
    drawTo(5, 45);
    drawTo(65, 45);
    drawTo(65, 40);

    drawTo(5, 40);
    drawTo(5, 35);
    drawTo(65, 35);
    drawTo(65, 30);

    drawTo(5, 30);
    drawTo(5, 25);
    drawTo(65, 25);
    drawTo(65, 20);

    drawTo(5, 20);
    drawTo(60, 44);

    drawTo(75.2, 47);
    panUp;

    break;

  case 11:
    drawTo(bx + 5 * scale, by + 15 * scale);
    panDown;
    bogenGZS(bx + 5 * scale, by + 15 * scale, 0.1 * scale, 1, -1, 1);
    panUp;
    drawTo(bx + 5 * scale, by + 5 * scale);
    panDown;
    bogenGZS(bx + 5 * scale, by + 5 * scale, 0.1 * scale, 1, -1, 1);
    panUp;
    break;

  }
}
void bogenUZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = -0.1;
  float count = 0;

  do {
    drawTo(sqee * radius * cos(start + count) + bx,
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) > ende);

}

void bogenGZS(float bx, float by, float radius, int start, int ende, float sqee) {
  float inkr = 0.1;
  float count = 0;
  

  do {
    drawTo(sqee * radius * cos(start + count) + bx, 
    radius * sin(start + count) + by);
    count += inkr;
  } 
  while ((start + count) <= ende);
}


void drawTo(double pX, double pY) {
  double dx, dy, c;
  
  dx = pX - lastX;
  dy = pY - lastY;
  //path lenght in mm, times 4 equals 4 steps per mm
  c = floor(8 * sqrt(dx * dx + dy * dy));

  if (c < 1) c = 1;

  for (i = 0; i <= c; i++) {
    // draw line point by point
    po = point2angle(lastX + (i * dx / c), lastY + (i * dy / c));
    moveTo(po.o1,po.o2);
  }
  lastX = pX;
  lastY = pY;
}


