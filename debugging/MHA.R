# below, set to TRUE if modifications have been made to cpp package
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
alpha <- .05
nu <- 100
i <- 2
my_data <- 1:N


cat("\n~ cpp ~\n")
#cat('runtime (t):', runtimeOHA(my_data, alpha, nu, i), '\n')
test_MHA_constr2(my_data, alpha, nu, i)    


cat("\n~ R ~\n")
ski <- function(k, i, my_data) {
    pi <- 1 - 1 / 2^i
    
    res <- 0
    for(j in seq_len(k)) {
        res <- res + sum(my_data[1:(j * 2^i)]) / j
    }
    res <- pi * res
    return(res)
}
k <- N / 2 ^ i
ski_test <- ski(k, i, my_data)
#cat('R ski', ski_test, '\n') # (1.2.0.3) atw
#pi <- 1 - 1 / 2 ^ i
#cat('R vki, ski_test / (pi * N)











