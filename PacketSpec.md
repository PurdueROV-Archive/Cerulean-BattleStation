Packet Spec

0x12 = Header byte  
Motor 1 = Signed int (1 byte)   
Motor 2 = Signed int (1 byte)  
Motor 3 = Signed int (1 byte)  
Motor 4 = Signed int (1 byte)  
Motor 5 = Signed int (1 byte)  
Motor 6 = Signed int (1 byte)  
Motor 7 = Signed int (1 byte)  
Motor 8 = Signed int (1 byte)  
Tools 1 = 1 bit more each state of tool (maybe more if tool is complex)  
Foot Turning Motor = Signed int (1 byte) 
LED1 = 1 byte  
LED2 = 1 byte  
LED3 = 1 byte  
LED4 = 1 byte  
LED5 = 1 byte  
CRC 8 checksum (use 0xD5 as polynomial)  
0x13 = Tail Byte  


Motor signed bit representation (and foot turner)
Use bit masking to get the sign bit, and then the motor value  
Scale the percentage from 0 to 127 to 0% to 100%  

Bit Values | Dec Value | Motor Percent 
-----------|-----------|---------------
0000 0000  |         0 |            0
0000 0001  |         1 |            1
0111 1111  |       127 |          100
1000 0000  |       128 |           -0
1000 0001  |       129 |           -1
1111 1111  |       255 |         -100


Tool Representation (Subject to change depending on tools)  
Use bit masking to get off the values you need (magic!)  

Tool Byte 1
Bit # |   Tool   | State (0)  | State (1)  
------|----------|------------|----------  
  1   |Cam Mux 1 |      Front | Back  
  2   |Cam Mux 2 |     Side 1 | Side 2  
  3   |  Bilge   |        Off | On  
  4   |   Volt   |        Off | On 
  5   |  Laser   |        Off | On
  6   |  Claw 1  |        Off | Open  
  7   |  Claw 2  |        Off | Close  
  8   |  Claw 3  |    No Par. | Parallel  


Claw States
 Value | State
-------|--------------------------------
   000 | Do Nothing  
   001 | Open  
   010 | Close 
   011 | Open & Close, BAD -> Set to 00  
   100 | Set parallel (Also do nothing)  
   101 | Set parallel, Open  
   110 | Set parallel, Close  
   111 | Do nothing  
   

Laser Tool: 1 bit for controller whether the horizontal or
vertical stepper move l/r and 3 bits for 0 to 7 steps to move
Bit # | State (0)  | State (1)
------|------------|----------
  1   | H - Left   | H - Right
  2   | Step Amnt  | Step Amnt
  3   | Step Amnt  | Step Amnt
  4   | Step Amnt  | Step Amnt
  5   | V - Left   | V - Right
  6   | Step Amnt  | Step Amnt
  7   | Step Amnt  | Step Amnt
  8   | Step Amnt  | Step Amnt
