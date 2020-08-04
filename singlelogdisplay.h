#ifndef SINGLELOGDISPLAY_H
#define SINGLELOGDISPLAY_H

#include <QWidget>
#include <QTextBlockFormat>

#include "search_structure.h"

class LogsDisplay;

namespace Ui {
class SingleLogDisplay;
}

class SingleLogDisplay : public QWidget
{
    Q_OBJECT

public:
    QStringList text;

    explicit SingleLogDisplay(QStringList& l, LogsDisplay *parent);
    ~SingleLogDisplay();

public:
    Ui::SingleLogDisplay *ui;

public slots:
    void copySelectionToClipboard();
    void emphasiseSelection();
    void applySearch(search_structure s);

private:
    void setUpActions();

    QList<QTextBlockFormat> existingFormats;
};

#endif // SINGLELOGDISPLAY_H
