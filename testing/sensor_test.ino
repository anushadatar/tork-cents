// Code to test hall effect sensor. Open up serial plotter to see the output. 

const int sensorPin = A0;
int sensorValue = 0;        

void setup() {
  // Kick off serial plotter.
  Serial.begin(9600);
}

void loop() {
  // Read in the value.
  sensorValue = analogRead(sensorPin);

  // Print the results to the Serial Monitor (though probably use the plotter)
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print('\n');

  // Let the ADC readjust as needed.
  delay(2);
}
