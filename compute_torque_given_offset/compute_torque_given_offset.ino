// compute_torque_given_offset.ino
// Computes torque associated with measurement of phase offset from IC.
// Requires calibration curve associated with the direct relationship
// between phase offset of hall effect sensor and torque.
// Modeled after the AD9901 part which converts phase offset to a duty cycle.

//// Constants associated with duty cycle calculaton.
// Digital pin associated with reading in pulse. 
int phaseOffsetPin = 7;
// Time pulse spends at HIGH state.
float timeOn;
// Time pulse spends at LOW state.
float timeOff;
// Sum of timeOn and timeOff, used to calculate cycle.
float totalTime;
// Duty cycle of sensor output (and pin input). 
int dutyCycle;


void setup() {
  Serial.begin(115200);
  pinMode(phaseOffsetPin, INPUT);
}

void loop() {
  /*
    Measure the duty cycle to find the phase offset associated with the
    measurement, and then calculate the torque associated with that. Print that
    offset to the serial monitor.
  */
  // Input value based out output of the AD9901 phase offset calculation.  
  timeOn = pulseIn(phaseOffsetPin, HIGH);
  timeOff = pulseIn(phaseOffsetPin, LOW);
  totalTime = timeOn + timeOff;
  dutyCycle = (timeOn/totalTime) * 100;
  float torque = cycleToTorque(dutyCycle);
  Serial.print("Torque: ");
  Serial.println(torque);
  // Let the ADC readjust as needed.
  delay(100);
}

float cycleToTorque(int offset) {
  /*
    Compute torque value associated with phase offset. This would
    need to be manually calibrated based on the actual relationship
    between known torques and associated offsets. In their absence, 
    this function returns the original offset value multiplied by 
    a constant and added to some unit offset. 
    Otherwise would convert offset output to torque in Nm.
  */ 
    
  // Constants associated with torque calculation - currently arbitrary.
  float k = .02;
  float b = .01;
  return offset * k + b;
}
