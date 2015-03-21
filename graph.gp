set style data lines
set logscale xy
set title 'K-P model vs Improved Model - John Tramm - 22.14 PSet 4' font 'Arial,25'
set xlabel 'Recoil Energy, T (eV)' font 'Arial,25'
set ylabel 'v(T) (atoms per primary recoil)' font 'Arial,25'
set key right bottom Left title 'Legend' box
plot 'data.dat' using 1:2 title 'Improved' lw 3, 'data.dat' using 1:3 title 'K-P' lw 3
