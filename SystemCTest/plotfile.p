#set terminal png size 1024,240
set lmargin 7
set multiplot layout 4, 1 #title "Ampelsteuerung"
set title "Zeit"
unset key
set xrange [-1:241]
set yrange [-0.05:1.05]
set ytics 0,1,1
set xtics 0,10,241
plot 'gnuplot.dat' using 1:2 title 'Zeit' with steps
set title "Ampeln"
set xrange [-1:241]
set yrange [-0.05:3.5]
set ytics 0,1,3
set xtics 0,20,241
set ytics add ("Rot" 0)
set ytics add ("RotGelb" 1)
set ytics add ("Gruen" 2)
set ytics add ("Gelb" 3)
plot 'gnuplot.dat' using 1:3 title 'Ampel1' with steps,\
'gnuplot.dat' using 1:4 title 'Ampel2' with steps
set title "Bahnsignal"
set xrange [-1:241]
set yrange [-0.05:1.1]
set ytics 0,1,1
set ytics add ("F0" 0)
set ytics add ("F1" 1)
plot 'gnuplot.dat' using 1:5 title 'Bahnsignal' with steps
set title "Roter Pfeil"
set xrange [-1:241]
set yrange [-0.05:1.1]
set ytics 0,1,1
set ytics add ("Aus" 0)
set ytics add ("An" 1)
plot 'gnuplot.dat' using 1:6 title 'Pfeil' with steps
unset multiplot

