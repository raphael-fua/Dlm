cat('\14')
if(F) {rebuild()}

library(Dlm)
cat("\n~~~ out of danger zone ~~~\n")
cat("~~ test_MHA_constr2 ~~\n")

cat("~ cpp ~\n\n")
v <- 16:20
thresh <- 10 
test_GHA_constr2(v, 1)
cat('------------------------------\n')
set.seed(7)
d <- rnorm(2^7)
test_GDLM_constr(q = 4,  v = d, thresh = 5)


