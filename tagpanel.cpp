#include "tagpanel.h"
#include "ui_tagpanel.h"

TagPanel::TagPanel(QWidget *parent) :
    QScrollArea(parent),
    ui(new Ui::TagPanel)
{
    ui->setupUi(this);
}

TagPanel::~TagPanel()
{
    delete ui;
}
