const byte BluekeypadCaptain = A0;    // buttons for directions and surface for the captain (board of 5 buttons)
const byte BluePospadCaptain = A1;  // pad of 16 buttons in series with resistors that allow for coordinates entries (1 push for x-axis then 1 push for y-axis)
const byte BluekeypadFM = A2;         // buttons for First Mate modules (6 buttons in serie with 1K resistors) covering all modules
const long BluekeypadEngiWest = A3;
const byte BluekeypadEngiNorth = A4;  // 4 sets of 6 buttons wired in series with resistors. One for each direction.
const byte BluekeypadEngiSouth = A5;
const byte BluekeypadEngiEast = A6;
//Yellow
const byte YellowkeypadCaptain = A7;    // buttons for directions and surface for the captain (board of 5 buttons)
const byte YellowPospadCaptain = A8;  // pad of 16 buttons in series with resistors that allow for coordinates entries (1 push for x-axis then 1 push for y-axis)
const byte YellowkeypadFM = A9;         // buttons for First Mate modules (6 buttons in serie with 1K resistors) covering all modules
const long YellowkeypadEngiWest = A10;
const byte YellowkeypadEngiNorth = A11;  // 4 sets of 6 buttons wired in series with resistors. One for each direction.
const byte YellowkeypadEngiSouth = A12;
const byte YellowkeypadEngiEast = A13;

const byte BluePinLedWeaponWestAutopipe = 2;    //WEST   //The following constants are the pins for the Engineer modules.
const byte BluePinLedSpecialWestAutopipe = 3; // they act as indicators of the state of the module : lit if the module is damaged (or 'crossed')
const byte BluePinLedDetectionWestAutopipe = 4;   // and shut down if the module is not damaged.
const byte BluePinLedRadiationWestpersistant1 = 5;
const byte BluePinLedRadiationWestpersistant2 = 6;
const byte BluePinLedDetectionWestpersistant = 7;
const byte BluePinLedWeaponNorthAutopipe = 8; // NORTH
const byte BluePinLedSpecialNorthAutopipe1 = 9;  //If all module on a direction (North,West...) have been crossed (=1)
const byte BluePinLedSpecialNorthAutopipe2 = 10;  // including the "persistant" ones, the sub takes 1 damage and all mechanical
const byte BluePinLedDetectionNorthpersistant = 11; // modules are disengaged (=0).
const byte BluePinLedWeaponNorthpersistant = 12;
const byte BluePinLedRadiationNorthpersistant = 13;
const byte BluePinLedWeaponSudAutopipe = 14;       //SOUTH
const byte BluePinLedDetectionSudAutopipe = 15;
const byte BluePinLedSpecialSudAutopipe = 16;
const byte BluePinLedWeaponSudpersistant = 17;
const byte BluePinLedRadiationSudpersistant = 18;
const byte BluePinLedSpecialSudpersistant = 19;
const byte BluePinLedWeaponEstAutopipe = 22;         //EAST
const byte BluePinLedDetectionEstAutopipe = 23;
const byte BluePinLedSpecialEstAutopipe = 24;
const byte BluePinLedDetectionEstpersistant = 25;
const byte BluePinLedRadiationEstpersistant1 = 26;
const byte BluePinLedRadiationEstpersistant2 = 27;
//Yellow
const byte YellowPinLedWeaponWestAutopipe = 29;    //WEST   //The following constants are the pins for the Engineer modules.
const byte YellowPinLedSpecialWestAutopipe = 30; // they act as indicators of the state of the module : lit if the module is damaged (or 'crossed')
const byte YellowPinLedDetectionWestAutopipe = 31;   // and shut down if the module is not damaged.
const byte YellowPinLedRadiationWestpersistant1 = 32;
const byte YellowPinLedRadiationWestpersistant2 = 33;
const byte YellowPinLedDetectionWestpersistant = 34;
const byte YellowPinLedWeaponNorthAutopipe = 35; // NORTH
const byte YellowPinLedSpecialNorthAutopipe1 = 36;  //If all module on a direction (North,West...) have been crossed (=1)
const byte YellowPinLedSpecialNorthAutopipe2 = 37;  // including the "persistant" ones, the sub takes 1 damage and all mechanical
const byte YellowPinLedDetectionNorthpersistant = 38; // modules are disengaged (=0).
const byte YellowPinLedWeaponNorthpersistant = 39;
const byte YellowPinLedRadiationNorthpersistant = 40;
const byte YellowPinLedWeaponSudAutopipe = 41;       //SOUTH
const byte YellowPinLedDetectionSudAutopipe = 42;
const byte YellowPinLedSpecialSudAutopipe = 43;
const byte YellowPinLedWeaponSudpersistant = 44;
const byte YellowPinLedRadiationSudpersistant = 45;
const byte YellowPinLedSpecialSudpersistant = 46;
const byte YellowPinLedWeaponEstAutopipe = 47;         //EAST
const byte YellowPinLedDetectionEstAutopipe = 48;
const byte YellowPinLedSpecialEstAutopipe = 49;
const byte YellowPinLedDetectionEstpersistant = 50;
const byte YellowPinLedRadiationEstpersistant1 = 51;
const byte YellowPinLedRadiationEstpersistant2 = 52;
typedef struct {
  byte green;
  byte yellow;
  byte red;
} TriColor;

#include <Wire.h>     //Necessary code for the extender
#include <Adafruit_MCP23017.h>  //tricolor lights will be attached to it

#define MCP_LED1 0
#define MCP_LED2 1
#define MCP_LED3 2
#define MCP_LED4 3
#define MCP_LED5 4
#define MCP_LED6 5
Adafruit_MCP23017 mcp;

const TriColor BlueCaptainTriColor = {MCP_LED1, MCP_LED2, MCP_LED3};
const TriColor YellowCaptainTriColor = {MCP_LED4, MCP_LED5, MCP_LED6};

byte BlueEngineerDamage = 0;      //Number of damage to be allocated by the engineer. The sub will return to state 0 if
// both the FM and the engineer allocate their charge/damage.
byte BlueWeaponWestAutopipe = 0;   //WEST    //Autopipe mechanical damage. if a module has been "crossed" by the
byte BlueDetectionWestAutopipe = 0; // engineer, its state switch from 0 (not engaged) to 1 (engaged).
byte BlueSpecialWestAutopipe = 0;   //If every module on the same autopipe have been crossed (=1) then they all are disengaged (=0).
byte BlueDetectionWestpersistant = 0;   //"persistant" means mechanical damage that can only be repaired by Surface
byte BlueRadiationWestpersistant1 = 0;  // or by taking a damage via mechanical damage.
byte BlueRadiationWestpersistant2 = 0;
byte BlueWeaponNorthAutopipe = 0; // NORTH
byte BlueSpecialNorthAutopipe1 = 0;  //If all module on a direction (North,West...) have been crossed (=1)
byte BlueSpecialNorthAutopipe2 = 0;  // including the "persistant" ones, the sub takes 1 damage and all mechanical
byte BlueDetectionNorthpersistant = 0; // modules are disengaged (=0).
byte BlueWeaponNorthpersistant = 0;
byte BlueRadiationNorthpersistant = 0;
byte BlueWeaponSudAutopipe = 0;       //SOUTH
byte BlueDetectionSudAutopipe = 0;
byte BlueSpecialSudAutopipe = 0;
byte BlueWeaponSudpersistant = 0;
byte BlueRadiationSudpersistant = 0;
byte BlueSpecialSudpersistant = 0;
byte BlueWeaponEstAutopipe = 0;         //EAST
byte BlueDetectionEstAutopipe = 0;
byte BlueSpecialEstAutopipe = 0;
byte BlueDetectionEstpersistant = 0;
byte BlueRadiationEstpersistant1 = 0;
byte BlueRadiationEstpersistant2 = 0;
//Yellow
byte YellowEngineerDamage = 0;      //Number of damage to be allocated by the engineer. The sub will return to state 0 if
// both the FM and the engineer allocate their charge/damage.
byte YellowWeaponWestAutopipe = 0;   //WEST    //Autopipe mechanical damage. if a module has been "crossed" by the
byte YellowDetectionWestAutopipe = 0; // engineer, its state switch from 0 (not engaged) to 1 (engaged).
byte YellowSpecialWestAutopipe = 0;   //If every module on the same autopipe have been crossed (=1) then they all are disengaged (=0).
byte YellowDetectionWestpersistant = 0;   //"persistant" means mechanical damage that can only be repaired by Surface
byte YellowRadiationWestpersistant1 = 0;  // or by taking a damage via mechanical damage.
byte YellowRadiationWestpersistant2 = 0;
byte YellowWeaponNorthAutopipe = 0; // NORTH
byte YellowSpecialNorthAutopipe1 = 0;  //If all module on a direction (North,West...) have been crossed (=1)
byte YellowSpecialNorthAutopipe2 = 0;  // including the "persistant" ones, the sub takes 1 damage and all mechanical
byte YellowDetectionNorthpersistant = 0; // modules are disengaged (=0).
byte YellowWeaponNorthpersistant = 0;
byte YellowRadiationNorthpersistant = 0;
byte YellowWeaponSudAutopipe = 0;       //SOUTH
byte YellowDetectionSudAutopipe = 0;
byte YellowSpecialSudAutopipe = 0;
byte YellowWeaponSudpersistant = 0;
byte YellowRadiationSudpersistant = 0;
byte YellowSpecialSudpersistant = 0;
byte YellowWeaponEstAutopipe = 0;         //EAST
byte YellowDetectionEstAutopipe = 0;
byte YellowSpecialEstAutopipe = 0;
byte YellowDetectionEstpersistant = 0;
byte YellowRadiationEstpersistant1 = 0;
byte YellowRadiationEstpersistant2 = 0;

typedef struct {
  char col;
  int line;
} Position;
Position Islands[4][32] = {{67, 2, 71, 2, 77, 2, 78, 2, 67, 3, 73, 3, 77, 3, 73, 4, 66, 7, 68, 7, 71, 7, 73, 7, 66, 8, 68, 8, 71, 8, 68, 9, 72, 9, 76, 9, 77, 9, 78, 9, 68, 11, 67, 12, 72, 12, 76, 12, 65, 13, 77, 13, 67, 14, 71, 14, 73, 14, 78, 14, 68, 15, 0, 0}\
  , {67, 2, 77, 2, 78, 2, 67, 3, 73, 3, 73, 4, 68, 8, 68, 9, 76, 9, 77, 9, 78, 9, 68, 11, 67, 12, 72, 12, 76, 12, 73, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}\
  , {70, 3, 77, 3, 70, 4, 76, 4, 68, 8, 73, 8, 73, 9, 72, 10, 73, 10, 68, 13, 69, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int Map = -1;
byte MapConfirmation = 0;

Position BluePosition = {65, 0};   //Virtually A0, a non possible position
byte BlueSubState = 0;     //0 if the Sub is not surfacing and not in an unresolved move, 1 if it is in an unresolved move,
// and 2 if it is surfacing.
byte BlueMoveCount = 0;
Position BluePastPosition[100] = {}; //All the visited coordinates, for checking if the submarine can move or not.
Position BlueTorpedo = {0, 0};
byte BlueMineCount = 0;
Position BlueMine = {0, 0};
Position BlueMineReady[100] = {};
byte BlueNumberMineReady = 0;
byte BlueSubDamage = 0;
byte BlueSubMaxDamage = 4;
//Yellow
Position YellowPosition = {65, 0};   //Virtually A0, a non possible position
byte YellowSubState = 0;     //0 if the Sub is not surfacing and not in an unresolved move, 1 if it is in an unresolved move,
// and 2 if it is surfacing.
byte YellowMoveCount = 0;
Position YellowPastPosition[100] = {}; //All the visited coordinates, for checking if the submarine can move or not.
byte YellowNumberPastPositions = 0;
Position YellowTorpedo = {0, 0};
byte YellowMineCount = 0;
Position YellowMine = {0, 0};
Position YellowMineReady[100] = {};
byte YellowNumberMineReady = 0;
byte YellowSubDamage = 0;
byte YellowSubMaxDamage = 4;

byte BlueFMCharge = 0;      //Number of charge to be allocated by the First Mate(FM). The sub will return to state 0 if
// both the FM and the engineer allocate their charge/damage.
byte BlueChargeMine = 0;      //Every module start with a charge of 0. Once it reach the threesold specified in the next variable, it is charged and ready.
byte BlueChargeTorpedo = 0;
byte BlueChargeDrone = 0;
byte BlueChargeSonar = 0;
byte BlueChargeSilence = 0;
byte BlueSilenceDirection = 0;
byte BlueChargeScenario = 0;
byte BlueModuleEngaged = 0;
//Yellow
byte YellowFMCharge = 0;      //Number of charge to be allocated by the First Mate(FM). The sub will return to state 0 if
// both the FM and the engineer allocate their charge/damage.
byte YellowChargeMine = 0;      //Every module start with a charge of 0. Once it reach the threesold specified in the next variable, it is charged and ready.
byte YellowChargeTorpedo = 0;
byte YellowChargeDrone = 0;
byte YellowChargeSonar = 0;
byte YellowChargeSilence = 0;
byte YellowSilenceDirection = 0;
byte YellowChargeScenario = 0;
byte YellowModuleEngaged = 0;

byte MineCharged = 3;     //Threesold for the ChargeMine variable.
byte TorpedoCharged = 3;
byte DroneCharged = 4;
byte SonarCharged = 3;
byte SilenceCharged = 6;
byte ScenarioCharged = 5;

int BlueLine = 0;
char BlueColumn = 0;
byte BlueConfirmationLine = 0;
byte BlueConfirmationColumn = 0;
byte BluePositionReadingInitializer = 0;
byte BlueCapkey = 0;
byte BlueCapPad = 0;
byte BlueFMkey = 0;
byte BlueEngikey = 0;
byte BlueLastDirection = 0;
//Yellow
int YellowLine = 0;
char YellowColumn = 0;
byte YellowConfirmationLine = 0;
byte YellowConfirmationColumn = 0;
byte YellowPositionReadingInitializer = 0;
byte YellowCapkey = 0;
byte YellowCapPad = 0;
byte YellowFMkey = 0;
byte YellowEngikey = 0;
byte YellowLastDirection = 0;
const byte NONE = 0;
const byte LEFT = 1;
const byte UP = 2;
const byte RIGHT = 3;
const byte DOWN = 4;
const byte SURFACE = 5;
const byte MINE = 6;
const byte TORPEDO = 7;
const byte DRONE = 8;
const byte SONAR = 9;
const byte SILENCE = 10;
const byte SCENARIO = 11;
const byte DETONATEMINE = 12;

long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
long previousButtonMillis = 0; // time when last button pressed checked
long BluepreviousButtonMillisCap = 0;
long BluepreviousButtonMillisPad = 0;
long BluepreviousButtonMillisFM = 0;
long BluepreviousButtonMillisEngi = 0;
long BlueSurfaceBegin = 0;
//Yellow
long YellowpreviousButtonMillisCap = 0;
long YellowpreviousButtonMillisPad = 0;
long YellowpreviousButtonMillisFM = 0;
long YellowpreviousButtonMillisEngi = 0;
long YellowSurfaceBegin = 0;

const long buttonInterval = 10;      //Defines the number of milliseconds between each read button check
const long DebounceTime = 1000;      //Number of milliseconds before re-reading a button's input
const long SurfaceTime = 10000;
long BlueCoordDebounce = 0;
long YellowCoordDebounce = 0;

//Standard button's values for the Engi board. Those are then used to self-adapt in case of voltage variation.
const int Borne0 = 24;
int Offset = 0;
const int Borne1 = 68;
const int Borne2 = 80;
const int Borne3 = 90;
const int Borne4 = 123;
const int Borne5 = 190;
const int Borne6 = 503;
const int BorneMin = -3;
const int BorneMax = +4;
const int Borne3Min = -5;
const int Borne3Max = +13;
const int BornePermaMin = -15;
const int BornePermaMax = +20;

//Standard button's values for the Captain board. Those are then used to self-adapt in case of voltage variation.
const int Borne0PosPad = 3;
int BlueOffsetPosPad = 0;
int YellowOffsetPosPad = 0;

//Standard button's values for the First Mate board. Those are then used to self-adapt in case of voltage variation.
const int Borne0FM = 3;
int BlueOffsetFM = 0;
int YellowOffsetFM = 0;


//LIGHT functions, for FM and then for Engi.
//includes the settin up of NeoPixel lights
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

const byte BlueNeoPixelsPin =  28;
Adafruit_NeoPixel BlueFMPixels(48, BlueNeoPixelsPin, NEO_GRB + NEO_KHZ800);
const byte YellowNeoPixelsPin =  53;
Adafruit_NeoPixel YellowFMPixels(48, YellowNeoPixelsPin, NEO_GRB + NEO_KHZ800);


#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C Bluelcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C Yellowlcd(0x26, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
long Bluelcd0Reset = 0;
long Bluelcd1Reset = 0;
long Bluelcd2Reset = 0;
long Bluelcd3Reset = 0;
long Yellowlcd0Reset = 0;
long Yellowlcd1Reset = 0;
long Yellowlcd2Reset = 0;
long Yellowlcd3Reset = 0;
const long lcdTimer = 4000;
byte BluelcdResetPending0 = 0;
byte BluelcdResetPending1 = 0;
byte BluelcdResetPending2 = 0;
byte BluelcdResetPending3 = 0;
byte YellowlcdResetPending0 = 0;
byte YellowlcdResetPending1 = 0;
byte YellowlcdResetPending2 = 0;
byte YellowlcdResetPending3 = 0;

void lcdResetBlue(int line) {
  switch (line) {
    case 0:
      Bluelcd.setCursor(0, 0);
      Bluelcd.print("                    ");
      BluelcdResetPending0 = 1;
      Bluelcd0Reset = millis() + lcdTimer;
      break;
    case 1 :
      Bluelcd.setCursor(0, 1);
      Bluelcd.print("                    ");
      BluelcdResetPending1 = 1;
      Bluelcd1Reset = millis() + lcdTimer;
      break;
    case 2 :
      Bluelcd.setCursor(0, 2);
      Bluelcd.print("                    ");
      BluelcdResetPending2 = 1;
      Bluelcd2Reset = millis() + lcdTimer;
      break;
    case 3 :
      Bluelcd.setCursor(0, 3);
      Bluelcd.print("                    ");
      BluelcdResetPending3 = 1;
      Bluelcd3Reset = millis() + lcdTimer;
      break;
  }
}
void lcdResetYellow(int line) {
  switch (line) {
    case 0:
      Yellowlcd.setCursor(0, 0);
      Yellowlcd.print("                    ");
      YellowlcdResetPending0 = 1;
      Yellowlcd0Reset = millis() + lcdTimer;
      break;
    case 1 :
      Yellowlcd.setCursor(0, 1);
      Yellowlcd.print("                    ");
      YellowlcdResetPending1 = 1;
      Yellowlcd1Reset = millis() + lcdTimer;
      break;
    case 2 :
      Yellowlcd.setCursor(0, 2);
      Yellowlcd.print("                    ");
      YellowlcdResetPending2 = 1;
      Yellowlcd2Reset = millis() + lcdTimer;
      break;
    case 3 :
      Yellowlcd.setCursor(0, 3);
      Yellowlcd.print("                    ");
      YellowlcdResetPending3 = 1;
      Yellowlcd3Reset = millis() + lcdTimer;
      break;
  }
}

void Checklcd() {
  if ((currentMillis - Bluelcd0Reset >= lcdTimer) && (BluelcdResetPending0 == 1)) {
    Bluelcd.setCursor(0, 0);
    Bluelcd.print("                    ");
    BluelcdResetPending0 = 0;
  }
  if ((currentMillis - Bluelcd1Reset >= lcdTimer) && (BluelcdResetPending1 == 1)) {
    Bluelcd.setCursor(0, 1);
    Bluelcd.print("                    ");
    BluelcdResetPending1 = 0;
  }
  if ((currentMillis - Bluelcd2Reset >= lcdTimer) && (BluelcdResetPending2 == 1)) {
    Bluelcd.setCursor(0, 2);
    Bluelcd.print("                    ");
    BluelcdResetPending2 = 0;
  }
  if ((currentMillis - Bluelcd3Reset >= lcdTimer) && (BluelcdResetPending3 == 1)) {
    Bluelcd.setCursor(0, 3);
    Bluelcd.print("                    ");
    BluelcdResetPending3 = 0;
  }
  if ((currentMillis - Yellowlcd0Reset >= lcdTimer) && (YellowlcdResetPending0 == 1)) {
    Yellowlcd.setCursor(0, 0);
    Yellowlcd.print("                    ");
    YellowlcdResetPending0 = 0;
  }
  if ((currentMillis - Yellowlcd1Reset >= lcdTimer) && (YellowlcdResetPending1 == 1)) {
    Yellowlcd.setCursor(0, 1);
    Yellowlcd.print("                    ");
    YellowlcdResetPending1 = 0;
  }
  if ((currentMillis - Yellowlcd2Reset >= lcdTimer) && (YellowlcdResetPending2 == 1)) {
    Yellowlcd.setCursor(0, 2);
    Yellowlcd.print("                    ");
    YellowlcdResetPending2 = 0;
  }
  if ((currentMillis - Yellowlcd3Reset >= lcdTimer) && (YellowlcdResetPending3 == 1)) {
    Yellowlcd.setCursor(0, 3);
    Yellowlcd.print("                    ");
    YellowlcdResetPending3 = 0;
  }
}

//Functions for the FM board LEDs (WS2812)
// All leds are in series and connected to a single pin. The arguments 'first' and 'last' define the position of the first and last pin
// of the serie to be lighten up (or turned down).
void colorChargeBlue(int first, int last) { //update the leds of the FM modules when they are charged
  for (int i = first; i <= last; i++) {
    BlueFMPixels.setPixelColor(i, BlueFMPixels.Color(80,   10,   0));  //  Set every pixel in red/orange up to the charge of the module (pixel are 0-indexing)
    BlueFMPixels.show();                          //  Update strip to match
    delay(2);                           //  Pause for a moment
  }
}
void colorFullChargeBlue(int first, int last) { //update the leds of the FM modules when they are fully charged
  for (int i = first; i <= last; i++) { // For each pixel in strip...
    BlueFMPixels.setPixelColor(i, BlueFMPixels.Color(20,   80,  0));         //  Set every pixel in green up to the maximum charge of the module
    BlueFMPixels.show();                          //  Update strip to match
    delay(2);                           //  Pause for a moment
  }
}
void colorEmptyChargeBlue(int first, int last) {  //update the leds of the FM modules when they are discharged
  for (int i = first; i <= last; i++) { // For each pixel in strip...
    BlueFMPixels.setPixelColor(i, BlueFMPixels.Color(0,   0,   0));         // Turn off the pixels
    BlueFMPixels.show();                          //  Update strip to match
    delay(2);                           //  Pause for a moment
  }
}
//Yellow
void colorChargeYellow(int first, int last) { //update the leds of the FM modules when they are charged
  for (int i = first; i <= last; i++) {
    YellowFMPixels.setPixelColor(i, YellowFMPixels.Color(80,   10,   0));  //  Set every pixel in red/orange up to the charge of the module (pixel are 0-indexing)
    YellowFMPixels.show();                          //  Update strip to match
    delay(2);                           //  Pause for a moment
  }
}
void colorFullChargeYellow(int first, int last) { //update the leds of the FM modules when they are fully charged
  for (int i = first; i <= last; i++) { // For each pixel in strip...
    YellowFMPixels.setPixelColor(i, YellowFMPixels.Color(20,   80,  0));         //  Set every pixel in green up to the maximum charge of the module
    YellowFMPixels.show();                          //  Update strip to match
    delay(2);                           //  Pause for a moment
  }
}
void colorEmptyChargeYellow(int first, int last) {  //update the leds of the FM modules when they are discharged
  for (int i = first; i <= last; i++) { // For each pixel in strip...
    YellowFMPixels.setPixelColor(i, YellowFMPixels.Color(0,   0,   0));         // Turn off the pixels
    YellowFMPixels.show();                          //  Update strip to match
    delay(2);                           //  Pause for a moment
  }
}

void colorOff() { //turn off all the FM leds
  for (int i = 0; i <= 47; i++) {
    BlueFMPixels.setPixelColor(i, BlueFMPixels.Color(0,   0,   0));  //  Set every pixel in red/orange up to the charge of the module (pixel are 0-indexing)
    BlueFMPixels.show();                          //  Update strip to match
    YellowFMPixels.setPixelColor(i, YellowFMPixels.Color(0,   0,   0));  //  Set every pixel in red/orange up to the charge of the module (pixel are 0-indexing)
    YellowFMPixels.show();                          //  Update strip to match
    delay(2);
  }
}

// Functions for the engi board lights
void BlueEngiLedLow() { //turn all the leds of the engi panel off
  for (int i = 2; i <= 19; i++) {
    digitalWrite(i, LOW);
    delay(10);
  }
  for (int i = 22; i <= 27; i++) {
    digitalWrite(i, LOW);
    delay(10);
  }
}
void BlueEngiLedHigh() {  //turn all the leds of the engi panel on
  for (int i = 2; i <= 19; i++) {
    digitalWrite(i, HIGH);
    delay(10);
  }
  for (int i = 22; i <= 27; i++) {
    digitalWrite(i, HIGH);
    delay(10);
  }
}
//Yellow
void YellowEngiLedLow() { //turn all the leds of the engi panel off
  for (int i = 29; i <= 52; i++) {
    digitalWrite(i, LOW);
    delay(10);
  }
}
void YellowEngiLedHigh() {  //turn all the leds of the engi panel on
  for (int i = 29; i <= 52; i++) {
    digitalWrite(i, HIGH);
    delay(10);
  }
}

// Functions for the Captain board Lights
void TricolorBlue(int color) { //0 for green, 1 for yellow, 2 for red
  mcp.digitalWrite(BlueCaptainTriColor.green, LOW);
  mcp.digitalWrite(BlueCaptainTriColor.yellow, LOW);
  mcp.digitalWrite(BlueCaptainTriColor.red, LOW);
  switch (color) {
    case 0:
      mcp.digitalWrite(BlueCaptainTriColor.green, HIGH);
      break;
    case 1:
      mcp.digitalWrite(BlueCaptainTriColor.yellow, HIGH);
      break;
    case 2:
      mcp.digitalWrite(BlueCaptainTriColor.red, HIGH);
      break;
  }
}
void TricolorYellow(int color) { //0 for green, 1 for yellow, 2 for red
  mcp.digitalWrite(YellowCaptainTriColor.green, LOW);
  mcp.digitalWrite(YellowCaptainTriColor.yellow, LOW);
  mcp.digitalWrite(YellowCaptainTriColor.red, LOW);
  switch (color) {
    case 0:
      mcp.digitalWrite(YellowCaptainTriColor.green, HIGH);
      break;
    case 1:
      mcp.digitalWrite(YellowCaptainTriColor.yellow, HIGH);
      break;
    case 2:
      mcp.digitalWrite(YellowCaptainTriColor.red, HIGH);
      break;
  }
}

byte getKeyPositionMap()   //Reads the input from the 4X4 pad of the captain board
{
  int val = 0;
  
  while ((Map == -1) || (MapConfirmation == 1)) {
    if (MapConfirmation == 1) {
      ConfirmMapChoice();
    } else if ((MapConfirmation == 0) && (Map == -1)) {
      if (millis() - previousButtonMillis >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
        val = getKeyPadCaptainBlue() ;   // Read first input on the position pad (sets the line)
          if ( val == 1)  {
          Map = 0;
          ConfirmMapChoice();
          }
          else if (val == 2)   {
          Map = 1;
          ConfirmMapChoice();
          }
          else if (val == 3)   {
          Map = 2;
          ConfirmMapChoice();
          }
          previousButtonMillis += buttonInterval;
      }
    }
  }
}
void ConfirmMapChoice() {
  int valmov = 0;
  if (MapConfirmation == 0) {
    MapConfirmation = 1;

    Yellowlcd.setCursor(0, 1);
    Yellowlcd.print("Map choisie: ");
    Bluelcd.setCursor(0, 1);
    Bluelcd.print("Map choisie: ");
    Serial.print("Map chosen is : ");
    switch (Map) {
      case 0:
        Serial.println("Alpha");
        Yellowlcd.setCursor(14, 1);
        Yellowlcd.print("Alpha");
        Bluelcd.setCursor(14, 1);
        Bluelcd.print("Alpha");
        break;
      case 1:
        Serial.println("Bravo");
        Yellowlcd.setCursor(14, 1);
        Yellowlcd.print("Bravo");
        Bluelcd.setCursor(14, 1);
        Bluelcd.print("Bravo");
        break;
      case 2:
        Serial.println("Charlie");
        Yellowlcd.setCursor(13, 1);
        Yellowlcd.print("Charlie");
        Bluelcd.setCursor(13, 1);
        Bluelcd.print("Charlie");
        break;
    }
    delay(500);
    Serial.println("Confirm : press Surface");
    Serial.println("Cancel : press West");
    Bluelcd.setCursor(0, 2);
    Bluelcd.print("Confirmer : SURFACE");
    Bluelcd.setCursor(0, 3);
    Bluelcd.print("Cancel : WEST");
  } else if (MapConfirmation == 1) {
    if (millis() - previousButtonMillis >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
      valmov = analogRead(BluekeypadCaptain);
      if ( (valmov >= 700) &&  ( valmov <= 800)  )   {  // Surface
        MapConfirmation = 0;
        Serial.println("Confirmed");
        Bluelcd.clear();
        Yellowlcd.clear();
        Bluelcd.print("Map choisie: ");
        Yellowlcd.print("Map choisie: ");
        Serial.print("Let's play on Map");
        switch (Map) {
          case 0:
            Serial.println("Alpha");
            Yellowlcd.setCursor(14, 0);
            Yellowlcd.print("Alpha");
            Bluelcd.setCursor(14, 0);
            Bluelcd.print("Alpha");
            break;
          case 1:
            Serial.println("Bravo");
            Yellowlcd.setCursor(14, 0);
            Yellowlcd.print("Bravo");
            Bluelcd.setCursor(14, 0);
            Bluelcd.print("Bravo");
            break;
          case 2:
            Serial.println("Charlie");
            Yellowlcd.setCursor(13, 0);
            Yellowlcd.print("Charlie");
            Bluelcd.setCursor(13, 0);
            Bluelcd.print("Charlie");
            break;
        }
      } else if ( valmov <= 35)  {    // West
        MapConfirmation = 0;
        Map = -1;
        Serial.println("Canceled");
        Bluelcd.clear();
        Yellowlcd.clear();
        Yellowlcd.print("Annule, nouv choix ?");
        Bluelcd.print("Annule, nouv choix ?");
      }
      previousButtonMillis += buttonInterval;
    }
  }
}
//Functions for reading inputs from 4X4 button board
void LineColumnSetupBlue() {
  BlueLine = 0;
  BlueColumn = 0;
}
byte getKeyStartingPositionBlue()   //Reads the input from the 4X4 pad of the captain board
{
  Serial.println("Input the line :");
  Bluelcd.setCursor(0, 2);
  Bluelcd.print("Ligne :");
  while ((BlueLine == 0) || (BlueColumn == 0) || (BlueConfirmationColumn == 1) || (BluePositionReadingInitializer == 0)) {
    if (BluePositionReadingInitializer == 0) {
      LineColumnSetupBlue();
      BluePositionReadingInitializer = 1;
    } else {
      byte val = 0;      // Placeholder for the analogRead value
      if (BlueConfirmationLine == 1) {
        ConfirmLineBlue();
      } else if (BlueConfirmationColumn == 1) {
        ConfirmColumnBlue();
      } else if ((BlueConfirmationLine == 0) && (BlueConfirmationColumn == 0)) {

        if ((BlueLine == 0) || (BlueColumn == 0))  { //While Line and Column has not been set
          if (millis() - previousButtonMillis >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
            val = getKeyPadCaptainBlue();   // Read first input on the position pad (sets the line)
            
            if (BlueLine == 0) {
              if ((val >= 1) && (val <= 15)) {
                BlueLine = val;
                ConfirmLineBlue();
              }
            } else {
              if ((val >= 1) && (val <= 15)) {
                BlueColumn = val + 64;
                ConfirmColumnBlue();
              }
            }
            previousButtonMillis += buttonInterval;
          }
        }
      }
    }
  }
  Serial.println("Position has been set to");
  Bluelcd.clear();
  Bluelcd.print("Position depart: ");
  Bluelcd.setCursor(17, 0);
  Bluelcd.print(BlueColumn);
  Bluelcd.setCursor(18, 0);
  Bluelcd.print(BlueLine);
  Serial.print(BlueLine);
  Serial.print(" - ");
  Serial.println(BlueColumn);
  BluePositionReadingInitializer = 0;
  BluePosition.line = BlueLine;
  BluePosition.col = BlueColumn;
  CheckInitialPosition();
  delay(2000);
}
void ConfirmLineBlue() {
  int valmov = 0;
  if (BlueConfirmationLine == 0) {
    BlueConfirmationLine = 1;
    Serial.print("Line value is : ");
    Serial.println(BlueLine);
    Bluelcd.setCursor(0, 2);
    Bluelcd.print("Ligne : ");
    Bluelcd.setCursor(8, 2);
    Bluelcd.print(BlueLine);
    delay(500);
    Serial.println("Confirm : press Surface");
    Serial.println("Cancel : press West");
    Bluelcd.setCursor(0, 3);
    Bluelcd.print("Conf:SURF Annul:WEST");
  } else if (BlueConfirmationLine == 1) {
    if (millis() - previousButtonMillis >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
      valmov = analogRead(BluekeypadCaptain);
      if ( (valmov >= 700) &&  ( valmov <= 800)  )   {  // Surface
        BlueConfirmationLine = 0;
        Serial.println("Confirmed");
        Bluelcd.setCursor(0, 3);
        Bluelcd.print("Confirme.           ");
        delay(2000);
        Bluelcd.setCursor(0, 3);
        Bluelcd.print("                    ");
        Serial.println("Input the column :");
        Bluelcd.setCursor(0, 2);
        Bluelcd.print("Colonne : ");
        Bluelcd.setCursor(10, 2);
        Bluelcd.print("          ");
      } else if ( valmov <= 35)  {    // West
        BlueConfirmationLine = 0;
        BlueLine = 0;
        Serial.println("Canceled");
        Serial.println("Input line again:");
        Bluelcd.setCursor(0, 3);
        Bluelcd.print("Annule. Saisir a nv ");
        delay(2000);
        Bluelcd.setCursor(8, 2);
        Bluelcd.print("             ");
        Bluelcd.setCursor(0, 3);
        Bluelcd.print("                    ");
      }
      previousButtonMillis += buttonInterval;
    }
  }
}
void ConfirmColumnBlue() {
  int valmov = 0;
  if (BlueConfirmationColumn == 0) {
    BlueConfirmationColumn = 1;
    Serial.print("Column value is : ");
    Serial.println(BlueColumn);
    Bluelcd.setCursor(0, 2);
    Bluelcd.print("Colonne : ");
    Bluelcd.setCursor(10, 2);
    Bluelcd.print(BlueColumn);
    delay(500);
    Serial.println("Confirm : press Surface");
    Serial.println("Cancel : press West");
    Bluelcd.setCursor(0, 3);
    Bluelcd.print("Conf:SURF Annul:WEST");
  } else if (BlueConfirmationColumn == 1) {
    if (millis() - previousButtonMillis >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
      valmov = analogRead(BluekeypadCaptain);
      if ( (valmov >= 700) &&  ( valmov <= 800)  )   {  // Surface
        BlueConfirmationColumn = 0;
        Serial.println("Confirmed");
        Bluelcd.setCursor(0, 3);
        Bluelcd.print("Confirme.           ");
        delay(2000);
        Bluelcd.setCursor(0, 3);
        Bluelcd.print("                    ");
      } else if ( valmov <= 35)  {    // West
        BlueConfirmationColumn = 0;
        BlueColumn = 0;
        Serial.println("Canceled");
        Serial.println("Input column again:");
        Bluelcd.setCursor(0, 3);
        Bluelcd.print("Annule. Saisir a nv");
        delay(2000);
        Bluelcd.setCursor(8, 2);
        Bluelcd.print("             ");
        Bluelcd.setCursor(0, 3);
        Bluelcd.print("                    ");
      }
      previousButtonMillis += buttonInterval;
    }
  }
}
//Yellow
void LineColumnSetupYellow() {
  YellowLine = 0;
  YellowColumn = 0;
}
byte getKeyStartingPositionYellow()   //Reads the input from the 4X4 pad of the captain board
{
  Serial.println("Input the line :");
  Yellowlcd.setCursor(0, 2);
  Yellowlcd.print("Ligne :");
  while ((YellowLine == 0) || (YellowColumn == 0) || (YellowConfirmationColumn == 1) || (YellowPositionReadingInitializer == 0)) {
    if (YellowPositionReadingInitializer == 0) {
      LineColumnSetupYellow();
      YellowPositionReadingInitializer = 1;
    } else {
      byte val = 0;      // Placeholder for the analogRead value
      if (YellowConfirmationLine == 1) {
        ConfirmLineYellow();
      } else if (YellowConfirmationColumn == 1) {
        ConfirmColumnYellow();
      } else if ((YellowConfirmationLine == 0) && (YellowConfirmationColumn == 0)) {

        if ((YellowLine == 0) || (YellowColumn == 0))  { //While Line and Column has not been set
          if (millis() - previousButtonMillis >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
            val = getKeyPadCaptainYellow();   // Read first input on the position pad (sets the line)
            if (YellowLine == 0) {
              if ((val >= 1) && (val <= 15)) {
                YellowLine = val;
                ConfirmLineYellow();
              }
            } else {
              if ((val >= 1) && (val <= 15)) {
                YellowColumn = val + 64;
                ConfirmColumnYellow();
              }
            }
            previousButtonMillis += buttonInterval;
          }
        }
      }
    }
  }
  Serial.println("Position has been set to");
  Yellowlcd.clear();
  Yellowlcd.print("Position depart: ");
  Yellowlcd.setCursor(17, 0);
  Yellowlcd.print(YellowColumn);
  Yellowlcd.setCursor(18, 0);
  Yellowlcd.print(YellowLine);
  Serial.print(YellowLine);
  Serial.print(" - ");
  Serial.println(YellowColumn);
  YellowPositionReadingInitializer = 0;
  YellowPosition.line = YellowLine;
  YellowPosition.col = YellowColumn;
  CheckInitialPosition();
  delay(2000);
}
void ConfirmLineYellow() {
  int valmov = 0;
  if (YellowConfirmationLine == 0) {
    YellowConfirmationLine = 1;
    Serial.print("Line value is : ");
    Serial.println(YellowLine);
    Yellowlcd.setCursor(0, 2);
    Yellowlcd.print("Ligne : ");
    Yellowlcd.setCursor(8, 2);
    Yellowlcd.print(YellowLine);
    delay(500);
    Serial.println("Confirm : press Surface");
    Serial.println("Cancel : press West");
    Yellowlcd.setCursor(0, 3);
    Yellowlcd.print("Conf:SURF Annul:WEST");
  } else if (YellowConfirmationLine == 1) {
    if (millis() - previousButtonMillis >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
      valmov = analogRead(YellowkeypadCaptain);
      if ( (valmov >= 700) &&  ( valmov <= 800)  )   {  // Surface
        YellowConfirmationLine = 0;
        Serial.println("Confirmed");
        Yellowlcd.setCursor(0, 3);
        Yellowlcd.print("Confirme.           ");
        delay(2000);
        Yellowlcd.setCursor(0, 3);
        Yellowlcd.print("                    ");
        Serial.println("Input the column :");
        Yellowlcd.setCursor(0, 2);
        Yellowlcd.print("Colonne : ");
        Yellowlcd.setCursor(10, 2);
        Yellowlcd.print("          ");
      } else if ( valmov <= 35)  {    // West
        YellowConfirmationLine = 0;
        YellowLine = 0;
        Serial.println("Canceled");
        Serial.println("Input line again:");
        Yellowlcd.setCursor(0, 3);
        Yellowlcd.print("Annule. Saisir a nv ");
        delay(2000);
        Yellowlcd.setCursor(8, 2);
        Yellowlcd.print("             ");
        Yellowlcd.setCursor(0, 3);
        Yellowlcd.print("                    ");
      }
      previousButtonMillis += buttonInterval;
    }
  }
}
void ConfirmColumnYellow() {
  int valmov = 0;
  if (YellowConfirmationColumn == 0) {
    YellowConfirmationColumn = 1;
    Serial.print("Column value is : ");
    Serial.println(YellowColumn);
    Yellowlcd.setCursor(0, 2);
    Yellowlcd.print("Colonne : ");
    Yellowlcd.setCursor(10, 2);
    Yellowlcd.print(YellowColumn);
    delay(500);
    Serial.println("Confirm : press Surface");
    Serial.println("Cancel : press West");
    Yellowlcd.setCursor(0, 3);
    Yellowlcd.print("Conf:SURF Annul:WEST");
  } else if (YellowConfirmationColumn == 1) {
    if (millis() - previousButtonMillis >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
      valmov = analogRead(YellowkeypadCaptain);
      if ( (valmov >= 700) &&  ( valmov <= 800)  )   {  // Surface
        YellowConfirmationColumn = 0;
        Serial.println("Confirmed");
        Yellowlcd.setCursor(0, 3);
        Yellowlcd.print("Confirme.           ");
        delay(2000);
        Yellowlcd.setCursor(0, 3);
        Yellowlcd.print("                    ");
      } else if ( valmov <= 35)  {    // West
        YellowConfirmationColumn = 0;
        YellowColumn = 0;
        Serial.println("Canceled");
        Serial.println("Input column again:");
        Yellowlcd.setCursor(0, 3);
        Yellowlcd.print("Annule. Saisir a nv");
        delay(2000);
        Yellowlcd.setCursor(8, 2);
        Yellowlcd.print("             ");
        Yellowlcd.setCursor(0, 3);
        Yellowlcd.print("                    ");
      }
      previousButtonMillis += buttonInterval;
    }
  }
}
void CheckInitialPosition() {
  for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island
    if ((Islands[Map][i].col == BluePosition.col) && (Islands[Map][i].line == BluePosition.line)) {
      Serial.println("You can't be here. There's an island !");
      mcp.digitalWrite(BlueCaptainTriColor.green, LOW);
      Bluelcd.setCursor(0, 0);
      Bluelcd.print("Position interdite !");
      Bluelcd.setCursor(0, 1);
      Bluelcd.print("Re-saisir Position  ");
      delay(3000);
      Yellowlcd.clear();
      getKeyStartingPositionBlue();
    } else {
      if ((BluePosition.col != 0) && (BluePosition.line != 0)) {
        mcp.digitalWrite(BlueCaptainTriColor.green, HIGH);
      }
    }
  }
  for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island
    if ((Islands[Map][i].col == YellowPosition.col) && (Islands[Map][i].line == YellowPosition.line)) {
      Serial.println("You can't be here. There's an island !");
      Yellowlcd.setCursor(0, 0);
      Yellowlcd.print("Position interdite !");
      Yellowlcd.setCursor(0, 1);
      Yellowlcd.print("Re-saisir Position  ");
      mcp.digitalWrite(YellowCaptainTriColor.green, LOW);
      delay(3000);
      Yellowlcd.clear();
      getKeyStartingPositionYellow();
    } else {
      if ((YellowPosition.col != 0) && (YellowPosition.line != 0)) {
        mcp.digitalWrite(YellowCaptainTriColor.green, HIGH);
      }
    }
  }
}

byte getKeyPadCaptainBlue() {
  currentMillis = millis();
  long val = 0;
  int button = NONE;

  if (currentMillis - BluepreviousButtonMillisPad >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
    val = analogRead(BluePospadCaptain) ;   // Read first input on the position pad (sets the line)
    if (val <= 50) {
      BlueOffsetPosPad = val - Borne0PosPad;
    } else if ( val >= 970 + BlueOffsetPosPad)  {
      button = 1;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 880 + BlueOffsetPosPad)  &&  (val <= 903 + BlueOffsetPosPad)  )   {
      button = 2;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 809 + BlueOffsetPosPad) &&  (val <= 829 + BlueOffsetPosPad) )   {
      button = 3;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 746 + BlueOffsetPosPad) &&  (val <= 767 + BlueOffsetPosPad)  )   {
      button = 4;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 640 + BlueOffsetPosPad) &&  ( val <= 659 + BlueOffsetPosPad)  )   {
      button = 5;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 603 + BlueOffsetPosPad) &&  ( val <= 617 + BlueOffsetPosPad)  )   {
      button = 6;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 567 + BlueOffsetPosPad)  &&  (val <= 570 + BlueOffsetPosPad)    )   {
      button = 7;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 526 + BlueOffsetPosPad) &&  (val <= 538 + BlueOffsetPosPad) )   {
      button = 8;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 470 + BlueOffsetPosPad) &&  (val <= 488 + BlueOffsetPosPad)  )   {
      button = 9;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 452 + BlueOffsetPosPad) &&  ( val <= 460 + BlueOffsetPosPad)  )   {
      button = 10;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 429 + BlueOffsetPosPad) &&  ( val <= 445 + BlueOffsetPosPad)  )   {
      button = 11;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 410 + BlueOffsetPosPad)  &&  (val <= 420 + BlueOffsetPosPad)    )   {
      button = 12;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 376 + BlueOffsetPosPad) &&  (val <= 386 + BlueOffsetPosPad) )   {
      button = 13;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 305 + BlueOffsetPosPad) &&  (val <= 312 + BlueOffsetPosPad)  )   {
      button = 14;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 256 + BlueOffsetPosPad) &&  ( val <= 262 + BlueOffsetPosPad)  )   {
      button = 15;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 223 + BlueOffsetPosPad) &&  ( val <= 230 + BlueOffsetPosPad)  )   {
      button = 16;
      BluepreviousButtonMillisPad = currentMillis + DebounceTime;
      DetonateMineBlue();
    }
    BluepreviousButtonMillisPad = currentMillis + buttonInterval;
  }
  return button;
}
byte getKeyMovCaptainBlue()   //Reads the input from the direction/surface pad of the captain board (5 buttons)
{
  long valmov = 0;
  byte button = 0;
  button = NONE; // use NONE as the default value

  if (currentMillis - BluepreviousButtonMillisCap >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
    valmov = analogRead(BluekeypadCaptain);

    if ( valmov <= 35)  {
      button = LEFT;  // left
      BluepreviousButtonMillisCap = millis() + DebounceTime;
    }
    else if ( (valmov >= 100)  &&  (valmov <= 200)    )   {
      button = UP;   // up
      BluepreviousButtonMillisCap = millis() + DebounceTime;
    }
    else if ( (valmov >= 300) &&  (valmov <= 400 ) )  {
      button = DOWN;   // down
      BluepreviousButtonMillisCap = millis() + DebounceTime;
    }
    else if ( (valmov >= 480) &&  (valmov <= 560)  )   {
      button = RIGHT;   // right
      BluepreviousButtonMillisCap = millis() + DebounceTime;
    }
    else if ( (valmov >= 700) &&  ( valmov <= 800)  )   {
      button = SURFACE;   // Surface
      BluepreviousButtonMillisCap = millis() + DebounceTime;
    }

    BluepreviousButtonMillisCap += buttonInterval;
  }
  return button;
}
//Functions for changing/setting/checking Position
void AllowMovementBlue() //Check if the move is possible (in terms of submarine state) and call for the function ChangingPosition if needed
{
  if (BlueModuleEngaged != NONE) {

  } else {
    if (BlueCapkey == LEFT)    {
      if (SubStateCheckBlue() == 0) {
        if (ChangingPositionBlue(-1, 0) == 1) {
        } else {
          Serial.println("Cap à l'Ouest");
          lcdResetBlue(0);
          Bluelcd.setCursor(0, 0);
          Bluelcd.print("Cap a l'Ouest !     ");
        }
      } else {
        Serial.println("You can't move right now.");
        lcdResetBlue(2);
        Bluelcd.setCursor(0, 2);
        Bluelcd.print("Ne peut pas bouger. ");
      }
    }
    if (BlueCapkey == RIGHT)   {
      if (SubStateCheckBlue() == 0) {
        if (ChangingPositionBlue(1, 0) == 1) {
        } else {
          Serial.println("Cap à l'Est.");
          lcdResetBlue(0);
          Bluelcd.setCursor(0, 0);
          Bluelcd.print("Cap a l'est !      ");
        }
      } else {
        Serial.println("You can't move right now.");
        lcdResetBlue(2);
        Bluelcd.setCursor(0, 2);
        Bluelcd.print("Ne peut pas bouger. ");
      }
    }
    if (BlueCapkey == UP)     {
      if (SubStateCheckBlue() == 0) {
        if (ChangingPositionBlue(0, -1) == 1) {
        } else {
          Serial.println("Cap au Nord.");
          lcdResetBlue(0);
          Bluelcd.setCursor(0, 0);
          Bluelcd.print("Cap au Nord !       ");
        }
      } else {
        Serial.println("You can't move right now.");
        lcdResetBlue(2);
        Bluelcd.setCursor(0, 2);
        Bluelcd.print("Ne peut pas bouger. ");
      }
    }
    if (BlueCapkey == DOWN)     {
      if (SubStateCheckBlue() == 0) {
        if (ChangingPositionBlue(0, 1) == 1) {
        } else {
          Serial.println("Cap au Sud.");
          lcdResetBlue(0);
          Bluelcd.setCursor(0, 0);
          Bluelcd.print("Cap au Sud !        ");
        }
      } else {
        Serial.println("You can't move right now.");
        lcdResetBlue(2);
        Bluelcd.setCursor(0, 2);
        Bluelcd.print("Ne peut pas bouger. ");
      }
    }
    if (BlueCapkey == SURFACE)  {
      if (SubStateCheckBlue() == 0) {
        BlueSubState = 2;
        TricolorBlue(2);
        Serial.println("You are surfacing ! Annonce Sector.");
        lcdResetBlue(0);
        Bluelcd.setCursor(0, 0);
        Bluelcd.print("Surface !           ");
        Serial.print("Your position is : ");
        Serial.print(BluePosition.col);
        Serial.println(BluePosition.line);
        lcdResetBlue(1);
        Bluelcd.setCursor(0, 1);
        Bluelcd.print("Position : ");
        Bluelcd.setCursor(11, 1);
        Bluelcd.print(BluePosition.col);
        Bluelcd.setCursor(12, 1);
        Bluelcd.print(BluePosition.line);
        SurfaceBlue();
      } else if (SubStateCheckBlue() == 1) {
        Serial.println("You can't surface right now.");
        lcdResetBlue(2);
        Bluelcd.setCursor(0, 2);
        Bluelcd.print("Surface Impossible. ");
      } else if (SubStateCheckBlue() == 2) {
        Serial.println("You are already surfacing.");
        lcdResetBlue(2);
        Bluelcd.setCursor(0, 2);
        Bluelcd.print("Deja en surface.    ");
      }
    }
  }
}
void SurfaceBlue() {
  BlueSurfaceBegin = millis();
  BluepreviousButtonMillisCap += SurfaceTime;
  BluepreviousButtonMillisFM += SurfaceTime;
  BluepreviousButtonMillisEngi += SurfaceTime;
}
//Yellow
byte getKeyPadCaptainYellow() {
  currentMillis = millis();
  long val = 0;
  byte button = NONE;

  if (currentMillis - YellowpreviousButtonMillisPad >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
    val = analogRead(YellowPospadCaptain) ;   // Read first input on the position pad (sets the line)
    if (val <= 50) {
      YellowOffsetPosPad = val - Borne0PosPad;
    } else if ( val >= 970 + YellowOffsetPosPad)  {
      button = 1;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 880 + YellowOffsetPosPad)  &&  (val <= 903 + YellowOffsetPosPad)  )   {
      button = 2;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 809 + YellowOffsetPosPad) &&  (val <= 829 + YellowOffsetPosPad) )   {
      button = 3;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 746 + YellowOffsetPosPad) &&  (val <= 767 + YellowOffsetPosPad)  )   {
      button = 4;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 640 + YellowOffsetPosPad) &&  ( val <= 659 + YellowOffsetPosPad)  )   {
      button = 5;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 603 + YellowOffsetPosPad) &&  ( val <= 617 + YellowOffsetPosPad)  )   {
      button = 6;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 567 + YellowOffsetPosPad)  &&  (val <= 580 + YellowOffsetPosPad)    )   {
      button = 7;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 536 + YellowOffsetPosPad) &&  (val <= 550 + YellowOffsetPosPad) )   {
      button = 8;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 480 + YellowOffsetPosPad) &&  (val <= 493 + YellowOffsetPosPad)  )   {
      button = 9;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 458 + YellowOffsetPosPad) &&  ( val <= 470 + YellowOffsetPosPad)  )   {
      button = 10;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 436 + YellowOffsetPosPad) &&  ( val <= 448 + YellowOffsetPosPad)  )   {
      button = 11;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 416 + YellowOffsetPosPad)  &&  (val <= 430 + YellowOffsetPosPad)    )   {
      button = 12;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 384 + YellowOffsetPosPad) &&  (val <= 393 + YellowOffsetPosPad) )   {
      button = 13;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 308 + YellowOffsetPosPad) &&  (val <= 318 + YellowOffsetPosPad)  )   {
      button = 14;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 259 + YellowOffsetPosPad) &&  ( val <= 266 + YellowOffsetPosPad)  )   {
      button = 15;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
    }
    else if ( (val >= 223 + YellowOffsetPosPad) &&  ( val <= 230 + YellowOffsetPosPad)  )   {
      button = 16;
      YellowpreviousButtonMillisPad = currentMillis + DebounceTime;
      DetonateMineYellow();
    }
    YellowpreviousButtonMillisPad = currentMillis + buttonInterval;
  }
  return button;
}
byte getKeyMovCaptainYellow()   //Reads the input from the direction/surface pad of the captain board (5 buttons)
{
  long valmov = 0;
  byte button = 0;
  button = NONE; // use NONE as the default value

  if (currentMillis - YellowpreviousButtonMillisCap >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
    valmov = analogRead(YellowkeypadCaptain);
    //Serial.println(valmov);

    if ( valmov <= 35)  {
      button = LEFT;  // left
      YellowpreviousButtonMillisCap = millis() + DebounceTime;
    }
    else if ( (valmov >= 100)  &&  (valmov <= 200)    )   {
      button = UP;   // up
      YellowpreviousButtonMillisCap = millis() + DebounceTime;
    }
    else if ( (valmov >= 300) &&  (valmov <= 400 ) )  {
      button = DOWN;   // down
      YellowpreviousButtonMillisCap = millis() + DebounceTime;
    }
    else if ( (valmov >= 480) &&  (valmov <= 560)  )   {
      button = RIGHT;   // right
      YellowpreviousButtonMillisCap = millis() + DebounceTime;
    }
    else if ( (valmov >= 700) &&  ( valmov <= 800)  )   {
      button = SURFACE;   // Surface
      YellowpreviousButtonMillisCap = millis() + DebounceTime;
    }

    YellowpreviousButtonMillisCap += buttonInterval;
  }
  //Serial.println(button);
  return button;
}
//Functions for changing/setting/checking Position
void AllowMovementYellow() //Check if the move is possible (in terms of submarine state) and call for the function ChangingPosition if needed
{
  if (YellowModuleEngaged != NONE) {

  } else {
    if (YellowCapkey == LEFT)    {
      if (SubStateCheckYellow() == 0) {
        if (ChangingPositionYellow(-1, 0) == 1) {
        } else {
          Serial.println("Cap à l'Ouest");
          lcdResetYellow(0);
          Yellowlcd.setCursor(0, 0);
          Yellowlcd.print("Cap a l'Ouest !     ");
        }
      } else {
        Serial.println("You can't move right now.");
        lcdResetYellow(2);
        Yellowlcd.setCursor(0, 2);
        Yellowlcd.print("Ne peut pas bouger. ");
      }
    }
    if (YellowCapkey == RIGHT)   {
      if (SubStateCheckYellow() == 0) {
        if (ChangingPositionYellow(1, 0) == 1) {
        } else {
          Serial.println("Cap à l'Est.");
          lcdResetYellow(0);
          Yellowlcd.setCursor(0, 0);
          Yellowlcd.print("Cap a l'est !       ");
        }
      } else {
        Serial.println("You can't move right now.");
        lcdResetYellow(2);
        Yellowlcd.setCursor(0, 2);
        Yellowlcd.print("Ne peut pas bouger. ");
      }
    }
    if (YellowCapkey == UP)     {
      if (SubStateCheckYellow() == 0) {
        if (ChangingPositionYellow(0, -1) == 1) {
        } else {
          Serial.println("Cap au Nord.");
          lcdResetYellow(0);
          Yellowlcd.setCursor(0, 0);
          Yellowlcd.print("Cap au Nord !       ");
        }
      } else {
        Serial.println("You can't move right now.");
        lcdResetYellow(2);
        Yellowlcd.setCursor(0, 2);
        Yellowlcd.print("Ne peut pas bouger. ");
      }
    }
    if (YellowCapkey == DOWN)     {
      if (SubStateCheckYellow() == 0) {
        if (ChangingPositionYellow(0, 1) == 1) {
        } else {
          Serial.println("Cap au Sud.");
          lcdResetYellow(0);
          Yellowlcd.setCursor(0, 0);
          Yellowlcd.print("Cap au Sud !        ");
        }
      } else {
        Serial.println("You can't move right now.");
        lcdResetYellow(2);
        Yellowlcd.setCursor(0, 2);
        Yellowlcd.print("Ne peut pas bouger. ");
      }
    }
    if (YellowCapkey == SURFACE)  {
      if (SubStateCheckYellow() == 0) {
        YellowSubState = 2;
        TricolorYellow(2);
        Serial.println("You are surfacing ! Annonce Sector.");
        lcdResetYellow(0);
        Yellowlcd.setCursor(0, 0);
        Yellowlcd.print("Surface !           ");
        Serial.print("Your position is : ");
        Serial.print(YellowPosition.col);
        Serial.println(YellowPosition.line);
        lcdResetYellow(1);
        Yellowlcd.setCursor(0, 1);
        Yellowlcd.print("Position : ");
        Yellowlcd.setCursor(11, 1);
        Yellowlcd.print(YellowPosition.col);
        Yellowlcd.setCursor(12, 1);
        Yellowlcd.print(YellowPosition.line);
        SurfaceYellow();
      } else if (SubStateCheckYellow() == 1) {
        Serial.println("You can't surface right now.");
        lcdResetYellow(2);
        Yellowlcd.setCursor(0, 2);
        Yellowlcd.print("Surface Impossible. ");
      } else if (SubStateCheckYellow() == 2) {
        Serial.println("You are already surfacing.");
        lcdResetYellow(2);
        Yellowlcd.setCursor(0, 2);
        Yellowlcd.print("Deja en surface.    ");
      }
    }
  }
}
void SurfaceYellow() {
  YellowSurfaceBegin = millis();
  YellowpreviousButtonMillisCap += SurfaceTime;
  YellowpreviousButtonMillisFM += SurfaceTime;
  YellowpreviousButtonMillisEngi += SurfaceTime;
}

void CheckSurface() {
  if ((currentMillis - BlueSurfaceBegin >= SurfaceTime) && (BlueSubState == 2)) {
    BlueSubState = 0;
    TricolorBlue(0);
    BlueEngiLedLow();
    for (int i = 0; i <= 99 ; i++) { // Resets previous path
      (BluePastPosition[i].col = 65);
      (BluePastPosition[i].line = 0);
    }
    BlueWeaponWestAutopipe = 0;
    BlueDetectionWestAutopipe = 0;
    BlueSpecialWestAutopipe = 0;
    BlueDetectionWestpersistant = 0;
    BlueRadiationWestpersistant1 = 0;
    BlueRadiationWestpersistant2 = 0;
    BlueWeaponNorthAutopipe = 0;
    BlueSpecialNorthAutopipe1 = 0;
    BlueSpecialNorthAutopipe2 = 0;
    BlueDetectionNorthpersistant = 0;
    BlueWeaponNorthpersistant = 0;
    BlueRadiationNorthpersistant = 0;
    BlueWeaponSudAutopipe = 0;
    BlueDetectionSudAutopipe = 0;
    BlueSpecialSudAutopipe = 0;
    BlueWeaponSudpersistant = 0;
    BlueRadiationSudpersistant = 0;
    BlueSpecialSudpersistant = 0;
    BlueWeaponEstAutopipe = 0;
    BlueDetectionEstAutopipe = 0;
    BlueSpecialEstAutopipe = 0;
    BlueDetectionEstpersistant = 0;
    BlueRadiationEstpersistant1 = 0;
    BlueRadiationEstpersistant2 = 0;
  }
  if ((currentMillis - YellowSurfaceBegin >= SurfaceTime) && (YellowSubState == 2)) {
    YellowSubState = 0;
    TricolorYellow(0);
    YellowEngiLedLow();
    for (int i = 0; i <= 99 ; i++) { // Resets previous path
      (YellowPastPosition[i].col = 65);
      (YellowPastPosition[i].line = 0);
    }
    YellowWeaponWestAutopipe = 0;
    YellowDetectionWestAutopipe = 0;
    YellowSpecialWestAutopipe = 0;
    YellowDetectionWestpersistant = 0;
    YellowRadiationWestpersistant1 = 0;
    YellowRadiationWestpersistant2 = 0;
    YellowWeaponNorthAutopipe = 0;
    YellowSpecialNorthAutopipe1 = 0;
    YellowSpecialNorthAutopipe2 = 0;
    YellowDetectionNorthpersistant = 0;
    YellowWeaponNorthpersistant = 0;
    YellowRadiationNorthpersistant = 0;
    YellowWeaponSudAutopipe = 0;
    YellowDetectionSudAutopipe = 0;
    YellowSpecialSudAutopipe = 0;
    YellowWeaponSudpersistant = 0;
    YellowRadiationSudpersistant = 0;
    YellowSpecialSudpersistant = 0;
    YellowWeaponEstAutopipe = 0;
    YellowDetectionEstAutopipe = 0;
    YellowSpecialEstAutopipe = 0;
    YellowDetectionEstpersistant = 0;
    YellowRadiationEstpersistant1 = 0;
    YellowRadiationEstpersistant2 = 0;
  }
}

int CheckModuleAvailabilityBlue(char type) {
  switch (type) {
    case 68:
      if ((BlueDetectionWestAutopipe == 0) && (BlueDetectionWestpersistant == 0) && \
          (BlueDetectionNorthpersistant == 0) && (BlueDetectionSudAutopipe == 0) && (BlueDetectionEstAutopipe == 0) && (BlueDetectionEstpersistant == 0)) {
        return 0;
      } else {
        return 1;
      }
      break;
    case 83:
      if ((BlueSpecialWestAutopipe == 0) && (BlueSpecialNorthAutopipe1 == 0) && (BlueSpecialNorthAutopipe2 == 0) \
          && (BlueSpecialSudAutopipe == 0) && (BlueSpecialSudpersistant == 0) && (BlueSpecialEstAutopipe == 0)) {
        return 0;
      } else {
        return 1;
      }
      break;
    case 87:
      if ((BlueWeaponWestAutopipe == 0) && (BlueWeaponNorthpersistant == 0) && (BlueWeaponSudAutopipe == 0) \
          && (BlueWeaponSudpersistant == 0) && (BlueWeaponEstAutopipe == 0) && (BlueWeaponNorthAutopipe == 0)) {
        return 0;
      } else {
        return 1;
      }
      break;
  }
}
//Yellow
int CheckModuleAvailabilityYellow(char type) {
  switch (type) {
    case 68:
      if ((YellowDetectionWestAutopipe == 0) && (YellowDetectionWestpersistant == 0) \
          && (YellowDetectionNorthpersistant == 0) && (YellowDetectionSudAutopipe == 0) && (YellowDetectionEstAutopipe == 0) && (YellowDetectionEstpersistant == 0)) {
        return 0;
      } else {
        return 1;
      }
      break;
    case 83:
      if ((YellowSpecialWestAutopipe == 0) && (YellowSpecialNorthAutopipe1 == 0) && (YellowSpecialNorthAutopipe2 == 0) \
          && (YellowSpecialSudAutopipe == 0) && (YellowSpecialSudpersistant == 0) && (YellowSpecialEstAutopipe == 0)) {
        return 0;
      } else {
        return 1;
      }
      break;
    case 87:
      if ((YellowWeaponWestAutopipe == 0) && (YellowWeaponNorthpersistant == 0) && (YellowWeaponSudAutopipe == 0) \
          && (YellowWeaponSudpersistant == 0) && (YellowWeaponEstAutopipe == 0) && (YellowWeaponNorthAutopipe == 0))  {
        return 0;
      } else {
        return 1;
      }
      break;
  }
}

int SubStateCheckBlue()  //Check the state of the sub for allowing or not some functions (move, activate a module...)
{
  if (BlueSubState == 0) {      // Is the sub in state 0 ?
    return (0);
  } else if (BlueSubState == 1) {
    return (1);     //You haven't resolved your last move
  } else {
    return (2);     //You are surfacing
  }
}
//Yellow
int SubStateCheckYellow()  //Check the state of the sub for allowing or not some functions (move, activate a module...)
{
  if (YellowSubState == 0) {      // Is the sub in state 0 ?
    return (0);
  } else if (YellowSubState == 1) {
    return (1);     //You haven't resolved your last move
  } else {
    return (2);     //You are surfacing
  }
}

void UpdateSubState() {
  if (BlueSubState == 1) {
    if ((BlueEngineerDamage == 0) && (BlueFMCharge == 0)) {
      BlueSubState = 0;
      TricolorBlue(0);
    }
  } else if (BlueSubState == 0) {
    if ((BlueEngineerDamage == 1) || (BlueFMCharge == 1)) {
      BlueSubState = 1;
      TricolorBlue(1);
    }
  }
  if (YellowSubState == 1) {
    if ((YellowEngineerDamage == 0) && (YellowFMCharge == 0)) {
      YellowSubState = 0;
      TricolorYellow(0);
    }
  } else if (YellowSubState == 0) {
    if ((YellowEngineerDamage == 1) || (YellowFMCharge == 1)) {
      YellowSubState = 1;
      TricolorYellow(1);
    }
  }
}

byte ChangingPositionBlue(int x, int y) {   //change the position of the sub if the move is legal
  //Check if the move is legal (not leading to past Position or Island)
  for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
    if ((Islands[Map][i].col == BluePosition.col + x) && (Islands[Map][i].line == BluePosition.line + y)) {
      Serial.println("Blue can't move here. There's an island !");
      lcdResetBlue(2);
      Bluelcd.setCursor(0, 2);
      Bluelcd.print("Mvt interdit : ile. ");
      return 1;
    } else {
    }
  }
  if ((BluePosition.col + x < 65) || (BluePosition.line + y < 1) || (BluePosition.col + x > 79) || (BluePosition.line + y > 15)) { //check for out of map
    // The move is not possible, Position would be out of map
    Serial.println("Blue can't move here. Out of map.");
    lcdResetBlue(2);
    Bluelcd.setCursor(0, 2);
    Bluelcd.print("Mvt interdit : OoM. ");
    return 1;
  }
  for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
    if ((BluePastPosition[i].col == BluePosition.col + x) && (BluePastPosition[i].line == BluePosition.line + y)) {
      Serial.println("Blue can't move here. Can't cross path !");
      lcdResetBlue(2);
      Bluelcd.setCursor(0, 2);
      Bluelcd.print("Mvt interdit : cross");
      return 1;
    } else {
    }
  }
  //  Update BluePastPosition
  BluePastPosition[BlueMoveCount].line = BluePosition.line;
  BluePastPosition[BlueMoveCount].col = BluePosition.col;
  BlueMoveCount += 1;

  BluePosition.col = BluePosition.col + x;
  BluePosition.line = BluePosition.line + y;
  Serial.print("Blue position is : ");
  Serial.print(BluePosition.col);
  Serial.println(BluePosition.line);
  //Serial.println(BlueCapkey);
  switch (BlueCapkey) {
    case LEFT:   //LEFT
      BlueLastDirection = 1;
      break;
    case UP:   //UP
      BlueLastDirection = 2;
      break;
    case RIGHT:   //RIGHT
      BlueLastDirection = 3;
      break;
    case DOWN:   //DOWN
      BlueLastDirection = 4;
      break;
  }
  BlueSubState = 1;
  TricolorBlue(1);
  BlueEngineerDamage = 1;
  BlueFMCharge = 1;
  return 0;
}
//Yellow
byte ChangingPositionYellow(int x, int y) {   //change the position of the sub if the move is legal
  //Check if the move is legal (not leading to past Position or Island)
  for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
    if ((Islands[Map][i].col == YellowPosition.col + x) && (Islands[Map][i].line == YellowPosition.line + y)) {
      Serial.println("Yellow can't move here. There's an island !");
      lcdResetYellow(2);
      Yellowlcd.setCursor(0, 2);
      Yellowlcd.print("Mvt interdit : ile. ");
      return 1;
    } else {
    }
  }
  if ((YellowPosition.col + x < 65) || (YellowPosition.line + y < 1) || (YellowPosition.col + x > 79) || (YellowPosition.line + y > 15)) { //check for out of map
    // The move is not possible, Position would be out of map
    Serial.println("Yellow can't move here. Out of map.");
    lcdResetYellow(2);
    Yellowlcd.setCursor(0, 2);
    Yellowlcd.print("Mvt interdit : OoM. ");
    return 1;
  }
  for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
    if ((YellowPastPosition[i].col == YellowPosition.col + x) && (YellowPastPosition[i].line == YellowPosition.line + y)) {
      Serial.println("Yellow can't move here. Can't cross path !");
      lcdResetYellow(2);
      Yellowlcd.setCursor(0, 2);
      Yellowlcd.print("Mvt interdit : cross");
      return 1;
    } else {
    }
  }
  //  Update YellowPastPosition
  YellowPastPosition[YellowMoveCount].line = YellowPosition.line;
  YellowPastPosition[YellowMoveCount].col = YellowPosition.col;
  YellowMoveCount += 1;

  YellowPosition.col = YellowPosition.col + x;
  YellowPosition.line = YellowPosition.line + y;
  Serial.print("Yellow position is : ");
  Serial.print(YellowPosition.col);
  Serial.println(YellowPosition.line);
  //Serial.println(YellowCapkey);
  switch (YellowCapkey) {
    case LEFT:   //LEFT
      YellowLastDirection = 1;
      break;
    case UP:   //UP
      YellowLastDirection = 2;
      break;
    case RIGHT:   //RIGHT
      YellowLastDirection = 3;
      break;
    case DOWN:   //DOWN
      YellowLastDirection = 4;
      break;
  }
  YellowSubState = 1;
  TricolorYellow(1);
  YellowEngineerDamage = 1;
  YellowFMCharge = 1;
  return 0;
}

byte getKeypadFMBlue()   //Reads the input from the direction/surface pad of the captain board (5 buttons)
{
  long valfm = 0;
  byte button = 0;
  button = NONE; // use NONE as the default value

  if (currentMillis - BluepreviousButtonMillisFM >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
    valfm = analogRead(BluekeypadFM);
    /*if ((valfm >= 100) && (valfm <= 165))  {
      button = MINE;
      }    else */
    if ( (valfm >= 166)  &&  (valfm <= 210)    )   {
      button = MINE;
    }    else if ( (valfm >= 221) &&  (valfm <= 240) )  {
      button = TORPEDO;
    }    else if ( (valfm >= 271) &&  (valfm <= 290)  )   {
      button = DRONE;
    }    else if ( (valfm >= 330) &&  ( valfm <= 380)  )   {
      button = SONAR;
    } else if ( (valfm >= 491) &&  ( valfm <= 530)  )   {
      button = SILENCE;
    }
    BluepreviousButtonMillisFM += buttonInterval;
  }
  return button;
}
//Yellow
byte getKeypadFMYellow()   //Reads the input from the direction/surface pad of the captain board (5 buttons)
{
  long valfm = 0;
  byte button = 0;
  button = NONE; // use NONE as the default value

  if (currentMillis - YellowpreviousButtonMillisFM >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
    valfm = analogRead(YellowkeypadFM);
    if ((valfm >= 100) && (valfm <= 132))  { //Panne du sixième bouton : décale les valeurs d'un cran pour compenser
      button = MINE;
    }    else if ( (valfm >= 138) && (valfm <= 150)    )   {
      button = TORPEDO;
    }    else if ( (valfm >= 151) && (valfm <= 170) )  {
      button = DRONE;
    }    else if ( (valfm >= 181) && (valfm <= 215)  )   {
      button = SONAR;
    }    else if ( (valfm >= 236) && (valfm <= 270)  )   {
      button = SILENCE;
    } else if ( (valfm >= 306) && (valfm <= 400)  )   {
      button = SCENARIO;
    }
    YellowpreviousButtonMillisFM += buttonInterval;
  }
  return button;
}

void ActivateModuleBlue() //Read and interpret the input from the FM board, triggers modules activation if they are fully charged,
// charge the modules if the situation allows it and calls for the proper lighting functions for the FM board.
{
  switch (BlueModuleEngaged) {
    case MINE:
      MineBlue();
      break;
    case DETONATEMINE:
      DetonateMineBlue();
      break;
    case TORPEDO:
      TorpedoBlue();
      break;
    case SILENCE:
      SilenceBlue();
      break;
  }
  if ((SubStateCheckBlue() == 0) && (BlueModuleEngaged == NONE)) {                            //You are in state 0 (underwater, not in a move)
    switch (BlueFMkey) {                                     // this should trigger a module if it is charged.
      case 6:
        if (BlueChargeMine == MineCharged) {
          if (CheckModuleAvailabilityBlue(87) == 0) {
            MineBlue();
            BlueChargeMine = 0;
            colorEmptyChargeBlue(0, 7);
          }
        }
        break;
      case 7:
        if (BlueChargeTorpedo == TorpedoCharged) {
          if (CheckModuleAvailabilityBlue(87) == 0) {
            TorpedoBlue();
            BlueChargeTorpedo = 0;
            colorEmptyChargeBlue(8, 15);
          }
        }
        break;
      case 8:
        if (BlueChargeDrone == DroneCharged) {
          if (CheckModuleAvailabilityBlue(68) == 0) {
            DroneBlue();
            BlueChargeDrone = 0;
            colorEmptyChargeBlue(16, 23);
          }
        }
        break;
      case 9:
        if (BlueChargeSonar == SonarCharged) {
          if (CheckModuleAvailabilityBlue(68) == 0) {
            SonarBlue();
            BlueChargeSonar = 0;
            colorEmptyChargeBlue(24, 31);
          }
        }
        break;
      case 10:
        if (BlueChargeSilence == SilenceCharged) {
          if (CheckModuleAvailabilityBlue(83) == 0) {
            BlueModuleEngaged = SILENCE;
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            if (SilenceBlue() == 1) { //calls function Silence, if 1 : the silence is absolutely impossible.
              Serial.println("The Blue Silence is impossible (can't move)");
              Bluelcd.setCursor(0, 0);
              Bluelcd.print("                    ");
              lcdResetBlue(2);
              Bluelcd.setCursor(0, 2);
              Bluelcd.print("Silence Interdit    ");
              BlueModuleEngaged = NONE;
            } else { //The silence is possible
              BlueChargeSilence = 0;
              colorEmptyChargeBlue(32, 39);
              BlueSubState = 1;
              TricolorBlue(1);
            }
          }
        }
        break;
      case 11:
        if (BlueChargeScenario == ScenarioCharged) {
          //calls function Scenario
          BlueChargeScenario = 0;
          colorEmptyChargeBlue(40, 47);
        }
    }
  } else if ((SubStateCheckBlue() == 1) && (BlueFMCharge == 1)) {                     //You are in an unresolved move
    if ((BlueChargeMine == MineCharged) && (BlueChargeTorpedo == TorpedoCharged) && (BlueChargeDrone == DroneCharged) && (BlueChargeSonar == SonarCharged) && (BlueChargeSilence == SilenceCharged) /*&& (BlueChargeScenario == BlueScenarioCharged)*/) {//If all modules are fully charged (scenario not included by default)
      BlueFMCharge = 0;   // then the charge to be attributed drops to 0.
      UpdateSubState();
      BluepreviousButtonMillisFM = currentMillis + DebounceTime;
    } else {
      switch (BlueFMkey) {                              //this should charge a FM module by 1 charge if it is not full.
        case 6:
          if (BlueChargeMine < MineCharged) {
            BlueChargeMine = BlueChargeMine + 1;
            colorChargeBlue(0, BlueChargeMine - 1);   //The -1 is due to the 0 indexing caracter of the Neopixel lights
            BlueFMCharge = 0;
            if (BlueChargeMine == MineCharged) {
              colorFullChargeBlue(0, BlueChargeMine - 1);
              BluepreviousButtonMillisFM = currentMillis + DebounceTime;   //So the push of the button that charges the module fully doesn't trigger immediately the module itself.
            }
          }
          break;
        case 7:
          if (BlueChargeTorpedo < TorpedoCharged) {
            BlueChargeTorpedo =  BlueChargeTorpedo + 1;
            colorChargeBlue(8, BlueChargeTorpedo + 7);    // The +7 is here because it refers to the position of the last led to turn on in the neopixel serie.
            BlueFMCharge = 0;
            if (BlueChargeTorpedo == TorpedoCharged) {
              colorFullChargeBlue(8, BlueChargeTorpedo + 7);
              BluepreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
        case 8:
          if (BlueChargeDrone < DroneCharged) {
            BlueChargeDrone += 1;
            colorChargeBlue(16, BlueChargeDrone + 15);
            BlueFMCharge = 0;
            if (BlueChargeDrone == DroneCharged) {
              colorFullChargeBlue(16, BlueChargeDrone + 15);
              BluepreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
        case 9:
          if (BlueChargeSonar < SonarCharged) {
            BlueChargeSonar += 1;
            colorChargeBlue(24, BlueChargeSonar + 23);
            BlueFMCharge = 0;
            if (BlueChargeSonar == SonarCharged) {
              colorFullChargeBlue(24, BlueChargeSonar + 23);
              BluepreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
        case 10:
          if (BlueChargeSilence < SilenceCharged) {
            BlueChargeSilence += 1;
            colorChargeBlue(32, BlueChargeSilence + 31);
            BlueFMCharge = 0;
            if (BlueChargeSilence == SilenceCharged) {
              colorFullChargeBlue(32, BlueChargeSilence + 31);
              BluepreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
        case 11:
          if (BlueChargeScenario < ScenarioCharged) {
            BlueChargeScenario += 1;
            colorChargeBlue(40, BlueChargeScenario + 39);
            BlueFMCharge = 0;
            if (BlueChargeScenario == ScenarioCharged) {
              colorFullChargeBlue(40, BlueChargeScenario + 39);
              BluepreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
      }
    }
    UpdateSubState();
  }
}
//Yellow version
void ActivateModuleYellow() //Read and interpret the input from the FM board, triggers modules activation if they are fully charged,
// charge the modules if the situation allows it and calls for the proper lighting functions for the FM board.
{
  switch (YellowModuleEngaged) {
    case MINE:
      MineYellow();
      break;
    case DETONATEMINE:
      DetonateMineYellow();
      break;
    case TORPEDO:
      TorpedoYellow();
      break;
    case SILENCE:
      SilenceYellow();
      break;
  }
  if ((SubStateCheckYellow() == 0) && (YellowModuleEngaged == NONE)) {                            //You are in state 0 (underwater, not in a move)
    switch (YellowFMkey) {                                     // this should trigger a module if it is charged.
      case 6:
        if (YellowChargeMine == MineCharged) {
          if (CheckModuleAvailabilityYellow(87) == 0) {
            MineYellow();
            YellowChargeMine = 0;
            colorEmptyChargeYellow(0, 7);
          }
        }
        break;
      case 7:
        if (YellowChargeTorpedo == TorpedoCharged) {
          if (CheckModuleAvailabilityYellow(87) == 0) {
            TorpedoYellow();
            YellowChargeTorpedo = 0;
            colorEmptyChargeYellow(8, 15);
          }
        }
        break;
      case 8:
        if (YellowChargeDrone == DroneCharged) {
          if (CheckModuleAvailabilityYellow(68) == 0) {
            DroneYellow();
            YellowChargeDrone = 0;
            colorEmptyChargeYellow(16, 23);
          }
        }
        break;
      case 9:
        if (YellowChargeSonar == SonarCharged) {
          if (CheckModuleAvailabilityYellow(68) == 0) {
            SonarYellow();
            YellowChargeSonar = 0;
            colorEmptyChargeYellow(24, 31);
          }
        }
        break;
      case 10:
        if (YellowChargeSilence == SilenceCharged) {
          if (CheckModuleAvailabilityYellow(83) == 0) {
            YellowModuleEngaged = SILENCE;
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            if (SilenceYellow() == 1) { //calls function Silence, if 1 : the silence is absolutely impossible.
              Serial.println("The Silence is impossible (can't move)");
              Yellowlcd.setCursor(0, 0);
              Yellowlcd.print("                    ");
              lcdResetYellow(2);
              Yellowlcd.setCursor(0, 2);
              Yellowlcd.print("Silence Interdit    ");
              YellowModuleEngaged = NONE;
            } else { //The silence is possible
              YellowChargeSilence = 0;
              colorEmptyChargeYellow(32, 39);
              YellowSubState = 1;
              TricolorYellow(1);
            }
          }
        }
        break;
      case 11:
        if (YellowChargeScenario == ScenarioCharged) {
          //calls function Scenario
          YellowChargeScenario = 0;
          colorEmptyChargeYellow(40, 47);
        }
    }
  } else if ((SubStateCheckYellow() == 1) && (YellowFMCharge == 1)) {                     //You are in an unresolved move
    if ((YellowChargeMine == MineCharged) && (YellowChargeTorpedo == TorpedoCharged) && (YellowChargeDrone == DroneCharged) && (YellowChargeSonar == SonarCharged)
        && (YellowChargeSilence == SilenceCharged) /*&& (YellowChargeScenario == YellowScenarioCharged)*/) {//If all modules are fully charged (scenario not included by default)
      YellowFMCharge = 0;   // then the charge to be attributed drops to 0.
      UpdateSubState();
      YellowpreviousButtonMillisFM = currentMillis + DebounceTime;                                                                // then the charge to be attributed drops to 0.
    } else {
      switch (YellowFMkey) {                              //this should charge a FM module by 1 charge if it is not full.
        case 6:
          if (YellowChargeMine < MineCharged) {
            YellowChargeMine = YellowChargeMine + 1;
            colorChargeYellow(0, YellowChargeMine - 1);   //The -1 is due to the 0 indexing caracter of the Neopixel lights
            YellowFMCharge = 0;
            if (YellowChargeMine == MineCharged) {
              colorFullChargeYellow(0, YellowChargeMine - 1);
              YellowpreviousButtonMillisFM = currentMillis + DebounceTime;   //So the push of the button that charges the module fully doesn't trigger immediately the module itself.
            }
          }
          break;
        case 7:
          if (YellowChargeTorpedo < TorpedoCharged) {
            YellowChargeTorpedo =  YellowChargeTorpedo + 1;
            colorChargeYellow(8, YellowChargeTorpedo + 7);    // The +7 is here because it refers to the position of the last led to turn on in the neopixel serie.
            YellowFMCharge = 0;
            if (YellowChargeTorpedo == TorpedoCharged) {
              colorFullChargeYellow(8, YellowChargeTorpedo + 7);
              YellowpreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
        case 8:
          if (YellowChargeDrone < DroneCharged) {
            YellowChargeDrone = YellowChargeDrone + 1;
            colorChargeYellow(16, YellowChargeDrone + 15);
            YellowFMCharge = 0;
            if (YellowChargeDrone == DroneCharged) {
              colorFullChargeYellow(16, YellowChargeDrone + 15);
              YellowpreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
        case 9:
          if (YellowChargeSonar < SonarCharged) {
            YellowChargeSonar += 1;
            colorChargeYellow(24, YellowChargeSonar + 23);
            YellowFMCharge = 0;
            if (YellowChargeSonar == SonarCharged) {
              colorFullChargeYellow(24, YellowChargeSonar + 23);
              YellowpreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
        case 10:
          if (YellowChargeSilence < SilenceCharged) {
            YellowChargeSilence += 1;
            colorChargeYellow(32, YellowChargeSilence + 31);
            YellowFMCharge = 0;
            if (YellowChargeSilence == SilenceCharged) {
              colorFullChargeYellow(32, YellowChargeSilence + 31);
              YellowpreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
        case 11:
          if (YellowChargeScenario < ScenarioCharged) {
            YellowChargeScenario += 1;
            colorChargeYellow(40, YellowChargeScenario + 39);
            YellowFMCharge = 0;
            if (YellowChargeScenario == ScenarioCharged) {
              colorFullChargeYellow(40, YellowChargeScenario + 39);
              YellowpreviousButtonMillisFM = currentMillis + DebounceTime;
            }
          }
          break;
      }
    }
    UpdateSubState();
  }
}

void getKeyEngiBlue()   //Reads the input from the board of the Engi, light up the damaged module if needed and resolve the move for the Engi action
{
  long val = 0;
  if (BlueEngineerDamage == 0) {          //If the Engineer isn't supposed to allocate a damage on a module, no need to read the inputs.

  } else {
    if (currentMillis - BluepreviousButtonMillisEngi >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
      switch (BlueLastDirection) {
        case LEFT:
          val = analogRead(BluekeypadEngiWest); //value for 6 buttons wired with 1KOhms resistors
          //Serial.println(val);
          if ((val <= 50)) {
            Offset = val - Borne0;
          } else if ((val >= Borne1 + Offset + BorneMin) && (val <= Borne1 + Offset + BorneMax) && (BlueWeaponWestAutopipe == 0))             {
            digitalWrite(BluePinLedWeaponWestAutopipe, HIGH);
            BlueWeaponWestAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne2 + Offset + BorneMin) && (val <= Borne2 + Offset + BorneMax) && (BlueSpecialWestAutopipe == 0))    {
            digitalWrite(BluePinLedSpecialWestAutopipe, HIGH);
            BlueSpecialWestAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne3 + Offset + Borne3Min) && (val <= Borne3 + Offset + Borne3Max) && (BlueDetectionWestAutopipe == 0))   {
            digitalWrite(BluePinLedDetectionWestAutopipe, HIGH);
            BlueDetectionWestAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne4 + Offset + BornePermaMin) && (val <= Borne4 + Offset + BornePermaMax) && (BlueRadiationWestpersistant1 == 0)) {
            digitalWrite(BluePinLedRadiationWestpersistant1, HIGH);
            BlueRadiationWestpersistant1 = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne5 + Offset + BornePermaMin) && (val <= Borne5 + Offset + BornePermaMax) && (BlueRadiationWestpersistant2 == 0)) {
            digitalWrite(BluePinLedRadiationWestpersistant2, HIGH);
            BlueRadiationWestpersistant2 = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne6 + Offset + BornePermaMin) && (val <= Borne6 + Offset + BornePermaMax) && (BlueDetectionWestpersistant == 0)) {
            digitalWrite(BluePinLedDetectionWestpersistant, HIGH);
            BlueDetectionWestpersistant = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          AutoPipes();
          UpdateSubState();
          break;
        case UP:
          val = analogRead(BluekeypadEngiNorth);
          if ((val <= 50)) {
            Offset = val - Borne0;
          } else if ((val >= Borne1 + Offset + BorneMin) && (val <= Borne1 + Offset + BorneMax) && (BlueWeaponNorthAutopipe == 0))             {
            digitalWrite(BluePinLedWeaponNorthAutopipe, HIGH);
            BlueWeaponNorthAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne2 + Offset + BorneMin) && (val <= Borne2 + Offset + BorneMax) && (BlueSpecialNorthAutopipe1 == 0))    {
            digitalWrite(BluePinLedSpecialNorthAutopipe1, HIGH);
            BlueSpecialNorthAutopipe1 = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne3 + Offset + Borne3Min) && (val <= Borne3 + Offset + Borne3Max) && (BlueSpecialNorthAutopipe2 == 0))   {
            digitalWrite(BluePinLedSpecialNorthAutopipe2, HIGH);
            BlueSpecialNorthAutopipe2 = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne4 + Offset + BornePermaMin) && (val <= Borne4 + Offset + BornePermaMax) && (BlueDetectionNorthpersistant == 0)) {
            digitalWrite(BluePinLedDetectionNorthpersistant, HIGH);
            BlueDetectionNorthpersistant = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne5 + Offset + BornePermaMin) && (val <= Borne5 + Offset + BornePermaMax) && (BlueWeaponNorthpersistant == 0)) {
            digitalWrite(BluePinLedWeaponNorthpersistant, HIGH);
            BlueWeaponNorthpersistant = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne6 + Offset + BornePermaMin) && (val <= Borne6 + Offset + BornePermaMax) && (BlueRadiationNorthpersistant == 0)) {
            digitalWrite(BluePinLedRadiationNorthpersistant, HIGH);
            BlueRadiationNorthpersistant = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          AutoPipes();
          UpdateSubState();
          break;
        case RIGHT:
          val = analogRead(BluekeypadEngiEast); //value for 6 buttons wired with 270 Ohms resistors
          if ((val <= 50)) {
            Offset = val - Borne0;
          } else if ((val >= Borne1 + Offset + BorneMin) && (val <= Borne1 + Offset + BorneMax) && (BlueWeaponEstAutopipe == 0))             {
            digitalWrite(BluePinLedWeaponEstAutopipe, HIGH);
            BlueWeaponEstAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne2 + Offset + BorneMin) && (val <= Borne2 + Offset + BorneMax) && (BlueDetectionEstAutopipe == 0))    {
            digitalWrite(BluePinLedDetectionEstAutopipe, HIGH);
            BlueDetectionEstAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne3 + Offset + Borne3Min) && (val <= Borne3 + Offset + Borne3Max) && (BlueSpecialEstAutopipe == 0))   {
            digitalWrite(BluePinLedSpecialEstAutopipe, HIGH);
            BlueSpecialEstAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne4 + Offset + BornePermaMin) && (val <= Borne4 + Offset + BornePermaMax) && (BlueDetectionEstpersistant == 0)) {
            digitalWrite(BluePinLedDetectionEstpersistant, HIGH);
            BlueDetectionEstpersistant = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne5 + Offset + BornePermaMin) && (val <= Borne5 + Offset + BornePermaMax) && (BlueRadiationEstpersistant1 == 0)) {
            digitalWrite(BluePinLedRadiationEstpersistant1, HIGH);
            BlueRadiationEstpersistant1 = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne6 + Offset + BornePermaMin) && (val <= Borne6 + Offset + BornePermaMax) && (BlueRadiationEstpersistant2 == 0)) {
            digitalWrite(BluePinLedRadiationEstpersistant2, HIGH);
            BlueRadiationEstpersistant2 = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          AutoPipes();
          UpdateSubState();
          break;
        case DOWN:
          val = analogRead(BluekeypadEngiSouth); //value for 6 buttons wired with 270 Ohms resistors
          //Serial.println(val);
          if ((val <= 50)) {
            Offset = val - Borne0;
          } else if ((val >= Borne1 + Offset + BorneMin) && (val <= Borne1 + Offset + BorneMax) && (BlueWeaponSudAutopipe == 0))             {
            digitalWrite(BluePinLedWeaponSudAutopipe, HIGH);
            BlueWeaponSudAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne2 + Offset + BorneMin) && (val <= Borne2 + Offset + BorneMax) && (BlueDetectionSudAutopipe == 0))    {
            digitalWrite(BluePinLedDetectionSudAutopipe, HIGH);
            BlueDetectionSudAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne3 + Offset + Borne3Min) && (val <= Borne3 + Offset + Borne3Max) && (BlueSpecialSudAutopipe == 0))   {
            digitalWrite(BluePinLedSpecialSudAutopipe, HIGH);
            BlueSpecialSudAutopipe = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne4 + Offset + BornePermaMin) && (val <= Borne4 + Offset + BornePermaMax) && (BlueWeaponSudpersistant == 0)) {
            digitalWrite(BluePinLedWeaponSudpersistant, HIGH);
            BlueWeaponSudpersistant = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne5 + Offset + BornePermaMin) && (val <= Borne5 + Offset + BornePermaMax) && (BlueRadiationSudpersistant == 0)) {
            digitalWrite(BluePinLedRadiationSudpersistant, HIGH);
            BlueRadiationSudpersistant = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          else if ((val >= Borne6 + Offset + BornePermaMin) && (val <= Borne6 + Offset + BornePermaMax) && (BlueSpecialSudpersistant == 0)) {
            digitalWrite(BluePinLedSpecialSudpersistant, HIGH);
            BlueSpecialSudpersistant = 1;
            BlueLastDirection = NONE;
            BlueEngineerDamage = 0;
          }
          AutoPipes();
          UpdateSubState();
          break;
      }
      BluepreviousButtonMillisEngi += buttonInterval;
    }
  }
}
//Yellow
void getKeyEngiYellow()   //Reads the input from the board of the Engi, light up the damaged module if needed and resolve the move for the Engi action
{
  long val = 0;
  if (YellowEngineerDamage == 0) {          //If the Engineer isn't supposed to allocate a damage on a module, no need to read the inputs.

  } else {
    if (currentMillis - YellowpreviousButtonMillisEngi >= buttonInterval) {  //Reading every 'buttonInterval' milliseconds
      switch (YellowLastDirection) {
        case LEFT:
          val = analogRead(YellowkeypadEngiWest); //value for 6 buttons wired with 1KOhms resistors
          if ((val <= 50)) {
            Offset = val - Borne0; Serial.print("Offset : "); Serial.println(Offset);
          } else if ((val >= Borne1 + Offset + BorneMin) && (val <= Borne1 + Offset + BorneMax) && (YellowWeaponWestAutopipe == 0))             {
            digitalWrite(YellowPinLedWeaponWestAutopipe, HIGH);
            YellowWeaponWestAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne2 + Offset + BorneMin) && (val <= Borne2 + Offset + BorneMax) && (YellowSpecialWestAutopipe == 0))    {
            digitalWrite(YellowPinLedSpecialWestAutopipe, HIGH);
            YellowSpecialWestAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne3 + Offset + Borne3Min) && (val <= Borne3 + Offset + Borne3Max) && (YellowDetectionWestAutopipe == 0))   {
            digitalWrite(YellowPinLedDetectionWestAutopipe, HIGH);
            YellowDetectionWestAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne4 + Offset + BornePermaMin) && (val <= Borne4 + Offset + BornePermaMax) && (YellowRadiationWestpersistant1 == 0)) {
            digitalWrite(YellowPinLedRadiationWestpersistant1, HIGH);
            YellowRadiationWestpersistant1 = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne5 + Offset + BornePermaMin) && (val <= Borne5 + Offset + BornePermaMax) && (YellowRadiationWestpersistant2 == 0)) {
            digitalWrite(YellowPinLedRadiationWestpersistant2, HIGH);
            YellowRadiationWestpersistant2 = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne6 + Offset + BornePermaMin) && (val <= Borne6 + Offset + BornePermaMax) && (YellowDetectionWestpersistant == 0)) {
            digitalWrite(YellowPinLedDetectionWestpersistant, HIGH);
            YellowDetectionWestpersistant = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          AutoPipes();
          UpdateSubState();
          break;
        case UP:
          val = analogRead(YellowkeypadEngiNorth);
          if ((val <= 50)) {
            Offset = val - Borne0; Serial.print("Offset : "); Serial.println(Offset);
          } else if ((val >= Borne1 + Offset + BorneMin) && (val <= Borne1 + Offset + BorneMax) && (YellowWeaponNorthAutopipe == 0))             {
            digitalWrite(YellowPinLedWeaponNorthAutopipe, HIGH);
            YellowWeaponNorthAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne2 + Offset + BorneMin) && (val <= Borne2 + Offset + BorneMax) && (YellowSpecialNorthAutopipe1 == 0))    {
            digitalWrite(YellowPinLedSpecialNorthAutopipe1, HIGH);
            YellowSpecialNorthAutopipe1 = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne3 + Offset + Borne3Min) && (val <= Borne3 + Offset + Borne3Max) && (YellowSpecialNorthAutopipe2 == 0))   {
            digitalWrite(YellowPinLedSpecialNorthAutopipe2, HIGH);
            YellowSpecialNorthAutopipe2 = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne4 + Offset + BornePermaMin) && (val <= Borne4 + Offset + BornePermaMax) && (YellowDetectionNorthpersistant == 0)) {
            digitalWrite(YellowPinLedDetectionNorthpersistant, HIGH);
            YellowDetectionNorthpersistant = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne5 + Offset + BornePermaMin) && (val <= Borne5 + Offset + BornePermaMax) && (YellowWeaponNorthpersistant == 0)) {
            digitalWrite(YellowPinLedWeaponNorthpersistant, HIGH);
            YellowWeaponNorthpersistant = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne6 + Offset + BornePermaMin) && (val <= Borne6 + Offset + BornePermaMax) && (YellowRadiationNorthpersistant == 0)) {
            digitalWrite(YellowPinLedRadiationNorthpersistant, HIGH);
            YellowRadiationNorthpersistant = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          AutoPipes();
          UpdateSubState();
          break;
        case RIGHT:
          val = analogRead(YellowkeypadEngiEast);
          if ((val <= 50)) {
            Offset = val - Borne0; Serial.print("Offset : "); Serial.println(Offset);
          } else if ((val >= Borne1 + Offset + BorneMin) && (val <= Borne1 + Offset + BorneMax) && (YellowWeaponEstAutopipe == 0))             {
            digitalWrite(YellowPinLedWeaponEstAutopipe, HIGH);
            YellowWeaponEstAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne2 + Offset + BorneMin) && (val <= Borne2 + Offset + BorneMax) && (YellowDetectionEstAutopipe == 0))    {
            digitalWrite(YellowPinLedDetectionEstAutopipe, HIGH);
            YellowDetectionEstAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne3 + Offset + Borne3Min) && (val <= Borne3 + Offset + Borne3Max) && (YellowSpecialEstAutopipe == 0))   {
            digitalWrite(YellowPinLedSpecialEstAutopipe, HIGH);
            YellowSpecialEstAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne4 + Offset + BornePermaMin) && (val <= Borne4 + Offset + BornePermaMax) && (YellowDetectionEstpersistant == 0)) {
            digitalWrite(YellowPinLedDetectionEstpersistant, HIGH);
            YellowDetectionEstpersistant = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne5 + Offset + BornePermaMin) && (val <= Borne5 + Offset + BornePermaMax) && (YellowRadiationEstpersistant1 == 0)) {
            digitalWrite(YellowPinLedRadiationEstpersistant1, HIGH);
            YellowRadiationEstpersistant1 = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne6 + Offset + BornePermaMin) && (val <= Borne6 + Offset + BornePermaMax) && (YellowRadiationEstpersistant2 == 0)) {
            digitalWrite(YellowPinLedRadiationEstpersistant2, HIGH);
            YellowRadiationEstpersistant2 = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          AutoPipes();
          UpdateSubState();
          break;
        case DOWN:
          val = analogRead(YellowkeypadEngiSouth); //value for 6 buttons wired with 270 Ohms resistors
          if ((val <= 50)) {
            Offset = val - Borne0; Serial.print("Offset : "); Serial.println(Offset);
          } else if ((val >= Borne1 + Offset + BorneMin) && (val <= Borne1 + Offset + BorneMax) && (YellowWeaponSudAutopipe == 0))             {
            digitalWrite(YellowPinLedWeaponSudAutopipe, HIGH);
            YellowWeaponSudAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne2 + Offset + BorneMin) && (val <= Borne2 + Offset + BorneMax) && (YellowDetectionSudAutopipe == 0))    {
            digitalWrite(YellowPinLedDetectionSudAutopipe, HIGH);
            YellowDetectionSudAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne3 + Offset + Borne3Min) && (val <= Borne3 + Offset + Borne3Max) && (YellowSpecialSudAutopipe == 0))   {
            digitalWrite(YellowPinLedSpecialSudAutopipe, HIGH);
            YellowSpecialSudAutopipe = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne4 + Offset + BornePermaMin) && (val <= Borne4 + Offset + BornePermaMax) && (YellowWeaponSudpersistant == 0)) {
            digitalWrite(YellowPinLedWeaponSudpersistant, HIGH);
            YellowWeaponSudpersistant = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne5 + Offset + BornePermaMin) && (val <= Borne5 + Offset + BornePermaMax) && (YellowRadiationSudpersistant == 0)) {
            digitalWrite(YellowPinLedRadiationSudpersistant, HIGH);
            YellowRadiationSudpersistant = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          else if ((val >= Borne6 + Offset + BornePermaMin) && (val <= Borne6 + Offset + BornePermaMax) && (YellowSpecialSudpersistant == 0)) {
            digitalWrite(YellowPinLedSpecialSudpersistant, HIGH);
            YellowSpecialSudpersistant = 1;
            YellowLastDirection = NONE;
            YellowEngineerDamage = 0;
          }
          AutoPipes();
          UpdateSubState();
          break;
      }
      YellowpreviousButtonMillisEngi += buttonInterval;
    }
  }
}

void AutoPipes() {
  if ((BlueWeaponWestAutopipe == 1) && (BlueSpecialWestAutopipe == 1) &&   //West Autopipe
      (BlueDetectionWestAutopipe == 1) && (BlueWeaponEstAutopipe == 1)) {
    digitalWrite(BluePinLedWeaponWestAutopipe, LOW);
    BlueWeaponWestAutopipe = 0;
    digitalWrite(BluePinLedSpecialWestAutopipe, LOW);
    BlueSpecialWestAutopipe = 0;
    digitalWrite(BluePinLedDetectionWestAutopipe, LOW);
    BlueDetectionWestAutopipe = 0;
    digitalWrite(BluePinLedWeaponEstAutopipe, LOW);
    BlueWeaponEstAutopipe = 0;
  } else if ((BlueWeaponNorthAutopipe == 1) && (BlueSpecialNorthAutopipe1 == 1)   //North Autopipe
             && (BlueSpecialNorthAutopipe2 == 1) && (BlueDetectionEstAutopipe == 1)) {
    digitalWrite(BluePinLedWeaponNorthAutopipe, LOW);
    BlueWeaponNorthAutopipe = 0;
    digitalWrite(BluePinLedSpecialNorthAutopipe1, LOW);
    BlueSpecialNorthAutopipe1 = 0;
    digitalWrite(BluePinLedSpecialNorthAutopipe2, LOW);
    BlueSpecialNorthAutopipe2 = 0;
    digitalWrite(BluePinLedDetectionEstAutopipe, LOW);
    BlueDetectionEstAutopipe = 0;
  } else if ((BlueWeaponSudAutopipe == 1) && (BlueDetectionSudAutopipe == 1)   //South Autopipe
             && (BlueSpecialSudAutopipe == 1) && (BlueSpecialEstAutopipe == 1)) {
    digitalWrite(BluePinLedWeaponSudAutopipe, LOW);
    BlueWeaponSudAutopipe = 0;
    digitalWrite(BluePinLedDetectionSudAutopipe, LOW);
    BlueDetectionSudAutopipe = 0;
    digitalWrite(BluePinLedSpecialSudAutopipe, LOW);
    BlueSpecialSudAutopipe = 0;
    digitalWrite(BluePinLedSpecialEstAutopipe, LOW);
    BlueSpecialEstAutopipe = 0;
  } else if ((BlueRadiationWestpersistant1 == 1) && (BlueRadiationWestpersistant2 == 1) //Radiation Damage
             && (BlueRadiationNorthpersistant == 1) && (BlueRadiationSudpersistant == 1) \
             && (BlueRadiationEstpersistant1 == 1) && (BlueRadiationEstpersistant2 == 1)) {
    BlueWeaponWestAutopipe = 0;
    BlueDetectionWestAutopipe = 0;
    BlueSpecialWestAutopipe = 0;
    BlueDetectionWestpersistant = 0;
    BlueRadiationWestpersistant1 = 0;
    BlueRadiationWestpersistant2 = 0;
    BlueWeaponNorthAutopipe = 0;
    BlueSpecialNorthAutopipe1 = 0;
    BlueSpecialNorthAutopipe2 = 0;
    BlueDetectionNorthpersistant = 0;
    BlueWeaponNorthpersistant = 0;
    BlueRadiationNorthpersistant = 0;
    BlueWeaponSudAutopipe = 0;
    BlueDetectionSudAutopipe = 0;
    BlueSpecialSudAutopipe = 0;
    BlueWeaponSudpersistant = 0;
    BlueRadiationSudpersistant = 0;
    BlueSpecialSudpersistant = 0;
    BlueWeaponEstAutopipe = 0;
    BlueDetectionEstAutopipe = 0;
    BlueSpecialEstAutopipe = 0;
    BlueDetectionEstpersistant = 0;
    BlueRadiationEstpersistant1 = 0;
    BlueRadiationEstpersistant2 = 0;
    BlueEngiLedLow();
    BlueSubDamage = BlueSubDamage + 1;
    CheckDamage();
  } else if ((BlueWeaponWestAutopipe == 1) && (BlueDetectionWestAutopipe == 1) && (BlueSpecialWestAutopipe == 1) && \
             (BlueDetectionWestpersistant == 1) && (BlueRadiationWestpersistant1 == 1) && (BlueRadiationWestpersistant2 == 1)) { //All West is damaged
    BlueWeaponWestAutopipe = 0;
    BlueDetectionWestAutopipe = 0;
    BlueSpecialWestAutopipe = 0;
    BlueDetectionWestpersistant = 0;
    BlueRadiationWestpersistant1 = 0;
    BlueRadiationWestpersistant2 = 0;
    BlueWeaponNorthAutopipe = 0;
    BlueSpecialNorthAutopipe1 = 0;
    BlueSpecialNorthAutopipe2 = 0;
    BlueDetectionNorthpersistant = 0;
    BlueWeaponNorthpersistant = 0;
    BlueRadiationNorthpersistant = 0;
    BlueWeaponSudAutopipe = 0;
    BlueDetectionSudAutopipe = 0;
    BlueSpecialSudAutopipe = 0;
    BlueWeaponSudpersistant = 0;
    BlueRadiationSudpersistant = 0;
    BlueSpecialSudpersistant = 0;
    BlueWeaponEstAutopipe = 0;
    BlueDetectionEstAutopipe = 0;
    BlueSpecialEstAutopipe = 0;
    BlueDetectionEstpersistant = 0;
    BlueRadiationEstpersistant1 = 0;
    BlueRadiationEstpersistant2 = 0;
    BlueEngiLedLow();
    BlueSubDamage = BlueSubDamage + 1;
    CheckDamage();
  } else if ((BlueWeaponNorthAutopipe == 1) && (BlueSpecialNorthAutopipe2 == 1) && (BlueSpecialNorthAutopipe1 == 1) && \
             (BlueRadiationNorthpersistant == 1) && (BlueWeaponNorthpersistant == 1) && (BlueDetectionNorthpersistant == 1)) { //All North is damaged
    BlueWeaponWestAutopipe = 0;
    BlueDetectionWestAutopipe = 0;
    BlueSpecialWestAutopipe = 0;
    BlueDetectionWestpersistant = 0;
    BlueRadiationWestpersistant1 = 0;
    BlueRadiationWestpersistant2 = 0;
    BlueWeaponNorthAutopipe = 0;
    BlueSpecialNorthAutopipe1 = 0;
    BlueSpecialNorthAutopipe2 = 0;
    BlueDetectionNorthpersistant = 0;
    BlueWeaponNorthpersistant = 0;
    BlueRadiationNorthpersistant = 0;
    BlueWeaponSudAutopipe = 0;
    BlueDetectionSudAutopipe = 0;
    BlueSpecialSudAutopipe = 0;
    BlueWeaponSudpersistant = 0;
    BlueRadiationSudpersistant = 0;
    BlueSpecialSudpersistant = 0;
    BlueWeaponEstAutopipe = 0;
    BlueDetectionEstAutopipe = 0;
    BlueSpecialEstAutopipe = 0;
    BlueDetectionEstpersistant = 0;
    BlueRadiationEstpersistant1 = 0;
    BlueRadiationEstpersistant2 = 0;
    BlueEngiLedLow();
    BlueSubDamage = BlueSubDamage + 1;
    CheckDamage();
  } else if ((BlueWeaponSudAutopipe == 1) && (BlueDetectionSudAutopipe == 1) && (BlueSpecialSudAutopipe == 1) && \
             (BlueWeaponSudpersistant == 1) && (BlueRadiationSudpersistant == 1) && (BlueSpecialSudpersistant == 1)) { //All South is damaged
    BlueWeaponWestAutopipe = 0;
    BlueDetectionWestAutopipe = 0;
    BlueSpecialWestAutopipe = 0;
    BlueDetectionWestpersistant = 0;
    BlueRadiationWestpersistant1 = 0;
    BlueRadiationWestpersistant2 = 0;
    BlueWeaponNorthAutopipe = 0;
    BlueSpecialNorthAutopipe1 = 0;
    BlueSpecialNorthAutopipe2 = 0;
    BlueDetectionNorthpersistant = 0;
    BlueWeaponNorthpersistant = 0;
    BlueRadiationNorthpersistant = 0;
    BlueWeaponSudAutopipe = 0;
    BlueDetectionSudAutopipe = 0;
    BlueSpecialSudAutopipe = 0;
    BlueWeaponSudpersistant = 0;
    BlueRadiationSudpersistant = 0;
    BlueSpecialSudpersistant = 0;
    BlueWeaponEstAutopipe = 0;
    BlueDetectionEstAutopipe = 0;
    BlueSpecialEstAutopipe = 0;
    BlueDetectionEstpersistant = 0;
    BlueRadiationEstpersistant1 = 0;
    BlueRadiationEstpersistant2 = 0;
    BlueEngiLedLow();
    BlueSubDamage = BlueSubDamage + 1;
    CheckDamage();
  } else if ((BlueWeaponEstAutopipe == 1) && (BlueDetectionEstAutopipe == 1) && (BlueSpecialEstAutopipe == 1) && \
             (BlueDetectionEstpersistant == 1) && (BlueRadiationEstpersistant1 == 1) && (BlueRadiationEstpersistant2 == 1)) { //All East is damaged
    BlueWeaponWestAutopipe = 0;
    BlueDetectionWestAutopipe = 0;
    BlueSpecialWestAutopipe = 0;
    BlueDetectionWestpersistant = 0;
    BlueRadiationWestpersistant1 = 0;
    BlueRadiationWestpersistant2 = 0;
    BlueWeaponNorthAutopipe = 0;
    BlueSpecialNorthAutopipe1 = 0;
    BlueSpecialNorthAutopipe2 = 0;
    BlueDetectionNorthpersistant = 0;
    BlueWeaponNorthpersistant = 0;
    BlueRadiationNorthpersistant = 0;
    BlueWeaponSudAutopipe = 0;
    BlueDetectionSudAutopipe = 0;
    BlueSpecialSudAutopipe = 0;
    BlueWeaponSudpersistant = 0;
    BlueRadiationSudpersistant = 0;
    BlueSpecialSudpersistant = 0;
    BlueWeaponEstAutopipe = 0;
    BlueDetectionEstAutopipe = 0;
    BlueSpecialEstAutopipe = 0;
    BlueDetectionEstpersistant = 0;
    BlueRadiationEstpersistant1 = 0;
    BlueRadiationEstpersistant2 = 0;
    BlueEngiLedLow();
    BlueSubDamage = BlueSubDamage + 1;
    CheckDamage();
  }
  if ((YellowWeaponWestAutopipe == 1) && (YellowSpecialWestAutopipe == 1) &&   //West Autopipe
      (YellowDetectionWestAutopipe == 1) && (YellowWeaponEstAutopipe == 1)) {
    digitalWrite(YellowPinLedWeaponWestAutopipe, LOW);
    YellowWeaponWestAutopipe = 0;
    digitalWrite(YellowPinLedSpecialWestAutopipe, LOW);
    YellowSpecialWestAutopipe = 0;
    digitalWrite(YellowPinLedDetectionWestAutopipe, LOW);
    YellowDetectionWestAutopipe = 0;
    digitalWrite(YellowPinLedWeaponEstAutopipe, LOW);
    YellowWeaponEstAutopipe = 0;
  } else if ((YellowWeaponNorthAutopipe == 1) && (YellowSpecialNorthAutopipe1 == 1)   //North Autopipe
             && (YellowSpecialNorthAutopipe2 == 1) && (YellowDetectionEstAutopipe == 1)) {
    digitalWrite(YellowPinLedWeaponNorthAutopipe, LOW);
    YellowWeaponNorthAutopipe = 0;
    digitalWrite(YellowPinLedSpecialNorthAutopipe1, LOW);
    YellowSpecialNorthAutopipe1 = 0;
    digitalWrite(YellowPinLedSpecialNorthAutopipe2, LOW);
    YellowSpecialNorthAutopipe2 = 0;
    digitalWrite(YellowPinLedDetectionEstAutopipe, LOW);
    YellowDetectionEstAutopipe = 0;
  } else if ((YellowWeaponSudAutopipe == 1) && (YellowDetectionSudAutopipe == 1)   //South Autopipe
             && (YellowSpecialSudAutopipe == 1) && (YellowSpecialEstAutopipe == 1)) {
    digitalWrite(YellowPinLedWeaponSudAutopipe, LOW);
    YellowWeaponSudAutopipe = 0;
    digitalWrite(YellowPinLedDetectionSudAutopipe, LOW);
    YellowDetectionSudAutopipe = 0;
    digitalWrite(YellowPinLedSpecialSudAutopipe, LOW);
    YellowSpecialSudAutopipe = 0;
    digitalWrite(YellowPinLedSpecialEstAutopipe, LOW);
    YellowSpecialEstAutopipe = 0;
  } else if ((YellowRadiationWestpersistant1 == 1) && (YellowRadiationWestpersistant2 == 1) //Radiation Damage
             && (YellowRadiationNorthpersistant == 1) && (YellowRadiationSudpersistant == 1) \
             && (YellowRadiationEstpersistant1 == 1) && (YellowRadiationEstpersistant2 == 1)) {
    YellowWeaponWestAutopipe = 0;
    YellowDetectionWestAutopipe = 0;
    YellowSpecialWestAutopipe = 0;
    YellowDetectionWestpersistant = 0;
    YellowRadiationWestpersistant1 = 0;
    YellowRadiationWestpersistant2 = 0;
    YellowWeaponNorthAutopipe = 0;
    YellowSpecialNorthAutopipe1 = 0;
    YellowSpecialNorthAutopipe2 = 0;
    YellowDetectionNorthpersistant = 0;
    YellowWeaponNorthpersistant = 0;
    YellowRadiationNorthpersistant = 0;
    YellowWeaponSudAutopipe = 0;
    YellowDetectionSudAutopipe = 0;
    YellowSpecialSudAutopipe = 0;
    YellowWeaponSudpersistant = 0;
    YellowRadiationSudpersistant = 0;
    YellowSpecialSudpersistant = 0;
    YellowWeaponEstAutopipe = 0;
    YellowDetectionEstAutopipe = 0;
    YellowSpecialEstAutopipe = 0;
    YellowDetectionEstpersistant = 0;
    YellowRadiationEstpersistant1 = 0;
    YellowRadiationEstpersistant2 = 0;
    YellowEngiLedLow();
    YellowSubDamage = YellowSubDamage + 1;
    CheckDamage();
  } else if ((YellowWeaponWestAutopipe == 1) && (YellowDetectionWestAutopipe == 1) && (YellowSpecialWestAutopipe == 1) && \
             (YellowDetectionWestpersistant == 1) && (YellowRadiationWestpersistant1 == 1) && (YellowRadiationWestpersistant2 == 1)) { //All West is damaged
    YellowWeaponWestAutopipe = 0;
    YellowDetectionWestAutopipe = 0;
    YellowSpecialWestAutopipe = 0;
    YellowDetectionWestpersistant = 0;
    YellowRadiationWestpersistant1 = 0;
    YellowRadiationWestpersistant2 = 0;
    YellowWeaponNorthAutopipe = 0;
    YellowSpecialNorthAutopipe1 = 0;
    YellowSpecialNorthAutopipe2 = 0;
    YellowDetectionNorthpersistant = 0;
    YellowWeaponNorthpersistant = 0;
    YellowRadiationNorthpersistant = 0;
    YellowWeaponSudAutopipe = 0;
    YellowDetectionSudAutopipe = 0;
    YellowSpecialSudAutopipe = 0;
    YellowWeaponSudpersistant = 0;
    YellowRadiationSudpersistant = 0;
    YellowSpecialSudpersistant = 0;
    YellowWeaponEstAutopipe = 0;
    YellowDetectionEstAutopipe = 0;
    YellowSpecialEstAutopipe = 0;
    YellowDetectionEstpersistant = 0;
    YellowRadiationEstpersistant1 = 0;
    YellowRadiationEstpersistant2 = 0;
    YellowEngiLedLow();
    YellowSubDamage = YellowSubDamage + 1;
    CheckDamage();
  } else if ((YellowWeaponNorthAutopipe == 1) && (YellowSpecialNorthAutopipe2 == 1) && (YellowSpecialNorthAutopipe1 == 1) && \
             (YellowRadiationNorthpersistant == 1) && (YellowWeaponNorthpersistant == 1) && (YellowDetectionNorthpersistant == 1)) { //All North is damaged
    YellowWeaponWestAutopipe = 0;
    YellowDetectionWestAutopipe = 0;
    YellowSpecialWestAutopipe = 0;
    YellowDetectionWestpersistant = 0;
    YellowRadiationWestpersistant1 = 0;
    YellowRadiationWestpersistant2 = 0;
    YellowWeaponNorthAutopipe = 0;
    YellowSpecialNorthAutopipe1 = 0;
    YellowSpecialNorthAutopipe2 = 0;
    YellowDetectionNorthpersistant = 0;
    YellowWeaponNorthpersistant = 0;
    YellowRadiationNorthpersistant = 0;
    YellowWeaponSudAutopipe = 0;
    YellowDetectionSudAutopipe = 0;
    YellowSpecialSudAutopipe = 0;
    YellowWeaponSudpersistant = 0;
    YellowRadiationSudpersistant = 0;
    YellowSpecialSudpersistant = 0;
    YellowWeaponEstAutopipe = 0;
    YellowDetectionEstAutopipe = 0;
    YellowSpecialEstAutopipe = 0;
    YellowDetectionEstpersistant = 0;
    YellowRadiationEstpersistant1 = 0;
    YellowRadiationEstpersistant2 = 0;
    YellowEngiLedLow();
    YellowSubDamage = YellowSubDamage + 1;
    CheckDamage();
  } else if ((YellowWeaponSudAutopipe == 1) && (YellowDetectionSudAutopipe == 1) && (YellowSpecialSudAutopipe == 1) && \
             (YellowWeaponSudpersistant == 1) && (YellowRadiationSudpersistant == 1) && (YellowSpecialSudpersistant == 1)) { //All South is damaged
    YellowWeaponWestAutopipe = 0;
    YellowDetectionWestAutopipe = 0;
    YellowSpecialWestAutopipe = 0;
    YellowDetectionWestpersistant = 0;
    YellowRadiationWestpersistant1 = 0;
    YellowRadiationWestpersistant2 = 0;
    YellowWeaponNorthAutopipe = 0;
    YellowSpecialNorthAutopipe1 = 0;
    YellowSpecialNorthAutopipe2 = 0;
    YellowDetectionNorthpersistant = 0;
    YellowWeaponNorthpersistant = 0;
    YellowRadiationNorthpersistant = 0;
    YellowWeaponSudAutopipe = 0;
    YellowDetectionSudAutopipe = 0;
    YellowSpecialSudAutopipe = 0;
    YellowWeaponSudpersistant = 0;
    YellowRadiationSudpersistant = 0;
    YellowSpecialSudpersistant = 0;
    YellowWeaponEstAutopipe = 0;
    YellowDetectionEstAutopipe = 0;
    YellowSpecialEstAutopipe = 0;
    YellowDetectionEstpersistant = 0;
    YellowRadiationEstpersistant1 = 0;
    YellowRadiationEstpersistant2 = 0;
    YellowEngiLedLow();
    YellowSubDamage = YellowSubDamage + 1;
    CheckDamage();
  } else if ((YellowWeaponEstAutopipe == 1) && (YellowDetectionEstAutopipe == 1) && (YellowSpecialEstAutopipe == 1) && \
             (YellowDetectionEstpersistant == 1) && (YellowRadiationEstpersistant1 == 1) && (YellowRadiationEstpersistant2 == 1)) { //All East is damaged
    YellowWeaponWestAutopipe = 0;
    YellowDetectionWestAutopipe = 0;
    YellowSpecialWestAutopipe = 0;
    YellowDetectionWestpersistant = 0;
    YellowRadiationWestpersistant1 = 0;
    YellowRadiationWestpersistant2 = 0;
    YellowWeaponNorthAutopipe = 0;
    YellowSpecialNorthAutopipe1 = 0;
    YellowSpecialNorthAutopipe2 = 0;
    YellowDetectionNorthpersistant = 0;
    YellowWeaponNorthpersistant = 0;
    YellowRadiationNorthpersistant = 0;
    YellowWeaponSudAutopipe = 0;
    YellowDetectionSudAutopipe = 0;
    YellowSpecialSudAutopipe = 0;
    YellowWeaponSudpersistant = 0;
    YellowRadiationSudpersistant = 0;
    YellowSpecialSudpersistant = 0;
    YellowWeaponEstAutopipe = 0;
    YellowDetectionEstAutopipe = 0;
    YellowSpecialEstAutopipe = 0;
    YellowDetectionEstpersistant = 0;
    YellowRadiationEstpersistant1 = 0;
    YellowRadiationEstpersistant2 = 0;
    YellowEngiLedLow();
    YellowSubDamage = YellowSubDamage + 1;
    CheckDamage();
  }
}

//Function for modules
void MineBlue() {
  int y = 0;
  int x = 0;
  if ((BlueMine.col == 0) && (BlueModuleEngaged == NONE)) {
    Serial.println("Entrez coord Mine");
    Serial.print("Colonne : ");
    Bluelcd.setCursor(0, 1);
    Bluelcd.print("Coord Mine :        ");
    BlueModuleEngaged = MINE;
    BlueCoordDebounce = currentMillis;
  } else if (BlueMine.col == 0) {
    if (currentMillis >= BlueCoordDebounce) {
      switch (BlueCapPad) {
        case 1 :
          BlueMine.col = 65;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 2 :
          BlueMine.col = 66;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 3 :
          BlueMine.col = 67;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 4 :
          BlueMine.col = 68;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 5 :
          BlueMine.col = 69;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 6 :
          BlueMine.col = 70;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 7 :
          BlueMine.col = 71;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 8 :
          BlueMine.col = 72;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 9 :
          BlueMine.col = 73;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 10 :
          BlueMine.col = 74;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 11:
          BlueMine.col = 75;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 12 :
          BlueMine.col = 76;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 13 :
          BlueMine.col = 77;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 14 :
          BlueMine.col = 78;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 15 :
          BlueMine.col = 79;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(13, 1);
          Bluelcd.print(BlueMine.col);
          break;
      }
      if (BlueMine.col != 0) {
        BlueCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((BlueMine.line == 0) && (BlueMine.col != 0)) {
    //revenir
    if (currentMillis >= BlueCoordDebounce) {
      switch (BlueCapPad) {
        case 1 :
          BlueMine.line = 1;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 2 :
          BlueMine.line = 2;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 3 :
          BlueMine.line = 3;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 4 :
          BlueMine.line = 4;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 5 :
          BlueMine.line = 5;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 6 :
          BlueMine.line = 6;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 7 :
          BlueMine.line = 7;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 8 :
          BlueMine.line = 8;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 9 :
          BlueMine.line = 9;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 10 :
          BlueMine.line = 10;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 11:
          BlueMine.line = 11;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 12 :
          BlueMine.line = 12;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 13 :
          BlueMine.line = 13;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 14 :
          BlueMine.line = 14;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 15 :
          BlueMine.line = 15;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.line);
          break;
      }
      if (BlueMine.line != 0) {
        BlueCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((BlueMine.col != 0) && (BlueMine.line != 0)) {
    //Vérifier que la Mine est dans la portée possible
    y = int(BluePosition.col) - int(BlueMine.col);
    x = BluePosition.line - BlueMine.line;
    if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1))) {
      //Vérifier que le point d'impact n'est pas une île
      for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
        if ((Islands[Map][i].col == BlueMine.col) && (Islands[Map][i].line == BlueMine.line)) {
          Serial.println("Bleu Pose Interdite (Ile)");
          Serial.println("Choisir autre coord");
          lcdResetBlue(2);
          Bluelcd.setCursor(0, 2);
          Bluelcd.print("Pose Mine interdite.");
          Bluelcd.setCursor(0, 1);
          Bluelcd.print("Coord Mine :        ");
          Serial.print("Colonne : ");
          BlueMine.col = 0;
          BlueMine.line = 0;
        } else {
        }
      }
      if ((BlueMine.col != 0) && (BlueMine.line != 0)) { //check wasn't canceled by the island
        if ((BluePastPosition[BlueMoveCount - 1].col == BlueMine.col) && (BluePastPosition[BlueMoveCount - 1].line == BlueMine.line)) { //check for the mine not being on the previous sub position
          Serial.println("Bleu Pose Interdite (chemin précédent)");
          Serial.println("Choisir autre coord");
          lcdResetBlue(2);
          Bluelcd.setCursor(0, 2);
          Bluelcd.print("Pose Mine interdite.");
          Bluelcd.setCursor(0, 1);
          Bluelcd.print("Coord Mine :        ");
          Serial.print("Colonne : ");
          BlueMine.col = 0;
          BlueMine.line = 0;
        } else {
          Serial.print("Mine bleue posée en ");
          lcdResetBlue(1);
          Bluelcd.setCursor(0, 1);
          Bluelcd.print("Mine posee :        ");
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueMine.col);
          Bluelcd.setCursor(15, 1);
          Bluelcd.print(BlueMine.line);
          Serial.print(BlueMine.col);
          Serial.println(BlueMine.line);
          BlueMineReady[BlueMineCount].line = BlueMine.line;
          BlueMineReady[BlueMineCount].col = BlueMine.col;
          BlueMineCount += 1;
          BlueModuleEngaged = NONE;
          BlueMine.col = 0;
          BlueMine.line = 0;
        }
      }
    } else {
      Serial.println("Pose Hors de portée");
      Serial.println("Choisir autre coord");
      lcdResetBlue(2);
      Bluelcd.setCursor(0, 2);
      Bluelcd.print("Pose Mine interdite.");
      Bluelcd.setCursor(0, 1);
      Bluelcd.print("Coord Mine :        ");
      Serial.print("Colonne : ");
      BlueMine.col = 0;
      BlueMine.line = 0;
    }
  }
}
//Yellow
void MineYellow() {
  int y = 0;
  int x = 0;
  if ((YellowMine.col == 0) && (YellowModuleEngaged == NONE)) {
    Serial.println("Entrez coord Mine");
    Serial.print("Colonne : ");
    Yellowlcd.setCursor(0, 1);
    Yellowlcd.print("Coord Mine :        ");
    YellowModuleEngaged = MINE;
    YellowCoordDebounce = currentMillis;
  } else if (YellowMine.col == 0) {
    if (currentMillis >= YellowCoordDebounce) {
      switch (YellowCapPad) {
        case 1 :
          YellowMine.col = 65;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 2 :
          YellowMine.col = 66;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 3 :
          YellowMine.col = 67;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 4 :
          YellowMine.col = 68;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 5 :
          YellowMine.col = 69;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 6 :
          YellowMine.col = 70;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 7 :
          YellowMine.col = 71;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 8 :
          YellowMine.col = 72;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 9 :
          YellowMine.col = 73;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 10 :
          YellowMine.col = 74;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 11:
          YellowMine.col = 75;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 12 :
          YellowMine.col = 76;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 13 :
          YellowMine.col = 77;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 14 :
          YellowMine.col = 78;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 15 :
          YellowMine.col = 79;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(13, 1);
          Yellowlcd.print(YellowMine.col);
          break;
      }
      if (YellowMine.col != 0) {
        YellowCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((YellowMine.line == 0) && (YellowMine.col != 0)) {
    if (currentMillis >= YellowCoordDebounce) {
      switch (YellowCapPad) {
        case 1 :
          YellowMine.line = 1;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 2 :
          YellowMine.line = 2;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 3 :
          YellowMine.line = 3;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 4 :
          YellowMine.line = 4;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 5 :
          YellowMine.line = 5;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 6 :
          YellowMine.line = 6;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 7 :
          YellowMine.line = 7;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 8 :
          YellowMine.line = 8;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 9 :
          YellowMine.line = 9;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 10 :
          YellowMine.line = 10;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 11:
          YellowMine.line = 11;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 12 :
          YellowMine.line = 12;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 13 :
          YellowMine.line = 13;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 14 :
          YellowMine.line = 14;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 15 :
          YellowMine.line = 15;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.line);
          break;
      }
      if (YellowMine.line != 0) {
        YellowCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((YellowMine.col != 0) && (YellowMine.line != 0)) {
    //Vérifier que la Mine est dans la portée possible
    y = int(YellowPosition.col) - int(YellowMine.col);
    x = YellowPosition.line - YellowMine.line;
    if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1))) {
      //Vérifier que le point d'impact n'est pas une île
      for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
        if ((Islands[Map][i].col == YellowMine.col) && (Islands[Map][i].line == YellowMine.line)) {
          Serial.println("Bleu Pose Interdite (Ile)");
          Serial.println("Choisir autre coord");
          lcdResetYellow(2);
          Yellowlcd.setCursor(0, 2);
          Yellowlcd.print("Pose Mine interdite.");
          Yellowlcd.setCursor(0, 1);
          Yellowlcd.print("Coord Mine :        ");
          Serial.print("Colonne : ");
          YellowMine.col = 0;
          YellowMine.line = 0;
        } else {
        }
      }
      if ((YellowMine.col != 0) && (YellowMine.line != 0)) { //check wasn't canceled by the island
        if ((YellowPastPosition[YellowMoveCount - 1].col == YellowMine.col) && (YellowPastPosition[YellowMoveCount - 1].line == YellowMine.line)) { //check for the mine not being on the previous sub position
          Serial.println("Bleu Pose Interdite (chemin précédent)");
          Serial.println("Choisir autre coord");
          lcdResetYellow(2);
          Yellowlcd.setCursor(0, 2);
          Yellowlcd.print("Pose Mine interdite.");
          Yellowlcd.setCursor(0, 1);
          Yellowlcd.print("Coord Mine :        ");
          Serial.print("Colonne : ");
          YellowMine.col = 0;
          YellowMine.line = 0;
        } else {
          Serial.print("Mine bleue posée en ");
          lcdResetYellow(1);
          Yellowlcd.setCursor(0, 1);
          Yellowlcd.print("Mine posee :        ");
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowMine.col);
          Yellowlcd.setCursor(15, 1);
          Yellowlcd.print(YellowMine.line);
          Serial.print(YellowMine.col);
          Serial.println(YellowMine.line);
          YellowMineReady[YellowMineCount].line = YellowMine.line;
          YellowMineReady[YellowMineCount].col = YellowMine.col;
          YellowMineCount += 1;
          YellowModuleEngaged = NONE;
          YellowMine.col = 0;
          YellowMine.line = 0;
        }
      }
    } else {
      Serial.println("Pose Hors de portée");
      Serial.println("Choisir autre coord");
      lcdResetYellow(2);
      Yellowlcd.setCursor(0, 2);
      Yellowlcd.print("Pose Mine interdite.");
      Yellowlcd.setCursor(0, 1);
      Yellowlcd.print("Coord Mine :        ");
      Serial.print("Colonne : ");
      YellowMine.col = 0;
      YellowMine.line = 0;
    }
  }
}

void DetonateMineBlue() {
  int x = 0;
  int y = 0;
  int i = 0;
  int ExistingMine = 0;
  //Passer en etat MineDetonate
  if ((BlueMine.col == 0) && (BlueModuleEngaged == NONE)) {
    Serial.println("Entrez Coord Mine");
    Bluelcd.setCursor(0, 1);
    Bluelcd.print("Coord Mine expl:    ");
    Serial.print("Colonne : ");
    BlueModuleEngaged = DETONATEMINE;
    BlueCoordDebounce = currentMillis;
  } else if (BlueMine.col == 0) {
    if (currentMillis >= BlueCoordDebounce) {
      switch (BlueCapPad) {
        case 1 :
          BlueMine.col = 65;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 2 :
          BlueMine.col = 66;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 3 :
          BlueMine.col = 67;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 4 :
          BlueMine.col = 68;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 5 :
          BlueMine.col = 69;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 6 :
          BlueMine.col = 70;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 7 :
          BlueMine.col = 71;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 8 :
          BlueMine.col = 72;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 9 :
          BlueMine.col = 73;
          Serial.println(BlueMine.col);
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          Serial.print("Ligne : ");
          break;
        case 10 :
          BlueMine.col = 74;
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          break;
        case 11:
          BlueMine.col = 75;
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          break;
        case 12 :
          BlueMine.col = 76;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 13 :
          BlueMine.col = 77;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 14 :
          BlueMine.col = 78;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
        case 15 :
          BlueMine.col = 79;
          Serial.println(BlueMine.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueMine.col);
          break;
      }
      if (BlueMine.col != 0) {
        BlueCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((BlueMine.line == 0) && (BlueMine.col != 0)) {
    if (currentMillis >= BlueCoordDebounce) {
      switch (BlueCapPad) {
        case 1 :
          BlueMine.line = 1;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 2 :
          BlueMine.line = 2;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 3 :
          BlueMine.line = 3;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 4 :
          BlueMine.line = 4;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 5 :
          BlueMine.line = 5;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 6 :
          BlueMine.line = 6;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 7 :
          BlueMine.line = 7;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 8 :
          BlueMine.line = 8;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 9 :
          BlueMine.line = 9;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 10 :
          BlueMine.line = 10;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 11:
          BlueMine.line = 11;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 12 :
          BlueMine.line = 12;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 13 :
          BlueMine.line = 13;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 14 :
          BlueMine.line = 14;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;
        case 15 :
          BlueMine.line = 15;
          Serial.println(BlueMine.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueMine.line);
          break;

      }
      if (BlueMine.line != 0) {
        BlueCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((BlueMine.col != 0) && (BlueMine.line != 0)) {
    for (i = 0; (i <= sizeof(BlueMineReady) / 3 - 1) || (ExistingMine == 1); i++) { //checks if mine has been planted at this coord
      if ((BlueMineReady[i].col == BlueMine.col) && (BlueMineReady[i].line == BlueMine.line)) {
        ExistingMine = 1;
        break;
      } else {
      }
    }
    if (ExistingMine == 1) {
      Serial.print("Mine explosée en ");
      Serial.print(BlueMine.col);
      Serial.println(BlueMine.line);
      lcdResetBlue(1);
      Bluelcd.setCursor(0, 1);
      Bluelcd.print("Mine explo en :    !");
      Bluelcd.setCursor(16, 1);
      Bluelcd.print(BlueMine.col);
      Bluelcd.setCursor(17, 1);
      Bluelcd.print(BlueMine.line);
      //Enlever cette mine du répertoire de mines posées
      BlueMineReady[i].col = 0;
      BlueMineReady[i].line = 0;

      y = int(BluePosition.col) - int(BlueMine.col);
      x = BluePosition.line - BlueMine.line;
      if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1)) ) {
        BlueSubDamage += 1;
        Serial.println("SM bleu allié touché !");
      } else if (abs(x) + abs(y) == 0) {
        BlueSubDamage += 2;
        Serial.println("SM bleu allié touché ! (tir direct)");
      }
      y = int(YellowPosition.col) - int(BlueMine.col);
      x = YellowPosition.line - BlueMine.line;
      if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1)) ) {
        YellowSubDamage += 1;
        Serial.println("SM bleu ennemi touché !");
      } else if (abs(x) + abs(y) == 0) {
        YellowSubDamage += 2;
        Serial.println("SM bleu ennemi touché (tir direct)!");
      }
      BlueModuleEngaged = NONE;
      BlueMine.col = 0;
      BlueMine.line = 0;
    } else {
      Serial.println("Pas de mine ici");
      lcdResetBlue(1);
      Bluelcd.setCursor(0, 1);
      Bluelcd.print("Pas de mine ici.    ");
      Serial.println("Annulation");
      lcdResetBlue(2);
      Bluelcd.setCursor(0, 2);
      Bluelcd.print("Annulation de l'xpls");
      BlueModuleEngaged = NONE;
      BlueMine.col = 0;
      BlueMine.line = 0;
    }
  }
}
//Yellow
void DetonateMineYellow() {
  int x = 0;
  int y = 0;
  int i = 0;
  int ExistingMine = 0;
  //Passer en etat MineDetonate
  if ((YellowMine.col == 0) && (YellowModuleEngaged == NONE)) {
    Serial.println("Entrez Coord Mine (Yellow)");
    Yellowlcd.setCursor(0, 1);
    Yellowlcd.print("Coord Mine expl:    ");
    Serial.print("Colonne : ");
    YellowModuleEngaged = DETONATEMINE;
    YellowCoordDebounce = currentMillis;
  } else if (YellowMine.col == 0) {
    if (currentMillis >= YellowCoordDebounce) {
      switch (YellowCapPad) {
        case 1 :
          YellowMine.col = 65;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 2 :
          YellowMine.col = 66;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 3 :
          YellowMine.col = 67;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 4 :
          YellowMine.col = 68;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 5 :
          YellowMine.col = 69;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 6 :
          YellowMine.col = 70;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 7 :
          YellowMine.col = 71;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 8 :
          YellowMine.col = 72;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 9 :
          YellowMine.col = 73;
          Serial.println(YellowMine.col);
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          Serial.print("Ligne : ");
          break;
        case 10 :
          YellowMine.col = 74;
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          break;
        case 11:
          YellowMine.col = 75;
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          break;
        case 12 :
          YellowMine.col = 76;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 13 :
          YellowMine.col = 77;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 14 :
          YellowMine.col = 78;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
        case 15 :
          YellowMine.col = 79;
          Serial.println(YellowMine.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowMine.col);
          break;
      }
      if (YellowMine.col != 0) {
        YellowCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((YellowMine.line == 0) && (YellowMine.col != 0)) {
    if (currentMillis >= YellowCoordDebounce) {
      switch (YellowCapPad) {
        case 1 :
          YellowMine.line = 1;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 2 :
          YellowMine.line = 2;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 3 :
          YellowMine.line = 3;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 4 :
          YellowMine.line = 4;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 5 :
          YellowMine.line = 5;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 6 :
          YellowMine.line = 6;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 7 :
          YellowMine.line = 7;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 8 :
          YellowMine.line = 8;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 9 :
          YellowMine.line = 9;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 10 :
          YellowMine.line = 10;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 11:
          YellowMine.line = 11;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 12 :
          YellowMine.line = 12;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 13 :
          YellowMine.line = 13;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 14 :
          YellowMine.line = 14;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
        case 15 :
          YellowMine.line = 15;
          Serial.println(YellowMine.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowMine.line);
          break;
      }
      if (YellowMine.line != 0) {
        YellowCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((YellowMine.col != 0) && (YellowMine.line != 0)) {
    for (i = 0; (i <= sizeof(YellowMineReady) / 3 - 1) || (ExistingMine == 1); i++) { //checks if mine has been planted at this coord
      if ((YellowMineReady[i].col == YellowMine.col) && (YellowMineReady[i].line == YellowMine.line)) {
        ExistingMine = 1;
        break;
      } else {
      }
    }
    if (ExistingMine == 1) {
      Serial.print("Mine explosée en ");
      Serial.print(YellowMine.col);
      Serial.println(YellowMine.line);
      lcdResetYellow(1);
      Yellowlcd.setCursor(0, 1);
      Yellowlcd.print("Mine explo en :    !");
      Yellowlcd.setCursor(16, 1);
      Yellowlcd.print(YellowMine.col);
      Yellowlcd.setCursor(17, 1);
      Yellowlcd.print(YellowMine.line);
      //Enlever cette mine du répertoire de mines posées
      YellowMineReady[i].col = 0;
      YellowMineReady[i].line = 0;

      y = int(YellowPosition.col) - int(YellowMine.col);
      x = YellowPosition.line - YellowMine.line;
      if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1)) ) {
        YellowSubDamage += 1;
        Serial.println("SM Yellow allié touché !");
      } else if (abs(x) + abs(y) == 0) {
        YellowSubDamage += 2;
        Serial.println("SM Yellow allié touché ! (tir direct)");
      }
      y = int(BluePosition.col) - int(YellowMine.col);
      x = BluePosition.line - YellowMine.line;
      if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1)) ) {
        BlueSubDamage += 1;
        Serial.println("SM Yellow ennemi touché !");
      } else if (abs(x) + abs(y) == 0) {
        BlueSubDamage += 2;
        Serial.println("SM Yellow ennemi touché (tir direct)!");
      }
      YellowModuleEngaged = NONE;
      YellowMine.col = 0;
      YellowMine.line = 0;
    } else {
      Serial.println("Pas de mine ici");
      lcdResetYellow(1);
      Yellowlcd.setCursor(0, 1);
      Yellowlcd.print("Pas de mine ici.    ");
      Serial.println("Annulation");
      lcdResetYellow(2);
      Yellowlcd.setCursor(0, 2);
      Yellowlcd.print("Annulation de l'xpls");
      YellowModuleEngaged = NONE;
      YellowMine.col = 0;
      YellowMine.line = 0;
    }
  }
}

void TorpedoBlue() {
  int x = 0;
  int y = 0;
  if ((BlueTorpedo.col == 0) && (BlueModuleEngaged == NONE)) {
    Serial.println("Entrez coord Torpille (Blue)");
    Serial.print("Colonne : ");
    Bluelcd.setCursor(0, 1);
    Bluelcd.print("Coord Torpille :    ");
    BlueModuleEngaged = TORPEDO;
    BlueCoordDebounce = currentMillis;
  } else if (BlueTorpedo.col == 0) {
    if (currentMillis >= BlueCoordDebounce) {
      switch (BlueCapPad) {
        case 1 :
          BlueTorpedo.col = 65;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 2 :
          BlueTorpedo.col = 66;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 3 :
          BlueTorpedo.col = 67;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 4 :
          BlueTorpedo.col = 68;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 5 :
          BlueTorpedo.col = 69;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 6 :
          BlueTorpedo.col = 70;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 7 :
          BlueTorpedo.col = 71;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 8 :
          BlueTorpedo.col = 72;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 9 :
          BlueTorpedo.col = 73;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 10 :
          BlueTorpedo.col = 74;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 11:
          BlueTorpedo.col = 75;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 12 :
          BlueTorpedo.col = 76;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 13 :
          BlueTorpedo.col = 77;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 14 :
          BlueTorpedo.col = 78;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
        case 15 :
          BlueTorpedo.col = 79;
          Serial.println(BlueTorpedo.col);
          Serial.print("Ligne : ");
          Bluelcd.setCursor(17, 1);
          Bluelcd.print(BlueTorpedo.col);
          break;
      }
      if (BlueTorpedo.col != 0) {
        BlueCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((BlueTorpedo.line == 0) && (BlueTorpedo.col != 0)) {
    if (currentMillis >= BlueCoordDebounce) {
      switch (BlueCapPad) {
        case 1 :
          BlueTorpedo.line = 1;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 2 :
          BlueTorpedo.line = 2;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 3 :
          BlueTorpedo.line = 3;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 4 :
          BlueTorpedo.line = 4;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 5 :
          BlueTorpedo.line = 5;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 6 :
          BlueTorpedo.line = 6;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 7 :
          BlueTorpedo.line = 7;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 8 :
          BlueTorpedo.line = 8;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 9 :
          BlueTorpedo.line = 9;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 10 :
          BlueTorpedo.line = 10;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 11:
          BlueTorpedo.line = 11;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 12 :
          BlueTorpedo.line = 12;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 13 :
          BlueTorpedo.line = 13;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 14 :
          BlueTorpedo.line = 14;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
        case 15 :
          BlueTorpedo.line = 15;
          Serial.println(BlueTorpedo.line);
          Bluelcd.setCursor(18, 1);
          Bluelcd.print(BlueTorpedo.line);
          break;
      }
      if (BlueTorpedo.line != 0) {
        BlueCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((BlueTorpedo.col != 0) && (BlueTorpedo.line != 0)) {
    //Vérifier que la Torpille est dans la portée possible
    y = int(BluePosition.col) - int(BlueTorpedo.col);
    x = BluePosition.line - BlueTorpedo.line;
    if (abs(x) + abs(y) <= 4) {
      //Vérifier que le point d'impact n'est pas une île/bord de map
      for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
        if ((Islands[Map][i].col == BlueTorpedo.col) && (Islands[Map][i].line == BlueTorpedo.line)) {
          Serial.println("Blue Tir Interdit (Ile)");
          Serial.println("Choisir autre coord");
          lcdResetBlue(2);
          Bluelcd.setCursor(0, 2);
          Bluelcd.print("Tir interdit.       ");
          Bluelcd.setCursor(0, 1);
          Bluelcd.print("Coord Torpille :    ");
          BlueTorpedo.col = 0;
          BlueTorpedo.line = 0;
        } else {
        }
      }
      if ((BlueTorpedo.col != 0) && (BlueTorpedo.line != 0)) { //check wasn't canceled by the island
        if ((BluePosition.col == BlueTorpedo.col) && (BluePosition.line == BlueTorpedo.line)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("Blue Tir Interdit (self)");
          Serial.println("Choisir autre coord");
          lcdResetBlue(2);
          Bluelcd.setCursor(0, 2);
          Bluelcd.print("Tir interdit.       ");
          Bluelcd.setCursor(0, 1);
          Bluelcd.print("Coord Torpille :    ");
          BlueTorpedo.col = 0;
          BlueTorpedo.line = 0;
        } else {
          Serial.print("Torpille en ");
          Serial.print(BlueTorpedo.col);
          Serial.println(BlueTorpedo.line);
          lcdResetBlue(1);
          Bluelcd.setCursor(0, 1);
          Bluelcd.print("Torpille en         ");
          Bluelcd.setCursor(12, 1);
          Bluelcd.print(BlueTorpedo.col);
          Bluelcd.setCursor(14, 1);
          Bluelcd.print(BlueTorpedo.line);
          y = int(BluePosition.col) - int(BlueTorpedo.col);
          x = BluePosition.line - BlueTorpedo.line;
          if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1)) ) {
            BlueSubDamage += 1;
            Serial.println("SM Blue allié touché !");
          }
          y = int(YellowPosition.col) - int(BlueTorpedo.col);
          x = YellowPosition.line - BlueTorpedo.line;
          if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1)) ) {
            YellowSubDamage += 1;
            Serial.println("SM Blue ennemi touché !");
          } else if (abs(x) + abs(y) == 0) {
            YellowSubDamage += 2;
            Serial.println("SM Blue ennemi touché (tir direct)!");
          }
          BlueModuleEngaged = NONE;
          BlueTorpedo.col = 0;
          BlueTorpedo.line = 0;
        }
      }
    } else {
      Serial.println("Tir Hors de portée");
      Serial.println("Choisir autre coord");
      Serial.print("Colonne : ");
      lcdResetBlue(2);
      Bluelcd.setCursor(0, 2);
      Bluelcd.print("Tir hors de portee. ");
      Bluelcd.setCursor(0, 1);
      Bluelcd.print("Coord Torpille :    ");
      BlueTorpedo.col = 0;
      BlueTorpedo.line = 0;
    }
  }
}
//Yellow
void TorpedoYellow() {
  int x = 0;
  int y = 0;
  if ((YellowTorpedo.col == 0) && (YellowModuleEngaged == NONE)) {
    Serial.println("Entrez coord Torpille (Yellow)");
    Serial.print("Colonne : ");
    Yellowlcd.setCursor(0, 1);
    Yellowlcd.print("Coord Torpille :    ");
    YellowModuleEngaged = TORPEDO;
    YellowCoordDebounce = currentMillis;
  } else if (YellowTorpedo.col == 0) {
    if (currentMillis >= YellowCoordDebounce) {
      switch (YellowCapPad) {
        case 1 :
          YellowTorpedo.col = 65;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 2 :
          YellowTorpedo.col = 66;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 3 :
          YellowTorpedo.col = 67;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 4 :
          YellowTorpedo.col = 68;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 5 :
          YellowTorpedo.col = 69;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 6 :
          YellowTorpedo.col = 70;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 7 :
          YellowTorpedo.col = 71;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 8 :
          YellowTorpedo.col = 72;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 9 :
          YellowTorpedo.col = 73;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 10 :
          YellowTorpedo.col = 74;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 11:
          YellowTorpedo.col = 75;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 12 :
          YellowTorpedo.col = 76;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 13 :
          YellowTorpedo.col = 77;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 14 :
          YellowTorpedo.col = 78;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
        case 15 :
          YellowTorpedo.col = 79;
          Serial.println(YellowTorpedo.col);
          Serial.print("Ligne : ");
          Yellowlcd.setCursor(17, 1);
          Yellowlcd.print(YellowTorpedo.col);
          break;
      }
      if (YellowTorpedo.col != 0) {
        YellowCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((YellowTorpedo.line == 0) && (YellowTorpedo.col != 0)) {
    if (currentMillis >= YellowCoordDebounce) {
      switch (YellowCapPad) {
        case 1 :
          YellowTorpedo.line = 1;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 2 :
          YellowTorpedo.line = 2;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 3 :
          YellowTorpedo.line = 3;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 4 :
          YellowTorpedo.line = 4;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 5 :
          YellowTorpedo.line = 5;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 6 :
          YellowTorpedo.line = 6;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 7 :
          YellowTorpedo.line = 7;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 8 :
          YellowTorpedo.line = 8;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 9 :
          YellowTorpedo.line = 9;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 10 :
          YellowTorpedo.line = 10;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 11:
          YellowTorpedo.line = 11;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 12 :
          YellowTorpedo.line = 12;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 13 :
          YellowTorpedo.line = 13;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 14 :
          YellowTorpedo.line = 14;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
        case 15 :
          YellowTorpedo.line = 15;
          Serial.println(YellowTorpedo.line);
          Yellowlcd.setCursor(18, 1);
          Yellowlcd.print(YellowTorpedo.line);
          break;
      }
      if (YellowTorpedo.line != 0) {
        YellowCoordDebounce = currentMillis + DebounceTime;
      }
    }
  } else if ((YellowTorpedo.col != 0) && (YellowTorpedo.line != 0)) {
    //Vérifier que la Torpille est dans la portée possible
    y = int(YellowPosition.col) - int(YellowTorpedo.col);
    x = YellowPosition.line - YellowTorpedo.line;
    if (abs(x) + abs(y) <= 4) {
      //Vérifier que le point d'impact n'est pas une île/bord de map
      for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
        if ((Islands[Map][i].col == YellowTorpedo.col) && (Islands[Map][i].line == YellowTorpedo.line)) {
          Serial.println("Yellow Tir Interdit (Ile)");
          Serial.println("Choisir autre coord");
          lcdResetYellow(2);
          Yellowlcd.setCursor(0, 2);
          Yellowlcd.print("Tir interdit.       ");
          Yellowlcd.setCursor(0, 1);
          Yellowlcd.print("Coord Torpille :    ");
          YellowTorpedo.col = 0;
          YellowTorpedo.line = 0;
        } else {
        }
      }
      if ((YellowTorpedo.col != 0) && (YellowTorpedo.line != 0)) { //check wasn't canceled by the island
        if ((YellowPosition.col == YellowTorpedo.col) && (YellowPosition.line == YellowTorpedo.line)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("Yellow Tir Interdit (self)");
          Serial.println("Choisir autre coord");
          lcdResetYellow(2);
          Yellowlcd.setCursor(0, 2);
          Yellowlcd.print("Tir interdit.       ");
          Yellowlcd.setCursor(0, 1);
          Yellowlcd.print("Coord Torpille :    ");
          YellowTorpedo.col = 0;
          YellowTorpedo.line = 0;
        } else {
          Serial.print("Torpille en ");
          Serial.print(YellowTorpedo.col);
          Serial.println(YellowTorpedo.line);
          lcdResetYellow(1);
          Yellowlcd.setCursor(0, 1);
          Yellowlcd.print("Torpille en         ");
          Yellowlcd.setCursor(12, 1);
          Yellowlcd.print(YellowTorpedo.col);
          Yellowlcd.setCursor(14, 1);
          Yellowlcd.print(YellowTorpedo.line);
          y = int(YellowPosition.col) - int(YellowTorpedo.col);
          x = YellowPosition.line - YellowTorpedo.line;
          if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1)) ) {
            YellowSubDamage += 1;
            Serial.println("SM Yellow allié touché !");
          }
          y = int(BluePosition.col) - int(YellowTorpedo.col);
          x = BluePosition.line - YellowTorpedo.line;
          if ((abs(x) + abs(y) == 1) || ((abs(x) == 1) && (abs(y) == 1)) ) {
            BlueSubDamage += 1;
            Serial.println("SM Yellow ennemi touché !");
          } else if (abs(x) + abs(y) == 0) {
            BlueSubDamage += 2;
            Serial.println("SM Yellow ennemi touché (tir direct)!");
          }
          YellowModuleEngaged = NONE;
          YellowTorpedo.col = 0;
          YellowTorpedo.line = 0;
        }
      }
    } else {
      Serial.println("Tir Hors de portée");
      Serial.println("Choisir autre coord");
      Serial.print("Colonne : ");
      lcdResetYellow(2);
      Yellowlcd.setCursor(0, 2);
      Yellowlcd.print("Tir hors de portee. ");
      Yellowlcd.setCursor(0, 1);
      Yellowlcd.print("Coord Torpille :    ");
      YellowTorpedo.col = 0;
      YellowTorpedo.line = 0;
    }
  }
}

void DroneBlue() {
  Serial.println("Drone Launched ! (Blue)");
  lcdResetBlue(1);
  Bluelcd.setCursor(0, 1);
  Bluelcd.print("Drone lance !       ");

}
//Yellow
void DroneYellow() {
  Serial.println("Drone Launched ! (Yellow)");
  lcdResetYellow(1);
  Yellowlcd.setCursor(0, 1);
  Yellowlcd.print("Drone lance !       ");
}

void SonarBlue() {
  Serial.println("Sonar Launched ! (Blue)");
  lcdResetBlue(1);
  Bluelcd.setCursor(0, 1);
  Bluelcd.print("Sonar lance !       ");
}
//Yellow
void SonarYellow() {
  Serial.println("Sonar Launched ! (Yellow)");
  lcdResetYellow(1);
  Yellowlcd.setCursor(0, 1);
  Yellowlcd.print("Sonar lance !       ");
}

byte SilenceBlue() {
  //check si au moins un mvt est possible
  if ((CheckSilencePossibleBlue(1, 0) == 1) && (CheckSilencePossibleBlue(-1, 0) == 1) && (CheckSilencePossibleBlue(0, 1) == 1) && (CheckSilencePossibleBlue(0, -1) == 1)) {
    return 1;
  }
  if (BlueSilenceDirection == 0) {

    switch  (BlueCapkey) {
      case LEFT:
        Serial.println("Deplacement Ouest");
        Bluelcd.setCursor(0, 0);
        Bluelcd.print("Silence vers Ouest  ");
        Serial.println("Combien de mvt?");
        Serial.println("Utilisez touches 1-4");
        Bluelcd.setCursor(0, 1);
        Bluelcd.print("Combien de mouv : ");
        BlueSilenceDirection = LEFT;
        break;
      case UP:
        Serial.println("Deplacement Nord");
        Bluelcd.setCursor(0, 0);
        Bluelcd.print("Silence vers Nord   ");
        Serial.println("Combien de mvt?");
        Serial.println("Utilisez touches 1-4");
        Bluelcd.setCursor(0, 1);
        Bluelcd.print("Combien de mouv : ");
        BlueSilenceDirection = UP;
        break;
      case DOWN:
        Serial.println("Deplacement Sud");
        Bluelcd.setCursor(0, 0);
        Bluelcd.print("Silence vers Sud    ");
        Serial.println("Combien de mvt?");
        Serial.println("Utilisez touches 1-4");
        Bluelcd.setCursor(0, 1);
        Bluelcd.print("Combien de mouv : ");
        BlueSilenceDirection = DOWN;
        break;
      case RIGHT:
        Serial.println("Deplacement Est");
        Bluelcd.setCursor(0, 0);
        Bluelcd.print("Silence vers Est    ");
        Serial.println("Combien de mvt?");
        Serial.println("Utilisez touches 1-4");
        Bluelcd.setCursor(0, 1);
        Bluelcd.print("Combien de mouv : ");
        BlueSilenceDirection = RIGHT;
        break;
      case SURFACE:
        Serial.println("Silence ! (sur place)");
        lcdResetBlue(0);
        Bluelcd.setCursor(0, 0);
        Bluelcd.print("Silence (sur place) ");
        BlueSilenceDirection = NONE;
        BlueModuleEngaged = NONE;
        BlueSubState = 0;
        TricolorBlue(0);
        break;
    }
  } else {
    switch (BlueSilenceDirection) {
      case LEFT:
        switch (BlueCapPad) {
          case 1:
            CheckMoveSilenceBlue(-1, 0);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.col = BluePosition.col - 1;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = LEFT;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 2:
            CheckMoveSilenceBlue(-2, 0);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.col = BluePosition.col - 2;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = LEFT;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 3:
            CheckMoveSilenceBlue(-3, 0);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.col = BluePosition.col - 3;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = LEFT;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 4:
            CheckMoveSilenceBlue(-4, 0);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.col = BluePosition.col - 4;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = LEFT;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
        }
        break;
      case UP:
        switch (BlueCapPad) {
          case 1:
            CheckMoveSilenceBlue(0, -1);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.line = BluePosition.line - 1;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = UP;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 2: CheckMoveSilenceBlue(0, -2);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.line = BluePosition.line - 2;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = UP;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 3:
            CheckMoveSilenceBlue(0, -3);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.line = BluePosition.line - 3;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = UP;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 4:
            CheckMoveSilenceBlue(0, -4);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.line = BluePosition.line - 4;
              Serial.print("Your position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = UP;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
        }
        break;
      case DOWN :
        switch (BlueCapPad) {
          case 1:
            CheckMoveSilenceBlue(0, 1);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.line = BluePosition.line + 1;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = DOWN;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 2:
            CheckMoveSilenceBlue(0, 2);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.line = BluePosition.line + 2;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = DOWN;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 3:
            CheckMoveSilenceBlue(0, 3);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.line = BluePosition.line + 3;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = DOWN;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 4:
            CheckMoveSilenceBlue(0, 4);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.line = BluePosition.line + 4;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = DOWN;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
        }
        break;
      case RIGHT:
        switch (BlueCapPad) {
          case 1:
            CheckMoveSilenceBlue(1, 0);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.col = BluePosition.col + 1;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = RIGHT;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 2:
            CheckMoveSilenceBlue(2, 0);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.col = BluePosition.col + 2;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = RIGHT;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 3:
            CheckMoveSilenceBlue(3, 0);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.col = BluePosition.col + 3;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = RIGHT;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
          case 4:
            CheckMoveSilenceBlue(4, 0);
            if (BlueSilenceDirection != NONE) {
              BlueSilenceDirection = NONE;
              BlueModuleEngaged = NONE;
              BluePosition.col = BluePosition.col + 4;
              Serial.print("Blue position is : ");
              Serial.print(BluePosition.col);
              Serial.println(BluePosition.line);
              BlueEngineerDamage = 1;
              BlueFMCharge = 1;
              BlueLastDirection = RIGHT;
              lcdResetBlue(1);
              Bluelcd.setCursor(0, 1);
              Bluelcd.print("Combien de mouv : ");
              Bluelcd.setCursor(18, 1);
              Bluelcd.print(BlueCapPad);
            }
            break;
        }
        break;
    }
    //REVIENT
  }
}
byte CheckSilencePossibleBlue(int x, int y) {
  for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
    if ((Islands[Map][i].col == BluePosition.col + x) && (Islands[Map][i].line == BluePosition.line + y)) {
      return (1);
    } else {
    }
  }
  if ((BluePosition.col + x < 65) || (BluePosition.line + y < 1) || (BluePosition.col + x > 79) || (BluePosition.line + y > 15)) {
    return (1);
  }
  for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
    if ((BluePastPosition[i].col == BluePosition.col + x) && (BluePastPosition[i].line == BluePosition.line + y)) {
      return (1);
    } else {
    }
  }
}
byte CheckMoveSilenceBlue(int x, int y) {
  int z = x + y;
  if (x == 0) {
    if (y > 0) {
      for (y = 1; y <= z ; y++) {
        for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
          if ((Islands[Map][i].col == BluePosition.col + x) && (Islands[Map][i].line == BluePosition.line + y)) {
            Serial.println("Island on path");
            Serial.println("Choose a different move");
            lcdResetBlue(2);
            Bluelcd.setCursor(0, 2);
            Bluelcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
          } else {
          }
        }
        if ((BluePosition.col + x < 65) || (BluePosition.line + y < 1) || (BluePosition.col + x > 79) || (BluePosition.line + y > 15)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("You can't move here. Out of map.");
          Serial.println("Choose a different move");
          lcdResetBlue(2);
          Bluelcd.setCursor(0, 2);
          Bluelcd.print("Silence Interdit    ");
          Serial.println("Indiquez la direction du Silence");
          Serial.println("bouton surface = Rester sur place");
          Bluelcd.setCursor(0, 0);
          Bluelcd.print("Direction Silence : ");
          lcdResetBlue(3);
          Bluelcd.setCursor(0, 3);
          Bluelcd.print("Surface = Sur Place ");
          BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
        }
        for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
          if ((BluePastPosition[i].col == BluePosition.col + x) && (BluePastPosition[i].line == BluePosition.line + y)) {
            Serial.println("You can't move here. Can't cross path !");
            Serial.println("Choose a different move");
            lcdResetBlue(2);
            Bluelcd.setCursor(0, 2);
            Bluelcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
          } else {
          }
        }
      }
    } else {
      for (y = z; y <= -1; y++) {
        Serial.println(y);
        for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
          if ((Islands[Map][i].col == BluePosition.col + x) && (Islands[Map][i].line == BluePosition.line + y)) {
            Serial.println("Island on path");
            Serial.println("Choose a different move");
            lcdResetBlue(2);
            Bluelcd.setCursor(0, 2);
            Bluelcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
          } else {
          }
        }
        if ((BluePosition.col + x < 65) || (BluePosition.line + y < 1) || (BluePosition.col + x > 79) || (BluePosition.line + y > 15)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("You can't move here. Out of map.");
          Serial.println("Choose a different move");
          lcdResetBlue(2);
          Bluelcd.setCursor(0, 2);
          Bluelcd.print("Silence Interdit    ");
          Serial.println("Indiquez la direction du Silence");
          Serial.println("bouton surface = Rester sur place");
          Bluelcd.setCursor(0, 0);
          Bluelcd.print("Direction Silence : ");
          lcdResetBlue(3);
          Bluelcd.setCursor(0, 3);
          Bluelcd.print("Surface = Sur Place ");
          BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
        }
        for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
          if ((BluePastPosition[i].col == BluePosition.col + x) && (BluePastPosition[i].line == BluePosition.line + y)) {
            Serial.println("You can't move here. Can't cross path !");
            Serial.println("Choose a different move");
            lcdResetBlue(2);
            Bluelcd.setCursor(0, 2);
            Bluelcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
          } else {
          }
        }
      }
    }
  } else {
    if (x > 0) {
      for (x = 1; x <= z; x++) {
        for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
          if ((Islands[Map][i].col == BluePosition.col + x) && (Islands[Map][i].line == BluePosition.line + y)) {
            Serial.println("Island on path");
            Serial.println("Choose a different move");
            lcdResetBlue(2);
            Bluelcd.setCursor(0, 2);
            Bluelcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
          } else {
          }
        }
        if ((BluePosition.col + x < 65) || (BluePosition.line + y < 1) || (BluePosition.col + x > 79) || (BluePosition.line + y > 15)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("You can't move here. Out of map.");
          Serial.println("Choose a different move");
          Serial.println("Indiquez la direction du Silence");
          lcdResetBlue(2);
          Bluelcd.setCursor(0, 2);
          Bluelcd.print("Silence Interdit    ");
          Serial.println("bouton surface = Rester sur place");
          Bluelcd.setCursor(0, 0);
          Bluelcd.print("Direction Silence : ");
          lcdResetBlue(3);
          Bluelcd.setCursor(0, 3);
          Bluelcd.print("Surface = Sur Place ");
          BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
        }
        for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
          if ((BluePastPosition[i].col == BluePosition.col + x) && (BluePastPosition[i].line == BluePosition.line + y)) {
            Serial.println("You can't move here. Can't cross path !");
            Serial.println("Choose a different move");
            lcdResetBlue(2);
            Bluelcd.setCursor(0, 2);
            Bluelcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
          } else {
          }
        }
      }
    } else {
      for (x = z; x <= -1; x++) {
        for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
          if ((Islands[Map][i].col == BluePosition.col + x) && (Islands[Map][i].line == BluePosition.line + y)) {
            Serial.println("Island on path");
            Serial.println("Choose a different move");
            lcdResetBlue(2);
            Bluelcd.setCursor(0, 2);
            Bluelcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
          } else {
          }
        }
        if ((BluePosition.col + x < 65) || (BluePosition.line + y < 1) || (BluePosition.col + x > 79) || (BluePosition.line + y > 15)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("You can't move here. Out of map.");
          Serial.println("Choose a different move");
          lcdResetBlue(2);
          Bluelcd.setCursor(0, 2);
          Bluelcd.print("Silence Interdit    ");
          Serial.println("Indiquez la direction du Silence");
          Serial.println("bouton surface = Rester sur place");
          Bluelcd.setCursor(0, 0);
          Bluelcd.print("Direction Silence : ");
          lcdResetBlue(3);
          Bluelcd.setCursor(0, 3);
          Bluelcd.print("Surface = Sur Place ");
          BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
        }
        for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
          if ((BluePastPosition[i].col == BluePosition.col + x) && (BluePastPosition[i].line == BluePosition.line + y)) {
            Serial.println("You can't move here. Can't cross path !");
            Serial.println("Choose a different move");
            lcdResetBlue(2);
            Bluelcd.setCursor(0, 2);
            Bluelcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Bluelcd.setCursor(0, 0);
            Bluelcd.print("Direction Silence : ");
            lcdResetBlue(3);
            Bluelcd.setCursor(0, 3);
            Bluelcd.print("Surface = Sur Place ");
            BlueSilenceDirection = NONE;
            Bluelcd.setCursor(0, 1);
            Bluelcd.print("                    ");
          } else {
          }
        }
      }
    }
  }
}
//Yellow (silence block)
byte SilenceYellow() {
  //check si au moins un mvt est possible
  if ((CheckSilencePossibleYellow(1, 0) == 1) && (CheckSilencePossibleYellow(-1, 0) == 1) && (CheckSilencePossibleYellow(0, 1) == 1) && (CheckSilencePossibleYellow(0, -1) == 1)) {
    return 1;
  }
  if (YellowSilenceDirection == 0) {
    switch  (YellowCapkey) {
      case LEFT:
        Serial.println("Deplacement Ouest");
        Yellowlcd.setCursor(0, 0);
        Yellowlcd.print("Silence vers Ouest  ");
        Serial.println("Combien de mvt?");
        Serial.println("Utilisez touches 1-4");
        Yellowlcd.setCursor(0, 1);
        Yellowlcd.print("Combien de mouv : ");
        YellowSilenceDirection = LEFT;
        break;
      case UP:
        Serial.println("Deplacement Nord");
        Yellowlcd.setCursor(0, 0);
        Yellowlcd.print("Silence vers Nord   ");
        Serial.println("Combien de mvt?");
        Serial.println("Utilisez touches 1-4");
        Yellowlcd.setCursor(0, 1);
        Yellowlcd.print("Combien de mouv : ");
        YellowSilenceDirection = UP;
        break;
      case DOWN:
        Serial.println("Deplacement Sud");
        Yellowlcd.setCursor(0, 0);
        Yellowlcd.print("Silence vers Sud    ");
        Serial.println("Combien de mvt?");
        Serial.println("Utilisez touches 1-4");
        Yellowlcd.setCursor(0, 1);
        Yellowlcd.print("Combien de mouv : ");
        YellowSilenceDirection = DOWN;
        break;
      case RIGHT:
        Serial.println("Deplacement Est");
        Yellowlcd.setCursor(0, 0);
        Yellowlcd.print("Silence vers Est    ");
        Serial.println("Combien de mvt?");
        Serial.println("Utilisez touches 1-4");
        Yellowlcd.setCursor(0, 1);
        Yellowlcd.print("Combien de mouv : ");
        YellowSilenceDirection = RIGHT;
        break;
      case SURFACE:
        Serial.println("Silence ! (sur place)");
        lcdResetYellow(0);
        Yellowlcd.setCursor(0, 0);
        Yellowlcd.print("Silence (sur place) ");
        YellowSilenceDirection = NONE;
        YellowModuleEngaged = NONE;
        YellowSubState = 0;
        TricolorYellow(0);
        break;
    }
  } else {
    switch (YellowSilenceDirection) {
      case LEFT:
        switch (YellowCapPad) {
          case 1:
            CheckMoveSilenceYellow(-1, 0);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.col = YellowPosition.col - 1;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = LEFT;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 2:
            CheckMoveSilenceYellow(-2, 0);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.col = YellowPosition.col - 2;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = LEFT;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 3:
            CheckMoveSilenceYellow(-3, 0);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.col = YellowPosition.col - 3;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = LEFT;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 4:
            CheckMoveSilenceYellow(-4, 0);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.col = YellowPosition.col - 4;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = LEFT;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
        }
        break;
      case UP:
        switch (YellowCapPad) {
          case 1:
            CheckMoveSilenceYellow(0, -1);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.line = YellowPosition.line - 1;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = UP;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 2: CheckMoveSilenceYellow(0, -2);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.line = YellowPosition.line - 2;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = UP;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 3:
            CheckMoveSilenceYellow(0, -3);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.line = YellowPosition.line - 3;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = UP;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 4:
            CheckMoveSilenceYellow(0, -4);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.line = YellowPosition.line - 4;
              Serial.print("Your position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = UP;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
        }
        break;
      case DOWN :
        switch (YellowCapPad) {
          case 1:
            CheckMoveSilenceYellow(0, 1);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.line = YellowPosition.line + 1;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = DOWN;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 2:
            CheckMoveSilenceYellow(0, 2);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.line = YellowPosition.line + 2;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = DOWN;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 3:
            CheckMoveSilenceYellow(0, 3);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.line = YellowPosition.line + 3;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = DOWN;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 4:
            CheckMoveSilenceYellow(0, 4);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.line = YellowPosition.line + 4;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = DOWN;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
        }
        break;
      case RIGHT:
        switch (YellowCapPad) {
          case 1:
            CheckMoveSilenceYellow(1, 0);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.col = YellowPosition.col + 1;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = RIGHT;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 2:
            CheckMoveSilenceYellow(2, 0);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.col = YellowPosition.col + 2;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = RIGHT;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 3:
            CheckMoveSilenceYellow(3, 0);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.col = YellowPosition.col + 3;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = RIGHT;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
          case 4:
            CheckMoveSilenceYellow(4, 0);
            if (YellowSilenceDirection != NONE) {
              YellowSilenceDirection = NONE;
              YellowModuleEngaged = NONE;
              YellowPosition.col = YellowPosition.col + 4;
              Serial.print("Yellow position is : ");
              Serial.print(YellowPosition.col);
              Serial.println(YellowPosition.line);
              YellowEngineerDamage = 1;
              YellowFMCharge = 1;
              YellowLastDirection = RIGHT;
              lcdResetYellow(1);
              Yellowlcd.setCursor(0, 1);
              Yellowlcd.print("Combien de mouv : ");
              Yellowlcd.setCursor(18, 1);
              Yellowlcd.print(YellowCapPad);
            }
            break;
        }
        break;
    }
  }
}
byte CheckSilencePossibleYellow(int x, int y) {
  for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
    if ((Islands[Map][i].col == YellowPosition.col + x) && (Islands[Map][i].line == YellowPosition.line + y)) {
      return (1);
    } else {
    }
  }
  if ((YellowPosition.col + x < 65) || (YellowPosition.line + y < 1) || (YellowPosition.col + x > 79) || (YellowPosition.line + y > 15)) {
    return (1);
  }
  for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
    if ((YellowPastPosition[i].col == YellowPosition.col + x) && (YellowPastPosition[i].line == YellowPosition.line + y)) {
      return (1);
    } else {
    }
  }
}
byte CheckMoveSilenceYellow(int x, int y) {
  int z = x + y;
  if (x == 0) {
    if (y > 0) {
      for (y = 1; y <= z ; y++) {
        for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
          if ((Islands[Map][i].col == YellowPosition.col + x) && (Islands[Map][i].line == YellowPosition.line + y)) {
            Serial.println("Island on path");
            Serial.println("Choose a different move");
            lcdResetYellow(2);
            Yellowlcd.setCursor(0, 2);
            Yellowlcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
          } else {
          }
        }
        if ((YellowPosition.col + x < 65) || (YellowPosition.line + y < 1) || (YellowPosition.col + x > 79) || (YellowPosition.line + y > 15)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("You can't move here. Out of map.");
          Serial.println("Choose a different move");
          lcdResetYellow(2);
          Yellowlcd.setCursor(0, 2);
          Yellowlcd.print("Silence Interdit    ");
          Serial.println("Indiquez la direction du Silence");
          Serial.println("bouton surface = Rester sur place");
          Yellowlcd.setCursor(0, 0);
          Yellowlcd.print("Direction Silence : ");
          lcdResetYellow(3);
          Yellowlcd.setCursor(0, 3);
          Yellowlcd.print("Surface = Sur Place ");
          YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
        }
        for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
          if ((YellowPastPosition[i].col == YellowPosition.col + x) && (YellowPastPosition[i].line == YellowPosition.line + y)) {
            Serial.println("You can't move here. Can't cross path !");
            Serial.println("Choose a different move");
            lcdResetYellow(2);
            Yellowlcd.setCursor(0, 2);
            Yellowlcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
          } else {
          }
        }
      }
    } else {
      for (y = z; y <= -1; y++) {
        Serial.println(y);
        for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
          if ((Islands[Map][i].col == YellowPosition.col + x) && (Islands[Map][i].line == YellowPosition.line + y)) {
            Serial.println("Island on path");
            Serial.println("Choose a different move");
            lcdResetYellow(2);
            Yellowlcd.setCursor(0, 2);
            Yellowlcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
          } else {
          }
        }
        if ((YellowPosition.col + x < 65) || (YellowPosition.line + y < 1) || (YellowPosition.col + x > 79) || (YellowPosition.line + y > 15)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("You can't move here. Out of map.");
          Serial.println("Choose a different move");
          lcdResetYellow(2);
          Yellowlcd.setCursor(0, 2);
          Yellowlcd.print("Silence Interdit    ");
          Serial.println("Indiquez la direction du Silence");
          Serial.println("bouton surface = Rester sur place");
          Yellowlcd.setCursor(0, 0);
          Yellowlcd.print("Direction Silence : ");
          lcdResetYellow(3);
          Yellowlcd.setCursor(0, 3);
          Yellowlcd.print("Surface = Sur Place ");
          YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
        }
        for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
          if ((YellowPastPosition[i].col == YellowPosition.col + x) && (YellowPastPosition[i].line == YellowPosition.line + y)) {
            Serial.println("You can't move here. Can't cross path !");
            Serial.println("Choose a different move");
            lcdResetYellow(2);
            Yellowlcd.setCursor(0, 2);
            Yellowlcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
          } else {
          }
        }
      }
    }
  } else {
    if (x > 0) {
      for (x = 1; x <= z; x++) {
        for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
          if ((Islands[Map][i].col == YellowPosition.col + x) && (Islands[Map][i].line == YellowPosition.line + y)) {
            Serial.println("Island on path");
            Serial.println("Choose a different move");
            lcdResetYellow(2);
            Yellowlcd.setCursor(0, 2);
            Yellowlcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
          } else {
          }
        }
        if ((YellowPosition.col + x < 65) || (YellowPosition.line + y < 1) || (YellowPosition.col + x > 79) || (YellowPosition.line + y > 15)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("You can't move here. Out of map.");
          Serial.println("Choose a different move");
          Serial.println("Indiquez la direction du Silence");
          lcdResetYellow(2);
          Yellowlcd.setCursor(0, 2);
          Yellowlcd.print("Silence Interdit    ");
          Serial.println("bouton surface = Rester sur place");
          Yellowlcd.setCursor(0, 0);
          Yellowlcd.print("Direction Silence : ");
          lcdResetYellow(3);
          Yellowlcd.setCursor(0, 3);
          Yellowlcd.print("Surface = Sur Place ");
          YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
        }
        for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
          if ((YellowPastPosition[i].col == YellowPosition.col + x) && (YellowPastPosition[i].line == YellowPosition.line + y)) {
            Serial.println("You can't move here. Can't cross path !");
            Serial.println("Choose a different move");
            lcdResetYellow(2);
            Yellowlcd.setCursor(0, 2);
            Yellowlcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
          } else {
          }
        }
      }
    } else {
      for (x = z; x <= -1; x++) {
        for (int i = 0; i <= sizeof(Islands[Map]) / 3 - 1; i++) { //checks for Island collision
          if ((Islands[Map][i].col == YellowPosition.col + x) && (Islands[Map][i].line == YellowPosition.line + y)) {
            Serial.println("Island on path");
            Serial.println("Choose a different move");
            lcdResetYellow(2);
            Yellowlcd.setCursor(0, 2);
            Yellowlcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
          } else {
          }
        }
        if ((YellowPosition.col + x < 65) || (YellowPosition.line + y < 1) || (YellowPosition.col + x > 79) || (YellowPosition.line + y > 15)) { //check for out of map
          // The move is not possible, Position would be out of map
          Serial.println("You can't move here. Out of map.");
          Serial.println("Choose a different move");
          lcdResetYellow(2);
          Yellowlcd.setCursor(0, 2);
          Yellowlcd.print("Silence Interdit    ");
          Serial.println("Indiquez la direction du Silence");
          Serial.println("bouton surface = Rester sur place");
          Yellowlcd.setCursor(0, 0);
          Yellowlcd.print("Direction Silence : ");
          lcdResetYellow(3);
          Yellowlcd.setCursor(0, 3);
          Yellowlcd.print("Surface = Sur Place ");
          YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
        }
        for (int i = 0; i <= 99 ; i++) { //checks for crossing previous path
          if ((YellowPastPosition[i].col == YellowPosition.col + x) && (YellowPastPosition[i].line == YellowPosition.line + y)) {
            Serial.println("You can't move here. Can't cross path !");
            Serial.println("Choose a different move");
            lcdResetYellow(2);
            Yellowlcd.setCursor(0, 2);
            Yellowlcd.print("Silence Interdit    ");
            Serial.println("Indiquez la direction du Silence");
            Serial.println("bouton surface = Rester sur place");
            Yellowlcd.setCursor(0, 0);
            Yellowlcd.print("Direction Silence : ");
            lcdResetYellow(3);
            Yellowlcd.setCursor(0, 3);
            Yellowlcd.print("Surface = Sur Place ");
            YellowSilenceDirection = NONE;
            Yellowlcd.setCursor(0, 1);
            Yellowlcd.print("                    ");
          } else {
          }
        }
      }
    }
  }
}

void CheckDamage() {
  if ((BlueSubDamage >= BlueSubMaxDamage) && (YellowSubDamage >= YellowSubMaxDamage)) {
    Serial.println("Glou glou glou...");
    Serial.println("Egalité !");
    Bluelcd.setCursor(0, 1);
    Bluelcd.print("Glou glou glou...   ");
    Bluelcd.setCursor(0, 2);
    Bluelcd.print("      Egalite       ");
    Yellowlcd.setCursor(0, 1);
    Yellowlcd.print("Glou glou glou...   ");
    Yellowlcd.setCursor(0, 2);
    Yellowlcd.print("      Egalite       ");
    byte H = 0;
    byte J = 0;
    byte K = 0;
    byte L = 0;
    for (int i = 0; i <= 1;) {

      H = random(1, 30);
      J = random(1, 30);
      K = random(1, 30);
      L = random(0, 40);

      YellowFMPixels.setPixelColor(L, YellowFMPixels.Color(H,   J,  K));
      BlueFMPixels.setPixelColor(L, BlueFMPixels.Color(H, J, K));
      YellowFMPixels.show();
      BlueFMPixels.show();
      TricolorBlue(1);
      TricolorYellow(1);
      BlueEngiLedHigh();
      YellowEngiLedHigh();
      BlueEngiLedLow();
      YellowEngiLedLow();
    }
  } else if (BlueSubDamage >= BlueSubMaxDamage) {
    Serial.println("Glou glou glou...");
    Serial.println("Victoire de l'équipe Jaune !");
    Bluelcd.setCursor(0, 1);
    Bluelcd.print("Glou glou glou...   ");
    Bluelcd.setCursor(0, 2);
    Bluelcd.print("      Perdu !       ");
    Yellowlcd.setCursor(0, 1);
    Yellowlcd.print("Boum !              ");
    Yellowlcd.setCursor(0, 2);
    Yellowlcd.print("      Gagne !       ");
    byte H = 0;
    byte J = 0;
    byte K = 0;
    byte L = 0;
    for (int i = 0; i <= 1;) {
      TricolorBlue(2);
      TricolorYellow(0);
      BlueEngiLedHigh();
      YellowEngiLedHigh();
      BlueEngiLedLow();
      YellowEngiLedLow();

      H = random(1, 30);
      J = random(1, 30);
      K = random(1, 30);
      L = random(0, 40);

      YellowFMPixels.setPixelColor(L, YellowFMPixels.Color(H,   J,  K));
      BlueFMPixels.setPixelColor(L, BlueFMPixels.Color(H, J, K));
      YellowFMPixels.show();
      BlueFMPixels.show();
    }
  } else if (YellowSubDamage >= YellowSubMaxDamage) {
    Serial.println("Glou glou glou...");
    Serial.println("Victoire de l'équipe Bleu !");
    Bluelcd.setCursor(0, 1);
    Bluelcd.print("Boum !              ");
    Bluelcd.setCursor(0, 2);
    Bluelcd.print("      Gagne !       ");
    Yellowlcd.setCursor(0, 1);
    Yellowlcd.print("Glou glou glou...   ");
    Yellowlcd.setCursor(0, 2);
    Yellowlcd.print("      Perdu !       ");
    byte H = 0;
    byte J = 0;
    byte K = 0;
    byte L = 0;
    for (int i = 0; i <= 1;) {
      TricolorBlue(0);
      TricolorYellow(2);
      BlueEngiLedHigh();
      YellowEngiLedHigh();
      BlueEngiLedLow();
      YellowEngiLedLow();
      H = random(1, 30);
      J = random(1, 30);
      K = random(1, 30);
      L = random(0, 40);

      YellowFMPixels.setPixelColor(L, YellowFMPixels.Color(H,   J,  K));
      BlueFMPixels.setPixelColor(L, BlueFMPixels.Color(H, J, K));
      YellowFMPixels.show();
      BlueFMPixels.show();
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Yellowlcd.begin(20, 4);
  Bluelcd.begin(20, 4);
  Yellowlcd.backlight();
  Bluelcd.backlight();
  pinMode(BluePospadCaptain, INPUT);
  pinMode(YellowPospadCaptain, INPUT);
  pinMode(BluekeypadFM, INPUT_PULLUP);
  pinMode(BluekeypadEngiWest, INPUT_PULLUP);
  pinMode(BluekeypadEngiNorth, INPUT_PULLUP);
  pinMode(BluekeypadEngiSouth, INPUT_PULLUP);
  pinMode(BluekeypadEngiEast, INPUT_PULLUP);
  pinMode(YellowkeypadEngiWest, INPUT_PULLUP);
  pinMode(YellowkeypadEngiNorth, INPUT_PULLUP);
  pinMode(YellowkeypadEngiSouth, INPUT_PULLUP);
  pinMode(YellowkeypadEngiEast, INPUT_PULLUP);
  pinMode(BluePinLedWeaponWestAutopipe, OUTPUT);      //The following constants are the pins for the Engineer modules.
  pinMode(BluePinLedDetectionWestAutopipe, OUTPUT); // they act as indicators of the state of the module : lit if the module is damaged (or 'crossed')
  pinMode(BluePinLedSpecialWestAutopipe, OUTPUT);   // and shut down if the module is not damaged.
  pinMode(BluePinLedRadiationWestpersistant1, OUTPUT);
  pinMode(BluePinLedRadiationWestpersistant2, OUTPUT);
  pinMode(BluePinLedDetectionWestpersistant, OUTPUT);
  pinMode(BluePinLedWeaponNorthAutopipe, OUTPUT);
  pinMode(BluePinLedSpecialNorthAutopipe1, OUTPUT);
  pinMode(BluePinLedSpecialNorthAutopipe2, OUTPUT);
  pinMode(BluePinLedDetectionNorthpersistant, OUTPUT);
  pinMode(BluePinLedWeaponNorthpersistant, OUTPUT);
  pinMode(BluePinLedRadiationNorthpersistant, OUTPUT);
  pinMode(BluePinLedWeaponSudAutopipe, OUTPUT);
  pinMode(BluePinLedDetectionSudAutopipe, OUTPUT);
  pinMode(BluePinLedSpecialSudAutopipe, OUTPUT);
  pinMode(BluePinLedWeaponSudpersistant, OUTPUT);
  pinMode(BluePinLedRadiationSudpersistant, OUTPUT);
  pinMode(BluePinLedSpecialSudpersistant, OUTPUT);
  pinMode(BluePinLedWeaponEstAutopipe, OUTPUT);
  pinMode(BluePinLedDetectionEstAutopipe, OUTPUT);
  pinMode(BluePinLedSpecialEstAutopipe, OUTPUT);
  pinMode(BluePinLedDetectionEstpersistant, OUTPUT);
  pinMode(BluePinLedRadiationEstpersistant1, OUTPUT);
  pinMode(BluePinLedRadiationEstpersistant2, OUTPUT);
  pinMode(YellowPinLedWeaponWestAutopipe, OUTPUT);      //The following constants are the pins for the Engineer modules.
  pinMode(YellowPinLedDetectionWestAutopipe, OUTPUT); // they act as indicators of the state of the module : lit if the module is damaged (or 'crossed')
  pinMode(YellowPinLedSpecialWestAutopipe, OUTPUT);   // and shut down if the module is not damaged.
  pinMode(YellowPinLedRadiationWestpersistant1, OUTPUT);
  pinMode(YellowPinLedRadiationWestpersistant2, OUTPUT);
  pinMode(YellowPinLedDetectionWestpersistant, OUTPUT);
  pinMode(YellowPinLedWeaponNorthAutopipe, OUTPUT);
  pinMode(YellowPinLedSpecialNorthAutopipe1, OUTPUT);
  pinMode(YellowPinLedSpecialNorthAutopipe2, OUTPUT);
  pinMode(YellowPinLedDetectionNorthpersistant, OUTPUT);
  pinMode(YellowPinLedWeaponNorthpersistant, OUTPUT);
  pinMode(YellowPinLedRadiationNorthpersistant, OUTPUT);
  pinMode(YellowPinLedWeaponSudAutopipe, OUTPUT);
  pinMode(YellowPinLedDetectionSudAutopipe, OUTPUT);
  pinMode(YellowPinLedSpecialSudAutopipe, OUTPUT);
  pinMode(YellowPinLedWeaponSudpersistant, OUTPUT);
  pinMode(YellowPinLedRadiationSudpersistant, OUTPUT);
  pinMode(YellowPinLedSpecialSudpersistant, OUTPUT);
  pinMode(YellowPinLedWeaponEstAutopipe, OUTPUT);
  pinMode(YellowPinLedDetectionEstAutopipe, OUTPUT);
  pinMode(YellowPinLedSpecialEstAutopipe, OUTPUT);
  pinMode(YellowPinLedDetectionEstpersistant, OUTPUT);
  pinMode(YellowPinLedRadiationEstpersistant1, OUTPUT);
  pinMode(YellowPinLedRadiationEstpersistant2, OUTPUT);
  mcp.begin();    //Initialisation for the extender module
  for (int pin = 0; pin <= 5; pin++) {
    mcp.pinMode(pin, OUTPUT);
    mcp.digitalWrite(pin, LOW);
  }
  //set up for neopixel :
  BlueFMPixels.begin();
  BlueFMPixels.clear();
  YellowFMPixels.begin();
  YellowFMPixels.clear();
  colorOff();
  BlueEngiLedHigh();
  colorFullChargeBlue(0, 47);
  colorFullChargeYellow(0, 47);
  YellowEngiLedHigh();
  delay(500);
  YellowEngiLedLow();
  BlueEngiLedLow();
  colorEmptyChargeBlue(0, 47);
  colorEmptyChargeYellow(0, 47);
  Serial.println("Choose your map");
  Yellowlcd.setCursor(0, 0);
  Yellowlcd.print("Choix de la Map");
  Bluelcd.setCursor(0, 0);
  Bluelcd.print("Choisissez la Map");
  getKeyPositionMap();
  Serial.println("Blue : input starting position");
  Bluelcd.setCursor(0, 1);
  Bluelcd.print("Choissisez Position:");
  getKeyStartingPositionBlue();
  Serial.println("Yellow : input starting position");
  Yellowlcd.setCursor(0, 1);
  Yellowlcd.print("Choissisez Position:");
  getKeyStartingPositionYellow();
  TricolorYellow(2);
  TricolorBlue(2);
  delay(1000);
  TricolorYellow(1);
  TricolorBlue(1);
  delay(1000);
  TricolorYellow(0);
  TricolorBlue(0);
  Bluelcd.clear();
  Yellowlcd.clear();
}

void loop() {
  currentMillis = millis();   // capture the latest value of millis() (for control purposes)
  // put your main code here, to run repeatedly:
  BlueCapkey = getKeyMovCaptainBlue();             //Reads the input from the captain board every buttonInterval milliseconds
  if (BlueCapkey == NONE) {       //No move
  } else {
    AllowMovementBlue();        //If a move button (or surface) has been pressed, the function is called
  }
  YellowCapkey = getKeyMovCaptainYellow();             //Reads the input from the captain board every buttonInterval milliseconds
  if (YellowCapkey == NONE) {       //No move
  } else {
    AllowMovementYellow();        //If a move button (or surface) has been pressed, the function is called
  }
  BlueCapPad = getKeyPadCaptainBlue();
  YellowCapPad = getKeyPadCaptainYellow();
  getKeyEngiBlue();
  getKeyEngiYellow();
  BlueFMkey = getKeypadFMBlue();
  if (BlueFMkey == NONE) {
  } else {
    ActivateModuleBlue();
  }
  if (BlueModuleEngaged != NONE) {
    ActivateModuleBlue();
  }
  YellowFMkey = getKeypadFMYellow();
  if (YellowFMkey == NONE) {
  } else {
    ActivateModuleYellow();
  }
  if (YellowModuleEngaged != NONE) {
    ActivateModuleYellow();
  }
  CheckSurface();
  CheckDamage();
  Checklcd();
}
