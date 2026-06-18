# ATmega32 Hardware Pin Mapping Table

| Peripheral Component | Component Pin | ATmega32 Hardware Pin | I/O Direction | Configuration Details |
| :--- | :--- | :--- | :--- | :--- |
| **16x2 LCD Data Bus** | D0 - D7 | Port C (`PC0` - `PC7`) | Output | 8-Bit Parallel, Push-Pull Mode |
| **LCD Control Line** | RS (Register Select) | Dedicated GPIO | Output | Character vs Command Selection |
| **LCD Control Line** | E (Enable Clock) | Dedicated GPIO | Output | High-to-Low Strobe Signal |
| **Pulse Counter Sensor**| Push-Button / Output | `PD2` (`INT0`) | Input | Hardware Internal Pull-Up Enabled |
| **Status Beacon LED** | Anode (+) | `PB2` | Output | Active-High Milestone Signal |