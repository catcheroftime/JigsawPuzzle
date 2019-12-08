#include "puzzle.h"
#include "puzzleplugin.h"

#include <QtPlugin>

PuzzlePlugin::PuzzlePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void PuzzlePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool PuzzlePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *PuzzlePlugin::createWidget(QWidget *parent)
{
    return new Puzzle(parent);
}

QString PuzzlePlugin::name() const
{
    return QLatin1String("Puzzle");
}

QString PuzzlePlugin::group() const
{
    return QLatin1String("");
}

QIcon PuzzlePlugin::icon() const
{
    return QIcon();
}

QString PuzzlePlugin::toolTip() const
{
    return QLatin1String("");
}

QString PuzzlePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool PuzzlePlugin::isContainer() const
{
    return false;
}

QString PuzzlePlugin::domXml() const
{
    return QLatin1String("<widget class=\"Puzzle\" name=\"puzzle\">\n</widget>\n");
}

QString PuzzlePlugin::includeFile() const
{
    return QLatin1String("puzzle.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(puzzleplugin, PuzzlePlugin)
#endif // QT_VERSION < 0x050000
