#ifndef PREVIEWCONTROLLER_H
#define PREVIEWCONTROLLER_H
#include <QObject>

class PreviewController : public QObject
{
    Q_OBJECT
public:
    explicit PreviewController(QObject *parent = nullptr);
};

#endif // PREVIEWCONTROLLER_H
