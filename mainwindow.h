#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QDebug>
#include <QFile>
#include <QArrayData>
#include <QScrollBar>
#include <QMessageBox>

#include "common.h"
#include "chip_reg.h"

namespace Ui {
class MainWindow;
}

#define YLOG(fmt...) logout((char *)__FUNCTION__,__LINE__, fmt)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QLabel *io_pin[10];

    QLabel *TunerSelect;
    QGroupBox *gBox;

    chip_reg m_chip_reg;
    QByteArray m_data;

    CHIP_TYPE_E m_chip_type;

    int item_init();
    int slot_init();

    int set_tuner_max_port(int tuner_port_count);
    int find_reg_config_and_add(char *pinname, char*funcname, bool isComment);
    int tuner_mxl214_config_add(bool isComment);
    int tuner_r858_config_add(bool isComment);
    int tuner_4line_config_add(bool isComment);
    int tuner_mxl214_code_add(QString fmt);
    int tuner_r858_code_add(QString fmt);
    int tuner_4line_code_add(QString fmt);
    int logout(char *func, int line, char *fmt, ...);
public slots:
    int chip_select(QAction *action);
    int tuner_select(int index);
    int demod_select(int index);
    int i2c_chnl_select(int index);
    int tsi_intf_line_select(bool clicked);

    int gen_regtable_btn_clicked(bool clicked);
    int gen_config_btn_clicked(bool clicked);
    int gen_code_btn_clicked(bool clicked);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
