#ifndef ICONMENUPOPUP_H
#define ICONMENUPOPUP_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTableWidgetItem>

namespace Ui {
class IconMenuPopup;
}
class NewBookmarkWindow;


class IconMenuPopup : public QWidget
{
    Q_OBJECT

public:
    explicit IconMenuPopup(QWidget *parent = nullptr);
    ~IconMenuPopup();

    void run();

    static void getIcon(NewBookmarkWindow* parent);

public slots:
    void favoriteIconSelectionFinished(QListWidgetItem*);
    void iconSelectionFinished(QTableWidgetItem*);

signals:
    void iconChosen(QIcon icon);

private:
    Ui::IconMenuPopup *ui;
};

#endif // ICONMENUPOPUP_H
