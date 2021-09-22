/**
  ******************************************************************************
  * @file           : reto_IP.cpp
  * @brief          : Validate IP Address
  ******************************************************************************
	* @Author: James Jaramillo - james.jh03@gmail.com
  ******************************************************************************
*/
#include <iostream>
#include <string>
#include <cstring>
#include <gtest/gtest.h>

using namespace std;

bool validateIP(const string& ip)
{   
  std::string ips = ip;
  char ip_str[200];
  uint8_t cont_valids = 0;
  char *endptr = NULL;
  while(true){
    errno = 0;
    auto n = ips.find(".");
    if (n != std::string::npos){
        ips.copy(ip_str, n);
        ip_str[n] = '\0';
        if(strtol(ip_str,&endptr,10) >=0 && strtol(ip_str,&endptr,10) <= 255) cont_valids++;
        if(strlen(ip_str)==0) cont_valids--;
        /*Evaluate the case when is a valid int but with additional characters*/
        if (errno == 0 && ip_str && *endptr != 0) cont_valids--;
        ips.erase(0,n+1);
    }else{
        ips.copy(ip_str, sizeof ips);
        if(strtol(ip_str,&endptr,10) >=0 && strtol(ip_str,&endptr,10) <= 255) cont_valids++;
        if(strlen(ip_str)==0) cont_valids--;
        if (errno == 0 && ip_str && *endptr != 0) cont_valids--;
        break;
    }
  }
  return cont_valids == 4 ? true : false ;
}

TEST(IPValidateTest, Test1){ EXPECT_TRUE(validateIP("192.168.0.1"));}
TEST(IPValidateTest, Test2){ EXPECT_TRUE(validateIP("0.0.0.0"));}
TEST(IPValidateTest, Test3){ EXPECT_TRUE(validateIP("123.24.59.99"));}
TEST(IPValidateTest, Test4){ EXPECT_FALSE(validateIP("192.168.123.456"));}
TEST(IPValidateTest, Test5){ EXPECT_FALSE(validateIP("1.2.3.4.5"));}
TEST(IPValidateTest, Test6){ EXPECT_FALSE(validateIP("1..23.4"));}
TEST(IPValidateTest, Test7){ EXPECT_FALSE(validateIP("123.256.34.56"));}
TEST(IPValidateTest, Test8){ EXPECT_FALSE(validateIP(".254.255.0"));}
TEST(IPValidateTest, Test9){ EXPECT_FALSE(validateIP("1.2.3.0x1"));}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
