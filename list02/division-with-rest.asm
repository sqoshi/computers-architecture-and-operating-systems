INPUT
Store X
INPUT
Store Y


loop,    Load X
         subt Y
         Store X

Load num
add one
Store num

load X
Skipcond 000 
Jump loop / no; repeat loop
 / yes, so exit the loop


Load num
subt one
Output
Load Y
add X
Output

load zero
store num
store  X
store  Y 
Halt

X, DEC 0
Y, DEC 0
num, DEC 0
one, DEC 1
zero, DEC 0

