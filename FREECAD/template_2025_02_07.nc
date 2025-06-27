(======START=====================)
(REPLACE .000000 ; )
(REPLACE Z-5; Z-5 S1000 	(---Laser 100% ON))
(REPLACE Z4 ; Z4 S0 	(---Laser 00% OFF))
(REPLACE F0 ; F1000  or F750 )
(REPLACE F0 ; F1000  or F750  remember some G code would like at F1000)
(======CODE MANDATORY============)
M3 S0  (M03 – Spindle on in a clockwise)
(================================)
S0 		(--LaserOff 000% OFF)
G0 F1000 X0.000000 Y0.000000
S1000	(---LaserOn 100% ON)
S0 		(---LaserOff 000% OFF)
(=BEGIN Engrave=========================)


(=END Engrave===========================)
(======END============)
(G00 – Rapid Positioning------------Laser OFF)
S0 (---Laser 00% OFF)
G0 Z10.000000
(======END============)
