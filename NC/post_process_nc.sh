#!/bin/bash

# Define the directory path
DIRECTORY=/home/pi/Documents/laser_nc/NC-CAR2
DIRECTORY=/home/pi/Documents/papyrusplane/NC_CAR2/
DIRECTORY=/home/pi/Documents/AdruinoAtariPaddle/NC

# Define the Python program name
PYTHON_PROGRAM=/home/pi/Documents/laser_nc/post_process_nc.py

# Execute the Python program with hardcoded command line parameters
echo $PYTHON_PROGRAM $DIRECTORY
python3 $PYTHON_PROGRAM $DIRECTORY

# Check the exit status of the Python program
if [ $? -ne 0 ]; then
    echo "Error: Python program failed with exit status $?"
    exit 1
fi

echo "NC files processed successfully."

