# Software Implementation in Proteus 8

## Here's a Quick Recap for the Software Simulation Implemented in Phase-1

The project implemented a **GPS and GSM-based vehicle tracking system** in **Proteus 8**, simulating the acquisition of GPS coordinates and their transmission via SMS using a **GSM module**. The system utilized an **Arduino Uno** to interface between the **GPS (NEO-6M)** and **GSM (SIM900)** modules. The **GPS module** provided real-time latitude and longitude data, while the **GSM module** sent this data as an SMS to a virtual terminal. 

The simulation allowed testing of both **GPS data acquisition** and **SMS transmission**, ensuring reliable communication between the components before hardware implementation. This project successfully demonstrated an efficient vehicle tracking solution in a virtual environment.


# **GPS-GSM Tracking System: Code & Hardware Integration**

## **Overview**
This system integrates a **GPS module, GSM module, LCD display, and an emergency button** to provide real-time location tracking and messaging functionality. It is designed for applications like vehicle tracking or personal safety alerts.

## **Hardware Components & Role**

| **Component**       | **Functionality** |
|---------------------|------------------|
| **GPS Module**      | Captures latitude & longitude coordinates. |
| **GSM Module (SIM800L)** | Sends SMS alerts containing the GPS location. |
| **LCD Display (16x2)** | Displays system status and GPS coordinates. |
| **SOS Button (Switch)** | Sends location when pressed in an emergency. |
| **Buzzer** | Alerts when GSM fails to initialize or when an SOS is triggered. |
| **Microcontroller (Arduino)** | Controls all modules, processes GPS data, and handles messaging. |

## **Code Breakdown & Execution Flow**

### **1️⃣ Initialization (`setup()`)**
- **LCD, GSM, and GPS** modules are initialized.
- A startup message is sent via SMS (`send_message("System Started")`).
- If GSM fails to initialize after multiple attempts, the system **hangs with a buzzer alert**.

### **2️⃣ GPS Data Acquisition**
- The **GPS module continuously sends data** via serial communication.
- `read_gps2()` extracts latitude and longitude from GPS strings.
- `process_gps_data()` converts raw GPS data into usable coordinates.

### **3️⃣ Sending Location via SMS**
- The function `send_msg_location()` is used to **send an SMS with a Google Maps link** containing the real-time GPS location.
- Example of an SMS message:

Location: http://maps.google.com/maps?q=12.34567,+77.89123


### **4️⃣ Emergency SOS Button Functionality**
- The **switch (Swi) is monitored** in `loop()`.
- If pressed, the system:
1. Reads the **current GPS location**.
2. Sends an **SOS alert SMS**.
3. Displays "SOS" on the LCD.

### **5️⃣ Receiving Commands via SMS**
- `receive_gsm_message()` checks for **incoming SMS messages**.
- If the SMS contains `<LOC>`, the system responds by **sending back its current location**.

### **6️⃣ Continuous Monitoring (`loop()`)**
- The system remains in a **ready state**, checking:  
- If an **SOS is triggered**.  
- If an **SMS request for location is received**.  
- If the **GSM module is still functional**.  

## **Conclusion**
This system ensures **real-time location tracking and emergency alerting** using a GPS-GSM combo. The modularized code structure makes it easy to modify, debug, and expand. 🚀
