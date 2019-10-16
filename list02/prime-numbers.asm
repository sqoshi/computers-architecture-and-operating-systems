
INPUT
Store R1
INPUT
Store R2

print, Load R1
       	output
		Add one
        Store R1
        subt R2
        skipcond 800
        jump loop
        Skipcond 800
   		Jump print
loop, Load X
        
Halt

R1, DEC 0
R2, DEC 0
X, DEC 0
Y, DEC 0
num, DEC 0
one, DEC 1
zero, DEC 0
end, halt
