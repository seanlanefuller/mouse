"PRIME NUMBERS!"
"1 "
N 3 =
(
    #P,N.;
    N . 1001 - ^
    N N . 1 + =
)
"!"

$P
" " %A . ! " " ^
    F 1 =       ' F = 1
    N 1 =       ' N = 1
    (
       ' F = F + 1
       F F. 1 + =
       ' break loop when F > A
       F. %A - ^
       ' if A / F * F >= 0
       F. %A / F. * %A - 1 -
       [
          ' set N = 0 and break out of loop
          N 0 =
          0 ^
       ]
    )
    ' if N > 0 then print %A
    N .
    [
       %A ! " "
    ]
' return
@
' end of program
$$

