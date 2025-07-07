#ifndef PLAYERMETATEST_H
#define PLAYERMETATEST_H

#include <QObject>
#include "PlayerMeta.h"

class PlayerMetaTest : public QObject
{
    Q_OBJECT

private slots:
    void testConstructor();
    void testMaxMPChange_increase();
    void testMaxMPChange_decreaseAndMPExceeds();
    void testSetMaxMP_valid();
    void testSetMaxMP_belowCurrentMP();
    void testSetMaxMP_negative();
};

#endif // PLAYERMETATEST_H