#include <iostream>
#include "Eigen/Core"
#include "Eigen/Geometry"

#ifdef WIN32
    #include <io.h>
    #include <windows.h>
    #include <direct.h>
    #include <sys/stat.h>
#endif

#include "glog/logging.h"

#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int init_glog(){

    google::InitGoogleLogging("app");
    google::SetStderrLogging(google::GLOG_INFO);
    FLAGS_colorlogtostderr = true;  // Set log color
    FLAGS_log_dir = "./logs";

#ifdef WIN32
            if (_access(FLAGS_log_dir.c_str(), 0) == -1) // 如果文件夹不存在
            {
                _mkdir(FLAGS_log_dir.c_str()); // 则创建
            }
#else
            if (access(FLAGS_log_dir.c_str(), 0) == -1) // 如果文件夹不存在
            {
                mkdir(FLAGS_log_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // 则创建
            }
#endif

    google::SetLogDestination(google::GLOG_INFO, "./logs/INFO_");
    google::SetLogDestination(google::GLOG_ERROR, "./logs/ERROR_");
    google::SetLogDestination(google::GLOG_WARNING, "./logs/WARNING_");
    google::SetLogDestination(google::GLOG_FATAL, "./logs/FATAL_");
    google::SetLogFilenameExtension(".log");
    FLAGS_logbufsecs = 0;  // Set log output speed(s)
    FLAGS_max_log_size = 10;  // Set max log file size, MB
    FLAGS_stop_logging_if_full_disk = true;  // If disk is full

    // TEST LOG
    LOG(INFO) << "============= start glog ===============";
    char str[20] = "hello log!";
    LOG(INFO) << str;
    std::string cStr = "hello google!";
    LOG(INFO) << cStr;
    LOG(INFO) << "info test" << "hello log!";  //输出一个Info日志
    LOG(WARNING) << "warning test";  //输出一个Warning日志
    LOG(ERROR) << "error test";  //输出一个Error日志
    LOG(INFO) << "============= start glog ===============";

    // google::ShutdownGoogleLogging();
    return 0;
}

int test_eigen(){
    Eigen::Quaterniond a(1,0,0,0);
    Eigen::Matrix3d  d;
    d<< 1,2,3,
    4,5,6,
    7,8,9;
    std::cout << d << "\n";

    Eigen::Vector3d gravity_vector_(0,0,-9.87);
    Eigen::Quaterniond orientation_(0.996,0,0,0.259);

    const Eigen::Quaterniond rotation = Eigen::Quaterniond::FromTwoVectors(
            gravity_vector_, orientation_.conjugate() * Eigen::Vector3d::UnitZ());

    std::cout  << "orientation_.conjugate(): "<< orientation_.conjugate() << "\n";;
    std::cout  << "rotation: "<< rotation << "\n";;
    LOG(INFO) << "rotation: "<< rotation;

    return 0;
}


int test_memory_leak1(){
    int* x = (int*)malloc(sizeof(int));
    *x = 7;
    printf("%d\n", *x);

    x = (int*)calloc(3, sizeof(int));
    x[0] = 7;
    x[1] = 77;
    x[2] = 777;

    printf("%d %d %d\n", x[0], x[1], x[2]);

    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG); 
    _CrtDumpMemoryLeaks();
    return 0;
}
int test_memory_leak2(){
    _CrtMemState s1, s2, s3;
    int* x = (int*)malloc(sizeof(int));
    *x = 7;
    printf("%d\n", *x);
    _CrtMemCheckpoint( &s1 );

    x = (int*)calloc(3, sizeof(int));
    x[0] = 7;
    x[1] = 77;
    x[2] = 777;
    _CrtMemCheckpoint( &s2 );
    if ( _CrtMemDifference( &s3, &s1, &s2) ) 
        _CrtMemDumpStatistics( &s3 );

    printf("%d %d %d\n", x[0], x[1], x[2]);

    return 0;
}

int main(int argc, char** argv) {
    init_glog();
    std::cout << "Hello, World!" << std::endl;

    // test_eigen();

    // 不打印，可能需要在visual studio中F5启动调试
    // test_memory_leak1();
    // test_memory_leak2();

    google::ShutdownGoogleLogging();
    return 0;
}
