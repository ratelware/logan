#include "iconmenupopup.h"
#include "ui_iconmenupopup.h"

#include "configuration_manager.h"
#include "newbookmarkwindow.h"

#include <QAction>
#include <QPaintEvent>
#include <QPainter>

IconMenuPopup::IconMenuPopup(QWidget *parent) :
    QWidget(),
    ui(new Ui::IconMenuPopup)
{
    ui->setupUi(this);

    auto& config = configuration_manager::get_instance();
    auto& icons = config.get_favorite_icons_paths();

    overrideWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Popup);
    move(parent->pos());

    for(auto i: icons) {
        auto item = new QListWidgetItem(QIcon(QPixmap(i)), "");
        ui->favorites->addItem(item);
    }
    connect(ui->favorites, &QListWidget::itemDoubleClicked, this, &IconMenuPopup::favoriteIconSelectionFinished);


    auto allIcons = config.get_all_icons_paths();

    auto maxCols = icons.size();
    ui->allIcons->setColumnCount(maxCols);
    ui->allIcons->setRowCount(allIcons.size() / maxCols + 1);
    for(int i = 0; i < maxCols; ++i) {
        ui->allIcons->setColumnWidth(i, 40);
    }
    connect(ui->allIcons, &QTableWidget::itemDoubleClicked, this, &IconMenuPopup::iconSelectionFinished);

    auto currentCol = 0;
    auto currentRow = 0;
    for(auto i: allIcons) {
        auto item = new QTableWidgetItem(QIcon(QPixmap(i)), "");
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        ui->allIcons->setItem(currentRow, currentCol++, item);
        if(currentCol >= maxCols) {
            ++currentRow;
            currentCol = 0;
        }
    }
}

void IconMenuPopup::favoriteIconSelectionFinished(QListWidgetItem* i) {
    qDebug("Emitting %p", i);
    emit iconChosen(i->icon());
    close();
}

void IconMenuPopup::iconSelectionFinished(QTableWidgetItem* i) {
    qDebug("Emitting 2x %p", i);
    emit iconChosen(i->icon());
    close();
}


IconMenuPopup::~IconMenuPopup()
{
    delete ui;
}


void IconMenuPopup::getIcon(NewBookmarkWindow *parent) {
    auto q = new IconMenuPopup(parent);
    connect(q, &IconMenuPopup::iconChosen, parent, &NewBookmarkWindow::setBookmarkIcon);
    q->run();
}


void IconMenuPopup::run() {
    show();
    update();
}
