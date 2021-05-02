/* Trine 2021 Pinewood Derby Senior Design Project
   By Jake Garlits, Gwen Pierce, and Nick Bonifant

   This code runs a 46-state state machine to allow
   for proper timing of the pinewood derby cars.

   The data collected by the sensors is then sent
   to a Google Firebase server to be displayed on
   our website.
*/

#include <Firebase_Arduino_WiFiNINA.h>

#define FIREBASE_HOST "trine-pinewood-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "0mWqlgBmWM63F5jm058DDH9kiuh6nYqdPl7W8A8D"
#define WIFI_SSID "YOUR WIFI SSID HERE" //Enter your SSID
#define WIFI_PASSWORD "YOUR WIFI PASSWORD HERE" //Enter your Password

//Variables
FirebaseData firebaseData;

String path = "/IMU_LSM6DS3";
String jsonStr;

double sensor[13]; // 0 => gate sensor; 1-6 => lane 1; 7-12 => lane 2
int state;


void setup() {
  Serial.begin(9600);
  state = 0;
  //Enable input pins and set times to 0;
  for (int i = 0; i < 13; i++) {
    pinMode(i, INPUT_PULLUP);
    sensor[i] = 0;
  }

  Serial.print("Connecting to WiFi…");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

}

void loop() {

  //The timing for the track is controlled by a 46-state state machine

  bool b1 = LOW;
  bool b2 = LOW;

  switch (state) {

    ////////////// State #0 - Reset ///////////////

    case 0:
      Serial.println("State #0");
      while (digitalRead(0) != LOW) {} //Wait for drop gate sensor to start race
      sensor[0] = micros();
      state = 1;
      break;

    ////////////// State #1 //////////////////////
    case 1:
      Serial.println("State #1");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(1);
        b2 = digitalRead(7);
        int x = (micros() - sensor[0])/1000000.0;
        if (x > 3){
          state = 0;
          return 0;
        }
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[1] = micros();
        state = 2;
      }
      else {
        sensor[7] = micros();
        state = 7;
      }
      break;

    ////////////// State #2 //////////////////////

    case 2:
      Serial.println("State #2");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(2);
        b2 = digitalRead(7);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[2] = micros();
        state = 3;
      }
      else {
        sensor[7] = micros();
        state = 8;
      }
      break;

    ////////////// State #3 //////////////////////

    case 3:
      Serial.println("State #3");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(3);
        b2 = digitalRead(7);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[3] = micros();
        state = 4;
      }
      else {
        sensor[7] = micros();
        state = 9;
      }
      break;

    ////////////// State #4 //////////////////////

    case 4:
      Serial.println("State #4");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(4);
        b2 = digitalRead(7);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[4] = micros();
        state = 5;
      }
      else {
        sensor[7] = micros();
        state = 10;
      }
      break;

    ////////////// State #5 //////////////////////

    case 5:
      Serial.println("State #5");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(5);
        b2 = digitalRead(7);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[5] = micros();
        state = 6;
      }
      else {
        sensor[7] = micros();
        state = 11;
      }
      break;

    ////////////// State #6 //////////////////////

    case 6:
      Serial.println("State #6");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(6);
        b2 = digitalRead(7);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[6] = micros();
        state = 0;
        car1_stats();
      }
      else {
        sensor[7] = micros();
        state = 12;
      }
      break;

    ////////////// State #7 //////////////////////

    case 7:
      Serial.println("State #7");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(1);
        b2 = digitalRead(8);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[1] = micros();
        state = 8;
      }
      else {
        sensor[8] = micros();
        state = 13;
      }
      break;

    ////////////// State #8 //////////////////////

    case 8:
      Serial.println("State #8");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(2);
        b2 = digitalRead(8);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[2] = micros();
        state = 9;
      }
      else {
        sensor[8] = micros();
        state = 14;
      }
      break;

    ////////////// State #9 //////////////////////

    case 9:
      Serial.println("State #9");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(3);
        b2 = digitalRead(8);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[3] = micros();
        state = 10;
      }
      else {
        sensor[8] = micros();
        state = 15;
      }
      break;

    ////////////// State #10 //////////////////////

    case 10:
      Serial.println("State #10");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(4);
        b2 = digitalRead(8);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[4] = micros();
        state = 11;
      }
      else {
        sensor[8] = micros();
        state = 16;
      }
      break;

    ////////////// State #11 //////////////////////

    case 11:
      Serial.println("State #11");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(5);
        b2 = digitalRead(8);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[5] = micros();
        state = 12;
      }
      else {
        sensor[8] = micros();
        state = 17;
      }
      break;

    ////////////// State #12 //////////////////////

    case 12:
      Serial.println("State #12");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(6);
        b2 = digitalRead(8);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[6] = micros();
        state = 42;
      }
      else {
        sensor[8] = micros();
        state = 18;
      }
      break;

    ////////////// State #13 //////////////////////

    case 13:
      Serial.println("State #13");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(1);
        b2 = digitalRead(9);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[1] = micros();
        state = 14;
      }
      else {
        sensor[9] = micros();
        state = 19;
      }
      break;

    ////////////// State #14 //////////////////////

    case 14:
      Serial.println("State #14");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(2);
        b2 = digitalRead(9);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[2] = micros();
        state = 15;
      }
      else {
        sensor[9] = micros();
        state = 20;
      }
      break;

    ////////////// State #15 //////////////////////

    case 15:
      Serial.println("State #15");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(3);
        b2 = digitalRead(9);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[3] = micros();
        state = 16;
      }
      else {
        sensor[9] = micros();
        state = 21;
      }
      break;

    ////////////// State #16 //////////////////////

    case 16:
      Serial.println("State #16");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(4);
        b2 = digitalRead(9);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[4] = micros();
        state = 17;
      }
      else {
        sensor[9] = micros();
        state = 22;
      }
      break;

    ////////////// State #17 //////////////////////

    case 17:
      Serial.println("State #17");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(5);
        b2 = digitalRead(9);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[5] = micros();
        state = 18;
      }
      else {
        sensor[9] = micros();
        state = 23;
      }
      break;

    ////////////// State #18 //////////////////////

    case 18:
      Serial.println("State #18");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(6);
        b2 = digitalRead(9);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[6] = micros();
        state = 43;
      }
      else {
        sensor[9] = micros();
        state = 24;
      }
      break;

    ////////////// State #19 //////////////////////

    case 19:
      Serial.println("State #19");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(1);
        b2 = digitalRead(10);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[1] = micros();
        state = 20;
      }
      else {
        sensor[10] = micros();
        state = 25;
      }
      break;

    ////////////// State #20 //////////////////////

    case 20:
      Serial.println("State #20");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(2);
        b2 = digitalRead(10);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[2] = micros();
        state = 21;
      }
      else {
        sensor[10] = micros();
        state = 26;
      }
      break;

    ////////////// State #21 //////////////////////

    case 21:
      Serial.println("State #21");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(3);
        b2 = digitalRead(10);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[3] = micros();
        state = 22;
      }
      else {
        sensor[10] = micros();
        state = 27;
      }
      break;

    ////////////// State #22 //////////////////////

    case 22:
      Serial.println("State #22");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(4);
        b2 = digitalRead(10);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[4] = micros();
        state = 23;
      }
      else {
        sensor[10] = micros();
        state = 28;
      }
      break;

    ////////////// State #23 //////////////////////

    case 23:
      Serial.println("State #23");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(5);
        b2 = digitalRead(10);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[5] = micros();
        state = 24;
      }
      else {
        sensor[10] = micros();
        state = 29;
      }
      break;

    ////////////// State #24 //////////////////////

    case 24:
      Serial.println("State #24");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(6);
        b2 = digitalRead(10);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[6] = micros();
        state = 44;
      }
      else {
        sensor[10] = micros();
        state = 30;
      }
      break;

    ////////////// State #25 //////////////////////

    case 25:
      Serial.println("State #25");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(1);
        b2 = digitalRead(11);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[1] = micros();
        state = 26;
      }
      else {
        sensor[11] = micros();
        state = 31;
      }
      break;

    ////////////// State #26 //////////////////////

    case 26:
      Serial.println("State #26");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(2);
        b2 = digitalRead(11);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[2] = micros();
        state = 27;
      }
      else {
        sensor[11] = micros();
        state = 32;
      }
      break;

    ////////////// State #27 //////////////////////

    case 27:
      Serial.println("State #27");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(3);
        b2 = digitalRead(11);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[3] = micros();
        state = 28;
      }
      else {
        sensor[11] = micros();
        state = 33;
      }
      break;

    ////////////// State #28 //////////////////////

    case 28:
      Serial.println("State #28");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(4);
        b2 = digitalRead(11);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[4] = micros();
        state = 29;
      }
      else {
        sensor[11] = micros();
        state = 34;
      }
      break;

    ////////////// State #29 //////////////////////

    case 29:
      Serial.println("State #29");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(5);
        b2 = digitalRead(11);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[5] = micros();
        state = 30;
      }
      else {
        sensor[11] = micros();
        state = 35;
      }
      break;

    ////////////// State #30 //////////////////////

    case 30:
      Serial.println("State #30");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(6);
        b2 = digitalRead(11);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[6] = micros();
        state = 45;
      }
      else {
        sensor[11] = micros();
        state = 36;
      }
      break;

    ////////////// State #31 //////////////////////

    case 31:
      Serial.println("State #31");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(1);
        b2 = digitalRead(12);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[1] = micros();
        state = 32;
      }
      else {
        sensor[12] = micros();
        state = 0;
        car2_stats();
      }
      break;

    ////////////// State #32 //////////////////////

    case 32:
      Serial.println("State #32");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(2);
        b2 = digitalRead(12);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[2] = micros();
        state = 33;
      }
      else {
        sensor[12] = micros();
        state = 37;
      }
      break;

    ////////////// State #33 //////////////////////

    case 33:
      Serial.println("State #33");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(3);
        b2 = digitalRead(12);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[3] = micros();
        state = 34;
      }
      else {
        sensor[12] = micros();
        state = 38;
      }
      break;

    ////////////// State #34 //////////////////////

    case 34:
      Serial.println("State #34");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(4);
        b2 = digitalRead(12);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[4] = micros();
        state = 35;
      }
      else {
        sensor[12] = micros();
        state = 39;
      }
      break;

    ////////////// State #35 //////////////////////

    case 35 :
      Serial.println("State #35");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(5);
        b2 = digitalRead(12);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[5] = micros();
        state = 36;
      }
      else {
        sensor[12] = micros();
        state = 40;
      }
      break;

    ////////////// State #36 //////////////////////

    case 36:
      Serial.println("State #36");
      while (b1 == LOW && b2 == LOW) {
        b1 = digitalRead(6);
        b2 = digitalRead(12);
        } //Wait for one of our desired sensors to be triggered
      if (b1 == HIGH) {
        sensor[6] = micros();
        state = 46;
      }
      else {
        sensor[12] = micros();
        state = 41;
      }
      break;

    ////////////// State #37 //////////////////////

    case 37:
      Serial.println("State #37");
      while (digitalRead(2) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[2] = micros();
      state = 38;

      break;

    ////////////// State #38 //////////////////////

    case 38:
      Serial.println("State #38");
      while (digitalRead(3) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[3] = micros();
      state = 39;

      break;

    ////////////// State #39 //////////////////////

    case 39:
      Serial.println("State #39");
      while (digitalRead(4) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[4] = micros();
      state = 40;

      break;

    ////////////// State #40 //////////////////////

    case 40:
      Serial.println("State #40");
      while (digitalRead(5) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[5] = micros();
      state = 41;

      break;

    ////////////// State #41 //////////////////////

    case 41:
      Serial.println("State #41");
      while (digitalRead(6) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[6] = micros();
      state = 0;
      car1_stats();
      car2_stats();
      winner();

      break;

    ////////////// State #42 //////////////////////

    case 42:
      Serial.println("State #42");
      while (digitalRead(8) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[8] = micros();
      state = 43;

      break;

    ////////////// State #43 //////////////////////

    case 43:
      Serial.println("State #43");
      while (digitalRead(9) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[9] = micros();
      state = 44;

      break;

    ////////////// State #44 //////////////////////

    case 44:
      Serial.println("State #44");
      while (digitalRead(10) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[10] = micros();
      state = 45;

      break;


    ////////////// State #45 //////////////////////

    case 45:
      Serial.println("State #45");
      while (digitalRead(11) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[11] = micros();
      state = 46;

      break;

    ////////////// State #46 //////////////////////

    case 46:
      Serial.println("State #46");
      while (digitalRead(12) == LOW) {} //Wait for one of our desired sensors to be triggered

      sensor[12] = micros();
      state = 0;

      car1_stats();
      car2_stats();
      winner();

      break;

  }

}

void car1_stats() {

  Serial.println("=== RACER #1 STATS ===");
  Serial.println("");

  //Checkpoint 1 Data
  double cp1_time = (sensor[2] - sensor[0]) / 1000000.0;
  double cp1_speed = 1000000.0 / (sensor[2] - sensor[1]);

  //Checkpoint 2 Data
  double cp2_time = (sensor[4] - sensor[0]) / 1000000.0;
  double cp2_speed = 1000000.0 / (sensor[4] - sensor[3]);

  //Checkpoint 3 Data
  double cp3_time = (sensor[6] - sensor[0]) / 1000000.0;
  double cp3_speed = 1000000.0 / (sensor[6] - sensor[5]);

  //checkpoint 1 time
  Serial.print("Checkpoint #1 Time: ");
  Serial.print(cp1_time, 6);
  Serial.println(" seconds");

  //checkpoint 1 speed
  Serial.print("Checkpoint #1 Speed: ");
  Serial.print(cp1_speed, 2);
  Serial.println(" ft/second");
  Serial.println("");

  //checkpoint 2 time
  Serial.print("Checkpoint #1 Time: ");
  Serial.print(cp2_time, 6);
  Serial.println(" seconds");

  //checkpoint 2 speed
  Serial.print("Checkpoint #1 Speed: ");
  Serial.print(cp2_speed, 2);
  Serial.println(" ft/second");
  Serial.println("");

  //checkpoint 3 time
  Serial.print("Finish Time: ");
  Serial.print(cp3_time, 6);
  Serial.println(" seconds");

  //checkpoint 3 speed
  Serial.print("Final Speed: ");
  Serial.print(cp3_speed, 2);
  Serial.println(" ft/second");
  Serial.println("");

  Serial.println("");

  // Send data to Firebase with specific path
  if (Firebase.setFloat(firebaseData, path + "/1-car1Stats/cp1s", cp1_speed)) {
    Serial.println(firebaseData.dataPath() + " = " + cp1_speed);
  }
  if (Firebase.setFloat(firebaseData, path + "/1-car1Stats/cp1t", cp1_time)) {
    Serial.println(firebaseData.dataPath() + " = " + cp1_time);
  }
  if (Firebase.setFloat(firebaseData, path + "/1-car1Stats/cp2s", cp2_speed)) {
    Serial.println(firebaseData.dataPath() + " = " + cp2_speed);
  }
  if (Firebase.setFloat(firebaseData, path + "/1-car1Stats/cp2t", cp2_time)) {
    Serial.println(firebaseData.dataPath() + " = " + cp2_time);
  }
  if (Firebase.setFloat(firebaseData, path + "/1-car1Stats/cp3s", cp3_speed)) {
    Serial.println(firebaseData.dataPath() + " = " + cp3_speed);
  }
  if (Firebase.setFloat(firebaseData, path + "/1-car1Stats/cp3t", cp3_time)) {
    Serial.println(firebaseData.dataPath() + " = " + cp3_time);
  }

  Serial.println();

}


void car2_stats() {

  Serial.println("=== RACER #2 STATS ===");
  Serial.println("");

  //Checkpoint 1 Data
  double cp1_time = (sensor[8] - sensor[0]) / 1000000.0;
  double cp1_speed = 1000000.0 / (sensor[8] - sensor[7]);

  //Checkpoint 2 Data
  double cp2_time = (sensor[10] - sensor[0]) / 1000000.0;
  double cp2_speed = 1000000.0 / (sensor[10] - sensor[9]);

  //Checkpoint 3 Data
  double cp3_time = (sensor[12] - sensor[0]) / 1000000.0;
  double cp3_speed = 1000000.0 / (sensor[12] - sensor[11]);

  //checkpoint 1 time
  Serial.print("Checkpoint #1 Time: ");
  Serial.print(cp1_time, 6);
  Serial.println(" seconds");

  //checkpoint 1 speed
  Serial.print("Checkpoint #1 Speed: ");
  Serial.print(cp1_speed, 2);
  Serial.println(" ft/second");
  Serial.println("");

  //checkpoint 2 time
  Serial.print("Checkpoint #1 Time: ");
  Serial.print(cp2_time, 6);
  Serial.println(" seconds");

  //checkpoint 2 speed
  Serial.print("Checkpoint #1 Speed: ");
  Serial.print(cp2_speed, 2);
  Serial.println(" ft/second");
  Serial.println("");

  //checkpoint 3 time
  Serial.print("Finish Time: ");
  Serial.print(cp3_time, 6);
  Serial.println(" seconds");

  //checkpoint 3 speed
  Serial.print("Final Speed: ");
  Serial.print(cp3_speed, 2);
  Serial.println(" ft/second");
  Serial.println("");

  Serial.println("");

  // Send data to Firebase with specific path
  if (Firebase.setFloat(firebaseData, path + "/2-car2Stats/cp1s", cp1_speed)) {
    Serial.println(firebaseData.dataPath() + " = " + cp1_speed);
  }
  if (Firebase.setFloat(firebaseData, path + "/2-car2Stats/cp1t", cp1_time)) {
    Serial.println(firebaseData.dataPath() + " = " + cp1_time);
  }
  if (Firebase.setFloat(firebaseData, path + "/2-car2Stats/cp2s", cp2_speed)) {
    Serial.println(firebaseData.dataPath() + " = " + cp2_speed);
  }
  if (Firebase.setFloat(firebaseData, path + "/2-car2Stats/cp2t", cp2_time)) {
    Serial.println(firebaseData.dataPath() + " = " + cp2_time);
  }
  if (Firebase.setFloat(firebaseData, path + "/2-car2Stats/cp3s", cp3_speed)) {
    Serial.println(firebaseData.dataPath() + " = " + cp3_speed);
  }
  if (Firebase.setFloat(firebaseData, path + "/2-car2Stats/cp3t", cp3_time)) {
    Serial.println(firebaseData.dataPath() + " = " + cp3_time);
  }

  Serial.println();

}

void winner() {


  //Finish Times
  double t1 = (sensor[6] - sensor[0]) / 1000000.0;
  double t2 = (sensor[12] - sensor[0]) / 1000000.0;

  if (t1 < t2) {
    Serial.print("Racer #1 won by a time of ");
    Serial.println((t2 - t1), 6);

  }
  else {
    Serial.print("Racer #2 won by a time of ");
    Serial.print((t1 - t2), 6);
  }

  Serial.println();
  

}
