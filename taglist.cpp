#include "taglist.h"
#include "ui_taglist.h"

TagList::TagList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagList)
{
    ui->setupUi(this);
}

TagList::~TagList()
{
    delete ui;
}
