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

/*!
 * \brief Klasa MainPageViewer, zawiera metody do rysowania w okienku VGLViewer przy
 * użyciu OpenGL'a, wyświetla animacje w okienku głównym
 */
class MainPageViewer : public Viewer {
public:
	/*!
	 * \brief Konstruktor klasy MainPageViewer.
	 * \param parent - tzw. "rodzic" okienka
	 */
    MainPageViewer(QWidget* parent = nullptr);


protected:
	/*!
	 * \brief Metoda wirtualna odpowiadająca za rysowanie obiektu
	 */
    virtual void draw();
	/*!
	 * \brief Metoda wirtualna odpowiedzialna za animację obiektu na ekranie
	 * głównym
	 */
    virtual void animate();

private:
	/*!
	 * \brief kąt obrotu q0
	 */
    float q0 = 0;
	/*!
	 * \brief kąt obrotu q1
	 */
	float q1 = 0;
	/*!
	 * \brief kąt obrotu q2
	 */
	float q2 = 0;
	/*!
	 * \brief kąt obrotu q3
	 */
	float q3 = 0;
};

#endif // VIEWER_H
