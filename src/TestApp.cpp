#include <cstdio>

#include <QApplication>
#include <QDebug>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>

#include "ColorPickerWidget.h"

class MainWindow: public QFrame {
    Q_OBJECT
public:
    MainWindow(): QFrame() {
        auto* l = new QVBoxLayout();
        setLayout(l);

        auto* picker = new ColorPickerWidget();
        l->addWidget(picker);

        auto* group = new QWidget();
        group->setLayout(new QHBoxLayout());
        l->addWidget(group);

        auto* picker2 = new ColorPickerWidget();
        group->layout()->addWidget(picker2);
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    qDebug() << "Started";

    auto* w = new MainWindow();
    w->show();
    return app.exec();
}

#include "TestApp.moc"
