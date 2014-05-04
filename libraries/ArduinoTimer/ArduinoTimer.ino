////////////////////////////////////////////////////////////////
// title: ArduinoTimer
// author: Elijah Voigt
// description: A binary timer for an arduino.
//              Measures up to 24 hours
//              Increments every minute
// date: May 04, 2014
////////////////////////////////////////////////////////////////

#define MINUTE 60000        // Set this to the time increment[60000 miliseconds are in a minute]
#define ANIM_TIMING 100     // This is the speed of the fancy animation at the end of each 24 hour period

// These arrays store the pins corresponding to the 'hours' and 'minutes'
int pin_hour[5] = {0,2,4,6,8};
int pin_min[6] = {1,3,5,7,9,11};
// This is the total time, it increments by one every cycle
int time = 0;
// Minutes and hours are determined based on the  time
int minutes = 0;
int hours = 0;
int i = 0;

// Setup goes through each pin in minutes and hours and sets it to OUTPUT
void setup() {
  for(i = 0; i < 5; i++){
    pinMode(pin_hour[i],OUTPUT);
  }
  for(i = 0; i < 6; i++){
     pinMode(pin_min[i], OUTPUT); 
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  binary_timer();
}

// Checks if it's been 24 hours or the program is starting
void reset_check(){
  if(hours == 24 || time == 0){
    // If either one, sets time to zero and plays fancy startup animation
    time = 0;
    loading_anim();
  }
}

// The binary timer
void binary_timer(){
  // Hour and minutes are set based on the time
  hours = time/60;
  minutes = time%60;
  
  // Checks if it's been 24 hours
  reset_check();
  
  // Goes through and sets each minute pin to on or off based on the time in binary
  for(i = 0; i < 6; i++){
    digitalWrite(pin_min[i], minutes%2);
    minutes = minutes/2;
  }
  
  // Goes through and sets each hour time to on or off based on the time in binary
  for(i = 0; i < 5; i++){
    digitalWrite(pin_hour[i], hours%2);
    hours = hours/2; 
  }
  // Increments time by one
  time++;
  // Waits a minute
  delay(MINUTE);
}

// An animtion to test the LEDs are all working and are in the right order
void loading_anim(){
  for(i = 0; i < 5; i++){
    digitalWrite(pin_hour[i], HIGH);
    delay(ANIM_TIMING);  
  }
  for(i = 0; i < 5; i++){
     digitalWrite(pin_hour[i], 0);
     delay(ANIM_TIMING);
  }
  for(i = 0; i < 6; i++){
    digitalWrite(pin_min[i], HIGH);
    delay(ANIM_TIMING);  
  }
  for(i = 0; i < 6; i++){
     digitalWrite(pin_min[i], 0);
     delay(ANIM_TIMING);
  }
}
