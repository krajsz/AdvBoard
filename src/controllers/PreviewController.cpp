#include "PreviewController.h"

PreviewController::PreviewController(QObject* parent) : QObject(parent)
{

}

void PreviewController::setView(PreviewWidget * const view)
{
    m_view = view;
}

void PreviewController::setAdvScene(AdvVideoScene * const scene)
{
	if (m_view)
	{
		m_view->setScene(scene);
	}
}

PreviewWidget* const PreviewController::view() const
{
    return m_view;
}
