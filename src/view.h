#include <gtkmm.h>
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
	virtual bool on_expose_event(GdkEventExpose*);
	virtual bool on_button_press_event(GdkEventButton*);

private:
	input_t input;
	Scene *scene;
	void clearInput(void);
	void setScene(Scene *);
	void getInput(input_t *);
	void update();
};

class MyImageMenuItem: public Gtk::ImageMenuItem {
public:
	MyImageMenuItem(BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);
	virtual ~MyImageMenuItem();
	int id;
protected:
	virtual void on_activate();

private:
	Gtk::Window *subWindow;
};

class ViewManager {
public:
	static ViewManager& get_instance() {
		static ViewManager instance;
		return instance;
	}

	void init_view(MyDrawingArea *area) {
		drawingArea = area;
	}

	void init_view_with_scene(Scene *scene) {
		drawingArea->setScene(scene);
	}

	void update() {
		drawingArea->update();
	}

	void get_input(input_t *i) {
		drawingArea->getInput(i);
	}

private:
	ViewManager(){}
	ViewManager(ViewManager&);
	void operator =(ViewManager&);

	MyDrawingArea *drawingArea;
};

#endif /* VIEW_H_ */
