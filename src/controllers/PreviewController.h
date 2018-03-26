#ifndef PREVIEWCONTROLLER_H
#define PREVIEWCONTROLLER_H
#include <QObject>
#include "src/widgets/PreviewWidget.h"

class PreviewController : public QObject
{
    Q_OBJECT
public:
    explicit PreviewController(QObject *parent = nullptr);
    void setView(PreviewWidget* const view);
    PreviewWidget* const view() const;
private:
    PreviewWidget* m_view;
};

#endif // PREVIEWCONTROLLER_H
