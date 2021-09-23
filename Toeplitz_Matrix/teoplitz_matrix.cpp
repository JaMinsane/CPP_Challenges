#include <iostream>
#include <vector>
#include <gtest/gtest.h>

using namespace std;

bool isToeplitz(const vector<vector<int>>& arr)
{
  for (int i = 0; i < arr.size(); i++){
    for (int j = 0; j < arr[i].size(); j++){
      if(i!=arr.size()-1 && j != arr[i].size()-1){
        if(arr[i][j] != arr[i+1][j+1]){
          return false;
        }
      }
    }
}
  return true;
}

TEST(ValidateToeplitz, Test1){ EXPECT_TRUE(isToeplitz({{4,0},{9,4}}));}
TEST(ValidateToeplitz, Test2){ EXPECT_TRUE(isToeplitz({{6,4,4}}));}
TEST(ValidateToeplitz, Test3){ EXPECT_TRUE(isToeplitz({{3},{5},{6}}));}
TEST(ValidateToeplitz, Test4){ EXPECT_TRUE(isToeplitz({{3,9},{5,3},{6,5}}));}
TEST(ValidateToeplitz, Test5){ EXPECT_FALSE(isToeplitz({{3,1,7},{4,1,1},{2,4,3}}));}
TEST(ValidateToeplitz, Test6){ EXPECT_FALSE(isToeplitz({{8,8,8,8,8},{8,8,8,8,9},{8,8,8,8,8},{8,8,8,8,8},{8,8,8,8,8}}));}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
