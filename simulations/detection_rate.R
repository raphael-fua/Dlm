#just dlm. works, don't touch ####
if(F) {
    # Objective of script:
    #   - replicate figure 6.2 made in 
    #     FOCuS-master/simulations/pre-change-unknown/detection_rate.R
    
    source('helper_functions.r')
    
    
    CORES_1 <- 4
    CORES_2 <- sqrt(CORES_1)
    NREP <- CORES_1
    if(! isWhole(CORES_2)) {
    	stop('sqrt(CORES_1) must be an integer')
    }
    
    SEED <- 42
    
    run_simulation <- function(p, REPS, noise, thresh) {
        #print(p)
        
        data <-
            mclapply(
                X = noise,
                FUN = function (eps) {
                    c(rep(0, p$changepoint), rep(p$delta, p$N - p$changepoint)) + eps
                },
                mc.cores = CORES_1
            )
        
        
        cp <- 
            unlist(
                mclapply(
                    X = data, 
                    FUN = runtime, stat_name = "cusum", thresh = thresh, # cpp fun
                    mc.cores = CORES_1
                )
            )
        #print(cp)
        return(
            data.frame(
                sim = 1:REPS, 
                magnitude = p$delta, 
                algo = "Dlm", 
                est = cp, 
                real = p$changepoint, 
                N = p$N
            )
        )
    }
        
    
    
    load(file = "results/avg_run_len.RData") # 'thre' and 'N' loaded
    
    realCP <- N / 20
    
    pows <- seq(5, 0, length.out = 10)
    sim_grid <- 
        expand.grid(
            N = 2 * N,
            changepoint = realCP,
            delta = c(- .5 ^ pows, .5 ^ pows) %>% sort
        )
    
    output_file <- "results/detection_rate.RData"
    
    if (T) {
        
        RNGkind("L'Ecuyer-CMRG")
        set.seed(SEED)
        
        t0 <- Sys.time()
        noise <- mclapply(1:NREP, function (i) rnorm(N), mc.cores = CORES_1)
        cat('l_noise done. '); print(Sys.time() - t0); 
        
        t0 <- Sys.time()
        outDF <- 
            mclapply(
                seq_len(nrow(sim_grid)), 
                function (i) {
                    p <- sim_grid[i, ]
                    return(run_simulation(p, NREP, noise, thresh = thre))
                },
            mc.cores = CORES_2
            )
        # ↓ expecting 20 * dlm_run from avg_run_len
        cat('outDF. '); print(Sys.time() - t0); 
        
        outDF <- Reduce(rbind, outDF)
        save(outDF, file = output_file)
    }
    
    
    load(output_file)
    
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
    cbPalette <- RColorBrewer::brewer.pal(6, "Paired")[c(2, 3, 4, 5, 6)]
    
    detection_delay <-
        ggplot(
            #grouped ,
            #grouped %>% filter(!(algo %in% c("FOCuS-t", "FOCuS0 1000"))),
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
        ggtitle(paste('NREP:', NREP, '| N:', N, '| Target run length:', targ_runLen, '| Real CP:', realCP)) +
        xlab("magnitude") +
        ylab("Detection Delay") +
        scale_y_log10() +
        scale_x_log10() +
        theme_idris() #+ theme(legend.position = "none")
    plot(detection_delay)
    
    # ↓ suppress message: Saving 14.5 x 9.21 in image
    suppressMessages(ggsave(detection_delay, file = 'results/detection_rate.png'))
}
# oha ####
if(T) {
    source('helper_functions.r')
    
    
    CORES_1 <- 4
    CORES_2 <- sqrt(CORES_1)
    NREP <- CORES_1
    if(! isWhole(CORES_2)) {
    	stop('sqrt(CORES_1) must be an integer')
    }
    
    SEED <- 42
    
    run_simulation <- function(p, REPS, noise, alpha) {
        #print(p)
        
        data <-
            mclapply(
                X = noise,
                FUN = function (eps) {
                    c(rep(0, p$changepoint), rep(p$delta, p$N - p$changepoint)) + eps
                },
                mc.cores = CORES_1
            )
        
        
        cp <- 
            unlist(
                mclapply(
                    X = data, 
                    FUN = runtimeOHA, alpha = alpha, nu = 100, # cpp fun
                    mc.cores = CORES_1
                )
            )
        #print(cp)
        return(
            data.frame(
                sim = 1:REPS, 
                magnitude = p$delta, 
                algo = "OHA", 
                est = cp, 
                real = p$changepoint, 
                N = p$N
            )
        )
    }
        
    
    
    load(file = "results/avg_run_len.RData") # 'thre' and 'N' loaded
    
    realCP <- N / 20
    
    pows <- seq(5, 0, length.out = 10)
    sim_grid <- 
        expand.grid(
            N = 2 * N,
            changepoint = realCP,
            delta = c(- .5 ^ pows, .5 ^ pows) %>% sort
        )
    
    output_file <- "results/detection_rateOHA.RData"
    
    if (T) {
        alpha <- .05
        RNGkind("L'Ecuyer-CMRG")
        set.seed(SEED)
        
        t0 <- Sys.time()
        noise <- mclapply(1:NREP, function (i) rnorm(N), mc.cores = CORES_1)
        cat('l_noise done. '); print(Sys.time() - t0); 
        
        t0 <- Sys.time()
        outDF <- 
            mclapply(
                seq_len(nrow(sim_grid)), 
                function (i) {
                    p <- sim_grid[i, ]
                    return(run_simulation(p, NREP, noise, alpha = alpha))
                },
            mc.cores = CORES_2
            )
        # ↓ expecting 20 * dlm_run from avg_run_len
        cat('outDF. '); print(Sys.time() - t0); 
        
        outDF <- Reduce(rbind, outDF)
        save(outDF, file = output_file)
    }
    
    
    load(output_file)
    
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
    cbPalette <- RColorBrewer::brewer.pal(6, "Paired")[c(2, 3, 4, 5, 6)]
    
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
        ggtitle(paste('NREP:', NREP, '| N:', N, '| Target run length:', targ_runLen, '| Real CP:', realCP)) +
        xlab("magnitude") +
        ylab("Detection Delay") +
        scale_y_log10() +
        scale_x_log10() +
        theme_idris() 
    plot(detection_delay)
    
    # ↓ suppress message: Saving 14.5 x 9.21 in image
    suppressMessages(ggsave(detection_delay, file = 'results/detection_rateOHA.png'))
}