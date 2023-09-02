# ArduinoDjStrobeLight
DIY Strobe light I made to go along with my DJing

# Features
- Adjust BPM by hand
- Half and Double BPM
- "Normal" Button to go back to original (non doubled or halved stance)
  - The two above are meant to be used for drops where BPM quickly changes
- "Start" button on rotary encoder
  - Hold it down to keep lights off
  - As soon as it is released,  lights flash. This is used to adjust timing

## Showcase Video
https://github.com/MarioPardo/ArduinoDjStrobeLight/assets/26777517/e2fd5d33-7d67-4bd2-8687-4f41f1738fb8


## Circuit
![DJStrobeLightCircuit](https://github.com/MarioPardo/ArduinoDjStrobeLight/assets/26777517/754d18e4-a739-4e98-95bc-b48eae063fa3)
Note that the pins do not match the code or design exactly due to not having the proper parts on the design software. 
Every pin is labeled in the code, so everything should be quite self explanatory
I'm using a 5V LED Strip so the power supply should be 5V.
Other voltages can be used, although the resistor used for the MOSFET might have to be different. In the diagram, a GDS (left to right) MOSFET is used.

![IMG_2673](https://github.com/MarioPardo/ArduinoDjStrobeLight/assets/26777517/0ad6c5a3-0148-4d28-bb42-8f022d9b1848)
