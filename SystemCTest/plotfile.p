#set terminal png size 1024,240
set lmargin 5
set multiplot layout 3, 1 title "Ampelsteuerung"
set tmargin 2
set title "Zeit"
unset key
set xrange [-1:241]
set yrange [-0.05:1.05]
set ytics 0,1,1
set xtics 0,10,241
plot 'out.dat' using 1:2 title 'Zeit' with steps
set title "Ampeln"
set xrange [-1:241]
set yrange [-0.05:3.5]
set ytics 0,1,3
set xtics 0,20,241
set ytics add ("Rot" 0)
set ytics add ("RotGelb" 1)
set ytics add ("Gruen" 2)
set ytics add ("Gelb" 3)
plot 'out.dat' using 1:3 title 'Ampel1' with steps,\
'out.dat' using 1:4 title 'Ampel2' with steps
unset multiplot

