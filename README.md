# LED Propeller Display
We made a LED Propeller Display in 24 hours for Bath Hack 2023 which is a hackathon aimed at students at the University of Bath. 

Our project rapidly rotates and controls 8 LEDs to trick our vision into seeing a circular display. It works by using the perception of vision effect where an after image will persist in our vision for a short amount of time for quick moving objects. 

| ![gallery](https://user-images.githubusercontent.com/43008203/229592135-ecd92f29-15f5-485d-b355-c066a31b60e8.jpg) |
|:--:| 
| *Our display showing the text BATH* |



| ![gallery (1)](https://user-images.githubusercontent.com/43008203/229592175-3c9b9f56-2a92-4eff-abac-e0a2d1a9f230.jpg) |
|:--:| 
| *Our system when its not rotating* |

## How we built it
The hardware was designed and assembled alongside the development of the software. We utilised 3 pre-built parts and 3D printed/cut 4 bespoke components. As our system rotates it is important for it to be reasonably well balanced around the centre of rotation, this was achieved by approximating the shape of the Arduino base and moving the battery on its mount to compensate for any discrepancy.

On the software side of things, we implemented all of our code in C++ and used the PlatformIO framework to manage our code on our Arduinos. Our program worked by creating frames which was an array of chars, where each char represented the 8 LEDs through its 8 bits. In our main program loop, we iterate through this grid, mapping it onto our circular display. Our project could automatically generate grids from strings or we could define custom grids to make cool custom patterns. This made it very easy to display whatever we wanted

## Devpost
Here is a link to the devpost we submitted in the hackathon: https://devpost.com/software/propeller-display
