# README
This repository contains files I used in modual 2 Electrical Engineering at the University of Twente, as part of my minor.

## CODE
The file Mosfet50Hz_H-bridge contains code for an ESP32, which can drive a full H-bridge in order to get from DC to AC current. It needs to be conneceted to the grid with an optocoupler in order to get syncing to the grid to work. A phase offset can be inputted to get the output to sync with the grid. It depends on your circuit and filter, how much this is [0-360].