# Ultrasonic_radar
The first file is the Arduino sketch
The second file contains the code for Processing IDE 

## General Approach to Embedded Security

1. Threat Analysis
2. Security Requirements
3. Security Evaluation
4. Security Implementation

### Threat Analysis

The Untrasonic_radar project combines Arduino-based hardware control with data
visualization using Processing. The setup involves using an ultrasonic sensor
for distance measurement, a servo motor for rotating the sensor, and a Processing
sketch for visualizing the data in real-time.

The "Ultrasonic Radar" project has several potential vulnerabilities that need
to be addressed to ensure its security and reliability. The main areas of
concern include data integrity, unauthorized access, and proper error handling.

### Security Requirements

1. Data Transmission Security - All data transmitted between the embedded system (Arduino) and external systems (e.g., Processing application) must be encrypted using a secure encryption protocol (e.g., AES, TLS) to prevent unauthorized interception or tampering.
2. Input validation and Sanitization - All input data received from external sources, including sensor data and user inputs, must be validated and sanitized. Input validation must include checks for data type, length, range, and format to prevent injection attacks and buffer overflows.
3. Error handling and logging - Implement comprehensive error handling and logging mechanisms. All errors, exceptions, and security-relevant events must be logged securely and reviewed regularly. Ensure that error messages do not disclose sensitive information that could be exploited by attackers.
4. Secure coding practices - Adhere to secure coding practices, including avoiding the use of deprecated or insecure functions, preventing buffer overflows, and ensuring proper memory management. Use static and dynamic analysis tools to identify and fix potential security vulnerabilities in the code.

### Security Evaluation

1. Data Transmission Security - The project uses unencrypted serial communication between the Arduino and the Processing application.
2. Input Validation and Sanitization - The Processing application reads data from the Arduino and assumes the format and correctness of the data without comprehensive validation.
3. Error Handling and Logging - The project lacks comprehensive error handling and logging mechanisms. There are no clear provisions for logging errors or security-relevant events.
4. Secure Coding Practices - The project does not explicitly demonstrate adherence to secure coding practices. For instance, there are potential issues with buffer overflows, especially in the Processing sketch when handling string data from the serial input.

### Security Implementation

1. Data Transmission Security - added AES encryption to data.
2. Input Validation and Sanitization - validated range of movement. 
3. Error Handling and Logging - added try / catch blocks, and logging.
4. Secure Coding Practices - formatted the code to the BARR embedded standard 
using clang-format.