#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QStyleFactory>
#include <QKeyEvent>
#include <QStyle>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->comboBox, SIGNAL(enter_pressed()), this, SLOT(enter_event()));

//    connect(ui->comboBox, SIGNAL(editTextChanged(const QString &)),
//            this, SLOT(updates_tips(const QString &)));
    open_dict();
}

MainWindow::~MainWindow() {
    dict.close();
    delete ui;
    delete que;
}

void MainWindow::open_dict() {
    dict = QSqlDatabase::addDatabase("QSQLITE");
    // 必须要绝对路径，不然会找不到表
    QString path = QCoreApplication::applicationDirPath() + "/stardict.db";
    dict.setDatabaseName(path);
    if (!dict.open()) {
        QMessageBox::critical(this, "Error",
                              "Database:" + dict.lastError().databaseText() + ".\nDriver:" + dict.lastError().driverText(),
                              QMessageBox::Ok);

        exit(-1);
    }
    que = new QSqlQuery(dict);
}

inline void MainWindow::set_word(const QString &s) {
    ui->word_content->setText(s);
}

inline void MainWindow::set_phonetic(const QString &s) {
    ui->phonetic_content->setText("[" + s + "]");
}

inline void MainWindow::set_definition(const QString &s) {
    ui->definition->setText(s);
    ui->definition->adjustSize();
}

inline void MainWindow::set_translation(const QString &s) {
    ui->translation->setText(s);
}

inline void MainWindow::set_collins_star(const QString &s) {
    ui->collins_star_container->setMinimumWidth(s.toInt() * 17);
    ui->collins_star_container->setMaximumWidth(s.toInt() * 17);
}

inline void MainWindow::set_oxford_3k(const QString &s) {
    s != "0" ? ui->oxford_3k_content->setText("是"):
              ui->oxford_3k_content->setText("否");
}

inline void MainWindow::set_tag(const QString &s) {
    if (s.contains("ielts")) {
        ui->tag_ielts->setVisible(true);
    } else {
        ui->tag_ielts->setVisible(false);
    }
    if (s.contains("toefl")) {
        ui->tag_toefl->setVisible(true);
    } else {
        ui->tag_toefl->setVisible(false);
    }
    if (s.contains("cet4")) {
        ui->tag_cet4->setVisible(true);
    } else {
        ui->tag_cet4->setVisible(false);
    }
    if (s.contains("cet6")) {
        ui->tag_cet6->setVisible(true);
    } else {
        ui->tag_cet6->setVisible(false);
    }
    if (s.contains("ky")) {
        ui->tag_ky->setVisible(true);
    } else {
        ui->tag_ky->setVisible(false);
    }
    if (s.contains("gk")) {
        ui->tag_gk->setVisible(true);
    } else {
        ui->tag_gk->setVisible(false);
    }
    if (s.contains("zk")) {
        ui->tag_zk->setVisible(true);
    } else {
        ui->tag_zk->setVisible(false);
    }
//    ui->tag_content->setText(t);
}

inline void MainWindow::set_bnc(const QString &s) {
    ui->bnc_content->setText(s);
}

inline void MainWindow::set_frq(const QString &s) {
    ui->frq_content->setText(s);
}

inline void MainWindow::set_exchange(const QString &s) {
    QStringList l = s.split("/");
    QString t = "";
    for (QString i : l) {
        if (i.startsWith("p:")) {
            t += i.replace("p:", "过去式:");
        }
        if (i.startsWith("d:")) {
            t += i.replace("d:", "过去分词:");
        }
        if (i.startsWith("i:")) {
            t += i.replace("i:", "现在分词:");
        }
        if (i.startsWith("3:")) {
            t += i.replace("3:", "第三人称单数:");
        }
        if (i.startsWith("r:")) {
            t += i.replace("r:", "形容词比较级:");
        }
        if (i.startsWith("t:")) {
            t += i.replace("t:", "形容词最高级:");
        }
        if (i.startsWith("s:")) {
            t += i.replace("s:", "名词复数形式:");
        }
        if (i.startsWith("0:")) {
            t += i.replace("0:", "词根:");
        }
        if (i != "") {
            t += "\n";
        }
        // TODO 待解决
//        if (i.startsWith("1:")) {}
    }
    ui->exchange_container->setText(t);
}

bool MainWindow::query(const QString &t) {
    if (que->exec(QString("SELECT * FROM stardict WHERE word = '%1'").arg(t))) {
        return true;
    }
    return false;
}

void MainWindow::enter_event() {
    QString w = ui->comboBox->currentText();
    if (que->exec(QString("SELECT * FROM stardict WHERE word = '%1'").arg(w))) {
        que->next();
        set_word(que->value(DICT_POS::WORD).toString());
        set_phonetic(que->value(DICT_POS::PHONETIC).toString());
        set_definition(que->value(DICT_POS::DEFINITION).toString());
        set_translation(que->value(DICT_POS::TRANSLATION).toString());
        set_collins_star(que->value(DICT_POS::COLLINS).toString());
        set_oxford_3k(que->value(DICT_POS::OXFORD).toString());
        set_tag(que->value(DICT_POS::TAG).toString());
        set_bnc(que->value(DICT_POS::BNC).toString());
        set_frq(que->value(DICT_POS::FRQ).toString());
        set_exchange(que->value(DICT_POS::EXCHANGE).toString());
    }
}


//void MainWindow::updates_tips(const QString &s) {
//    qDebug() << "recv signal:" << s << endl;
//    QSqlQuery que(dict);
//    // TODO　自定义排行
//    // TODO　自定义每次出现的数量
//    // TODO　增加模型model和视图view的绑定（如果可以的话）
//    int count = 0;
//    list.clear();
//    if (que.exec(QString("select * from stardict where word like '%1%' order by bnc limit 9").arg(s))) {
//        while (que.next()) {
//            qDebug() << que.value(1) << ++count;
//            list.push_back(que.value(1).toString());
//        }
//        delete model;
//        model = new QStringListModel(list, this);
//        delete completer;
//        completer = new QCompleter(list, this);
//        completer->setModel(model);
//        ui->comboBox->setCompleter(completer);
//    }
//}


void MainWindow::test() {
    qDebug() << QString("").toInt();
}
