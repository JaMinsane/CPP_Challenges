/**
  ******************************************************************************
  * @file           : mutex_singleSharedResource.cpp
  * @brief          : Single Shared Resource in Thread
  ******************************************************************************
	* @Author: James Jaramillo - james.jh03@gmail.com
  ******************************************************************************
*/
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <gtest/gtest.h>

using namespace std;

std::mutex g_mutex;
void thread_func()
{
  using namespace std::chrono_literals;
  {
  std::lock_guard<std::mutex> lock(g_mutex);
  std::cout << "running thread "
  << std::this_thread::get_id() << '\n';
  }
    std::this_thread::yield();
    std::this_thread::sleep_for(2s);
  {
  std::lock_guard<std::mutex> lock(g_mutex);
  std::cout << "done in thread "
  << std::this_thread::get_id() << '\n';
  }
}


int main(int argc, char* argv[]) {

  std::thread t(thread_func);
  t.join();

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
