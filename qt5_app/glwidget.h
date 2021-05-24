/*!
 * \file
 * \brief Ten plik zawiera definicje klasy GLWidget, odpowiadajacej za wyswietlanie wizualizacji manipulatora
 *
 */
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QWidget>
#include <QSurfaceFormat>
#include <cmath>

/*!
 * \brief Klasa GLWidget, zawiera metody do rysowania w okienku OpenGL'a
 */
class GLWidget : public QOpenGLWidget, QOpenGLFunctions
{
    Q_OBJECT
public:
    /*!
     * \brief Konstruktor klasy GLWidget
     * \param Przyjmuje jako argument rodzica tego okienka
     */
    GLWidget(QWidget* parent = nullptr);
    /*!
     * \brief tablica przechowujaca dane na temat dlugosci i szerokosci pierwszego ramienia
     */
    GLfloat link_one[2] = { 0.03f, 0.7f };
    /*!
     * \brief tablica przechowujaca dane na temat dlugosci i szerokosci drugiego ramienia
     */
    GLfloat link_two[2] = { 0.5f, 0.03f };
    /*!
     * \brief tablica przechowujaca dane na temat dlugosci i szerokosci trzeciego ramienia
     */
    GLfloat link_three[2] = { 0.03f, 0.1f };
    /*!
     * \brief tablica przechowujaca dane na temat przegubu obrotowego
     */
    GLfloat joint[3] = { 0.0f, 0.0f, 0.03f};
    /*!
     * \brief zmienna okreslajaca z ilu punktow bedzie skladalo sie kolo - przegub
     */
    int joint_steps = 20;

protected:
    /*!
     * \brief metoda wirtualna inicjalizujaca obiekt OpenGL'a
     */
    virtual void initializeGL();
    /*!
     * \brief metoda wirtualna rysujaca obiekt
     */
    virtual void paintGL();
    /*!
     * \brief metoda wirtualna wywolywana podczas zmieniania rozmiaru okna
     */
    virtual void resizeGL(int w, int h);

//private:

};

#endif // GLWIDGET_H
