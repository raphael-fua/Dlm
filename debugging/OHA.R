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
cat("~~ test_OHA_constr2 ~~\n\n")

N <- 10
alpha <- .05
my_data <- 1:N

cat("~ R ~\n")
# Below: see 'Simulations'. At time of writing (ATW), first page of chapter
cat('R threhsold', - 2 * log(alpha) - log(2 * pi), '\n') 

# Below: see 'Generalizing Hahn (2022)::Definitions'. ATW, equation (1.2.0.3)
ski <- function(k, i, my_data) {
    i <- 1
    pi <- 1 - 1 / 2^i
    
    res <- 0
    for(j in seq_len(k)) {
        res <- res + sum(my_data[1:(j * 2^i)]) / j
    }
    res <- pi * res
    return(res)
}

cat('R sHalf', ski(N/2, 1, my_data), '\n')

test_stat <- function(k, i, my_data) {
    t <- k*2^i 
    V2 <- t * (ski(k, i, my_data) / (t/2) - sum(my_data[1:t])/t)^2
    return((sqrt(2*V2) - sqrt(2))^2)
}

cat('stat evolution \n')
for(k in seq_len(N/2)) {
    print(test_stat(k, 1, my_data))
}
    
cat("\n~ cpp ~\n")
test_OHA_constr2(my_data, alpha)    
    
# no need for calibration for this one 
# next step is putting in in x:magnitude v y:dd plot











# Future tests ####