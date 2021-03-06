#include "tst_jsonconvertertest.h"

JsonConverterTest::JsonConverterTest()
{

}

JsonConverterTest::~JsonConverterTest()
{

}

void JsonConverterTest::test_gladiatorsToJson()
{
    QList<Gladiator> gladiators;
    Gladiator g1;
    g1.setAge(23);
    g1.setHealth(5);
    Gladiator g2;
    g2.setAge(20);
    gladiators.push_back(g1);
    gladiators.push_back(g2);

    // Serialize
    QString json = JsonConverter::gladiatorsToJson(gladiators);

    // Parse
    QList<Gladiator *> *parsedGladiators = JsonConverter::jsonToGladiators(json);

    QCOMPARE(parsedGladiators->size(), 2);
    QCOMPARE(parsedGladiators->value(0)->getAge(), g1.getAge());
    QCOMPARE(parsedGladiators->value(0)->getHealth(), g1.getHealth());
    QCOMPARE(parsedGladiators->value(1)->getAge(), g2.getAge());
}

void JsonConverterTest::test_towersToJson()
{
    QList<Tower> towers;
    Tower t1;
    t1.setId("1");
    Tower t2;
    t2.setId("2");
    towers.push_back(t1);
    towers.push_back(t2);

    // Serialize
    QString json = JsonConverter::towersToJson(towers);

    // Parse
    QList<Tower *> *parsedTowers = JsonConverter::jsonToTowers(json);

    QCOMPARE(parsedTowers->size(), 2);
    QCOMPARE(parsedTowers->value(0)->getId(), t1.getId());
    QCOMPARE(parsedTowers->value(1)->getId(), t2.getId());
}
