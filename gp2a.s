
set xdata time
set timefmt "%s"
set datafile separator ','
#set format x "%m/%d/%Y %H:%M:%S"
set format x "%H:%M"
set ytics 20, 5, 100
set y2tics 20, 5, 100
set grid
plot "data.csv" using ($1-14400):($2*9/5+32) with linespoints title "outside greenhouse, on ground", "data.csv" using ($1-14400):($3*9/5+32) with linespoints title "inside greenhouse, on ground"
set yrange[25:90]
set ylabel "Temp (F)"
while (1) {
    replot
    pause 1
}
