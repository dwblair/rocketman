
set xdata time
set timefmt "%s"
set datafile separator ','
set format x "%m/%d/%Y %H:%M:%S"
plot "data.csv" using 1:($2*9/5+32) with linespoints, "data.csv" using 1:($3*9/5+32) with linespoints
set yrange[0:100]
set ylabel "Temp (F)"
while (1) {
    replot
    pause 1
}
