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

    int readR(int colorValue) {
        return colorValue & 0xFF;
    }

    int readG(int colorValue) {
        return (colorValue >> 4) & 0xFF;
    }

    int readB(int colorValue) {
        return (colorValue >> 8) & 0xFF;
    }

    int getColorForPosition(double position) {
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

    int adjustBrightness(int color, double brightness) {
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
};
