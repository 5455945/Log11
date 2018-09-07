#include <iostream>
#include <tuple>
#include <thread>
#include <functional>
#include <future>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "log11.hpp"

void test1()
{
    FileLog flog("test.log");
    
    std::thread th_a([&](){
        for (unsigned int i = 0; i < 10000; i++)
        {
            flog.log.info("A", i, "->", 3.14);
        }
    });

    std::thread th_b([&](){
        for (unsigned int i = 0; i < 10000; i++)
        {
            flog.log.info("B", i, "->", 3.14, ":)");
        }
    });

    std::thread th_c([&](){
        for (unsigned int i = 0; i < 10000; i++)
        {
            flog.log.info("C", i, "->", 3.14, 5, "alfa", -1);
        }
    });

    th_a.join();
    th_b.join();
    th_c.join();

    std::cerr << "test1 completed" << std::endl;
}

void test2(Log11 log)
{
    std::thread th_a([&log](){
        for (unsigned int i = 0; i < 10000; i++)
        {
            log.info("A", i, "->", 3.14);
        }
    });

    std::thread th_b([&log](){
        for (unsigned int i = 0; i < 10000; i++)
        {
            log.info("B", i, "->", 2.7, ":)");
        }
    });


    std::thread th_c([&log](){
        for (unsigned int i = 0; i < 10000; i++)
        {
            log.debug("C", i, "->", "alfa", 1982);
        }
    });

    th_a.join();
    th_b.join();
    th_c.join();

    std::cout << "DONE" << std::endl;
}

#ifdef WIN32
#include <Shlobj.h>
#pragma comment( lib, "shell32.lib")
void GetLocalAppDataPathA(std::string &path)
{
    char lpszDefaultDir[MAX_PATH];
    char szDocument[MAX_PATH] = { 0 };
    memset(lpszDefaultDir, 0, _MAX_PATH);

    LPITEMIDLIST pidl = NULL;
    SHGetSpecialFolderLocation(NULL, CSIDL_APPDATA, &pidl);
    if (pidl && SHGetPathFromIDListA(pidl, szDocument))
    {
        GetShortPathNameA(szDocument, lpszDefaultDir, _MAX_PATH);
    }

    path = lpszDefaultDir;
}
#endif

void test03()
{
    std::string log_flag = "/log_";
    std::string app_path = "";
#ifdef WIN32
    GetLocalAppDataPathA(app_path);
#endif
    std::string logfile = app_path + log_flag;
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y%m");
    logfile += ss.str();
    logfile += ".log";
    g_log = new FileLog(logfile);
    LOG_INFO("创建日志文件:", logfile);
}

FileLog *g_log = nullptr;

int main(int argc, char** argv)
{
    test1();
    //test2(std::move(Log11()));
    test03();

    return 0;
}
