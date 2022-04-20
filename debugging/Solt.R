# Old version
cat('\14')

# indices ####
fn_get_tree <- function(layers) {
    tree <- c()
    for(i in 1:length(layers)) { tree <- c(tree,layers[[i]][,2]) }
    tree <- tree[!is.na(tree)]
    tree <- sort(unique(tree))
    return(tree)
}


p_max <- 6
N <- 2^p_max

solts_tree <- vector(mode = 'list', length = N) 
layers <- vector(mode = 'list', length = p_max + 2) # "layers" is core of Solts algo and is uptaded at every time point.

layers[[1]] <- matrix(c(1, 7, 1, 8), 2, 2, byrow = TRUE) # 1) Only layer with two segments instead of four 2) Updated at every iteration 
layers[[2]] <- cbind(1, 4:7)
layers[[3]] <- cbind(c(NA,NA, 1, 1),c(NA, NA, 4,6))

for(i in 4:length(layers)) { layers[[i]] <- matrix(NA, nrow = 4, ncol = 2) }
solts_tree[[8]] <- fn_get_tree(layers)

tmp <- matrix(NA, nrow = p_max + 2, ncol = 2)
counter <- rep(0, p_max + 2)
counter[1:5]<-c(1, 0, 0, 0, 1)#WRONG

sink('old.txt')
for(time in 9:2^p_max) {
    
    tmp[1,] <- layers[[1]][2,]
    layers[[1]][1,] <- layers[[1]][2,]
    layers[[1]][2,] <- c(1,time)
    
    for(i in 2:which(counter==0)[1]){
        counter[i] <- (counter[i]+1)%%2
        
        layers[[i]][1:3,] <- layers[[i]][2:4,]
        
        tmp[i,] <- layers[[i]][4,]
        
        layers[[i]][4,] <- tmp[i-1,]
    }
    solts_tree[[time]] <- fn_get_tree(layers)
    tmp <- matrix(NA, nrow = p_max + 2, ncol = 2)
    
    cat('\n#', layers[[1]][2, 2], '------------------------------\n')
    for(j in 1:length(layers)){
        if(! all(is.na( layers[[j]]))) {print(layers[[j]])}
    }
}
sink()


# plotting ####
if(F) {

    par(mfrow = c(1,1))
    a <- lengths(solts_tree)
    plot(a,type='l')
    
    b <- -diff(a)
    plot(b, type = "l")
}

# ignore for now ####
# abline(v = 32, col = "red"); abline(v = 94, col = "red") # 94 - 32 = 62 = 64 - 2


# 
# if (FALSE){
#     abline(v = 64, col = "blue"); abline(v = 190, col = "blue") # 190 - 64 = 126 = 128 - 2
#     
#     # Starting point (32 & 64) are dyadics
#     c <- b[32:94]
#     plot(1:(94 - 32 + 1), c,type = "l")
#     abline(v = c(16, 32, 48))
#     
#     cat(c, "\n\n")
#     
#     values <- sort(unique(c), decreasing = TRUE)
#     
#     library(binaryLogic)
#     for(value in values){ 
#         idx <- which(c == value)
#         cat(value, ":", idx, "\n")
#         binary_idx <- lapply(lapply(as.binary(idx), as.logical), as.numeric)
#         lapply(binary_idx, function(x) cat(rev(x), "\n"))
#         cat("\n")
#     }
#     
#     d <- b[32:80]
#     plot(1:(80 - 32 + 1), d,type = "l")
# }

# sums