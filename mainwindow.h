#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QCompleter>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void open_dict();

    QSqlDatabase dict;
    QSqlQuery *que;


    void set_word(const QString &s);
    void set_phonetic(const QString &s);
    void set_definition(const QString &s);
    void set_translation(const QString &s);
    void set_collins_star(const QString &s);
    void set_oxford_3k(const QString &s);
    void set_tag(const QString &s);
    void set_bnc(const QString &s);
    void set_frq(const QString &s);
    void set_exchange(const QString &s);
    void set_exchange(const QString &w, const QString &s);

    enum DICT_POS {
        WORD = 1,
        PHONETIC = 3,
        DEFINITION = 4,
        TRANSLATION = 5,
        COLLINS = 7,
        OXFORD = 8,
        TAG = 9,
        BNC = 10,
        FRQ = 11,
        EXCHANGE = 12
    };


public Q_SLOTS:
//    void updates_tips(const QString &s); // 这个方案过于消耗资源，下次尝试字典树
    void test();
    bool query(const QString &);
    void enter_event();

private:
    Ui::MainWindow *ui;
    QCompleter *completer;
    QStringList list;
    QStringListModel *model;
};


#endif // MAINWINDOW_H
