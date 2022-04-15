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

# Testing #####
library(Dlm)
print(get_sHalf("cusum", 5.5))
a <- "cusum"
b <- 5.5
c <- 1:10
test_update(a, b, c)   

cumsum(1:10)

21/6+4
