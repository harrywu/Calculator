#include "ros/ros.h"
#include "Calculator/AddTwoInts.h"
#include <gtest/gtest.h>

ros::ServiceClient client;
Calculator::AddTwoInts srv;

TEST(AddTwoIntsTest, test1)
{
  srv.request.a = 2;
  srv.request.b = 3;

  if (client.call(srv))
  {
      EXPECT_EQ(5, (long int)srv.response.sum);
  }
  else
  {
    EXPECT_TRUE(0);
  }
}

TEST(AddTwoIntsTest, test2)
{
  srv.request.a = -2;
  srv.request.b = -3;

  if (client.call(srv))
  {
      EXPECT_EQ(-5, (long int)srv.response.sum);
  }
  else
  {
    EXPECT_TRUE(0);
  }
}

TEST(AddTwoIntsTest, test3)
{
  srv.request.a = 0x7FFFFFFFFFFFFFFF;
  srv.request.b = 1;

  if (client.call(srv))
  {
    EXPECT_LT((long int)srv.response.sum, 0);
  }
  else
  {
    EXPECT_TRUE(0);
  }
}

TEST(AddTwoIntsTest, test4)
{
  srv.request.a = 0x8000000000000000;
  srv.request.b = 0xFFFFFFFFFFFFFFFF;

  if (client.call(srv))
  {
    EXPECT_LT(0, (long int)srv.response.sum);
  }
  else
  {
    EXPECT_TRUE(0);
  }
}

TEST(AddTwoIntsTest, test5)
{
  srv.request.a = 1.7;
  srv.request.b = 5.3;

  if (client.call(srv))
  {
    EXPECT_EQ(6, (long int)srv.response.sum);
  }
  else
  {
    EXPECT_TRUE(0);
  }
}


int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "tester_wu");

  ros::NodeHandle nh;
  client = nh.serviceClient<Calculator::AddTwoInts>("add_two_ints");

  return RUN_ALL_TESTS();
}
