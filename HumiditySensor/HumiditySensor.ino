//jb3804
#include <DHT.h>

// DHT configuration
#define DHTPIN 3       // Defines the pin for the humidity sensor as D3
#define DHTTYPE DHT11  // Tells the arduino using the downloaded DHT module which DHT sensor I'm using.
DHT dht(DHTPIN, DHTTYPE); //Configures the DHT given its type and pin

// Buzzer (transistor base) pin
#define BUZZER_PIN 5   // D5 (drives the base of NPN transistor)

void setup() {
  Serial.begin(9600); //Sets the baud rate for the serial monitor output
  dht.begin(); //Initialises the DHT module allowing me to use the functions such as readHumidity()
  pinMode(BUZZER_PIN, OUTPUT); //Defines the pinmode as an output pin because it is providing voltage.
  digitalWrite(BUZZER_PIN, LOW); // Make sure buzzer is off at start
}

void loop() {
  float humidity = dht.readHumidity(); //Saves the value read from the sensor using the DHT module and stores it as humidity

  // Check if reading failed
  if (isnan(humidity)) { //Checks if the humidity sensor returns a valid number, if not undergoes this loop to handle the error
    Serial.println("Failed to read from DHT11 sensor!"); //Print on to the serial monitor that the humidity sensor cannot be read
    delay(2000); //Waits so that it can recursively perform this in a reasonable time
    return;
  }

  Serial.print("Humidity: "); //Prints the current humidity by taking the humidity value that's read
  Serial.print(humidity);
  Serial.println(" %");

  if (humidity >= 60.0) {
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer by powering the base of the transistor
    Serial.println("BUZZER ON"); //Print on the serial monitor that the buzzer is on
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Turn OFF buzzer for when the humidity is less than 60%
  }

  delay(2000); // Wait before next reading
}