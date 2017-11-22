#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QFont font;
    font.setBold(false);
    font.setPointSize(9);
    setFont(font);

    ui->setupUi(this);

    item_init();
    slot_init();

    setWindowIcon(QIcon(":/logo.jpg"));
    setWindowTitle(tr("ysstb_tools V1.0"));
    resize(860, 650);
}

int MainWindow::item_init()
{
    tuner_select(4);
    demod_select(0);
    i2c_chnl_select(0);

    ui->eight_line_radioButton->setChecked(true);
    ui->eight_line_radioButton->setEnabled(false);
    ui->nine_line_radioButton->setEnabled(false);
    tsi_intf_line_select(true);

    ui->actionHI3796MV100->setEnabled(false);
    ui->actionHI3798MV100->setEnabled(false);
    ui->actionHI3798MV300->setEnabled(false);

    ui->actionHI3796MV100->setCheckable(true);
    ui->actionHI3798MV100->setCheckable(true);
    ui->actionHI3798MV300->setCheckable(true);
    ui->actionHI3798MV200->setCheckable(true);
    ui->actionHI3798CV200->setCheckable(true);

    ui->actionHI3798MV200->setChecked(true);

    //ui->logTextEdit->setMinimumHeight(1000);
    QTextCursor cursor = ui->logTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logTextEdit->setTextCursor(cursor);
    return 0;
}

int MainWindow::slot_init()
{
    connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(chip_select(QAction*)));
    //connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(chip_select(QAction*)));

    connect(ui->tuner_select_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(tuner_select(int)));
    connect(ui->demod_select_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(demod_select(int)));
    connect(ui->i2c_chnl_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(i2c_chnl_select(int)));
    connect(ui->eight_line_radioButton, SIGNAL(clicked(bool)), this, SLOT(tsi_intf_line_select(bool)));
    connect(ui->nine_line_radioButton, SIGNAL(clicked(bool)), this, SLOT(tsi_intf_line_select(bool)));

    connect(ui->gen_regtable_btn, SIGNAL(clicked(bool)), this, SLOT(gen_regtable_btn_clicked(bool)));
    connect(ui->gen_config_btn, SIGNAL(clicked(bool)), this, SLOT(gen_config_btn_clicked(bool)));
    connect(ui->gen_code_btn, SIGNAL(clicked(bool)), this, SLOT(gen_code_btn_clicked(bool)));
    return 0;
}

int MainWindow::logout(char *func, int line, char *fmt, ...)
{
    int MsgLen;
    char log_str[512];
    va_list args;
    va_start(args, fmt);
    MsgLen = vsnprintf(log_str, sizeof(log_str), fmt, args);
    va_end(args);

    ui->logTextEdit->appendPlainText(QString("[%1]:%2:%3").arg(func).arg(line).arg(log_str));
    QTextCursor cursor = ui->logTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logTextEdit->setTextCursor(cursor);

    QScrollBar *scrollbar = ui->logTextEdit->verticalScrollBar();
    scrollbar->setSliderPosition(scrollbar->maximum());

    return MsgLen;
}

int MainWindow::chip_select(QAction *action)
{
    if(action->text() == tr("help")){

        QMessageBox::information(this, "使用帮助",
         "本工具用于海思平台下外设快速适配，如：tuner，demod，ca卡，锁频灯。"
         "工具能快速生成管脚复用配置及代码，免去查询手册过程。enjoy it!\n"
         "使用步骤：\n"
        "1. 照硬件原理图，选择硬件的外设管脚配置。如I2C通道，TSI port管脚等。\n"
        "2. 依次配置到I2C，tuner，demod，ca等管脚信息。\n"
        "3. 点击生成按钮，生成文件。\n"
                                 );
        YLOG("help toggled!");
        return 0;
    }

    ui->actionHI3796MV100->setChecked(false);
    ui->actionHI3798MV100->setChecked(false);
    ui->actionHI3798MV300->setChecked(false);
    ui->actionHI3798MV200->setChecked(false);
    ui->actionHI3798CV200->setChecked(false);

    action->setChecked(true);
    if(action->text() == tr("HI3798MV200")){
        m_chip_type = CHIP_HI3798MV200;
        YLOG("HI3798MV200 toggled!");
    }else if(action->text() == tr("HI3798CV200")){
        m_chip_type = CHIP_HI3798CV200;
        YLOG("HI3798CV200 toggled!");
    }else if(action->text() == tr("HI3796MV100")){
        m_chip_type = CHIP_HI3796MV100;
        YLOG("HI3796MV100 toggled!");
    }else if(action->text() == tr("HI3798MV100")){
        m_chip_type = CHIP_HI3798MV100;
        YLOG("HI3798MV100 toggled!");
    }else if(action->text() == tr("HI3716MV310")){
        m_chip_type = CHIP_HI3716MV310;
        YLOG("HI3716MV310 toggled!");
    }else if(action->text() == tr("HI3716MV330")){
        m_chip_type = CHIP_HI3716MV330;
        YLOG("HI3716MV330 toggled!");
    }

    return 0;
}

int MainWindow::set_tuner_max_port(int tuner_port_count)
{
    ui->TSI0_pinmux->setEnabled(false);
    ui->TSI1_pinmux->setEnabled(false);
    ui->TSI2_pinmux->setEnabled(false);
    ui->TSI3_pinmux->setEnabled(false);

    switch(tuner_port_count){
        case 4:
        ui->TSI3_pinmux->setEnabled(true);
        case 3:
        ui->TSI2_pinmux->setEnabled(true);
        case 2:
        ui->TSI1_pinmux->setEnabled(true);
        case 1:
        ui->TSI0_pinmux->setEnabled(true);
        break;
        default:
        break;
    }
    YLOG("tuner_port_count=%d", tuner_port_count);
    return 0;
}

int MainWindow::tuner_select(int index)
{
    ui->tuner_select_comboBox->setCurrentIndex(index);
    QString tuner_type = ui->tuner_select_comboBox->currentText();
    if(tuner_type == tr("MXL608")) {
        ui->tuner_addr_lineEdit->setText(tr("C2"));
        set_tuner_max_port(1);
    }else if(tuner_type == tr("R836")) {
        ui->tuner_addr_lineEdit->setText(tr("34"));
        set_tuner_max_port(1);
    }else if(tuner_type == tr("R858")) {
        ui->tuner_addr_lineEdit->setText(tr("A0"));
        set_tuner_max_port(2);
    }else if(tuner_type == tr("MXL214C")) {
        ui->tuner_addr_lineEdit->setText(tr("A0"));
        set_tuner_max_port(4);
        ui->eight_line_radioButton->setEnabled(true);
        ui->nine_line_radioButton->setEnabled(true);
    }else if(tuner_type == tr("MXL254C")) {
        ui->tuner_addr_lineEdit->setText(tr("A0"));
        set_tuner_max_port(4);
        ui->eight_line_radioButton->setEnabled(true);
        ui->nine_line_radioButton->setEnabled(true);
    }

    YLOG("tuner_type=%s", tuner_type.toLocal8Bit().data());
    return 0;
}

int MainWindow::demod_select(int index)
{
    QString demod_type = ui->demod_select_comboBox->currentText();
    YLOG("demod_type=%s", demod_type.toLocal8Bit().data());
    return 0;
}

int MainWindow::i2c_chnl_select(int index)
{
    int pin_index;
    QString i2c_chnl = ui->i2c_chnl_comboBox->currentText();
    qDebug()<<"i2c_chnl_select"<<ui->i2c_chnl_comboBox->currentText();
    if(i2c_chnl == tr("I2C0")) {
        pin_index = ui->i2c_scl_pin_comboBox->findText(tr("PMC_GPU0"));
        ui->i2c_scl_pin_comboBox->setCurrentIndex(pin_index);
        qDebug()<<"PMC_GPU0 index:"<<pin_index;
        pin_index = ui->i2c_sda_pin_comboBox->findText(tr("PMC_CORE0"));
        ui->i2c_sda_pin_comboBox->setCurrentIndex(pin_index);
        qDebug()<<"PMC_CORE0 index:"<<pin_index;

    }else if(i2c_chnl == tr("I2C1")) {
        pin_index = ui->i2c_scl_pin_comboBox->findText(tr("GPIO4_5"));
        ui->i2c_scl_pin_comboBox->setCurrentIndex(pin_index);
        qDebug()<<"GPIO4_5 index:"<<pin_index;
        pin_index = ui->i2c_sda_pin_comboBox->findText(tr("GPIO4_4"));
        ui->i2c_sda_pin_comboBox->setCurrentIndex(pin_index);
        qDebug()<<"GPIO4_4 index:"<<pin_index;

    }else if(i2c_chnl == tr("I2C2")) {
        pin_index = ui->i2c_scl_pin_comboBox->findText(tr("GPIO6_1"));
        ui->i2c_scl_pin_comboBox->setCurrentIndex(pin_index);
        qDebug()<<"GPIO6_1 index:"<<pin_index;
        pin_index = ui->i2c_sda_pin_comboBox->findText(tr("GPIO6_2"));
        ui->i2c_sda_pin_comboBox->setCurrentIndex(pin_index);
        qDebug()<<"GPIO6_1 index:"<<pin_index;
    }

    YLOG(" i2c_chnl=%s", i2c_chnl.toLocal8Bit().data());
    return 0;
}

int MainWindow::tsi_intf_line_select(bool clicked)
{
    if(ui->nine_line_radioButton->isChecked()) {
        ui->clk_share_comboBox->setEnabled(true);
        ui->clk_share_comboBox->setCurrentIndex(ui->clk_share_comboBox->findText(tr("TSI2_CLK")));
        ui->tsi0_sync_comboBox->setEnabled(false);
        ui->tsi1_sync_comboBox->setEnabled(false);
        ui->tsi2_sync_comboBox->setEnabled(false);
        ui->tsi3_sync_comboBox->setEnabled(false);
        ui->tsi0_clk_comboBox->setEnabled(false);
        ui->tsi1_clk_comboBox->setEnabled(false);
        ui->tsi2_clk_comboBox->setEnabled(false);
        ui->tsi3_clk_comboBox->setEnabled(false);
        ui->tsi0_valid_comboBox->setEnabled(true);
        ui->tsi1_valid_comboBox->setEnabled(true);
        ui->tsi2_valid_comboBox->setEnabled(true);
        ui->tsi3_valid_comboBox->setEnabled(true);
        YLOG(" 设置9线制");
    }else{
        ui->clk_share_comboBox->setEnabled(false);
        ui->tsi0_sync_comboBox->setEnabled(true);
        ui->tsi1_sync_comboBox->setEnabled(true);
        ui->tsi2_sync_comboBox->setEnabled(true);
        ui->tsi3_sync_comboBox->setEnabled(true);
        ui->tsi0_clk_comboBox->setEnabled(true);
        ui->tsi1_clk_comboBox->setEnabled(true);
        ui->tsi2_clk_comboBox->setEnabled(true);
        ui->tsi3_clk_comboBox->setEnabled(true);
        ui->tsi0_valid_comboBox->setEnabled(false);
        ui->tsi1_valid_comboBox->setEnabled(false);
        ui->tsi2_valid_comboBox->setEnabled(false);
        ui->tsi3_valid_comboBox->setEnabled(false);
        YLOG(" 设置8线制");
    }

    return 0;
}

int MainWindow::find_reg_config_and_add(char *pinname, char*funcname, bool isComment)
{
    U32 reg_addr, reg_val;
    QString reg_addr_str, reg_val_str;
    QString comment;
    pinmux_reg_t *reg;

#define REG_CONFIG_ADD(reg_addr, reg_val) \
    do{\
        reg_addr_str = QString::number(reg_addr, 16);\
        reg_val_str = QString::number(reg_val, 16);\
        m_data.append("0x");\
        m_data.append(reg_addr_str);\
        m_data.append(", ");\
        m_data.append("0x");\
        m_data.append(reg_val_str);\
        m_data.append(comment);\
        m_data.append("\n");\
    }while(0)

    qDebug()<<"pinname:"<<pinname<<"funcname:"<<funcname;
    YLOG("pin_name:%s, func_name:%s", pinname, funcname);
    reg = m_chip_reg.get_pinmux_reg_config(pinname, funcname, &reg_addr, &reg_val);
    if(!reg)
        return -1;

    if(isComment){
        //comment = QString(" //%1, pin_name=%2, %3").arg(funcname).arg(pinname).arg(QString(reg->reg_name));
        comment = QString(" //%1, %2, %3").arg(funcname).arg(pinname).arg(QString(reg->reg_name));
    }
    REG_CONFIG_ADD(reg_addr, reg_val);
    return 0;
}

int MainWindow::tuner_mxl214_config_add(bool isComment)
{
    QString pinname, funcname;
    bool isClkShare = ui->clk_share_comboBox->isEnabled();

    /*tsi0 pin*/
    if(isClkShare) {

        pinname = ui->tsi0_clk_comboBox->currentText();
        funcname = "TSI0_CLK";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi0_dat_comboBox->currentText();
        funcname = "TSI0_D0";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi0_sync_comboBox->currentText();
        funcname = "TSI0_SYNC";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }
    else {
        pinname = ui->tsi0_clk_comboBox->currentText();
        funcname = "TSI0_VALID";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi0_dat_comboBox->currentText();
        funcname = "TSI0_D0";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }

    if(isClkShare) {

        pinname = ui->tsi1_clk_comboBox->currentText();
        funcname = "TSI1_CLK";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi1_dat_comboBox->currentText();
        funcname = "TSI1_D0";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi1_sync_comboBox->currentText();
        funcname = "TSI1_SYNC";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }
    else {
        pinname = ui->tsi1_clk_comboBox->currentText();
        funcname = "TSI1_VALID";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi1_dat_comboBox->currentText();
        funcname = "TSI1_D0";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }

    if(isClkShare) {

        pinname = ui->tsi2_clk_comboBox->currentText();
        funcname = "TSI2_CLK";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi2_dat_comboBox->currentText();
        funcname = "TSI2_D0";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi2_sync_comboBox->currentText();
        funcname = "TSI2_SYNC";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }
    else {
        pinname = ui->tsi2_clk_comboBox->currentText();
        funcname = "TSI2_VALID";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi2_dat_comboBox->currentText();
        funcname = "TSI2_D0";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }

    if(isClkShare) {

        pinname = ui->tsi3_clk_comboBox->currentText();
        funcname = "TSI3_CLK";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi3_dat_comboBox->currentText();
        funcname = "TSI3_D0";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi3_sync_comboBox->currentText();
        funcname = "TSI3_SYNC";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }
    else {
        pinname = ui->tsi3_clk_comboBox->currentText();
        funcname = "TSI3_VALID";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

        pinname = ui->tsi3_dat_comboBox->currentText();
        funcname = "TSI3_D0";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }

    if(isClkShare) {
        pinname = ui->clk_share_comboBox->currentText();
        funcname = "TSI2_CLK";
        find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);
    }

    return 0;
}

int MainWindow::tuner_mxl214_code_add(QString fmt)
{
    QString pinname, funcname;
    QString line;
    pinmux_reg_t *reg;
    U32 reg_addr, reg_val;
    bool isClkShare = ui->clk_share_comboBox->isEnabled();

    /*tsi0 pin*/
    if(isClkShare) {

        pinname = ui->tsi0_clk_comboBox->currentText();
        funcname = "TSI0_CLK";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi0_dat_comboBox->currentText();
        funcname = "TSI0_D0";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi0_sync_comboBox->currentText();
        funcname = "TSI0_SYNC";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }
    else {
        pinname = ui->tsi0_clk_comboBox->currentText();
        funcname = "TSI0_VALID";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi0_dat_comboBox->currentText();
        funcname = "TSI0_D0";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }

    if(isClkShare) {

        pinname = ui->tsi1_clk_comboBox->currentText();
        funcname = "TSI1_CLK";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi1_dat_comboBox->currentText();
        funcname = "TSI1_D0";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi1_sync_comboBox->currentText();
        funcname = "TSI1_SYNC";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }
    else {
        pinname = ui->tsi1_clk_comboBox->currentText();
        funcname = "TSI1_VALID";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi1_dat_comboBox->currentText();
        funcname = "TSI1_D0";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }

    if(isClkShare) {

        pinname = ui->tsi2_clk_comboBox->currentText();
        funcname = "TSI2_CLK";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi2_dat_comboBox->currentText();
        funcname = "TSI2_D0";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi2_sync_comboBox->currentText();
        funcname = "TSI2_SYNC";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }
    else {
        pinname = ui->tsi2_clk_comboBox->currentText();
        funcname = "TSI2_VALID";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi2_dat_comboBox->currentText();
        funcname = "TSI2_D0";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }

    if(isClkShare) {

        pinname = ui->tsi3_clk_comboBox->currentText();
        funcname = "TSI3_CLK";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi3_dat_comboBox->currentText();
        funcname = "TSI3_D0";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi3_sync_comboBox->currentText();
        funcname = "TSI3_SYNC";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }
    else {
        pinname = ui->tsi3_clk_comboBox->currentText();
        funcname = "TSI3_VALID";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);

        pinname = ui->tsi3_dat_comboBox->currentText();
        funcname = "TSI3_D0";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }

    if(isClkShare) {
        pinname = ui->clk_share_comboBox->currentText();
        funcname = "TSI2_CLK";
        reg = m_chip_reg.get_pinmux_reg_config(\
                    pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
        line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
        m_data.append(line);
    }

    return 0;
}

int MainWindow::tuner_r858_config_add(bool isComment)
{
    return 0;
}

int MainWindow::tuner_r858_code_add(QString fmt)
{
    return 0;
}

int MainWindow::tuner_4line_config_add(bool isComment)
{
    QString pinname, funcname;
    /*tsi0 pin*/
    pinname = ui->tsi0_clk_comboBox->currentText();
    funcname = "TSI0_CLK";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = ui->tsi0_dat_comboBox->currentText();
    funcname = "TSI0_D0";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = ui->tsi0_sync_comboBox->currentText();
    funcname = "TSI0_SYNC";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = ui->tsi0_sync_comboBox->currentText();
    funcname = "TSI0_VALID";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    return 0;
}

int MainWindow::tuner_4line_code_add(QString fmt)
{
    return 0;
}

int MainWindow::gen_regtable_btn_clicked(bool clicked)
{
    QFile file;
    QString pinname, funcname;
    QString tuner_type;
    bool isComment = 1;

    m_data.clear();

    /*i2c pin*/
    m_data.append("\n// i2c pin\n");
    pinname = ui->i2c_scl_pin_comboBox->currentText();
    funcname = ui->i2c_chnl_comboBox->currentText();
    funcname.append("_SCL");
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = ui->i2c_sda_pin_comboBox->currentText();
    funcname = ui->i2c_chnl_comboBox->currentText();
    funcname.append("_SDA");
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    /* tsi pin */
    m_data.append("\n// tuner tsi pin\n");
    tuner_type = ui->tuner_select_comboBox->currentText();
    if(tuner_type == tr("MXL214C") || tuner_type == tr("MXL254C"))
        tuner_mxl214_config_add(isComment);
    else if(tuner_type == tr("R858"))
        tuner_r858_config_add(isComment);
    else
        tuner_4line_config_add(isComment);


    /* reset gpio pin */
    m_data.append("\n// tuner rst pin\n");
    pinname = "NULL";
    funcname = ui->gpio_reset_lineEdit->text();
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);


    /* CA pin */
    m_data.append("\n// CA pin\n");
    pinname = "JTAG_TRSTN";
    funcname = "SIM0_DATA";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = "JTAG_TDI";
    funcname = "SIM0_DET";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = "JTAG_TMS";
    funcname = "SIM0_RST";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = "JTAG_TCK";
    funcname = "SIM0_CLK";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = "JTAG_TDO";
    funcname = "SIM0_PWREN";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

#if 0
    REG_CONFIG_ADD(0xF8A21060, 0x2133);
    REG_CONFIG_ADD(0xF8A21060, 0x2133);
    REG_CONFIG_ADD(0xF8A21064, 0x133);
    REG_CONFIG_ADD(0xF8A21068, 0x133);
    REG_CONFIG_ADD(0xF8A2106C, 0x133);
    REG_CONFIG_ADD(0xF8A21070, 0x133);
#endif

    /* output reg config to file */
    file.setFileName(tr("./pinmux.txt"));
    file.remove();
    file.open(QIODevice::ReadWrite);
    file.write(m_data);
    file.close();

    QMessageBox::information(this, "提示", "生成reg表成功！\n输出文件名：pinmux.txt");

    return 0;
}

int MainWindow::gen_config_btn_clicked(bool clicked)
{
    QFile file;
    QString pinname, funcname;
    QString tuner_type;
    bool isComment = 0;

    m_data.clear();

    /*i2c pin*/
    pinname = ui->i2c_scl_pin_comboBox->currentText();
    funcname = ui->i2c_chnl_comboBox->currentText();
    funcname.append("_SCL");
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = ui->i2c_sda_pin_comboBox->currentText();
    funcname = ui->i2c_chnl_comboBox->currentText();
    funcname.append("_SDA");
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    /* tsi pin */
    tuner_type = ui->tuner_select_comboBox->currentText();
    if(tuner_type == tr("MXL214C") || tuner_type == tr("MXL254C"))
        tuner_mxl214_config_add(isComment);
    else if(tuner_type == tr("R858"))
        tuner_r858_config_add(isComment);
    else
        tuner_4line_config_add(isComment);


    /* reset gpio pin */
    pinname = "NULL";
    funcname = ui->gpio_reset_lineEdit->text();
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    /* CA pin */
    pinname = "JTAG_TRSTN";
    funcname = "SIM0_DATA";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = "JTAG_TDI";
    funcname = "SIM0_DET";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = "JTAG_TMS";
    funcname = "SIM0_RST";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = "JTAG_TCK";
    funcname = "SIM0_CLK";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    pinname = "JTAG_TDO";
    funcname = "SIM0_PWREN";
    find_reg_config_and_add(pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), isComment);

    /* output reg config to file */
    file.setFileName(tr("./pinmux.config"));
    file.remove();
    file.open(QIODevice::ReadWrite);
    file.write(m_data);
    file.close();

    QMessageBox::information(this, "提示", "生成config成功！\n输出文件名：pinmux.config");
    return 0;
}

int MainWindow::gen_code_btn_clicked(bool clicked)
{
    QFile file;
    QString pinname, funcname, tuner_type;
    QString fmt;
    QString line;
    pinmux_reg_t *reg;
    U32 reg_addr, reg_val;

    m_data.clear();

    fmt = "    ret |= HI_SYS_WriteRegister(0x%1, 0x%2); //%3\n";

    m_data.append("\n\nint hisi_pinmux()\n{\n");
    m_data.append("    int ret = 0;\n");

    /*i2c pin*/
    pinname = ui->i2c_scl_pin_comboBox->currentText();
    funcname = ui->i2c_chnl_comboBox->currentText();
    funcname.append("_SCL");
    reg = m_chip_reg.get_pinmux_reg_config(\
                pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
    line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
    m_data.append(line);

    pinname = ui->i2c_sda_pin_comboBox->currentText();
    funcname = ui->i2c_chnl_comboBox->currentText();
    funcname.append("_SDA");
    reg = m_chip_reg.get_pinmux_reg_config(\
                pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
    line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
    m_data.append(line);

    m_data.append("\n"); //

    /* tsi pin */
    tuner_type = ui->tuner_select_comboBox->currentText();
    if(tuner_type == tr("MXL214C") || tuner_type == tr("MXL254C"))
        tuner_mxl214_code_add(fmt);
    else if(tuner_type == tr("R858"))
        tuner_r858_code_add(fmt);
    else
        tuner_4line_code_add(fmt);

    m_data.append("\n"); //

    /* reset gpio pin */
    pinname = "NULL";
    funcname = ui->gpio_reset_lineEdit->text();
    reg = m_chip_reg.get_pinmux_reg_config(\
                pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
    line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
    m_data.append(line);

    m_data.append("\n"); //

    /* CA pin */
    pinname = "JTAG_TRSTN";
    funcname = "SIM0_DATA";
    reg = m_chip_reg.get_pinmux_reg_config(\
                pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
    line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
    m_data.append(line);

    pinname = "JTAG_TDI";
    funcname = "SIM0_DET";
    reg = m_chip_reg.get_pinmux_reg_config(\
                pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
    line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
    m_data.append(line);

    pinname = "JTAG_TMS";
    funcname = "SIM0_RST";
    reg = m_chip_reg.get_pinmux_reg_config(\
                pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
    line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
    m_data.append(line);

    pinname = "JTAG_TCK";
    funcname = "SIM0_CLK";
    reg = m_chip_reg.get_pinmux_reg_config(\
                pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
    line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
    m_data.append(line);

    pinname = "JTAG_TDO";
    funcname = "SIM0_PWREN";
    reg = m_chip_reg.get_pinmux_reg_config(\
                pinname.toLocal8Bit().data(), funcname.toLocal8Bit().data(), &reg_addr, &reg_val);
    line = QString(fmt).arg(QString::number(reg_addr,16)).arg(QString::number(reg_val,16)).arg(funcname);
    m_data.append(line);

    m_data.append("\n"); //
    m_data.append("    return ret;\n");
    m_data.append("}\n\n");

    /* output reg config to file */
    file.setFileName(tr("./pinmux.c"));
    file.remove();
    file.open(QIODevice::ReadWrite);
    file.write(m_data);
    file.close();

    QMessageBox::information(this, "提示", "生成code成功！\n输出文件名：pinmux.c");

    return 0;
}

MainWindow::~MainWindow()
{

    delete ui;
}
