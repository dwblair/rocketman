
set xdata time
set timefmt "%s"
set datafile separator ','
set format x "%m/%d/%Y %H:%M:%S"
plot "data.csv" using 1:2 with linespoints