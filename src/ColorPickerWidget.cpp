#include "ColorPickerWidget.h"

#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QMouseEvent>

struct ColorPickerWidget::Private {
    bool cursorTracking;
    QPoint mousePos;

    QImage img;
    QPixmap pix;
    QSize imgSize;
    QSize gradientSize;

    const int cursorWidth = 10;
    const int cursorHeight = 10;

    Private(): img(1920, 1200, QImage::Format_RGB32),
            cursorTracking(false) {
    }
};

ColorPickerWidget::ColorPickerWidget(QWidget* parent):
        QWidget(parent) {

    state = new Private();
}

ColorPickerWidget::~ColorPickerWidget() {
    delete state;
}

void ColorPickerWidget::paintEvent(QPaintEvent *event) {
    QPainter p(this);

    if(size() != state->gradientSize) {
        recalculateGradient();
    }

    p.drawImage(0, 0, state->img);

    if(state->cursorTracking) {
        p.fillRect(state->mousePos.x(), state->mousePos.y(), 10, 10, Qt::black);
    }
}

inline int getColorForPosition(double position) {
    double m = position * 6;
    int n = static_cast<int>(m);
    double frac = m - n;
    int t = static_cast<int>(frac * 0xFF);
    int r, g, b;

    switch(n) {
        case 0:
            r = 255;
            g = t;
            b = 0;
            break;
        case 1:
            r = 255 - t;
            g = 255;
            b = 0;
            break;
        case 2:
            r = 0;
            g = 255;
            b = t;
            break;
        case 3:
            r = 0;
            g = 255 - t;
            b = 255;
            break;
        case 4:
            r = t;
            g = 0;
            b = 255;
            break;
        case 5:
            r = 255;
            g = 0;
            b = 255 - t;
            break;
    }

    const int colorValue = qRgb(r, g, b);
    return colorValue;
}

inline int adjustBrightness(int color, double brightness) {
    int r = qRed(color);
    int g = qGreen(color);
    int b = qBlue(color);

    double R = static_cast<double>(r) * brightness;
    double G = static_cast<double>(g) * brightness;
    double B = static_cast<double>(b) * brightness;

    r = static_cast<int>(R);
    g = static_cast<int>(G);
    b = static_cast<int>(B);

    const int colorValue = qRgb(r, g, b);
}

void ColorPickerWidget::recalculateGradient() {
    uint8_t* img = static_cast<uint8_t*>(state->img.bits());

    const int imgWidth = state->img.width();
    const int ylen = height() > state->img.height() ?
        state->img.height() : height();

    for(int y = 0; y < ylen; ++y) {
        const double brightness = static_cast<double>(ylen - y) / ylen;
        const int yidx = y * imgWidth * 4;
        uint8_t* scanLine = reinterpret_cast<uint8_t*>(&img[yidx]);

        recalculateGradientScanLine(scanLine, brightness);
    }

    state->gradientSize = size();
}

void ColorPickerWidget::recalculateGradientScanLine(uint8_t* scanLine,
        double brightness) {

    const int xlen = width() > state->img.width() ?
        state->img.width() : width();

    for(int x = 0; x < xlen; ++x) {
        const double position = static_cast<double>(x) / xlen;

        const int colorValue =
            adjustBrightness(getColorForPosition(position), brightness);

        *reinterpret_cast<int*>(&scanLine[x * 4]) = colorValue;
    }
}

QPoint ColorPickerWidget::ensureInBounds(QPoint p) {
    int x = p.x();
    if(x < 0)
        x = 0;
    else if(x > width() - state->cursorWidth)
        x = width() - state->cursorWidth;

    int y = p.y();
    if(y < 0)
        y = 0;
    else if(y > height() - state->cursorHeight)
        y = height() - state->cursorHeight;

    return QPoint(x, y);
}

void ColorPickerWidget::mousePressEvent(QMouseEvent *event) {
    state->cursorTracking = true;
    state->mousePos = ensureInBounds(event->pos());
    repaint();
}

void ColorPickerWidget::mouseReleaseEvent(QMouseEvent *event) {
    state->cursorTracking = false;
    state->mousePos = ensureInBounds(event->pos());
    repaint();
}

void ColorPickerWidget::mouseMoveEvent(QMouseEvent *event) {
    if(state->cursorTracking) {
        state->mousePos = ensureInBounds(event->pos());
        repaint();
    }
}
