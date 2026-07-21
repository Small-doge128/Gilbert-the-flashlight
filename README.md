# About
A really nice flashlight, which is small as a box of TIC-TACs with two buttons, an OLED and a bright LED powered by a battery. It looks like a samsung SSD and It's my first time using and coding a display. [onshape](https://cad.onshape.com/documents/cd0ef959b6cca3fa70459174/w/619a7eb4bf14ab27515c2c02/e/2342898b3dd9987e8f05f571). 

# features
A really nice OLED for informations powered by a 1 200 mAh LiPo battery. The brain is a seeed studio xiao esp32-s3. The main things are the powerfull warm LEDs with a resistor.

# step by step tutorial for firmware

1 - download the whole file called - gilbert the flashlight .bin files.                                                                                              
2 - connect your seeed studio via usb-c.                                                                                                                    
3 - Put it into bootloader mode (hold the **B** button, while holding press the **RST** button and then release).                                                  
4 - open this link in browser -> [esspresif bootloader](https://esptool.spacehuhn.com) (safari won't work install another browser).                                                        
5 - select your port where you have the seeed studio connected.                                                                                  
6 - set the baud rate to **115200**.                                                                                                                    
7 - load the files you downloaded earlier at these memory ofsets.                                                                        
 - `bootloader.bin` -> `0x0`                                                                                                                           
 - `partitions.bin` -> `0x8000`                                                                                                                           
 - `firmware.bin`   -> `0x10000`
                                                                                                        
8 - click **Program** to flash now it should work **enjoy**.

# dimensions
the LED pcb- 38 mm x 8 mm x 1.6 mm                                                                                                                                               
the whole flashlight- 40 mm x 78 mm x 9 mm

# why did i create it
I already had a good flashlight, but this is better and It's more like me with a warmer LEDs which are better and a display that shows lumens and more.

# pictures

<img width="1391" height="381" alt="image" src="https://github.com/user-attachments/assets/9120ba43-7540-40fa-a19c-ad9d4a4de088" />

<img width="1141" height="701" alt="2026-07-03-093042_hyprshot" src="https://github.com/user-attachments/assets/60025b9a-526c-4096-b800-291d1127b08e" />

<img width="901" height="620" alt="Screenshot 2026-07-18 180422" src="https://github.com/user-attachments/assets/fcc42672-fa0d-4f69-a435-ce81764d8d55" />

<img width="1319" height="850" alt="image" src="https://github.com/user-attachments/assets/d8cff0c7-420f-4c7b-97a9-5f99e7944c31" />
