# !/bin/bash
    
    echo 10240 > /proc/sys/vm/nr_hugepages

    echo "\n\n########################################################" >> Graphene_runtimes.statistics 
    echo "2019.8.29 compare with Graphene by rrws in SSD 64GB R730" >> Graphene_runtimes.statistics 

    ### 64GB R730, SSD, FS
    ################################################################################################
    echo "L = 10, different Rs" >> Graphene_runtimes.statistics 
    for(( R = 1000; R <= 1000000000; R*=10))
    do
        echo "L = 10, R = " $R >> Graphene_runtimes.statistics 
        for(( times = 0; times < 5; times++))
        do
            echo "times = " $times " from echo"
            free -m
            sync; echo 1 > /proc/sys/vm/drop_caches
            free -m
            ./bin/apps/rawrandomwalks 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 $R 10
        done
    done

    ### 64GB R730, SSD, FS
    ################################################################################################
    echo "R = 100000, different Ls" >> Graphene_runtimes.statistics 
    for(( L = 4; L <= 4096; L*=2))
    do
        echo "R = 100000, L = " $L >> Graphene_runtimes.statistics 
        for(( times = 0; times < 5; times++))
        do
            echo "times = " $times " from echo"
            free -m
            sync; echo 1 > /proc/sys/vm/drop_caches
            free -m
            ./bin/apps/rawrandomwalks 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 100000 $L
        done
    done

    echo 0 > /proc/sys/vm/nr_hugepages

    # echo 102400 > /proc/sys/vm/nr_hugepages

    # ./bin/apps/rawrandomwalks 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 100000 4

    # cat /proc/sys/vm/nr_hugepages
