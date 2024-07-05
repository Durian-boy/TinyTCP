#ifndef DBG_H
#define DBG_H

// 前景色的设置会影响后续的打印
#define DBG_STYLE_ERROR "\033[31m"   // 前景色设置为红色
#define DBG_STYLE_WARNNING "\033[33m"   // 前景色设置为黄色
#define DBG_STYLE_RESET "\033[0m"   // 将前景色恢复默认

// 定义调试输出等级
#define DBG_LEVEL_NONE      0   // 不显示任何调试信息
#define DBG_LEVEL_ERROR     1   // 只显示错误信息
#define DBG_LEVEL_WARNING   2   // 只显示警告和错误信息
#define DBG_LEVEL_INFO      3   // 显示所有调试信息

void dbg_print(const char* file, const char* func, int len, const char* fmt, ...);

#define dbg_info(fmt, ...) dbg_print(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#endif