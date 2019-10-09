#!/bin/bash
sudo rm -rf $HOME/PlanetMiner && cp -avr $WIN/PlanetMiner $HOME/PlanetMiner && cd $HOME/PlanetMiner && ./compile.sh && bin/planetminer && cd ..