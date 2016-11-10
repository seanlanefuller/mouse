' this is a comment
365!"!"
3 5 7 ! " " ! " " !
"!"
"Address of C!"
C !  "!"	' print address of C
"Set C = 8!"
C 8 =		' set C to 8
"Value of C!"
C . ! "!"	' print value of C
"Count from 1 to 10 in loop of 1 to 10!"
' count from 1 to 10
A 1 =
(
	"outter "
	A .  !  "!"	' print value of A
	A A .  1 + =	' A = A + 1
	' count from 1 to 10
	B 1 =
	(
		"inner "
		B .  !  "!"	' print value of B
		B B .  1 + =	' B = B + 1
		B . 11 - ^	' break loop if B > 10
	)
	A . 11 - ^	' break loop if A > 10
)
A 50 =
#M,A.,10;
#M,6,20;
"Recursive test!"
#P,5;
$M
	%A ! " and " %B ! " in M!"
	#N,20,30;
@
$N
	%A ! " and " %B ! " in N!"
	#O;
@
$O
	"in O!"
@
$P
	%A 0 - [ @ ]
	%A ! "!"
	N 1 %A - =
	#P,N.;
@
$$
