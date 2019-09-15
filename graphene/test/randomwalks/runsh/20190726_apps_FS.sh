# !/bin/bash
    
    # echo 10240 > /proc/sys/vm/nr_hugepages

    # echo "2019.7.26 compare with Graphene by apps in SSD 64GB R730" >> Graphene_runtimes.statistics 

    # ## PersonalizedPageRank
    # echo "app = PersonalizedPageRank, dataset = Friendster from echo" >> Graphene_runtimes.statistics 
    # echo "R = 1000, L = 10, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    # for(( times = 0; times < 5; times++))
    # do
    #     echo "times = " $times " from echo"
    #     free -m
    #     sync; echo 1 > /proc/sys/vm/drop_caches
    #     free -m
    #     ./bin/apps/personalizedpagerank 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 13 2000 10
    # done

    # ## SimRank
    # echo "app = SimRank, dataset = Friendster from echo" >> Graphene_runtimes.statistics 
    # echo "R = 2000, L = 11, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    # for(( times = 0; times < 5; times++))
    # do
    #     echo "times = " $times " from echo"
    #     free -m
    #     sync; echo 1 > /proc/sys/vm/drop_caches
    #     free -m
    #     ./bin/apps/simrank 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 12 13 1000 11
    # done

    # ## Graphlet
    # echo "app = Graphlet, dataset = Friendster from echo" >> Graphene_runtimes.statistics 
    # echo "R = 100000, L = 4, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    # for(( times = 0; times < 5; times++))
    # do
    #     echo "times = " $times " from echo"
    #     free -m
    #     sync; echo 1 > /proc/sys/vm/drop_caches
    #     free -m
    #     ./bin/apps/graphlet 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 100000 4
    # done

    # ## Friendster   
    # echo "app = RandomWalkDomination, dataset = Friendster from echo" >> Graphene_runtimes.statistics 
    # echo "R = 1×N, L = 6, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    # for(( times = 0; times < 5; times++))
    # do
    #     echo "times = " $times " from echo"
    #     free -m
    #     sync; echo 1 > /proc/sys/vm/drop_caches
    #     free -m
    #     ./bin/apps/rwdomination 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 1 6
    # done

    echo "\n\n########################################################" >> Graphene_runtimes.statistics 
    echo "2019.7.26 compare with Graphene by rrws in SSD 64GB R730" >> Graphene_runtimes.statistics 

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
