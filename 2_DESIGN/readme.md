# GPS and GSM-Based Vehicle Tracking System

## High-Level Design (HLD)

### 1. Architectural Overview

#### System Architecture
The system follows a three-tier architecture:

- **Frontend (Mobile Application):**  
  - Provides a user interface for real-time vehicle monitoring and notifications.

- **Backend (Server Infrastructure):**  
  - Manages data processing, storage, and analytics.

- **Hardware (Vehicle Tracking Unit):**  
  - Captures and transmits real-time location data.

#### Key Components

##### Vehicle Tracking Unit
- **GPS Module (uBlox 6M):** Tracks vehicle location with latitude and longitude updates.
- **GSM Module (SIM800L):** Sends real-time location data via SMS.
- **Microcontroller (Arduino Nano):** Coordinates data flow between GPS and GSM modules.
- **Power Management:** Battery with TP4056 charging module and MT3608 voltage regulator.

##### Mobile Application
- **Technologies:** Flutter/React Native for cross-platform support.
- **Features:**  
  - Live map view for real-time tracking.
  - Notification system for alerts (location updates, delays).
  - Feedback submission interface.

##### Server Infrastructure
- **Web Server:** Handles data requests and user management.
- **Database:** Stores user details, tracking history, and vehicle data.
- **APIs:** RESTful endpoints for seamless communication between the mobile app and backend.

### 2. Main Features
- **Real-time Vehicle Tracking:** Updates vehicle movements at regular intervals.
- **User Notifications:** Alerts for location changes, unexpected stops, and delays.
- **Mapping Services:** Google Maps API integration for visualizing routes.
- **Feedback System:** Users can provide feedback for service improvements.

---

## Low-Level Design (LLD)

### 1. Detailed Module Design

#### Vehicle Tracking Unit
- **GPS Module (uBlox 6M):**  
  - Captures geographic coordinates every 5 seconds.
- **GSM Module (SIM800L):**  
  - Sends SMS containing location data to the backend server.
- **Microcontroller (Arduino Nano):**  
  - Manages communication between GPS and GSM modules.
  - Programmed using Arduino IDE.
- **Power Supply:**  
  - Uses a 3.7V Li-ion battery, managed by a TP4056 module for charging and an MT3608 boost converter for voltage regulation.

#### Mobile Application
- **Technologies:** Flutter/React Native for Android & iOS compatibility.
- **Key Components:**  
  - **Home Page:** Displays real-time vehicle locations using Google Maps API.
  - **Tracking Page:** Shows historical location data.
  - **Feedback Page:** Allows users to submit ratings and comments.
  - **Authentication:** Secure login using email/password or OAuth.

#### Server Infrastructure
- **Technologies:** Node.js/Django for backend logic.
- **Data Handling:**  
  - Parses and stores SMS-based location updates.
  - Uses MongoDB for flexible, high-speed data storage.
- **API Endpoints:**  
  - `POST /api/track` → Stores new location updates.
  - `GET /api/vehicles/:id` → Retrieves vehicle tracking history.
  - `POST /api/feedback` → Collects user feedback.
- **Google Maps Integration:**  
  - Renders interactive maps.
  - Optimizes vehicle routes for better delivery efficiency.

### 2. Database Design

#### Tables and Schema

##### Users Table
| Column        | Data Type  | Description                          |
|--------------|-----------|--------------------------------------|
| UserID       | INT (PK)  | Unique identifier for users         |
| Name         | VARCHAR   | User's full name                    |
| Email        | VARCHAR   | User's email for authentication     |
| PasswordHash | VARCHAR   | Encrypted password                  |
| PhoneNumber  | VARCHAR   | Contact number                      |
| Role         | ENUM      | Defines user type (Admin, Consumer, Driver) |

##### Vehicles Table
| Column       | Data Type  | Description                          |
|-------------|-----------|--------------------------------------|
| VehicleID   | INT (PK)  | Unique identifier for each vehicle  |
| UserID      | INT (FK)  | References owner/driver             |
| VehicleType | VARCHAR   | Type of vehicle (Truck, Van, Bike)  |
| CurrentStatus | ENUM    | Active/Inactive                     |
| LastUpdated | TIMESTAMP | Last recorded update time           |

##### Tracking Data Table
| Column       | Data Type  | Description                          |
|-------------|-----------|--------------------------------------|
| TrackingID  | INT (PK)  | Unique identifier for each tracking entry |
| VehicleID   | INT (FK)  | References vehicle                  |
| Latitude    | FLOAT     | Current latitude                    |
| Longitude   | FLOAT     | Current longitude                   |
| Timestamp   | TIMESTAMP | Time of record                      |

##### Feedback Table
| Column       | Data Type  | Description                          |
|-------------|-----------|--------------------------------------|
| FeedbackID  | INT (PK)  | Unique feedback entry ID            |
| UserID      | INT (FK)  | References user                     |
| VehicleID   | INT (FK)  | References vehicle                  |
| Rating      | INT       | User rating (1-5)                   |
| Comments    | TEXT      | Additional feedback                 |
| Timestamp   | TIMESTAMP | Time of submission                  |

#### Relationships
- **One-to-Many:** Users → Vehicles.
- **One-to-Many:** Vehicles → Tracking Data.
- **One-to-Many:** Users → Feedback.

### 3. Scalability & Performance Considerations
- **Load Balancing:** Distributes network requests across multiple backend servers.
- **Data Caching:** Uses Redis to store frequently accessed data, improving response times.
- **Rate Limiting:** Prevents abuse by restricting excessive API requests.


