# External Interrupt Counter Configuration

The ATmega32 processes incoming external pulses using **External Interrupt 0 (INT0)**. This configuration guarantees real-time accuracy completely independent of background display cycles.

### Register Control Logic
1. **Data Direction (`DDRD`):** Pin `PD2` is cleared (`0`) to operate as a digital input stage.
2. **Pull-Up Activation (`PORTD`):** Pin `PD2` is asserted (`1`) to activate the internal pull-up resistor, preventing floating signal states.
3. **Interrupt Sense Control (`MCUCR`):** The `ISC01` bit is set to `1` and `ISC00` is cleared to `0`. This configures the hardware to trigger uniquely on a **falling edge** (when the input pulse transitions from High to Low).
4. **Global Enable (`GICR` & Status Register):** Bit 6 (`INT0`) of the `GICR` register is enabled, and global interrupts are activated via the `sei()` assembly instruction macro.