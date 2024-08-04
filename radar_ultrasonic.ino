#include <Servo.h>
#include <Crypto.h>
#include <AES.h>
#include <string.h>

#define trigPin 8
#define echoPin 9

#define MAX_DISTANCE 400 // Max distance in cm (adjust as necessary)

long duration;
int  distance;

Servo myservo;

// 1. Data Transmission Security
byte key[16];
byte iv[16];

int
calculateDistance ()
{
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = duration * 0.034 / 2;

	// 2. Input Validation and Sanitization
	if (distance < 0 || distance > MAX_DISTANCE)
	{
		distance = -1;
	}

	return distance;
}

void
setup ()
{
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	myservo.attach(11);
	Serial.begin(9600);
	// 1. Data Transmission Security
	receiveKeyAndIV();
}

void
loop ()
{
	int  i;
	byte plaintext[16], ciphertext[16];

	for (i = 15; i <= 165; i++)
	{
		myservo.write(i);
		delay(15);
		calculateDistance();

		// Prepare plaintext: angle and distance
		snprintf(
			(char *)plaintext, sizeof(plaintext), "%03d,%03d", i, distance);

		// 1. Data Transmission Security
		aes256.setKey(key, sizeof(key));
		aes256.setIV(iv, sizeof(iv));
		aes256.encrypt(ciphertext, plaintext, sizeof(plaintext));

		// Send encrypted data over Serial
		Serial.write(ciphertext, sizeof(ciphertext));
		// 3. Error handling and logging
		Serial.println("[INFO] Encrypted data sent.");
	}

	for (i = 165; i >= 15; i--)
	{
		myservo.write(i);
		delay(15);
		calculateDistance();

		// Prepare plaintext: angle and distance
		snprintf(
			(char *)plaintext, sizeof(plaintext), "%03d,%03d", i, distance);

		// 1. Data Transmission Security
		aes256.setKey(key, sizeof(key));
		aes256.setIV(iv, sizeof(iv));
		aes256.encrypt(ciphertext, plaintext, sizeof(plaintext));

		// Send encrypted data over Serial
		Serial.write(ciphertext, sizeof(ciphertext));
	}
}

void
receiveKeyAndIV ()
{
	while (Serial.available() < 64)
	{
		// Wait for the entire key and IV to be received
	}

	if (Serial.available() >= 32)
	{
		// Read the key and IV
		for (int i = 0; i < 16; i++)
		{
			key[i] = Serial.read();
		}
		for (int i = 0; i < 16; i++)
		{
			iv[i] = Serial.read();
		}
		Serial.println("[INFO] Key and IV received successfully.");
	}
	else
	{
		Serial.println("[ERROR] Failed to receive key and IV.");
	}
}