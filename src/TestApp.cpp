#include <cstdio>

#include <QApplication>
#include <QDebug>
#include <QColorDialog>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
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

        QObject::connect(picker, &ColorPickerWidget::colorChanged, [&] (QColor col) {
            qDebug() << col;
        });

        auto* group = new QWidget();
        group->setLayout(new QHBoxLayout());
        l->addWidget(group);

        auto* picker2 = new ColorPickerWidget();
        group->layout()->addWidget(picker2);

        auto* btn = new QPushButton("QtColorDialog");
        l->addWidget(btn);

        QObject::connect(btn, &QPushButton::clicked, [&] () {
            QColorDialog dlg;
            dlg.exec();
        });
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
