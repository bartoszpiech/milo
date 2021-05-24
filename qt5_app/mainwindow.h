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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Klasa MainWindow. Zawiera metody glownego okna.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//private slots:
public slots:
    /*!
     * \brief Metoda szukajaca urzadzen podlaczonych do komputera
     */
    void on_pushButton_search_clicked();
    /*!
     * \brief Metoda pozwalajaca podlaczyc urzadzenie do komputera po przycisnieciu przycisku
     */
    void on_pushButton_connect_clicked();
    /*!
     * \brief Metoda rozlaczajaca aktualnie podlaczone urzadzenie
     */
    void on_pushButton_disconnect_clicked();
    /*!
     * \brief Metoda pozwalajaca na odczyt danych z podlaczonego urzadzenia
     */
    void read_from_port();
    /*!
     * \brief Metoda wysylajaca wiadomosc do urzadzenia poprzez interfejs UART
     * \param wiadomosc, ktora ma byc wyslana do urzadzenia poprzez UART
     */
    void send_msg_to_device(QString message);
//private:
public:
    /*!
     * \brief Uchwyt na glowne okno
     */
    Ui::MainWindow *ui;
    /*!
     * \brief  Uchwyt na urzadzenie
     */
    QSerialPort *device;
    /*!
     * \brief Metoda dodajaca logi w formacie R.M.D G:M:S <info>
     */
    void add_log(QString message);
    /*!
     * \brief Kat obrotu serwomechanizmu
     */
    int servo_angle[3];
    /*!
     * \brief Wartosc jaka ma byc dodana/odjeta od katu obrotu serwomechanizmu
     *  podczas przycisniecia jednego z przyciskow (h,y) - pierwszy serwomechanizm,
     *  (j,u) - drugi serwomechanizm, (k,i) trzeci serwomechanizm, (l,o) - czwarty serwomechanizm.
     */
    const int keypress_diff = 1;
    /*!
     * \brief keyPressEvent - Metoda przechwytujaca nacisniecie przycisku na klawiaturze
     */
    void keyPressEvent(QKeyEvent *);
};
#endif // MAINWINDOW_H
