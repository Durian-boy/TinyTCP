#include "net.h"
#include "net_err.h"
#include "exmsg.h"
#include "net_plat.h"

net_err_t net_init(void) {
    // 针对特定平台的初始化
    net_plat_init();
    // 核心线程的初始化
    exmsg_init();
    return NET_ERR_OK;
}
net_err_t net_start(void) {
    // 核心线程的启动
    exmsg_start();
    return NET_ERR_OK;
}