#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QStyleFactory>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->comboBox, SIGNAL(enter_pressed()),
            this, SLOT(enter_event()));

//    connect(ui->comboBox, SIGNAL(editTextChanged(const QString &)),
//            this, SLOT(updates_tips(const QString &)));
    open_dict();
    test();
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
        QMessageBox::warning(this, "warning", dict.lastError().text(), QMessageBox::Ok);
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
    ui->definition_content->setText(s);
    ui->definition_content->adjustSize();
}

inline void MainWindow::set_translation(const QString &s) {
    ui->translation_content->setText(s);
}

inline void MainWindow::set_collins_star(const QString &s) {
    s != "" ? ui->collins_star_content->setText(s):
              ui->collins_star_content->setText("无");
}

inline void MainWindow::set_oxford_3k(const QString &s) {
    s != "0" ? ui->oxford_3k_content->setText("是"):
              ui->oxford_3k_content->setText("否");
}

inline void MainWindow::set_tag(const QString &s) {
    QString t = "";
    if (s.contains("ielts")) {
        t += "雅思 ";
    }
    if (s.contains("toefl")) {
        t += "托福";
    }
    if (s.contains("cet4")) {
        t += "四级 ";
    }
    if (s.contains("cet6")) {
        t += "六级 ";
    }
    if (s.contains("ky")) {
        t += "考研 ";
    }
    if (s.contains("gk")) {
        t += "高考 ";
    }
    if (s.contains("zk")) {
        t += "中考";
    }
    ui->tag_content->setText(t);
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
        t += "\n";
        // TODO 待解决
//        if (i.startsWith("1:")) {}
    }
    ui->exchange_content->setText(t);
}

bool MainWindow::query(const QString &t) {
    if (que->exec(QString("SELECT * FROM stardict WHERE word = '%1'").arg(t))) {
        return true;
    }
    return false;
}


void MainWindow::enter_event() {
    QString w = ui->comboBox->currentText();
    if (que->exec(QString("select * from stardict where word = '%1'").arg(w))) {
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

}
