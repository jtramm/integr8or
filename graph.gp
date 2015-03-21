set style data lines
set logscale xy
set key left bottom Left title 'Legend' box
plot 'data.dat' using 1:2 title 'Improved', 'data.dat' using 1:3 title 'K-P'
