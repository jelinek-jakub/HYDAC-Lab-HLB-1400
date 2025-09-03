# Library for interfacing with the HYDAC Lab® HLB 1400 sensor

 **HYDAC Lab® HLB 1400** is a multifunctional sensor for online monitoring of the condition of standard oils and bio-oils in industrial and mobile applications.

---

## 🛠️ Features

- **HSP Protocol Implementation**: Decodes and handles requests and responses based on the Hydac Simple Protocol (HSP) / RS485.
- **Request Types**:
  - `Id`: Retrieves the sensor's identification information.
  - `Status`: Obtains the current operational status of the sensor.
  - `Data`: Fetches real-time oil condition data.
- **Data Decoding**: Requests and responses were captured via a COM analyzer and decoded due to the lack of available online documentation.

---

## 🧰 Hardware Requirements

- **Microcontroller e.g.**: ATmega328 (Arduino UNO), ESP32 (ESP32 DevKitC), RP2040 (Raspberry Pi Pico), ..
- **RS485 Transceiver**: e.g., MAX485 or similar module
- **Connections**:
  - Connect the RS485 module to the ESP32 UART pins.
  - Ensure proper termination and biasing for RS485 communication.

---

## ⚙️ Usage

- Upon successful communication, the program will retrieve and display sensor data such as saturation level, temperature, dielectric constant, and electrical conductivity.
- Consider integrating with a display or logging system to visualize and store the retrieved data.

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

For more information on the HYDAC Lab® HLB 1400 sensor, refer to the official documentation:
- [HYDAC Lab® HLB 1400 Product Page](https://www.hydac.com/shop/en/sensors/fluid-monitoring-sensors/oil-condition)
- [HYDAC Lab® HLB 1400 Catalog PDF](https://catalog.schroederindustries.com/Asset/_HLB%201400%20Catalog%20Pages.pdf)

For detailed technical specifications and installation guidelines, consult the [HLB 1400 User Manual](https://www.hydac.com/shop/en/924586).
