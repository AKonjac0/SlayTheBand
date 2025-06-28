#include "Card.h"

Card::Card(Card_Meta *meta, MainWindow *parent) :meta(meta) {
    button = new QPushButton("card", parent);

}

