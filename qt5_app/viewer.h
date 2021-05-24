/*!
 * \file
 * \brief Ten plik zawiera definicję klasy Viewer, odpowiadającej za wyświetlanie wizualizacji manipulatora
 *
 */
#ifndef VIEWER_H
#define VIEWER_H

#include <QGLViewer/qglviewer.h>

/*!
 * \brief Klasa Viewer, zawiera metody do rysowania w okienku VGLViewer przy
 * użyciu OpenGL'a
 */
class Viewer : public QGLViewer
{
public:
	/*!
	 * \brief Konstruktor klasy Viewer.
	 * \param parent - tzw. "rodzic" okienka
	 */
    Viewer(QWidget* parent = nullptr);
protected:
	/*!
	 * \brief Metoda wirtualna odpowiadająca za rysowanie obiektu
	 */
	virtual void draw();
	/*!
	 * \brief Metoda wirtualna inicjalizująca obiekt QGLViewer
	 */
	virtual void init();
	/*!
	 * \brief Metoda wirtualna odpowiedzialna za animację okienka
	 */
	virtual void animate();
};

class MainPageViewer : public QGLViewer {
    MainPageViewer(QWidget* parent = nullptr);
    float q0 = 0, q1 = 0, q2 = 0, q3 = 0;

protected:
    virtual void draw();
    virtual void init();
    virtual void animate();

};

#endif // VIEWER_H
