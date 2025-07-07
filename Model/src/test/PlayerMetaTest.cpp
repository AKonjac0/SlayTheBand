#include "test/PlayerMetaTest.h"
#include "PlayerMeta.h"

#include <QtTest>

void PlayerMetaTest::testConstructor()
{
    PlayerMeta player("Hero", 50, 100, 30);
    QCOMPARE(player.getname(), QString("Hero"));
    QCOMPARE(player.getHP(), 50);
    QCOMPARE(player.getmaxHP(), 100);
    QCOMPARE(player.getMP(), 30);
    QCOMPARE(player.getmaxMP(), 30);
}

void PlayerMetaTest::testMaxMPChange_increase()
{
    PlayerMeta player("Hero", 50, 100, 40);
    player.maxMP_change(30); // maxMP = 70
    QCOMPARE(player.getmaxMP(), 70);
    QCOMPARE(player.getMP(), 40);
}

void PlayerMetaTest::testMaxMPChange_decreaseAndMPExceeds()
{
    PlayerMeta player("Hero", 50, 100, 40);
    player.setMaxMP(50); // ensure maxMP is 50
    player.maxMP_change(-40); // maxMP = 10
    QCOMPARE(player.getmaxMP(), 10);
    QCOMPARE(player.getMP(), 10);
}

void PlayerMetaTest::testSetMaxMP_valid()
{
    PlayerMeta player("Hero", 50, 100, 30);
    player.setMaxMP(60);
    QCOMPARE(player.getmaxMP(), 60);
    QCOMPARE(player.getMP(), 30);
}

void PlayerMetaTest::testSetMaxMP_belowCurrentMP()
{
    PlayerMeta player("Hero", 50, 100, 40);
    player.setMaxMP(30);
    QCOMPARE(player.getmaxMP(), 30);
    QCOMPARE(player.getMP(), 30);
}

void PlayerMetaTest::testSetMaxMP_negative()
{
    PlayerMeta player("Hero", 50, 100, 40);
    player.setMaxMP(-10);
    QCOMPARE(player.getmaxMP(), 0);
    QCOMPARE(player.getMP(), 0);
}