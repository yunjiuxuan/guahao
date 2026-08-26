#include "ui_LoginAndRegiste.h"




int main(void)
{
    DBG_PRINT();
    // lvgl初始化操作
    lvgl_init();
    // lv_port_disp_init();
    //  显示项目主界面
    //   show_main_win();

    DBG_PRINT();
    ui_init();
    DBG_PRINT();

   // create_timer();
    /*Handle LitlevGL tasks (tickless mode)*/
    while (1)
    {
        lv_timer_handler();
        usleep(5000);
    }

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if (start_ms == 0)
    {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
