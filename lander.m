"!"
"     ___    !"
"    /...\   !"
"   /.=.=.\  !"
"   |_____|  !"
"   _/ | \_  !"
"            !"
"Lunar Lander!"
"!"

F 1000 =  'Fuel
A 100 =   'Altitude
R 100 =   'Range
I 0 =     'Horizontal Velocity
J 0 =     'Vertical Velocity
G 3 0 - = 'Gravity

(
   "!"
   "### Alt=" A.! " Range=" R.! " Fuel=" F.!
   " HV=" I.! " VV=" J.! " Grav=" G.! " ###!"

   F.                      'if there is fuel left
   [
      "Horizontal Thrust? "
      H ? =
      "Vertical Thrust? "
      V ? =
   ]
   F. 0 -                  'if out of fuel
   [
      "Out of fuel.!"      'then no thrust
      H 0 =
      V 0 =
   ]
   I I. H. + =             'Horizontal Accel
   J J. G. + V. + =        'Vertical Accel
   A A. J. + =             'Adjust Altitude
   R R. I. + =             'Adjust Range
                           'take abs val of h and v
   H. 0 -                  'if h < 0
   [
      H H. 0 - =           'then h = - h
   ]
   V. 0 -                  'if v < 0
   [
      V V. 0 - =           'then v = -v
   ]
   F H. V. F. - - =        'fuel = fuel - v - h
   A. 0 -                  'if altitude < 0
   [
      "!!### You landed with!"
      "a horizontal velocity of " I.! "!"
      "a vertical velocity of " J.! "!"
      R.! " meters from the landing pad.!"
      0 ^
   ]
)
$$
