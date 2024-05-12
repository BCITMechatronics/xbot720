/***************************************************************************
 *                            Bitwise Definition                           *
 ***************************************************************************/
#define BIT0    0x01
#define BIT1    0x02
#define BIT2    0x04
#define BIT3    0x08
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40
#define BIT7    0x80
/***************************************************************************
 *                        Arduino Pinout Definition                        *
 ***************************************************************************/
#define TX      1   // HC-05 RX
#define RX      0   // HC-05 TX

#define RCHA    2   // Right Encoder Channel A
#define LCHA    3   // Left Encoder Channel A
#define RIN1    6   // Right Motor Enable 1
#define RIN2    5   // Right Motor Enable 2
#define LIN1    9   // Left Motor Enable 1
#define LIN2    10  // Left Motor Enable 2
/***************************************************************************
 *                           System Specification                          *
 ***************************************************************************/
#define WHEEL_DIA_MM 90
#define PI           3.1415
#define WHEEL_TRAVEL WHEEL_DIA_MM * PI
#define CPR          757       // Count per Revolution

#define LEFT         0
#define RIGHT        1
/***************************************************************************
 *                                 Globals                                 *
 ***************************************************************************/
volatile unsigned int counts[2] = {0};   // Real time counter for Left Channel A

void setup() {
  Serial.begin(57600);
  // Setup the pinout
  pinMode(RIN1, OUTPUT);
  pinMode(RIN2, OUTPUT);
  pinMode(RCHA, INPUT);
  attachInterrupt(digitalPinToInterrupt(RCHA), rPulse, RISING);

  pinMode(LIN1, OUTPUT);
  pinMode(LIN2, OUTPUT);
  pinMode(LCHA, INPUT);
  attachInterrupt(digitalPinToInterrupt(LCHA), lPulse, RISING);
}

void loop() {
  char buff[50];
  sprintf(buff, "Left:%d\tRight:%d", counts[LEFT], counts[RIGHT]);
  Serial.println(buff);
}

/* rPulse
 * This function is for the interrupt for Right Encoder Channel A
 * It only increment the count from right wheel by 1
 */
void rPulse(){
  counts[RIGHT]++;
}

/* lPulse
 * This function is for the interrupt for Left Encoder Channel A
 * It only increment the count from left wheel by 1
 */
void lPulse(){
  counts[LEFT]++;
}