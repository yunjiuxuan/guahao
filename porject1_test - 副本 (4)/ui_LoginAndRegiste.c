#include "ui/ui.h"
#include "ui_LoginAndRegiste.h"
#define MAX_LINE_LEN 200
static lv_timer_t *g_hide_timer = NULL;
user LoginUserinfo = {0};
/*
static void hide_label_timer_cb(lv_timer_t *timer)
{
    lv_obj_t *label = (lv_obj_t *)lv_timer_get_user_data(timer);
    if (label)
    {
        lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
    }
    g_hide_timer = NULL;
}

void show_temp_label(lv_obj_t *label, const char *text, uint32_t duration_ms)
{
    if (!label || !text)
        return;

    lv_label_set_text(label, text);
    lv_obj_clear_flag(label, LV_OBJ_FLAG_HIDDEN);

    if (g_hide_timer)
    {
        lv_timer_del(g_hide_timer);
    }

    g_hide_timer = lv_timer_create(hide_label_timer_cb, duration_ms, NULL);
    lv_timer_set_user_data(g_hide_timer, label);
} */
void ui_event_zhuce(lv_event_t *e)
{
    printf("\n=======================================================点击注册按钮");
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t *target = lv_event_get_target(e);

    if (event_code == LV_EVENT_CLICKED)
    {
        const char *docID = lv_textarea_get_text(ui_TextdocID);
        const char *id_card = lv_textarea_get_text(ui_userIDcardText_);
        const char *name = lv_textarea_get_text(ui_usernameText);
        const char *mima = lv_textarea_get_text(ui_mmText_);
        char role_buf[64];
        lv_dropdown_get_selected_str(ui_shenfen, role_buf, sizeof(role_buf)); // ← 正确方式
        DBG_PRINT();
        printf("\n已接收 → 身份证: %s, 姓名: %s, 密码: %s, 身份: %s\n", id_card, name, mima, role_buf);
        DBG_PRINT();
        if (!id_card || !name || !mima || !role_buf || strlen(id_card) == 0 || strlen(name) == 0 || strlen(mima) == 0 || strlen(role_buf) == 0)
        {

            show_popup("失败", "请填写完整信息");

            return;
        }

        DBG_PRINT();
        char path[20] = {0};
        if (strcmp(role_buf, "普通用户") == 0)
        {
            strcat(path, "PatientInfo.txt");
        }
        else
        {

            strcat(path, "DoctorInfo.txt");
        }

        DBG_PRINT();
        char path_buf[50] = {0};
        if (strlen(path) > 0)
        {
            sprintf(path_buf, "jiuxuanyiliao/%s", path);
        }
        else
        {
            printf("path为空");
            return;
        }

        DBG_PRINT();
        FILE *fp = fopen(path_buf, "r");
        bool id_exists = false;

        if (fp != NULL)
        {
            char line[MAX_LINE_LEN];
            char id_prefix[256];
            snprintf(id_prefix, sizeof(id_prefix), "id:%s ", id_card);

            while (fgets(line, sizeof(line), fp))
            {
                if (strncmp(line, id_prefix, strlen(id_prefix)) == 0)
                {
                    id_exists = true;
                    break;
                }
            }
            fclose(fp);
        }

        if (id_exists)
        {
            show_popup("失败", "该身份证已注册");
            printf("该身份证已注册\n");
            return; // 阻止注册
        }

        char new_line[MAX_LINE_LEN];
        int len;
        if (strcmp(role_buf, "普通用户"))
        {
            len = snprintf(new_line, sizeof(new_line), "id:%s name:%s mima:%s role_buf:%s\n", id_card, name, mima, role_buf);
        }
        else
        {
            len = snprintf(new_line, sizeof(new_line), "id:%s name:%s mima:%s \n", id_card, name, mima);
        }

        if (len >= (int)sizeof(new_line))
        {
            printf("输入数据过长\n");
            return;
        }
        bool fileres = is_doc_registered("patsTXT", docID); // true 存在 false 不存在

        if (strcmp(docID, "630630") == 0)
        {
            DBG_MSG("医生编号正确   ,开始写入文件");

            char docfile[50];
            sprintf(docfile, "patsTXT/%s.txt", docID);
            FILE *fp = fopen(docfile, "w");
            if (fp)
            { 
                fprintf(fp, "空闲中\n\n"); // 两行：就诊中 + 呼唤中（空）
                fclose(fp);
                DBG_MSG("医生注册成功，文件已创建: %s", docfile);
                show_popup("注册成功", "医生信息已保存");
            }
            else
            {
                DBG_MSG("无法创建文件: %s", docfile);
                show_popup("注册失败", "无法写入文件");
                return ;
            }

            fp = fopen(path_buf, "a");
            if (!fp)
            {
                fprintf(stderr, "无法打开文件 '%s': %s\n", path_buf, strerror(errno));
                return;
            }
            fputs(new_line, fp);
            DBG_PRINT();
            fclose(fp);
            DBG_PRINT();
            printf("\n--- 当前 %s.txt 全部内容 ---\n", path_buf);
            fp = fopen(path_buf, "r");
            if (!fp)
            {
                printf("写入后无法读取文件");
            }
            DBG_PRINT();
            char line[MAX_LINE_LEN] = {0};
            char last_line[MAX_LINE_LEN] = {0};
            DBG_PRINT();
            while (fgets(line, sizeof(line), fp))
            {
                printf("%s", line);

                char temp[MAX_LINE_LEN];
                strncpy(temp, line, sizeof(temp) - 1);
                temp[strcspn(temp, "\r\n")] = '\0';
                if (strlen(temp) > 0)
                {
                    strncpy(last_line, temp, sizeof(last_line) - 1);
                }
            }
            DBG_PRINT();
            fclose(fp);
            printf("----------------------------------\n");
            DBG_PRINT();

            char expected[MAX_LINE_LEN] = {0};
            DBG_PRINT();
            strncpy(expected, new_line, sizeof(expected) - 1);
            DBG_PRINT();
            expected[strcspn(expected, "\r\n")] = '\0';
            DBG_PRINT();
            if (strcmp(expected, last_line) == 0)
            {

                DBG_MSG("expected    %s\n", expected);
                DBG_MSG("last_line    %s\n", last_line);

                DBG_PRINT();
                show_popup("成功", "注册成功");
                DBG_MSG("注册成功");
            }
            else
            {
                DBG_PRINT();
                DBG_MSG("expected: '%s'\n", expected);
                DBG_MSG("last_line: '%s'\n", last_line);
                return "写入验证失败";
            }
        }

        else if (fileres)
        {
            show_popup("注册失败", "该编号已注册");
            DBG_MSG("该编号已注册");
            return;
        }
        else
        {
            show_popup("注册失败", "请填写医院邮箱中的医生编号");
            DBG_MSG("请填写医院邮箱中的医生编号");
            return;
        }
    }
    DBG_PRINT();
}

void ui_event_denglu_click(lv_event_t *e)
{
    DBG_PRINT();
    lv_event_code_t event_code = lv_event_get_code(e);
    DBG_PRINT();
    if (event_code != LV_EVENT_RELEASED)
    {
        DBG_PRINT();
        if (is_processing == true)
            return;
    }
    is_processing = true;
    printf("\n=======================================================点击登录按钮");

    DBG_PRINT();
    // 获取输入
    const char *id_card = lv_textarea_get_text(ui_userIDcardText_);
    const char *docID = lv_textarea_get_text(ui_TextdocID);
    DBG_PRINT(); // 身份证号
    const char *name = lv_textarea_get_text(ui_usernameText);
    DBG_PRINT(); // 姓名
    const char *password = lv_textarea_get_text(ui_mmText_);
    DBG_PRINT(); // 密码

    static char role_buf[64];
    DBG_PRINT();
    lv_dropdown_get_selected_str(ui_shenfen, role_buf, sizeof(role_buf));
    DBG_PRINT();
    if (!id_card || !name || !password || !role_buf || strlen(id_card) == 0 || strlen(name) == 0 || strlen(password) == 0 || strlen(role_buf) == 0)
    {
        DBG_PRINT();
        show_popup("失败", "请填写完整信息");
        printf("未接收到完整数据\n");
        is_processing = false;
        return;
    }
    DBG_PRINT();

    printf("接收到 身份证: %s, 姓名: %s, 密码: %s, 角色: %s\n", id_card, name, password, role_buf);
    DBG_PRINT();
    const char *filepath;
    DBG_PRINT();
    if (!docID)
    {
        show_popup("注册失败", "请输入医院邮箱中的编码");
        return;
    }
    DBG_PRINT();
    if (strcmp(role_buf, "普通用户"))
    {
        printf("\n是本院医生\n");
        show_popup("注意", "请输入医院邮箱中的编码");
        DBG_PRINT();
        bool fileres = is_doc_registered("patsTXT", docID); // true 存在 false 不存在

        if (fileres)
        {
            filepath = "jiuxuanyiliao/DoctorInfo.txt";
        }
        else
        {
            DBG_PRINT();
            show_popup("注册失败", "请输入医院邮箱中的编码");
            return;
        }
    }
    else
    {
        DBG_PRINT();
        lv_obj_add_flag(ui_jiuzhenzhongDropdown, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(ui_huhuanzhongDropdown, LV_OBJ_FLAG_HIDDEN);
        filepath = "jiuxuanyiliao/PatientInfo.txt";
    }
    DBG_PRINT();

    printf("使用文件: %s\n", filepath);

    FILE *fp = fopen(filepath, "r");
    if (!fp)
    {
        printf("%s 不存在或无法打开\n", filepath);
        is_processing = false;
        return;
    }
    DBG_PRINT();
    char line[200];
    bool user_found = false;
    bool login_success = false;
    DBG_PRINT();
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\r\n")] = '\0'; // 去换行
        if (strlen(line) == 0)
            continue;

        printf("line: %s\n", line);

        char file_id[100] = {0}, file_name[100] = {0}, file_pwd[100] = {0};
        if (sscanf(line, "id:%99s name:%99s mima:%99s", file_id, file_name, file_pwd) != 3)
        {
            continue;
        }
        DBG_PRINT();

        DBG_MSG("读取到 id:%s name:%s mima:%s", file_id, file_name, file_pwd);

        // 比对身份证
        if (strcmp(file_id, id_card) == 0)
        {
            user_found = true;
            printf("身份证匹配: %s\n", id_card);

            // 比对姓名
            if (strcmp(file_name, name) != 0)
            {
                show_popup("错误", "姓名与身份证不符");
                printf("姓名不匹配！输入: %s, 读取到: %s\n", name, file_name);

                //  show_temp_label(ui_errorLabel, "姓名与身份证不符", 2000);
                is_processing = false;
                printf("姓名与身份证不符\n");
                return;
            }
            else
            {
                // 比对密码
                if (strcmp(file_pwd, password) != 0)
                {
                    printf("file_pwd: %s    password: %s", file_pwd, password);
                    show_popup("失败", "密码错误！");
                    printf("密码错误！\n");

                    is_processing = false;
                    return;
                }
                else
                {
                    printf("密码正确！\n");

                    is_processing = false;
                }
            }
            DBG_PRINT();

            // 全部匹配
            login_success = true;
            break;
        }
        DBG_PRINT();
    }
    fclose(fp);

    if (!user_found)
    {
        show_popup("失败", "用户不存在");
        printf("用户不存在\n");

        // show_temp_label(ui_errorLabel, "用户不存在", 2000);
    }
    else if (login_success)
    {
        show_popup("登录成功", "1层挂号后可前往2,3层等候诊治");
        printf("登录成功！\n");
        lv_obj_clear_flag(label_timeANDdate, LV_OBJ_FLAG_HIDDEN); // 显示
        DBG_MSG("显示时间标签");
        strcat(LoginUserinfo.username, name);
        if (strcmp(role_buf, "普通用户"))
            LoginUserinfo.role = 0;
        if (strcmp(role_buf, "中医科医师"))
            LoginUserinfo.role = 1;
        if (strcmp(role_buf, "康复科医师"))
            LoginUserinfo.role = 2;
        if (strcmp(role_buf, "内科医师"))
            LoginUserinfo.role = 3;
        if (strcmp(role_buf, "外科医师"))
            LoginUserinfo.role = 4;

        strcat(LoginUserinfo.idcard, id_card);

        //  show_temp_label(ui_errorLabel, "登录成功", 2000);

        printf("跳转到地图界面\n");
        // lv_disp_load_scr(ui_doctorWin);
        lv_disp_load_scr(ui_ditu123);
        is_processing = false;
        return;
    }

    is_processing = false;
}