# below, set to TRUE if modifications have been made to cpp package
cat('\14')
if(T){
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

set.seed(1)
noise <- 1
X <- rep(0:1,c(100,100)) + rnorm(200, 0, noise)
plot(X)

# You need to add a S_0 = 0 (empty sum)
S <- matrix(cumsum(c(0,X)), nrow=1)

# Binary Segmentation
OneStepSearch(S, shift=0, method="naive")
OneStepSearch(S, shift=0, method="advanced")
OneStepSearch(S, shift=0, method="combined")
OneStepSearch(S, shift=0, method="full")
# $ind = candidate indices
# $stat is CUSUM statistic at ind (sqrt of log-likelihood ratio)
