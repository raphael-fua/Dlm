# below, set to TRUE if modifications have been made to cpp package
cat('\14')
if(F){
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

if(T){
# Testing 1: good (don't touch) ####

library(Dlm)
cat("\n~~~ out of danger zone ~~~\n")
cat("~~ test_MHA_constr2 ~~\n\n")
cat("\n~ cpp ~\n")
N <- 1e6
alpha <- .3
nu <- 1
i <- 2

set.seed(7)
sink(file = 'debugging/output/test_MHA_constr2.txt')
for (count in 1:100) {
    cat('------------------------------\n')
    cat('-', count, '\n')
    cat('------------------------------\n')
    my_data <- rnorm(N)
    test_MHA_constr2(my_data, alpha, nu, i)  
    cat('\n')
}
sink()
# Note that alarms much more for small k... too little power  
# for alpha == .3, got .1 fpr



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

}

# test 2: test fp rate ####
library(Dlm)
nsim <- 100
N <- 1000000
alpha <- .2
nu <- 1
i <- 2

nfp <- 0 # number of false positives
count <- 1
while (count < nsim) {
    # print(count)
    count <- count + 1
    if(! test_MHA_fpr(rnorm(N), alpha, nu, i)) {
        nfp <- nfp + 1
    }
}

cat('fpr:', nfp / nsim, '\n')

    

# we expect a slightly smaller fpr than alpha since N != infinity