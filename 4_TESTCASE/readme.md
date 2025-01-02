# Test Cases for GPS and GSM Vehicle Tracking System - Software Simulation

This document outlines the test cases for validating the functionality of the **GPS and GSM Vehicle Tracking System** simulation implemented in Proteus 8. The tests ensure that the system behaves as expected in terms of data acquisition, SMS sending, and error handling.

## Test Case Structure

### 1. **Test Case ID**: TC-GPS-001
**Objective**: Verify GPS Data Acquisition

- **Preconditions**: 
  - The simulation is running in Proteus 8.
  - GPS module is correctly connected to the Arduino.

- **Test Steps**:
  1. Run the simulation.
  2. Observe the output from the GPS module.

- **Expected Result**: 
  - The system should acquire valid GPS coordinates (latitude and longitude) within one second of simulation.

- **Pass/Fail Criteria**:
  - Pass if valid coordinates are displayed in the output.
  - Fail if the output shows `Latitude = 0.0, Longitude = 0.0` without valid GPS data.

### 2. **Test Case ID**: TC-GSM-001
**Objective**: Verify SMS Sending Functionality

- **Preconditions**:
  - The GPS module successfully acquires valid coordinates.
  - The GSM module is connected and properly powered.

- **Test Steps**:
  1. Run the simulation after the GPS coordinates are acquired.
  2. Check the virtual terminal output for SMS sent by the GSM module.

- **Expected Result**: 
  - The GSM module should send an SMS with the correct format:
    ```
    Latitude = [valid_latitude], Longitude = [valid_longitude]
    ```

- **Pass/Fail Criteria**:
  - Pass if the SMS appears in the virtual terminal with correct coordinates.
  - Fail if the SMS is missing or the coordinates are incorrect.

### 3. **Test Case ID**: TC-ERROR-001
**Objective**: Verify System Behavior on GPS Signal Loss

- **Preconditions**:
  - The simulation is running in Proteus 8.
  - GPS module was successfully sending data before the signal loss.

- **Test Steps**:
  1. Manually disconnect the GPS module in the simulation to simulate a signal loss.
  2. Observe the output for GPS data retrieval.

- **Expected Result**: 
  - The system should handle the signal loss gracefully, sending an SMS with:
    ```
    Latitude = 0.0, Longitude = 0.0
    ```

- **Pass/Fail Criteria**:
  - Pass if the SMS is sent with `0.0` values for latitude and longitude.
  - Fail if the system crashes or behaves unpredictably without sending a message.

### 4. **Test Case ID**: TC-GSM-ERROR-001
**Objective**: Verify GSM Module Response to Failed SMS Sending

- **Preconditions**:
  - The simulation is running with a valid GSM connection.

- **Test Steps**:
  1. Introduce an error condition in the GSM module by simulating a failure in sending an SMS (e.g., invalid phone number).
  2. Observe the serial output for any error messages.

- **Expected Result**: 
  - The system should indicate an error in sending the SMS.

- **Pass/Fail Criteria**:
  - Pass if the error condition is logged in the output.
  - Fail if there’s no indication of a sending error.

## Conclusion

These test cases are designed to comprehensively verify the functionality of the GPS and GSM Vehicle Tracking System simulation. By following these tests, developers can ensure that both modules operate correctly and handle errors gracefully, enhancing the reliability of the overall system.

For any failures observed during testing, please review the connections and configurations in the Proteus simulation environment.
