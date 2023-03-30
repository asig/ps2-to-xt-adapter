ps2-to-xt-adapter
=================

When I bought an ancient IBM 5150 without a keyboard, I first assumed that I could just use one of my old PS/2 keyboards. Well, I learned that this is not true... So I built a small adapter that lets you use a PS/2 keyboard with an IBM 5150 or 5160 (XT) computer. It was a great learning experience :-)

How to build the adapter
------------------------
Building the adapter is quite simple. All you need is:

1. a 5-pin DIN 41524 plug 
2. a PS/2 socket
3. an ATtiny85 microcontroller (optionally with socket)
4. a prototype board

Solder the PS/2 and DIN 41524 connectors according to the schematics and adapter.fzz

Use the Arduino IDE to build the code and upload it to an ATtiny85. 

Files
-----

|File                                                | Description                                                  |
|----------------------------------------------------|--------------------------------------------------------------|
| capture/*                                          | Bunch of protocol captures, captured with saleae Logc 1.2.18 |
| schematics/adapter.fzz                             | schematics for the breadboard in Fritzing                    |
| schematics/adapter_bb.png                          | PNG export of breadboard schematics                          |
| schematics/adapter_bb.svg                          | SVG export of breadboard schematics                          |
| schematics/DIN-Stecker-Pinbelegung-AT-Keyboard.svg | XT connector's pinout                                        |
| schematics/ps2-pcb.svg                             | PS/2 connector's pinout                                      |
| ps2-to-xt-adapter.ino                              | Code for the actual protocol conversion                      |
| ScanCodeMapping.tsv                                | Tab-separated file containg the scan code mapping from XT to PS/2. Collected from all over the internet, most prominently from Adam Chapweske's PS/2 pages |
| gen_mapping.py                                     | Python script that reads ScanCodeMapping.tsv and generates the translation tables used in ps2-to-xt-adapter.ino |
| README.md                                          | This file.                                                   |

