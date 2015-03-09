#include "QCategoryView.h"
#include <QWheelEvent>
#include <QScrollBar>
#include <QGraphicsItem>
#include <iostream>
QCategoryView::QCategoryView(QWidget* parent) : QGraphicsView(parent) { initialize(); }
QCategoryView::QCategoryView(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent) { initialize(); }

QCategoryView::~QCategoryView()
{
}

// When a user scrolls, zoom in or out of the scene
void QCategoryView::wheelEvent(QWheelEvent* e) {
	//this->setTransformationAnchor(QGraphicsView::ViewportAnchor::AnchorUnderMouse);
	// 
	const double max_zoom = 1.0;
	const double min_zoom = 0.2;
	// How quickly the scale will change with respect to mouse scroling
	const double zoom_speed = 0.15;

	int mult = 0;
	// Determine which way the user wishes to scroll
	if (e->angleDelta().y() > 0)
		mult = 1;
	else if (e->angleDelta().y() < 0)
		mult = -1;

	double s = 1 + (mult * zoom_speed);

	QTransform t = this->transform();
	t.scale(s, s);

	// Bound the zoom by min_zoom and max_zoom
	// We will only run on scaling factor of one axis, as they should always be equivalent
	if (t.m11() > max_zoom || t.m11() < min_zoom) {
		double new_zoom = qMax(qMin(max_zoom, t.m11()), min_zoom);
		t.setMatrix(new_zoom, t.m12(), t.m13(),
			t.m21(), new_zoom, t.m23(),
			t.m31(), t.m32(), t.m33());
	}

	//std::cout << t.m11() << ", " << t.m22() << std::endl;

	this->setTransform(t);

	e->accept();
}

void QCategoryView::mousePressEvent(QMouseEvent* event) {
	// If the user is pressing ctrl, remove interactivity from the scene
	// so that they can not click on a cluster/image
	if (event->modifiers().testFlag(Qt::KeyboardModifier::ControlModifier))
		this->setInteractive(false);

	QGraphicsView::mousePressEvent(event);
}

void QCategoryView::mouseReleaseEvent(QMouseEvent* event) {
	QGraphicsView::mouseReleaseEvent(event);

	// Restore interactivity to the scene
	if (!this->isInteractive())
		this->setInteractive(true);
}

void QCategoryView::initialize() {
	// Set it so that we can drag through the scene with the mouse
	this->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
	this->setInteractive(true);

	// Remove the scroll bars as they are no longer needed due to the hand drag option
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
	this->setCacheMode(QGraphicsView::CacheBackground);
	// Set the background colour of the view
	QBrush b = QBrush(QColor(15, 15, 15));
	this->setBackgroundBrush(b);
	
}
