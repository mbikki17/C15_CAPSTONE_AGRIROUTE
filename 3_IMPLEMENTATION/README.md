# SOFTWARE IMPLEMENTATION: GPS and GSM Vehicle Tracking System in Proteus 8

This project simulates a GPS and GSM-based vehicle tracking system using **Proteus 8**. The simulation demonstrates how real-time GPS coordinates can be obtained and sent via SMS using GSM communication, all within a virtual environment.

## How the Simulation Works

The simulation models a **vehicle tracking system** using GPS and GSM modules. It performs the following tasks:
1. **Simulate GPS Data**: The GPS module generates latitude and longitude coordinates.
2. **Send SMS Using GSM**: The GSM module sends the location information to a virtual phone number in the Proteus environment.

### 1. `inc/gps_tracking.h`

This file contains the declarations for the functions and global variables:
- **TinyGPS gps**: Object for simulating GPS data.
- **SoftwareSerial SIM900(7, 8)**: Serial communication object for the GSM module simulation.

### 2. `src/gps_tracking.cpp`

This file contains the main logic for the GPS and GSM modules in the simulation environment.

- **`setupGPS()`**:
  - Initializes serial communication for the simulated GPS and GSM modules in Proteus.

- **`loopGPS()`**:
  - Simulates reading GPS data for one second.
  - If valid GPS data is available, it retrieves the latitude and longitude.
  - Sends this data through the GSM module as an SMS using AT commands.

### 3. `test/gps_tracking_test.cpp`

This file is used to run and test the simulation in Proteus.

- **`setup()`**: Initializes the simulated GPS and GSM modules.
- **`loop()`**: Simulates the continuous process of acquiring GPS data and sending it via SMS in Proteus.

## How to Run the Simulation in Proteus 8

### Step 1: Create a New Project in Proteus 8
- **GPS Module**: Place the **NEO-6M GPS** module in the simulation environment.
- **GSM Module**: Place the **SIM900 GSM** module in the simulation environment.
- **Arduino**: Add an **Arduino Uno** to interface the GPS and GSM modules.

### Step 2: Connect Components
- Connect the GPS module’s **TX** to Arduino **pin 4** and **RX** to **pin 3**.
- Connect the GSM module’s **TX** to Arduino **pin 7** and **RX** to **pin 8**.
- Set up the necessary power supplies and ground connections for the modules.

### Step 3: Upload the Code
- In **Proteus**, load the compiled HEX file generated from the `gps_tracking_test.cpp` file into the Arduino.

### Step 4: Simulate the System
- Run the simulation in **Proteus 8**.
- The GPS module will generate location data, and the GSM module will send an SMS with the following format:
- Latitude = 12.971598, Longitude = 77.594566

### Step 5: Monitor Output
- In the **Virtual Terminal** of Proteus, monitor the incoming messages from the GSM module.
- The system will display the latitude and longitude based on the simulated GPS coordinates and send the data via SMS.

## Test Cases in Simulation

### 1. **GPS Data Acquisition Simulation**
- **Objective**: Verify that the GPS module in Proteus simulates valid latitude and longitude data.
- **Expected Result**: The simulated GPS module should generate valid coordinates and send them to the Arduino.

### 2. **GSM SMS Simulation**
- **Objective**: Verify that the GSM module can send an SMS with the correct GPS coordinates.
- **Expected Result**: The GSM module should simulate sending an SMS to the virtual terminal with the format:
- Latitude = X.XXXXXX, Longitude = Y.YYYYYY

## Conclusion

This simulation in Proteus 8 demonstrates the core functionality of the GPS and GSM vehicle tracking system:
- Reading GPS coordinates.
- Sending the coordinates via SMS using the GSM module.

It provides a controlled virtual environment for testing the communication between GPS, GSM, and Arduino before implementing the hardware.

