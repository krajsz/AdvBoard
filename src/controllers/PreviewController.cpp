#include "PreviewController.h"

PreviewController::PreviewController(QObject* parent) : QObject(parent)
{

}

void PreviewController::setView(PreviewWidget * const view)
{
    m_view = view;
}

PreviewWidget* const PreviewController::view() const
{
    return m_view;
}
