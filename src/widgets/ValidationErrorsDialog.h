#ifndef VALIDATIONERRORSDIALOG_H
#define VALIDATIONERRORSDIALOG_H

#include <QDialog>

namespace Ui {
class ValidationErrorsDialog;
}

class ValidationErrorsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ValidationErrorsDialog(QWidget *parent = 0);
    ~ValidationErrorsDialog();

private:
    Ui::ValidationErrorsDialog *ui;
};

#endif // VALIDATIONERRORSDIALOG_H
