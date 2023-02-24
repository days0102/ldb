/*
 * @Author: Outsider
 * @Date: 2023-02-24 11:06:31
 * @LastEditors: Outsider
 * @LastEditTime: 2023-02-24 13:19:56
 * @Description: In User Settings Edit
 * @FilePath: /ldb/client.cc
 */
#include <iostream>
#include <getopt.h>
auto main(int argc, char *argv[]) -> int
{
    int opt;
    while ((opt = getopt(argc, argv, "p:")) > 0)
    {
        std::cout << opt << std::endl;
    }
}