#ifndef DEF_GRAPHWALKER_WALK
#define DEF_GRAPHWALKER_WALK

#include <iostream>
#include <cstdio>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <map>
#include <queue>

#include "util.h"

class WalkManager
{
public:
	sa_t *walk_num;
	std::map<vertex_t,std::vector<walk_t> >  walks;
public:
	WalkManager(){
		walk_num = NULL;
		walks.clear();
	}
	~WalkManager(){
		// free(walk_num);
		walks.clear();
	}

	walk_t encode( vertex_t sourceId, offset_t nextOff, hop_t hop ){
		assert( hop < 1024 );
		return (( (walk_t)sourceId & 0xfff ) << 22 ) |(( (walk_t)nextOff & 0x3ff ) << 10 ) | ( (walk_t)hop & 0x3ff ) ;
	}

	vertex_t getSourceId( walk_t walk ){
		return (vertex_t)( walk >> 22 ) & 0xfff;
	}

	offset_t getNextOff( walk_t walk ){
		return (offset_t)( walk >> 10 ) & 0x3ff;
	}

	hop_t getHop( walk_t walk ){
		return (hop_t)(walk & 0x3ff) ;
	}

	walk_t setNextOff( walk_t walk, off_t nextOff ){
		return encode(getSourceId(walk),nextOff,getHop(walk));
	}

	walk_t moveWalk( walk_t walk,hop_t hop){
		return encode(getSourceId(walk),0,hop);
	}

	/* void moveWalktoHop( walk_t walk, vertex_t toVertex, int hop ){
		walk = encode( getSourceId(walk), toVertex, hop );
	}

	void initialnizeWalks( std::string filename ){
		// walks.resize(nshards);
		// walknum = (int*)malloc(nshards*sizeof(int));
		// base_filename = filename;
		// mkdir((base_filename+"_GraphWalker/walks/").c_str(), 0777);
	}

     int walksum(){
     		metrics_entry me = m.start_time();
     		int sum = 0;
          	for(int p=0; p < nshards; p++){
          		sum += walknum[p];
          	}
          	m.stop_time(me, "_check-finish");
          	return sum;
     }

     void setMinStep(int p, int hop ){
		#pragma omp critical
		{
		  	minstep[p] = minstep[p] < hop? minstep[p] : hop;
		}
     }

     int intervalWithMaxWalks(){
     		metrics_entry me = m.start_time();
     		int maxw = 0, maxp = 0;
          	for(int p = 0; p < nshards; p++) {
          		std::cout << p << " : *w: " << walknum[p] << "   s: " << minstep[p] << std::endl ;
		      	if( maxw < walknum[p] ){
	      			maxw = walknum[p];
	      			maxp = p;
	          	}
	   	}
	   	std::cout << std::endl;
          	m.stop_time(me, "_find-block-with-max-walks");
          	return maxp;
     }

     int intervalWithMinStep(){
     		metrics_entry me = m.start_time();
     		int mins = 0xfffffff, minp = 0;
          	for(int p = 0; p < nshards; p++) {
          		std::cout << p << " : w: " << walknum[p] << "   *s: " << minstep[p] << std::endl ;
		      	if( mins > minstep[p] ){
          			mins = minstep[p];
          			minp = p;
          		}
	   	}
	   	std::cout << std::endl;
          	m.stop_time(me, "_find-interval-with-min-steps");
          	return minp;
     }

     int intervalWithMaxWeight(){
     		metrics_entry me = m.start_time();
     		float maxwt = 0;
     		int maxp = 0;
          	for(int p = 0; p < nshards; p++) {
	      		if(  maxwt < (float)walknum[p]/minstep[p] ){
          			maxwt = (float)walknum[p]/minstep[p];
          			maxp = p;
          		}
	   	}
          	m.stop_time(me, "_find-interval-with-max-weight");
          	return maxp;
     }

     int intervalWithRandom(){
     		metrics_entry me = m.start_time();
     		int ranp = rand() % nshards;
          	m.stop_time(me, "_find-interval-with-random");
          	return ranp;
     }

     void printWalksDistribution( int exec_interval ){
     		//print walk number decrease trend
     		metrics_entry me = m.start_time();
     		std::string walk_filename = base_filename + ".walks";
     		std::ofstream ofs;
	     ofs.open(walk_filename.c_str(), std::ofstream::out | std::ofstream::app );
	   	int sum = 0;
	  	for(int p = 0; p < nshards; p++) {
	      		sum += walknum[p];
	   	}
	  	ofs << exec_interval << " \t " << walknum[exec_interval] << " \t " << sum << std::endl;
	 	ofs.close();
	 	m.stop_time(me, "_print-walks-distribution");
     }

     size_t readIntervalWalks( int p ){
     		std::string walksfile = walksname( base_filename, p );
     		int f = open(walksfile.c_str(),O_RDONLY | O_CREAT, S_IROTH | S_IWOTH | S_IWUSR | S_IRUSR);
        	if (f < 0) {
            	logstream(LOG_FATAL) << "Could not load :" << walksfile << " error: " << strerror(errno) << std::endl;
        	}
        	assert(f > 0);
        	size_t sz = readfull(f, &curwalks);
        	int count = sz/sizeof(walk_t);
        	close(f);
        	return count;
     }

     void writeIntervalWalks( int p ){
     		std::string walksfile = walksname( base_filename, p );
     		int f = open(walksfile.c_str(), O_WRONLY | O_TRUNC, S_IROTH | S_IWOTH | S_IWUSR | S_IRUSR);
		if (f < 0) {
		    logstream(LOG_ERROR) << "Could not open " << walksfile << " error: " << strerror(errno) << std::endl;
		 }
		close(f);
		free(curwalks);
		walknum[p] = 0;
		minstep[p] = 0xfffffff;
		for( p = 0; p < nshards; p++){
			std::string walksfile = walksname( base_filename, p );
     			int f = open(walksfile.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IROTH | S_IWOTH | S_IWUSR | S_IRUSR);
			if (f < 0) {
			    logstream(LOG_ERROR) << "Could not open " << walksfile << " error: " << strerror(errno) << std::endl;
			}
			if(!walks[p].empty())
				writea( f, &walks[p][0], walks[p].size()*sizeof(walk_t));
        		close(f);
        		walknum[p] += walks[p].size();
        		std::vector<walk_t> ().swap( walks[p] );
        		// walks[p].clear();
        		// walks[p].shrink_to_fit();
		}
     }    

     void freshIntervalWalks( ){
		for( int p = 0; p < nshards; p++){
			std::string walksfile = walksname( base_filename, p );
     			int f = open(walksfile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IROTH | S_IWOTH | S_IWUSR | S_IRUSR);
			if(!walks[p].empty())
				pwritea( f, &walks[p][0], walks[p].size()*sizeof(walk_t) );
        		close(f);
        		walknum[p] += walks[p].size();
        		std::vector<walk_t> ().swap( walks[p] );
        		// walks[p].clear();
        		// walks[p].shrink_to_fit();
		}
     }    

      void freshIntervalWalks(int p){
		std::string walksfile = walksname( base_filename, p );
   		int f = open(walksfile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IROTH | S_IWOTH | S_IWUSR | S_IRUSR);
		if(!walks[p].empty())
			pwritea( f, &walks[p][0], walks[p].size()*sizeof(walk_t) );
      		close(f);
      		walknum[p] += walks[p].size();
      		std::vector<walk_t> ().swap( walks[p] );
      		// walks[p].clear();
      		// walks[p].shrink_to_fit();
     }     */

};

#endif