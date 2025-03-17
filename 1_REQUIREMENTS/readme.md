# High-Level Requirements (HLR)

1. **Real-Time Vehicle Tracking**  
   - The system must track vehicle locations in real-time using the NEO-6M GPS module, ensuring location accuracy within 2.5 meters.  

2. **User-Friendly Application**  
   - Develop a mobile application compatible with both Android and iOS platforms to display vehicle location via Google Maps API.  

3. **GSM-Based Communication**  
   - Enable seamless communication of vehicle location data through SMS using the SIM800L GSM module.  

4. **Supply Chain Transparency**  
   - Promote transparency by providing real-time updates on vehicle movement, environmental conditions, and product safety to all stakeholders.  

---

# Low-Level Requirements (LLR)

1. **Arduino Integration**  
   - Utilize Arduino Uno R3 to manage data flow and coordination between GPS, GSM, DHT11, HX711 load cell, and other modules.  

2. **GPS Module**  
   - Integrate the NEO-6M GPS module for precise location tracking.  

3. **GSM Module**  
   - Implement the SIM800L GSM module to transmit real-time location and environmental data via SMS.  

4. **Environmental Sensors**  
   - **DHT11 Sensor**: Monitor temperature and humidity levels during transit.  
   - **HX711 Load Cell**: Measure and display load weight to ensure adherence to safe loading limits.  

5. **Real-Time Data Display**  
   - Equip the vehicle with a 16x2 LCD display to show live data such as coordinates, temperature, humidity, and load weight for operators.  

6. **Mobile App Integration**  
   - Ensure compatibility with Google Maps API for intuitive location tracking and route visualization.

---

# Non-Functional Requirements (NFR)

1. **Energy Efficiency**  
   - Optimize the system to minimize battery consumption, ensuring uninterrupted operation during extended transit durations.  

2. **Scalability**  
   - Design the system to support tracking and monitoring multiple vehicles, allowing for fleet management capabilities in larger-scale operations.  

3. **Cost-Effectiveness**  
   - Ensure the system remains affordable for farmers and small-scale operators without compromising essential features.  

4. **Reliability**  
   - Ensure reliable operation even in areas with weak GSM network coverage, leveraging optimized communication protocols.  

5. **Tamper Resistance**  
   - Incorporate robust physical and software-based measures to prevent unauthorized access or tampering with the system hardware and data.  

6. **Modular Design**  
   - Design the system to allow easy integration of additional sensors or upgrades, such as cloud-based data analytics, without significant structural changes.  

