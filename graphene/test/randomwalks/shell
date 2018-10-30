# !/bin/bash

    # 2018.9.14
    echo "2018.9.14 compare with Graphene " >> Graphene_runtimes.statistics 

## LiveJournal   
    echo "app = PageRank, dataset = LiveJournal from echo" >> Graphene_runtimes.statistics 
    echo "R = 1×N, L = 20, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/pagerank 1 1 2 '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene' '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene/' soc-LiveJournal1.txt-split_beg soc-LiveJournal1.txt-split_csr 8 20971520 4 32 16 128 1 20
   done

    echo "app = RandomWalkDomination, dataset = LiveJournal from echo" >> Graphene_runtimes.statistics 
    echo "R = 1×N, L = 6, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/rwdomination 1 1 2 '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene' '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene/' soc-LiveJournal1.txt-split_beg soc-LiveJournal1.txt-split_csr 8 20971520 4 32 16 128 1 6
   done

    echo "app = Graphlet, dataset = LiveJournal from echo" >> Graphene_runtimes.statistics 
    echo "R = 10000, L = 4, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/graphlet 1 1 2 '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene' '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene/' soc-LiveJournal1.txt-split_beg soc-LiveJournal1.txt-split_csr 8 20971520 4 32 16 128 10000 4
   done

    echo "app = PersonalizedPageRank, dataset = LiveJournal from echo" >> Graphene_runtimes.statistics 
    echo "R = 1000, L = 10, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/personalizedpagerank 1 1 2 '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene' '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene/' soc-LiveJournal1.txt-split_beg soc-LiveJournal1.txt-split_csr 8 20971520 4 32 16 128 0 1000 10
   done

    echo "app = SimRank, dataset = LiveJournal from echo" >> Graphene_runtimes.statistics 
    echo "R = 2000, L = 11, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/simrank 1 1 2 '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene' '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene/' soc-LiveJournal1.txt-split_beg soc-LiveJournal1.txt-split_csr 8 20971520 4 32 16 128 0 1 1000 11
    done

    echo "app = Reachability, dataset = LiveJournal from echo" >> Graphene_runtimes.statistics 
    echo "R = 1000, L = 100, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/reachability 1 1 2 '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene' '/home/wang/Documents/DataSet/LiveJournal/soc-LiveJournal1.txt_Graphene/' soc-LiveJournal1.txt-split_beg soc-LiveJournal1.txt-split_csr 8 20971520 4 32 16 128 0 1 1000 100

    done

## Wikipedia
    echo "app = PageRank, dataset = Wikipedia from echo" >> Graphene_runtimes.statistics 
    echo "R = 1×N, L = 20, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/pagerank 1 1 2 '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene' '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene/' wikipedia_sorted.data-split_beg wikipedia_sorted.data-split_csr 8 20971520 4 32 16 128 1 20
   done

    echo "app = RandomWalkDomination, dataset = Wikipedia from echo" >> Graphene_runtimes.statistics 
    echo "R = 1×N, L = 6, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/rwdomination 1 1 2 '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene' '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene/' wikipedia_sorted.data-split_beg wikipedia_sorted.data-split_csr 8 20971520 4 32 16 128 1 6
   done

    echo "app = Graphlet, dataset = Wikipedia from echo" >> Graphene_runtimes.statistics 
    echo "R = 10000, L = 4, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/graphlet 1 1 2 '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene' '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene/' wikipedia_sorted.data-split_beg wikipedia_sorted.data-split_csr 8 20971520 4 32 16 128 10000 4
   done

    echo "app = PersonalizedPageRank, dataset = Wikipedia from echo" >> Graphene_runtimes.statistics 
    echo "R = 1000, L = 10, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/personalizedpagerank 1 1 2 '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene' '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene/' wikipedia_sorted.data-split_beg wikipedia_sorted.data-split_csr 8 20971520 4 32 16 128 1 1000 10
   done

    echo "app = SimRank, dataset = Wikipedia from echo" >> Graphene_runtimes.statistics 
    echo "R = 2000, L = 11, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/simrank 1 1 2 '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene' '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene/' wikipedia_sorted.data-split_beg wikipedia_sorted.data-split_csr 8 20971520 4 32 16 128 1 3 1000 11
    done

    echo "app = Reachability, dataset = Wikipedia from echo" >> Graphene_runtimes.statistics 
    echo "R = 1000, L = 100, choose prob=0.2 from echo" >> Graphene_runtimes.statistics 
    for(( times = 0; times < 5; times++))
    do
        echo "times = " $times " from echo"
        ./bin/apps/reachability 1 1 2 '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene' '/home/wang/Documents/DataSet/Wikipedia/wikipedia_sorted.data_Graphene/' wikipedia_sorted.data-split_beg wikipedia_sorted.data-split_csr 8 20971520 4 32 16 128 1 3 1000 100
    done