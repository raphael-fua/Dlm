cat('\14')
source('/Users/raphael/Documents/University/ethz/semester_3/Thesis/rebuild.R')
if(T) {rebuild()}

library(Dlm)
cat("\n~~~ out of danger zone ~~~\n")
cat("~~ test_MHA_constr2 ~~\n")

cat("~ cpp ~\n\n")
v <- 16:20
thresh <- 10 
test_GHA_constr2(v, 1)
cat('------------------------------\n')
set.seed(7)
d <- rnorm(100)
test_GHA_constr2(d, 1)

















    