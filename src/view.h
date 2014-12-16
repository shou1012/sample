// #define USE_OPENGL
#include <gtkmm.h>
#define GTKMM3	GTK_VERSION_GE(3,0)
#ifdef USE_OPENGL
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "common.h"

#ifndef VIEW_H_
#define VIEW_H_


class ViewManager;

class MyDrawingArea: public Gtk::DrawingArea {
	friend class ViewManager;
public:
	MyDrawingArea(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);
	virtual ~MyDrawingArea();

protected:
	virtual void on_realize();
	virtual bool on_key_press_event(GdkEventKey*);
	virtual bool on_key_release_event(GdkEventKey*);
	virtual bool on_button_press_event(GdkEventButton*);
#if GTKMM3
	virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>&);
#else
	virtual bool on_expose_event(GdkEventExpose*);
#endif
private:
//	Scene *scene;
	void update();
#ifdef USE_OPENGL
	GdkGLConfig *gl_config;
#endif
};

class MyImageMenuItem: public Gtk::ImageMenuItem {
public:
	MyImageMenuItem(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);
	virtual ~MyImageMenuItem();
	int menuId;
protected:
	virtual void on_activate();

private:
	Gtk::Window *subWindow;
	Gtk::Window *fileWindow;
};

class ViewManager {
public:
	static ViewManager& getInstance() {
		static ViewManager instance;
		return instance;
	}

	void update(void){
		drawingArea->update();
	}
	void checkInput(void);

	MyDrawingArea *drawingArea;
private:
	ViewManager(){drawingArea=0;}
	ViewManager(ViewManager&);
	void operator =(ViewManager&);
};

#endif /* VIEW_H_ */
