#pragma once

#include <QWidget>

class ColorPickerWidget: public QWidget {
    Q_OBJECT

public:
    explicit ColorPickerWidget(QWidget* parent = nullptr);
    virtual ~ColorPickerWidget();

    void paintEvent(QPaintEvent *event) override;

private:
    class Private;
    Private* state;

    void recalculateGradient();
    void recalculateGradientScanLine(uint8_t* scanLine, double brightness);
    QPoint ensureInBounds(QPoint s);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    int readR(int colorValue) {
        return colorValue & 0xFF;
    }

    int readG(int colorValue) {
        return (colorValue >> 4) & 0xFF;
    }

    int readB(int colorValue) {
        return (colorValue >> 8) & 0xFF;
    }
};
