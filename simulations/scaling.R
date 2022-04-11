source('helper_functions.r')

#

#### variables used in for loop ####
N <- 2 ^ (1:19) 
times <- rep(NA, length(N)) # main variable of interest
times <- data.frame(matrix(NA, length(N), 4))
colnames(times) <- c('l_noise', 'dlm_run', 'avg_run_len', 'thre')

SEED <- 45
RNGkind("L'Ecuyer-CMRG")
set.seed(SEED)

CORES_1 <- 1
CORES_2 <- sqrt(CORES_1)
if(! isWhole(CORES_2)) {
    stop('sqrt(CORES_1) must be an integer')
}
REP <- CORES_1

#### functions ####
fn_scores_inf <- function(noise) {
    #message_parallel('in fn_scores_inf')
    return(
        get_maxs(
            c_fromData(
                class = 'dlmh',
                my_data = noise,
                thresh = Inf, 
                stat = cusum,
                )
        )
    )
}

run_len_calculator <- function (score, thres) {
    cp <- which(score >= thres)[1]
    ifelse(is.na(cp), length(score), cp)
}

fn_thre_cand <- function(avg_run_len, thre_seq, target) {
    thre_seq[which(avg_run_len > target)[1]]
}


#### for loop ####
for (i in seq_along(N)) {

    n <- N[i]
    targ_runLen <- n/2

    t0 <- Sys.time()
    l_noise <- mclapply(1:REP, function (i) rnorm(n), mc.cores = CORES_1)
    t1 <- Sys.time()
    times$l_noise[i] <- as.numeric(difftime(t1, t0, units = 'secs'))

    t0 <- Sys.time()
    dlm_run <- mclapply(X = l_noise, 
                        FUN = scores, stat_name = "cusum", thresh = Inf,#cpp fun
                        mc.cores = CORES_1
    ) # this is what takes a long time
    t1 <- Sys.time()
    times$dlm_run[i] <- as.numeric(difftime(t1, t0, units = 'secs'))

    t0 <- Sys.time()
    thre_seq <- seq(1, 10, by = .05)
    avg_run_len <- rep(NA, length(thre_seq))
    avg_run_len <- 
        mclapply(seq_along(thre_seq), 
            function(i) {
                mclapply(dlm_run, run_len_calculator, 
                         thres = thre_seq[i], 
                         mc.cores = CORES_2) %>% 
                                    unlist %>% 
                                    mean
            }, 
            mc.cores = CORES_2
        ) %>% unlist
    t1 <- Sys.time()
    times$avg_run_len[i] <- as.numeric(difftime(t1, t0, units = 'secs'))

    t0 <- Sys.time()
    thre <- fn_thre_cand(avg_run_len, thre_seq, targ_runLen)
    t1 <- Sys.time()
    times$thre[i] <- as.numeric(difftime(t1, t0, units = 'secs'))

}

#### vizualizing results ####
col_choice <- c('red', 'green', 'blue', 'black')
png('results/scaling.png')  
matplot(x = N, y = times, log = 'xy', type = 'l', col = col_choice)
lines(x = N, y = N / 10000, type = 'l', col = 'pink')
legend(x = 'topleft', legend = c(colnames(times), 'O(T)'), lty = 'solid', col = c(col_choice, 'pink'))
invisible(dev.off())

save(list = c('times'),                        
      file = "results/times.RData")
print(times)
