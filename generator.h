#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QRandomGenerator>
#include <QtMath>
#include <QDebug>
#include <QVariantMap>
#include <coefficients.h>

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);

signals:



private:


};

#endif // GENERATOR_H
