2015 BattleStation for X7
=========================

Implemented Features:
---------------------
- SDL joystick compatbility
- QTSerial library for connection to top board (writing)
- Basic interpretor to handle ramping up thrusters
- Looks cool  

Todo Features:
--------------
- Compute thruster values based of joystick
- Compute a checksum- Handle reading from serial
- More configuration on main window

How to install and run:
-----------------------
Download and install [Qt](http://qt-project.org/). Open project file in Qt Creater and run qmake to set up build system. Try running it and hopefully everything works. Only dependcies should be Qt and SDL. SDL libraries for Windows and OS X are included in the repository and should be configured to compile with them.


Basic Structure Information:
----------------------------
**QT/**: Contains all main files for the program  
- **ROVTest.pro**: Main project file with build flags/information  
- **C++ Files**:  
 - **main**: includes main function, starts up an instance of battlestation  
 - **battlestation**: main class for the battlestation, handles settings things up and exiting  
 - **threadcontroller**: handles the different threads for the program  
 - **mainticker**: main thread that runs fast, will be used to manage things we need to do every tick (computing thruster vectors, serial, etc.)  
 - **joystick**: joystick class to handle abstraction of SDL and joystick  
 - **inputhandler**: handles input from joystick and main window  
 - **interpolator**: handles ramping up/down of thrusters  
 - **serial**: handles initialization of serial and sending information  
- **QML Files**:  
 - **main**: Main qml file that handles layout of GUI  
 - **ROVBox**: Box to hold things in, with battlestation style  
 - **ROVButton**: Button with battlestation style  
 - **ROVComboBox**: ComboBox with battlestation style  
 - **ROVSlider**: Sliders with battlestation style  
- **Others**:  
 - There are some others small ones, but they have to do with some Qt build things. Nothing that we will editing  

**SDL/**: Contains SDL libraries for Windows and OS X  


# REMINDER: PLEASE EDIT AS NEED. KEEP EVERYTHING AS UP TO DATE AS WE CAN -MM #
