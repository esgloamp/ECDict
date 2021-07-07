#include "combobox.h"

#include <QDebug>

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent) {}

ComboBox::~ComboBox() {}

void ComboBox::keyReleaseEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        qDebug() << "press";
        emit enter_pressed();
    }
}
