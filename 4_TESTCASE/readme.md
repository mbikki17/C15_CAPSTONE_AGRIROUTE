# Test Case Summary for GPS and GSM Vehicle Tracking System from Phase-1

The test cases for the GPS and GSM Vehicle Tracking System in Proteus 8 focus on validating core functionalities like GPS data acquisition and SMS transmission. The tests ensure that the system:

- Correctly acquires valid GPS coordinates.
- Displays accurate latitude and longitude.
- Sends the GPS data as SMS messages in the correct format.

Additionally, the system is checked for handling GPS signal loss by displaying default values (`0.0, 0.0`) for latitude and longitude. The GSM module’s ability to send the correct SMS after successful GPS data retrieval is also tested, ensuring accurate communication and system behavior.


# **Test Case Summary for GPS-GSM Tracking System from Phase-2**

The test cases for the **GPS-GSM Tracking System** focus on validating the **core functionalities** such as GPS data acquisition, SMS transmission, and emergency alert handling. The tests ensure that the system:

- Successfully **acquires valid GPS coordinates**.
- Displays **accurate latitude and longitude** on the LCD.
- Sends **SMS messages with correct GPS data and Google Maps link**.
- Properly detects and responds to the **SOS button press**.
- Correctly receives and processes **SMS commands** for location retrieval.

Additionally, the system is tested for **GPS signal loss handling**, ensuring that default values (`0.0, 0.0`) are displayed when no GPS signal is detected. The GSM module’s ability to send SMS messages **only after successful GPS data retrieval** is also verified to ensure **accurate system behavior and reliable communication**.
