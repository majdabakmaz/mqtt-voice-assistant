# Setting up 
This project conatins two apps: oled-app and speech-recognition-app.
The oled-app is created to run on any ESP32 development board, and the speech-recognition-app is created for the ESP32LyraT v4.3 board
Connect both boards to the computer

## An mqtt broker
You need to create an instance of an mqtt broker and find its url, write this into the projectconf.h file of both apps
Also write the SSID and password of the network your computer that's running the broker is connected to 

## WSL setup
If you're not running Linux, you will need to set up WSL2 and enable it to access COM ports.
Use this guide: # https://learn.microsoft.com/en-us/windows/wsl/connect-usb

### Find the port 
```
ls -al /dev/ttyUSB*
```

### Build and run apps
Open two terminals, position yourself in the project directory, and in each do the following:
```
cd speech-recognition-app 
sudo docker build --build-arg="PORT=/dev/ttyUSB1" -t my-image-lyra .                
sudo docker run --rm -v $PWD:/project -u $UID -e HOME=/tmp --group-add dialout --device=/dev/ttyUSB1 -it  my-image-lyra
```
Replace the "/dev/ttyUSB*" with the port the board is connected to
```
cd oled-app
sudo docker build --build-arg="PORT=/dev/ttyUSB0" -t my-image-esp32 .
sudo docker run --rm -v $PWD:/project -u $UID -e HOME=/tmp --group-add dialout --device=/dev/ttyUSB0 -it  my-image-esp32
```

### Now press the Mode button on LyraT and say "Say hello!"
