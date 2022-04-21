cat('\14')

t0 <- Sys.time()
source('helper_functions.r')
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Set up ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
CORES_1 <- 4
N <- 2e3
NREP <- 100 # number of simulation runs

realCP <- N / 20
pows <- seq(5, 0, length.out = 10)
customDelta <- c(- .5 ^ pows, .5 ^ pows) %>% sort 
customDelta <- customDelta[c(-8, -9, -10, -11, -12, -13)]
sim_grid <- 
    expand.grid(
        N = N / 2,
        changepoint = realCP,
        delta = customDelta
    )

CORES_2 <- sqrt(CORES_1)
if(!isWhole(CORES_2)) {
    stop('sqrt(CORES_1) must be an integer')
}

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Auxiliary function ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
MAXcusum <- function(idx, sums) {
    if(length(idx) <= 1) {
        return(0)
    }
    
    s <- head(idx, -1)
    sl <- head(sums, -1)
    
    t <- tail(idx, 1)
    st <- tail(sums, 1)
    
    return(max(sqrt(t / (s * (t - s))) * abs(s / t * st - sl)))
}
runtimeGDLM_allocate <- function(q, d, th) {
    S <- cumsum(d)
    C <- ceiling(log(length(d), 2)) + 3
    m <- matrix(NA, nrow = 2^q, ncol = C)
    k <- rep(0, C)
    k[1] <- 1 
    tmp <- rep(NA, C)
    
    t <- 1 # t = time corresponds to new data
    while(t <= length(d)) {
        tmp[1] <- m[1, 1]
        m[2, 1] <- m[1, 1]
        m[1, 1] <- t
        
        for(i in 2:which(k == 0)[1]){
            tmp[i] <- m[1, i]
            m[, i] <- c(tmp[i -1], head(m[, i], -1))
            k[i] <- (k[i]+1)%%2
        }
        idx <- unique(sort(na.omit(c(m))))
        if(MAXcusum(idx, S[idx]) > th) {
            return(t)
        }
        t <- t + 1
    }
    return(t)
}

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Core function ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# i is for MHA
# q is for GDLM
run_simulation <- function(p, REPS, noise, alpha, nu, i, q, treshDlmGdlmAos, threshGHA){
    cat('\n'); print(p)
    data <- mclapply(X = noise, FUN = function (eps) { c(rep(0, p$changepoint), rep(p$delta, p$N - p$changepoint)) + eps }, mc.cores = CORES_1)
    
    print("DLM")
    cp <- unlist(mclapply(X = data, FUN = runtime, stat_name = "cusum", thresh = treshDlmGdlmAos, mc.cores = CORES_1))
    output <- data.frame(sim = 1:REPS, magnitude = p$delta, algo = "DLM", est = cp, real = p$changepoint, N = p$N)
    
    print("GDLM")
    cp <- unlist(mclapply(X = data, FUN = runtimeGDLM_allocate, q = q, th = treshDlmGdlmAos, mc.cores = CORES_1))
    output <- data.frame(sim = 1:REPS, magnitude = p$delta, algo = "GDLM", est = cp, real = p$changepoint, N = p$N)
    
    # print("AOS")
    # S <- mclapply(X = data , FUN = function(d) { return(matrix(cumsum(c(0,d)), nrow=1)) }, mc.cores = CORES_1)
    # cp <-  unlist(mclapply(X = S,  FUN = runtimeAOS, thresh = treshDlmGdlmAos, mc.cores = CORES_1))
    # output <- rbind(output, data.frame(sim = 1:REPS, magnitude = p$delta, algo = "AOS", est = cp, real = p$changepoint, N = p$N))
    
    print("GHA")
    cp <-  unlist(mclapply(X = data,  FUN = runtimeGHA, thresh = threshGHA, mc.cores = CORES_1))
    output <- rbind(output, data.frame(sim = 1:REPS, magnitude = p$delta, algo = "GHA", est = cp, real = p$changepoint, N = p$N))
    
    print("OHA_alpha")
    cp <-  unlist(mclapply(X = data,  FUN = runtimeOHA, alpha = alpha, nu = nu, mc.cores = CORES_1))
    output <- rbind(output, data.frame(sim = 1:REPS, magnitude = p$delta, algo = "OHA_alpha", est = cp, real = p$changepoint, N = p$N))
    
    print("MHA_alpha i = 1")
    cp <-  unlist(mclapply(X = data,  FUN = runtimeMHA, alpha = alpha, nu = nu, i = 1, mc.cores = CORES_1))
    output <- rbind(output, data.frame(sim = 1:REPS, magnitude = p$delta, algo = "MHA_alpha i = 1", est = cp, real = p$changepoint, N = p$N))
    
    print(paste("MHA_alpha i =", i))
    cp <-  unlist(mclapply(X = data,  FUN = runtimeMHA, alpha = alpha, nu = nu, i = i, mc.cores = CORES_1))
    output <- rbind(output, data.frame(sim = 1:REPS, magnitude = p$delta, algo = paste("MHA_alpha i =", i), est = cp, real = p$changepoint, N = p$N)) 
    
    return(output)
}

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Calibrated thresholds ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
threshGHA <- 6.43
treshDlmGdlmAos <- 5.28

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Simulation ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Data generation ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
RNGkind("L'Ecuyer-CMRG")
set.seed(42)
noise <- mclapply(1:NREP, function (i) rnorm(N), mc.cores = CORES_1)

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Calling run_simulation ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
outDF <- 
    lapply(
        X = seq_len(nrow(sim_grid)), 
        FUN = function (i) {
            p <- sim_grid[i, ]
            res <- run_simulation(p = p, REPS = NREP, noise = noise, alpha = 0.05, nu = 100, i = 4, q = 4, treshDlmGdlmAos = 5.28, threshGHA = 6.43)
            return(res)
        }
    )

outDF <- Reduce(rbind, outDF)

    
summary_df <- outDF %>% mutate(
    run_len = ifelse(est == -1, N, est), # changed ifelse
    no_detection = if_else(est == -1, 1, 0),
    false_alarm = if_else(!no_detection & (est - real < 0), 1, 0),
    det_delay = ifelse((est - real >= 0) & (!false_alarm), est - real, NA),
    true_positive = if_else(!no_detection & !false_alarm,1, 0), # if it's not a missed detection nor it's a false alarm, then it's a true positive
)

##### Hopefully, don't need to edit anything under here ####

# plug (N - tau) in case we get a missed detection!
summary_df[(summary_df$no_detection) == 1, "det_delay"] <- 
    sim_grid$N[1] - sim_grid$changepoint[1]

# ↓ suppress warning: `summarise()` has grouped output by 'magnitude'. 
options(dplyr.summarise.inform = FALSE) 
grouped <- 
    summary_df %>% 
    group_by(magnitude, algo) %>%
    summarise(
        no_detection = mean(no_detection), 
        false_alarm = mean(false_alarm), 
        tp_rate = mean(true_positive), 
        det_del = mean(det_delay, na.rm = T)
    )

grouped <- 
    summary_df %>% 
    mutate(magnitude = abs(magnitude)) %>% 
    group_by(magnitude, algo) %>%
    summarise(
        no_detection = mean(no_detection), 
        false_alarm = mean(false_alarm), 
        tp_rate = mean(true_positive), 
        det_del = mean(det_delay, na.rm = T)
    )
options(dplyr.summarise.inform = TRUE)

### detection delay ####
generate_labels <- function (dataset, var, XFUNC) {
    library(ggrepel)
    dataset <- dataset[which(dataset[, var] == XFUNC(dataset[, var])), ] %>% mutate(label = as.character(algo))
    dataset
}

data_label <- generate_labels(grouped, "magnitude", max)

cbPalette <- RColorBrewer::brewer.pal(6, "Paired")[c(2, 1, 3, 4, 5, 6)]
#cbPalette <- RColorBrewer::brewer.pal(6, "Paired")[c(2, 3, 4, 5, 6)]

detection_delay <-
    ggplot(
        grouped %>% filter(!(algo %in% c("FOCuS-t"))),
        aes(
            x = magnitude,
            y = det_del,
            group = algo,
            col = algo
        )
    ) +
    geom_line() +
    scale_color_manual(values = cbPalette) +
    ggtitle(paste('NREP:', NREP, '| N:', N, '| Target run length:', N/2, '| Real CP:', realCP)) +
    xlab("magnitude") +
    ylab("Detection Delay") +
    scale_y_log10() +
    scale_x_log10() +
    theme_idris() #+ theme(legend.position = "none")
plot(detection_delay)

# ↓ suppress message: Saving 14.5 x 9.21 in image
#suppressMessages(ggsave(detection_delay, file = 'results/detection_rate.png'))


t1 <- Sys.time()

cat('\n')
cat('Total script time:\n')

print(difftime(t1, t0, 'secs'))