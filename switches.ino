#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define box1        2 // On Trinket or Gemma, suggest changing this to 1
#define box2        7
#define box3        4

#define NUMPIXELS 16 // Popular NeoPixel ring size

Adafruit_NeoPixel pixel1(NUMPIXELS, box1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel2(NUMPIXELS, box2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel3(NUMPIXELS, box3, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels


Servo first_servoR;  // create servo object to control a servo
Servo first_servoL;
Servo second_servoR;
Servo second_servoL;
Servo third_servoR;
Servo third_servoL;
int pos = 0;    // variable to store the servo position
// twelve servo objects can be created on most boards


//画面のサイズの設定
#define SCREEN_WIDTH    (128)
#define SCREEN_HEIGHT   (64)

//画面のサイズ(データシートから)
#define SCREEN_ADDRESS  (0x3C)

int loopCount = 0;

// ディスプレイ変数の宣言
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
Adafruit_SSD1306 display(-1);    //ディスプレイ変数の宣言

void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(8, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);  first_servoL.attach(3);
  first_servoR.attach(10);
  second_servoL.attach(11);
  second_servoR.attach(5);
  third_servoL.attach(9);
  third_servoR.attach(6);
  Serial.begin(9600);
  //初期位置
  first_servoL.write(40);
  first_servoR.write(135);
  second_servoL.write(40);
  second_servoR.write(150);
  third_servoL.write(55);
  third_servoR.write(150);
  //初期位置
  first_servoL.write(40);
  first_servoR.write(135);
  second_servoL.write(40);
  second_servoR.write(150);
  third_servoL.write(35);
  third_servoR.write(150);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixel1.begin();
  pixel2.begin();
  pixel3.begin();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("");
  display.display();
}

int pink, blue, murasaki, right, center, left = 0;
void loop() {
  int i = 0;
  pink = digitalRead(14);
  blue = digitalRead(15);
  murasaki = digitalRead(16);
  //檻の設定
  right = digitalRead(17);
  center = digitalRead(12);
  left = digitalRead(8);
  if (left + center + right != 0) {
    if (left == 0) {                 //押したら1出力
      if (pink + blue + murasaki != 1) {
        if (pink + blue + murasaki != 0) {
          //Clear display.
          if (pink + blue + murasaki != 3) {
            display.clearDisplay();
            display.setTextSize(2);
            display.setTextColor(WHITE);
            display.setCursor(0, 0);
            display.println("ERROR");

            if (pink == 1) {
              display.print("p ");
            }
            if (blue == 1) {
              display.print("b ");
            }
            if (murasaki == 1) {
              display.print("m");
            }
            display.display();
          }
          Serial.println("---<ERROR>---");
          if (pink == 1) {
            Serial.println("pink");
          }
          if (murasaki == 1) {
            Serial.println("murasaki");
          }
          if (blue == 1) {
            Serial.println("blue");
          }
          Serial.println("");
        }
      } else if (pink + blue + murasaki == 1) {
        if (pink == 1) {
          //アタリのLED発光
          pixel3.clear();
          pixel3.fill(pixel1.Color(0, 0, 128));
          pixel3.show();
          Serial.println("アタリ");
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Atari");
          display.display();
          //正解の檻を開ける
          third_servoL.write(90);
          third_servoR.write(90);
        } else if (blue == 1) {
          //ハズレのLED発光
          pixel1.clear();
          pixel1.fill(pixel1.Color(128, 0, 0));
          pixel1.show();
          Serial.println("ハズレblue");
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Hazure");
          display.display();
          //ハズレの檻を開ける
          first_servoL.write(90);
          first_servoR.write(90);
        } else if (murasaki == 1) {
          //ハズレのLED発光
          pixel2.clear();
          pixel2.fill(pixel1.Color(128, 0, 0));
          pixel2.show();
          Serial.println("ハズレmurasaki");
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Hazure");
          display.display();
          //ハズレの檻を開ける
          second_servoL.write(90);
          second_servoR.write(90);
        }
      }
    }
    if (center == 0) {                 //押したら1出力
      if (pink + blue + murasaki != 1) {
        if (pink + blue + murasaki != 0) {
          Serial.println("---<ERROR>---");
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("ERROR");

          if (pink == 1) {
            display.print("p ");
          }
          if (blue == 1) {
            display.print("b ");
          }
          if (murasaki == 1) {
            display.print("m");
          }
          display.display();

          if (pink == 1) {
            Serial.println("pink");
          }
          if (murasaki == 1) {
            Serial.println("murasaki");
          }
          if (blue == 1) {
            Serial.println("blue");
          }
          Serial.println("");
        }
      } else if (pink + blue + murasaki == 1) {
        if (pink == 1) {
          Serial.println("ハズレpink");
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Hazure");
          display.display();
          //ハズレの檻を開ける
          pixel1.clear();
          pixel1.fill(pixel1.Color(128, 0, 0));
          pixel1.show();
          first_servoL.write(90);
          first_servoR.write(90);
        } else if (blue == 1) {
          Serial.println("アタリ");
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Atari");
          display.display();
          //正解の檻を開ける
          pixel3.clear();
          pixel3.fill(pixel3.Color(0, 0, 128));
          pixel3.show();
          third_servoL.write(90);
          third_servoR.write(90);
        } else if (murasaki == 1) {
          Serial.println("ハズレmurasaki");
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Hazure");
          display.display();
          //ハズレの檻を開ける
          pixel2.clear();
          pixel2.fill(pixel2.Color(128, 0, 0));
          pixel2.show();
          second_servoL.write(90);
          second_servoR.write(90);
        }
      }
    }
    if (right == 0) {                 //押したら1出力
      if (pink + blue + murasaki != 1) {
        if (pink + blue + murasaki != 0) {
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("ERROR");

          if (pink == 1) {
            display.print("p ");
          }
          if (blue == 1) {
            display.print("b ");
          }
          if (murasaki == 1) {
            display.print("m");
          }
          display.display();

          Serial.println("---<ERROR>---");
          if (pink == 1) {
            Serial.println("pink");
          }
          if (murasaki == 1) {
            Serial.println("murasaki");
          }
          if (blue == 1) {
            Serial.println("blue");
          }
          Serial.println("");
        }
      } else if (pink + blue + murasaki == 1) {
        //サーボ回転、檻を開ける
        if (pink == 1) {
          Serial.println("ハズレpink");
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Hazure");
          display.display();
          pixel1.clear();
          pixel1.fill(pixel1.Color(128, 0, 0));
          pixel1.show();
          //ハズレの檻を開ける
          first_servoL.write(90);
          first_servoR.write(90);
        } else if (blue == 1) {
          Serial.println("ハズレblue");
          pixel2.clear();
          pixel2.fill(pixel2.Color(128, 0, 0));
          pixel2.show();
          //Clear display.
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Hazure");
          display.display();
          //ハズレの檻を開ける
          second_servoL.write(90);
          second_servoR.write(90);
        } else if (murasaki == 1) {
          Serial.println("アタリ");
          //Clear display.
          pixel3.clear();
          pixel3.fill(pixel3.Color(0, 0, 128));
          pixel3.show();
          display.clearDisplay();
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0, 0);
          display.println("Atari");
          display.display();
          //正解の檻を開ける
          third_servoL.write(90);
          third_servoR.write(90);
        }
      }
    }
    delay(200);
  }
}

/*D2 LED　箱1
  D3 Servo 箱1　left （向かい合ったとき）
  D4 LED　箱3
  D5 Servo 箱２ right
  D6 Servo　箱3　right
  D7 LED　箱2
  D8 Front Switch Left
  D9 Servo　箱3 left
  D10 Servo 箱1 right
  D11 Servo　箱2　left
  D12 Front Switch Center
  D14 Red Switch　ピンク...1
  D15 Red Switch　青緑...2
  D16 Red Switch　紫...3
  D17 Front Switch Right

  1,2,3押して左ボタンでモーターのリセット
  右ボタンでディスプレイのリセット
*/
