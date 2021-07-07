#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>
#include <QKeyEvent>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    ComboBox(QWidget *parent = nullptr);
    ~ComboBox();

protected:
    void keyReleaseEvent(QKeyEvent *e);

signals:
    void enter_pressed();

public slots:
};

#endif // COMBOBOX_H
