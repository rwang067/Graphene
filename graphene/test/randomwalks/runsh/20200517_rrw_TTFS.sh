# !/bin/bash
    
    echo 10240 > /proc/sys/vm/nr_hugepages

    echo "2020.5.17 compare with Graphene/GraFSoft by Raw Randomwalks in Twitter in Node2( SSD 64GB R730 ）" >> Graphene_runtimes.statistics
    echo "Raw RW from echo, R*10 walks from echo"  >> Graphene_runtimes.statistics
    ## Raw RW
    echo "app = RawRW, dataset = Twitter from echo" >> Graphene_runtimes.statistics
    for(( R = 1000; R <= 1000000000; R*=10))
    do
        echo "R = " $R ", fixed R*10 walks from echo" >> Graphene_runtimes.statistics
        for(( times = 0; times < 5; times++))
        do
            echo "times = " $times " from echo"
            free -m
            sync; echo 1 > /proc/sys/vm/drop_caches
            free -m
            ./bin/apps/rawrandomwalks 1 1 2 '/home/kvgroup/ruiwang/data/raid0_defghij_ssd/Twitter/twitter_rv.net_Graphene/' '//home/kvgroup/ruiwang/data/raid0_defghij_ssd/Twitter/twitter_rv.net_Graphene/' twitter_rv.net-split_beg twitter_rv.net-split_csr 8 20971520 4 32 16 128 $R 10
        done
    done

    # echo "2020.5.16 compare with Graphene/GraFSoft by Raw Randomwalks in Friendster in Node2( SSD 64GB R730 ）" >> Graphene_runtimes.statistics
    # echo "Raw RW from echo, R*10 walks from echo"  >> Graphene_runtimes.statistics
    # ## Raw RW
    # echo "app = RawRW, dataset = Friendster from echo" >> Graphene_runtimes.statistics
    # for(( R = 1000; R <= 1000000000; R*=10))
    # do
    #     echo "R = " $R ", fixed R*10 walks from echo" >> Graphene_runtimes.statistics
    #     for(( times = 0; times < 5; times++))
    #     do
    #         echo "times = " $times " from echo"
    #         free -m
    #         sync; echo 1 > /proc/sys/vm/drop_caches
    #         free -m
    #         ./bin/apps/rawrandomwalks 1 1 2 '/home/kvgroup/ruiwang/data/raid0_defghij_ssd/Friendster/out.friendster-reorder_Graphene/' '//home/kvgroup/ruiwang/data/raid0_defghij_ssd/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 8 20971520 4 32 16 128 $R 10
    #     done
    # done

    echo 0 > /proc/sys/vm/nr_hugepages

    # echo 102400 > /proc/sys/vm/nr_hugepages

    # ./bin/apps/rawrandomwalks 1 1 2 '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' '/home/wang/raid0_defghij/Friendster/out.friendster-reorder_Graphene/' out.friendster-reorder-split_beg out.friendster-reorder-split_csr 64 33554432 4 32 16 128 100000 4

    # cat /proc/sys/vm/nr_hugepages
