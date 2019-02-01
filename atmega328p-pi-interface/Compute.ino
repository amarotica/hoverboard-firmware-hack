void Compute() {
  //This module will calculate the needed velocites and times for everything, in standard metric units (Meters)
  //The output scalar value will be used to calibrate commands+error with actual motion.
  //All input measurements will be in CM
  int VcL = 0; //Velocity change per loop
  int VcR = 0; //Velocity change per loop
  int LoopsL = 0;
  int LoopsR = 0;
  int tfaL = 0; //Time for acceleration
  int tfaR = 0; //Time for acceleration
  int dfaL = 0; //Distance for acceleration
  int dfaR = 0; //Distance for acceleration
  int drL = 0; //Distance remaining
  int drR = 0; //Distance remaining
  int trL = 0; //Time remaining
  int trR = 0; //Time remaining
  int rLoopsL = 0; //Remaining loops
  int rLoopsR = 0; //Remaining loops
  int tftL = 0; //Time for travel
  int tftR = 0; //Time for travel
  int tftLoopsL = 0; //Loops in tft mode
  int tftLoopsR = 0; //Loops in tft mode
  int LoopsMax = 0;
  int rLoopsMax = 0;
  int tftLoopsMax = 0;
  
  int RD = RightDistanceInput; //CM
  int LD = LeftDistanceInput; //CM
  int a = AccelerationInput; //CM

  VcL = a * (1 / 1000) * timeDelay; //Velocity change in CM/s
  LoopsL = velocityMax / VcL; //Calculates how many times to run the loop
  tfaL = LoopsL * timeDelay / 1000;  //Seconds
  dfaL = (1 / 2) * a * tfaL ^ 2; //Distance in cm

  VcR = a * (1 / 1000) * timeDelay; //Velocity change in CM/s
  LoopsR = velocityMax / VcR; //Calculates how many times to run the loop
  tfaR = LoopsR * timeDelay / 1000;  //Seconds
  dfaR = (1 / 2) * a * tfaR ^ 2; //Distance in cm


  if (dfaL <= LD) {
    drL = LD - dfaL;
    trL = drL / velocityMax;
    rLoopsL = trL / timeDelay; //Loops to run at max velocity
  }
  else {
    tftL = RD / velocityMin;
    tftLoopsL = 1000 * tftL / timeDelay;
  }
  if (dfaR <= LD) {
    drR = LD - dfaR;
    trR = drR / velocityMax;
    rLoopsR = trR / timeDelay; //Loops to run at max velocity
  }
  else {
    tftR = RD / velocityMin;
    tftLoopsR = 1000 * tftR / timeDelay;
  }
  LoopsMax = max(LoopsR, LoopsL);
  rLoopsMax = max(rLoopsR, rLoopsL);
  tftLoopsMax = max(tftLoopsR, tftLoopsL);








}
