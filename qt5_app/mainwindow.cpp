#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->device = new QSerialPort(this);

	this->servo_angle[0] = 0;
	this->servo_angle[1] = 45;
	this->servo_angle[2] = 45;
	this->servo_angle[3] = 0;

	q0 = &servo_angle[0];
	q1 = &servo_angle[1];
	q2 = &servo_angle[2];
	q3 = &servo_angle[3];

	timer = new QTimer();
	//timer->setInterval(200);
	timer->setInterval(500);
	connect(timer, &QTimer::timeout, this, [=](){
	send_msg_to_device("d;");
	});


    set0 = new QBarSet("q0");
    set1 = new QBarSet("q1");
    set2 = new QBarSet("q2");
    set3 = new QBarSet("q3");

    *set0 << servo_angle[0];
    *set1 << servo_angle[1];
    *set2 << servo_angle[2];
    *set3 << servo_angle[3];

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    //ui->charts_page->setLayout(new QGridLayout);
    chart = new QChart();
    chart_view = new QChartView(chart, ui->visualization_page);
    chart->addSeries(series);
    chart->setTitle("Encoder measurement");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    //chart_view->chart()->setTheme(QChart::ChartTheme::ChartThemeBrownSand);

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

    ui->visualization_page->layout()->addWidget(chart_view);
    chart_view->setChart(chart);


    set_x = new QBarSet("X");
    set_y = new QBarSet("Y");
    set_z = new QBarSet("Z");


    this->effector[0] = 52;
    this->effector[1] = 28;
    this->effector[2] = 0;

    *set_x << effector[0];
    *set_y << effector[1];
    *set_z << effector[2];
    QBarSeries *series_xyz = new QBarSeries();
    series_xyz->append(set_x);
    series_xyz->append(set_y);
    series_xyz->append(set_z);


    chart_xyz = new QChart();
    chart_xyz_view = new QChartView(chart, ui->visualization_page);
    chart_xyz->addSeries(series_xyz);

    chart_xyz->setTitle("Effector coordinates");
    chart_xyz->setAnimationOptions(QChart::SeriesAnimations);
    //chart_xyz_view->chart()->setTheme(QChart::ChartTheme::ChartThemeBrownSand);

    QStringList categories_xyz;
    categories_xyz << "";
    QBarCategoryAxis *axisX_xyz = new QBarCategoryAxis();
    //QValueAxis *axisX = new QValueAxis();
    axisX_xyz->setTitleText("Coordinate");
    axisX_xyz->append(categories_xyz);
    chart_xyz->addAxis(axisX_xyz, Qt::AlignBottom);
    series_xyz->attachAxis(axisX_xyz);

    QValueAxis *axisY_xyz = new QValueAxis();
    axisY_xyz->setTitleText("distance [cm]");
    axisY_xyz->setRange(-70,70);
    chart_xyz->addAxis(axisY_xyz, Qt::AlignLeft);
    series_xyz->attachAxis(axisY_xyz);


    ui->visualization_page->layout()->addWidget(chart_xyz_view);
    chart_view->setChart(chart_xyz);
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
            this->device->setBaudRate(QSerialPort::Baud115200);
            this->device->setDataBits(QSerialPort::Data8);
            this->device->setParity(QSerialPort::NoParity);
            this->device->setStopBits(QSerialPort::OneStop);
            this->device->setFlowControl(QSerialPort::NoFlowControl);
            this->add_log("Port " + port_name + " opened.");
            connect(this->device, SIGNAL(readyRead()), this, SLOT(read_from_port()));
			timer->start();
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
		timer->stop();
    } else {
        this->add_log("No Port to close");
    }
}
void MainWindow::read_from_port() {
    while (this->device->canReadLine()) {
        QString line = this->device->readLine();
        if(line[0] == 'a') {
            int index = line[1].unicode() - 48;
            //qDebug() << index;
            servo_angle[index] = line.split(" ")[1].split(";")[0].toInt();
            //qDebug() << line.split(" ")[1].split(";")[0];
        } else if (line[0] == 'd') {
            qDebug() << line.split(";");
            servo_angle[0] = line.split(";")[1].toInt();
            servo_angle[1] = line.split(";")[2].toInt();
            servo_angle[2] = line.split(";")[3].toInt();
            servo_angle[3] = line.split(";")[4].toInt();
            effector[0] = line.split(";")[5].toInt();
            effector[1] = line.split(";")[6].toInt();
            effector[2] = line.split(";")[7].toInt();
			set0->replace(0, servo_angle[0]);
			set1->replace(0, servo_angle[1]);
			set2->replace(0, servo_angle[2]);
			set3->replace(0, servo_angle[3]);
            set_x->replace(0, effector[0]);
            set_y->replace(0, effector[1]);
            set_z->replace(0, effector[2]);
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
		servo_angle[0]++;
        add_log("a0 = " + QString::number(servo_angle[0]));
        set0->replace(0, servo_angle[0]);
    } else if (event->key() == Qt::Key_X) {
		q1++;
        add_log("q1 = " + QString::number(*q1));
    } else if (event->key() == Qt::Key_N) {
		q2++;
        add_log("q2 = " + QString::number(*q2));
    } else if (event->key() == Qt::Key_V) {
		q3++;
        add_log("q3 = " + QString::number(*q3));
    } else if (event->key() == Qt::Key_H) {
        //send_msg_to_device("a0;");
        this->servo_angle[0] = this->servo_angle[0] - keypress_diff;
        send_msg_to_device("s0 " + QString::number(servo_angle[0]) + ";");
        add_log("servo_angle[0] = " + QString::number(servo_angle[0]));
        set0->replace(0, servo_angle[0]);
    } else if (event->key() == Qt::Key_Y) {
        //send_msg_to_device("a0;");
        this->servo_angle[0] = this->servo_angle[0] + keypress_diff;
        send_msg_to_device("s0 " + QString::number(servo_angle[0]) + ";");
        add_log("servo_angle[0] = " + QString::number(servo_angle[0]));
        set0->replace(0, servo_angle[0]);
    } else if (event->key() == Qt::Key_J) {
        //send_msg_to_device("a1;");
        this->servo_angle[1] = this->servo_angle[1] - keypress_diff;
        send_msg_to_device("s1 " + QString::number(servo_angle[1]) + ";");
        add_log("servo_angle[1] = " + QString::number(servo_angle[1]));
        set1->replace(0, servo_angle[1]);
    } else if (event->key() == Qt::Key_U) {
        //send_msg_to_device("a1;");
        this->servo_angle[1] = this->servo_angle[1] + keypress_diff;
        send_msg_to_device("s1 " + QString::number(servo_angle[1]) + ";");
        add_log("servo_angle[1] = " + QString::number(servo_angle[1]));
        set1->replace(0, servo_angle[1]);
    } else if (event->key() == Qt::Key_K) {
        //send_msg_to_device("a2;");
        this->servo_angle[2] = this->servo_angle[2] - keypress_diff;
        send_msg_to_device("s2 " + QString::number(servo_angle[2]) + ";");
        add_log("servo_angle[2] = " + QString::number(servo_angle[2]));
        set2->replace(0, servo_angle[2]);
    } else if (event->key() == Qt::Key_I) {
        //send_msg_to_device("a2;");
        this->servo_angle[2] = this->servo_angle[2] + keypress_diff;
        send_msg_to_device("s2 " + QString::number(servo_angle[2]) + ";");
        add_log("servo_angle[2] = " + QString::number(servo_angle[2]));
        set2->replace(0, servo_angle[2]);
    }
}

void MainWindow::on_pushButton_send_ik_clicked()
{
    int x, y, z;
    QString x_str = ui->lineEdit_x->text();
    x = x_str.toInt();
    QString y_str = ui->lineEdit_y->text();
    y = y_str.toInt();
    QString z_str = ui->lineEdit_z->text();
    z = z_str.toInt();
    send_msg_to_device("q;" + QString::number(x) + ";" + QString::number(y) + ";" + QString::number(z) + ";");
}

