/*!
 * \file
 * \brief Ten plik zawiera definicję klasy MainWindow
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
#include <QKeyEvent>
#include <QtCharts>

#include "viewer.h"

/*!
 * \brief Zmienne tymczasowo przechowujące informacje o kącie obrotu
 * poszczególnych przegubów obrotowych
 */
extern float q0, q1, q2, q3;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Klasa MainWindow. Zawiera metody głównego okna.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /*!
     * \brief Metoda szukająca urządzeń podłączonych do komputera
     */
    void on_pushButton_search_clicked();
    /*!
     * \brief Metoda pozwalająca podłączyć urządzenie do komputera po
	 * przyciśnięciu przycisku
     */
    void on_pushButton_connect_clicked();
    /*!
     * \brief Metoda rozłączajaca aktualnie połączone urządzenie
     */
    void on_pushButton_disconnect_clicked();
    /*!
     * \brief Metoda pozwalająca na odczyt danych z połączonego urządzenia
     */
    void read_from_port();
    /*!
     * \brief Metoda wysyłająca wiadomość do urządzenia poprzez interfejs UART
     * \param message - wiadomość, która ma być wysłana do urządzenia poprzez 
	 * UART
     */
    void send_msg_to_device(QString message);

private:
    /*!
     * \brief Uchwyt na główne okno
     */
    Ui::MainWindow *ui;
    /*!
     * \brief  Uchwyt na urządzenie
     */
    QSerialPort *device;
    /*!
     * \brief Metoda dodająca logi w formacie R.M.D G:M:S <info>
	 * \param message - wiadomość, która ma być zapisana do logu
     */
    void add_log(QString message);
    /*!
     * \brief Zmienna przechowująca kąt obrotu serwomechanizmu
     */
    int servo_angle[4];
    /*!
     * \brief Wartość, jaka ma być dodana/odjęta od kątu obrotu serwomechanizmu
     *  podczas przyciśnięcia jednego z przycisków (h,y) - pierwszy serwomechanizm,
     *  (j,u) - drugi serwomechanizm, (k,i) trzeci serwomechanizm, (l,o) -
	 *  czwarty serwomechanizm.
     */
    const int keypress_diff = 1;
    /*!
     * \brief Uchwyt na wykres
     */
    QChart *chart;
    /*!
     * \brief Uchwyt na Widget wykresu
     */
    QChartView *chart_view;

    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;
    QBarSet *set3;
    /*!
     * \brief keyPressEvent - Metoda przechwytująca naciśnięcie przycisku
	 * na klawiaturze
     */
    void keyPressEvent(QKeyEvent *);
};
#endif // MAINWINDOW_H
