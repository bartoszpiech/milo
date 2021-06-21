#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);



    set0 = new QBarSet("q0");
    set1 = new QBarSet("q1");
    set2 = new QBarSet("q2");
    set3 = new QBarSet("q3");

    *set0 << q0;
    *set1 << q1;
    *set2 << q2;
    *set3 << q3;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    //ui->charts_page->setLayout(new QGridLayout);
    chart = new QChart();
    chart_view = new QChartView(chart, ui->charts_page);
    chart->addSeries(series);
    chart->setTitle("Encoder measurement");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories << "";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    //QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Joint number");
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Angle [°]");
    axisY->setRange(0,180);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    ui->charts_page->layout()->addWidget(chart_view);
    chart_view->setChart(chart);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_search_clicked()
{
    this->add_log("Searching...");
    ui->comboBox_device_list->clear();
    QList<QSerialPortInfo> devices = QSerialPortInfo::availablePorts();
    for (auto &i : devices) {
        this->add_log("Found device on port: " + i.portName() + " - " + i.description());
        ui->comboBox_device_list->addItem(i.portName() + " " + i.description());
    }
    if (ui->comboBox_device_list->count() == 0) {
        this->add_log("No devices found.");
    }
}

void MainWindow::add_log(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    ui->textEdit_logs->append(currentDateTime + "\t" + message);
}

void MainWindow::on_pushButton_connect_clicked()
{
    if (ui->comboBox_device_list->count() == 0) {
        this->add_log("No devices found.");
        return;
    }
    QString port_name = ui->comboBox_device_list->currentText().split(" ").first();
    this->device->setPortName(port_name);
    if (!this->device->isOpen()) { // tu forbot bug
        if(this->device->open(QSerialPort::ReadWrite)) { // tu tez
            this->device->setBaudRate(QSerialPort::Baud38400);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);
            this->add_log("Port " + port_name + " opened.");
            connect(this->device, SIGNAL(readyRead()), this, SLOT(read_from_port()));
            send_msg_to_device("d;");
        } else {
            this->add_log("Port " + port_name + " could not be opened!");
        }
    } else {
        this->add_log("Port " + port_name + " was already opened!");
    }
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    if (this->device->isOpen()) {
        this->add_log("Port " + this->device->portName() + " closed");
        this->device->close();
    } else {
        this->add_log("No Port to close");
    }
}
void MainWindow::read_from_port() {
    while (this->device->canReadLine()) {
        QString line = this->device->readLine();
        if(line[0] == 'a') {
            int index = line[1].unicode() - 48;
            qDebug() << index;
            servo_angle[index] = line.split(" ")[1].split(";")[0].toInt();
            qDebug() << line.split(" ")[1].split(";")[0];
        } else if (line[0] == 'd') {
            qDebug() << line.split(";");
            servo_angle[0] = line.split(";")[1].toInt();
            servo_angle[1] = line.split(";")[2].toInt();
            servo_angle[2] = line.split(";")[3].toInt();
            servo_angle[3] = line.split(";")[4].toInt();
        }
        this->add_log(line);
    }
}

void MainWindow::send_msg_to_device(QString message) {
    if(this->device->isOpen() && this->device->isWritable()) {
        this->add_log("Sending message to device " + message);
        this->device->write(message.toStdString().c_str());
      } else {
        this->add_log("Cannot send message to device, Port is closed!");
      }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_B) {
        send_msg_to_device("b;");
    } else if (event->key() == Qt::Key_0) {
        send_msg_to_device("c0;");
    } else if (event->key() == Qt::Key_1) {
        send_msg_to_device("c1;");
    } else if (event->key() == Qt::Key_2) {
        send_msg_to_device("c2;");
    } else if (event->key() == Qt::Key_3) {
        send_msg_to_device("c3;");
    } else if (event->key() == Qt::Key_A) {
        send_msg_to_device("a0;");
    } else if (event->key() == Qt::Key_Z) {
		q0++;
        add_log("q0 = " + QString::number(q0));
        set0->replace(0, q0);
    } else if (event->key() == Qt::Key_X) {
		q1++;
        add_log("q1 = " + QString::number(q1));
    } else if (event->key() == Qt::Key_N) {
		q2++;
        add_log("q2 = " + QString::number(q2));
    } else if (event->key() == Qt::Key_V) {
		q3++;
        add_log("q3 = " + QString::number(q3));
    } else if (event->key() == Qt::Key_H) {
        send_msg_to_device("a0;");
        this->servo_angle[0] = this->servo_angle[0] - keypress_diff;
        send_msg_to_device("s0 " + QString::number(servo_angle[0]) + ";");
        add_log("servo_angle[0] = " + QString::number(servo_angle[0]));
    } else if (event->key() == Qt::Key_Y) {
        send_msg_to_device("a0;");
        this->servo_angle[0] = this->servo_angle[0] + keypress_diff;
        send_msg_to_device("s0 " + QString::number(servo_angle[0]) + ";");
        add_log("servo_angle[0] = " + QString::number(servo_angle[0]));
    } else if (event->key() == Qt::Key_J) {
        send_msg_to_device("a1;");
        this->servo_angle[1] = this->servo_angle[1] - keypress_diff;
        send_msg_to_device("s1 " + QString::number(servo_angle[1]) + ";");
        add_log("servo_angle[1] = " + QString::number(servo_angle[1]));
    } else if (event->key() == Qt::Key_U) {
        send_msg_to_device("a1;");
        this->servo_angle[1] = this->servo_angle[1] + keypress_diff;
        send_msg_to_device("s1 " + QString::number(servo_angle[1]) + ";");
        add_log("servo_angle[1] = " + QString::number(servo_angle[1]));
    } else if (event->key() == Qt::Key_K) {
        send_msg_to_device("a2;");
        this->servo_angle[2] = this->servo_angle[2] - keypress_diff;
        send_msg_to_device("s2 " + QString::number(servo_angle[2]) + ";");
        add_log("servo_angle[2] = " + QString::number(servo_angle[2]));
    } else if (event->key() == Qt::Key_I) {
        send_msg_to_device("a2;");
        this->servo_angle[2] = this->servo_angle[2] + keypress_diff;
        send_msg_to_device("s2 " + QString::number(servo_angle[2]) + ";");
        add_log("servo_angle[2] = " + QString::number(servo_angle[2]));
    }
}
