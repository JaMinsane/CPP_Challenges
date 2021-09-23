/**
  ******************************************************************************
  * @file           : mutex_multipleSharedResource.cpp
  * @brief          : Operations with shared vectors in threads scopes
  ******************************************************************************
	* @Author: James Jaramillo - james.jh03@gmail.com
  ******************************************************************************
*/
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <gtest/gtest.h>

//Define a mutex for each shared resource in the appropriate context (global or class scope)
template <typename T>
struct container {
    std::mutex mutex;
    std::vector<T> data;
};

//Lock the mutexes at the same time using a deadlock avoidance algorithm with std::lock()
template <typename T>
void move_between(container<T> & c1, container<T> & c2, T const value)
{
std::lock(c1.mutex, c2.mutex);

/*After locking them, adopt the ownership of each mutex into an std::lock_
guard class to ensure they are safely released at the end of the function (or
scope):*/
std::lock_guard<std::mutex> l1(c1.mutex, std::adopt_lock);
std::lock_guard<std::mutex> l2(c2.mutex, std::adopt_lock);

/*C++ 17: A new mutex wrapper is available. The 3 lines of code behind can 
be replaced with a single line of code:
    std::scoped_lock lock(c1.mutex, c2.mutex);
*/

c1.data.erase(
    std::remove(c1.data.begin(), c1.data.end(), value), 
    c1.data.end());
c2.data.push_back(value);

}

container<int> c1;
container<int> c2;
/*CASE: C1 = { 1,2,3 } ; C2 = { 4,5,6 } */
/*CASE ORDER T1, T2:
* 1° Thread: (Value = 3) -> c1 = 1, 2  ;  c2 = 4, 5, 6, 3
* 2° Thread: (Value = 6) -> c2 = 4, 5, 3  ;  c1 = 1, 2, 6
*CASE ORDER T2, T1:
* 2° Thread: (Value = 6) -> c2 = 4, 5  ;  c1 = 1, 2, 3, 6
* 1° Thread: (Value = 3) -> c1 = 1, 2, 6  ;  c2 = 4, 5, 3
* Finally: c1 = 1, 2, 6   ;   c2 = 4, 5, 3   */
TEST(Test, Test1){ 
    EXPECT_EQ(c1.data[0], 1); EXPECT_EQ(c1.data[1], 2); EXPECT_EQ(c1.data[2], 6);
    EXPECT_EQ(c2.data[0], 4); EXPECT_EQ(c2.data[1], 5); EXPECT_EQ(c2.data[2], 3);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    std::vector<int> v1 = { 1,2,3 };
    c1.data = v1;
    std::vector<int> v2 = { 4,5,6 };
    c2.data = v2;
    
    std::thread t1(move_between<int>, std::ref(c1), std::ref(c2), 3);
    std::thread t2(move_between<int>, std::ref(c2), std::ref(c1), 6);

    t1.join();
    t2.join();

    std::cout << "Resultado de c1: " ;
    for (auto i: c1.data)
        std::cout << i << ' ';
    std::cout << std::endl;
    std::cout << "Resultado de c2: " ;
    for (auto i: c2.data)
        std::cout << i << ' ';
    std::cout << std::endl;

    
    return RUN_ALL_TESTS();
}
