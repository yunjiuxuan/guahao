#include "ui_LoginAndRegiste.h"


#define DISP_BUF_SIZE (600 * 1024)

// lvgl初始化操作
void lvgl_init(void)
{
    /*LittlevGL init 设备初始化*/
    lv_init();

    /*Linux frame buffer device init 帧缓冲初始化*/
    fbdev_init();

    /*A small buffer for LittlevGL to draw the screen's content*/
    static lv_color_t buf[DISP_BUF_SIZE];

    /*Initialize a descriptor for the buffer 绘制区域*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

    /*Initialize and register a display driver 帧缓冲设备参数*/
    static lv_disp_drv_t disp_drv;   // 定义设备结构体
    lv_disp_drv_init(&disp_drv);     // 初始化设备对象
    disp_drv.draw_buf = &disp_buf;   // 结构体记录绘制区域首地址
    disp_drv.flush_cb = fbdev_flush; // 屏幕显示数据
    disp_drv.hor_res = 1024;         // 可见宽度
    disp_drv.ver_res = 600;          // 可见高度
    lv_disp_drv_register(&disp_drv); // 注册lcd设备到lvgl当中

    evdev_init(); // 输入设备初始化
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);          // 设备结构体初始化
    indev_drv_1.type = LV_INDEV_TYPE_POINTER; // 设置设备类型为点击触摸
    indev_drv_1.read_cb = evdev_read;         // 读取输入设备的事件
    lv_indev_drv_register(&indev_drv_1);      // 注册输入事件到lvgl当中
}

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
