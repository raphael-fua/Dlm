# below, set to TRUE if modifications have been made to cpp package
cat('\14')
if(TRUE){
    # Making changes abailable by reloading the package ####
    topDir <- "~/Documents/University/ethz/semester_3/Thesis"
    pkg_name <- "Dlm"
    bottomDir <- paste0(topDir, '/', pkg_name)
    setwd(topDir)
    
    library("Rcpp")
    compileAttributes(pkgdir = paste0("./", pkg_name), verbose = TRUE) # makes RcppExports.cpp
    
    library("devtools")
    library("roxygen2")
    setwd(bottomDir)
    devtools::load_all()
    document()
    
    setwd(topDir)
    install(pkg_name)
}

# Testing 1: good (don't touch) ####

library(Dlm)
cat("\n~~~ out of danger zone ~~~\n")
cat("~~ test_MHA_constr2 ~~\n\n")

N <- 8
alpha <- .01
nu <- 100
i <- 2
set.seed(7)
my_data <- rnorm(N)


cat("\n~ cpp ~\n")
#cat('runtime (t):', runtimeOHA(my_data, alpha, nu, i), '\n')
test_MHA_constr2(my_data, alpha, nu, i)    


cat("\n~ R ~\n")
ski <- function(k, i, my_data) {
    pii <- 1 - 1 / 2 ^ i
    
    res <- 0
    for(j in seq_len(k)) {
        res <- res + sum(my_data[1:(j * 2^i)]) / j
    }
    res <- pii * res
    return(res)
}
k <- N / 2 ^ i
ski_test <- ski(k, i, my_data)
#cat('R ski', ski_test, '\n') # (1.2.0.3) atw
#pi <- 1 - 1 / 2 ^ i
#cat('R vki, ski_test / (pi * N)



valpha <- rep(NA, nu)
for (n in 1:nu) {
    valpha[n] <- alpha * (n / (n + nu) - (n - 1) / (n - 1 + nu))
}

res <- -2 * log(valpha) - log(2 * pi)

# test 2: test fp rate ####

# N <- 100
# alpha <- .2
# nu <- 100
# i <- 2
# set.seed(7)
# my_data <- rnorm(N)
# 
# 
# cat("\n~ cpp ~\n")
# #cat('runtime (t):', runtimeOHA(my_data, alpha, nu, i), '\n')
# test_MHA_constr2(my_data, alpha, nu, i)