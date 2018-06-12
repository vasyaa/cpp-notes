/*
 * parallel_for_each.h
 *
 *  Created on: Jun 5, 2018
 *      Author: vasyaa
 */

#ifndef PARALLEL_FOR_EACH_H_
#define PARALLEL_FOR_EACH_H_


#include <thread>
#include <future>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename Iterator,typename Func>
void parallel_for_each(Iterator first,Iterator last,Func f)
{
    ptrdiff_t const range_length=last-first;
    if(!range_length)
        return;
    if(range_length==1)
    {
        f(*first);
        return;
    }

    Iterator const mid=first+(range_length/2);

    std::future<void> bgtask=std::async(&parallel_for_each<Iterator,Func>,
                                        first,mid,f);
    try
    {
        parallel_for_each(mid,last,f);
    }
    catch(...)
    {
        bgtask.wait();
        throw;
    }
    bgtask.get();
}


void test() {
    vector<int> v(1024, 0);

    parallel_for_each(v.begin(), v.end(), [](int& a){a++;});

    copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    cout << endl;

//    for_all();
}



#endif /* PARALLEL_FOR_EACH_H_ */
