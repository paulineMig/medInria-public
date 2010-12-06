/* medViewerConfiguration.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu May 13 14:12:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 15 11:04:35 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "medViewerConfiguration.h"

#include "medToolBox.h"
#include "medViewerToolBoxLayout.h"
#include "medViewContainer.h"

class medViewerConfigurationPrivate
{
public:
    QWidget *parent;
    medViewerToolBoxLayout *layoutToolBox;
    QList<medToolBox*> toolboxes;
    int viewLayoutType;
    int layoutType;
    int customLayoutType;
    int databaseVisibility;
};

medViewerConfiguration::medViewerConfiguration(QWidget *parent) : QObject(), d(new medViewerConfigurationPrivate)
{
    d->parent = parent;
    d->layoutType = medViewerConfiguration::LeftDdRightTb;
    d->viewLayoutType = medViewContainer::Single;
    d->customLayoutType = 0;
    d->databaseVisibility = 1;
    
    d->layoutToolBox = new medViewerToolBoxLayout(parent);
    this->addToolBox(d->layoutToolBox);
}

medViewerConfiguration::~medViewerConfiguration(void)
{
    delete d;
    d = NULL;
}

void medViewerConfiguration::addToolBox(medToolBox *toolbox)
{
    if (!d->toolboxes.contains(toolbox)) {
        connect (toolbox, SIGNAL(addToolBox(medToolBox*)),    this, SIGNAL(toolboxAdded  (medToolBox*)));
        connect (toolbox, SIGNAL(removeToolBox(medToolBox*)), this, SIGNAL(toolboxRemoved(medToolBox*)));
        d->toolboxes.append(toolbox);
        emit toolboxAdded(toolbox);
    }
}

void medViewerConfiguration::removeToolBox(medToolBox *toolbox)
{
    if (d->toolboxes.contains(toolbox)) {
        disconnect (toolbox, SIGNAL(addToolBox(medToolBox*)),    this, SIGNAL(toolboxAdded  (medToolBox*)));
        disconnect (toolbox, SIGNAL(removeToolBox(medToolBox*)), this, SIGNAL(toolboxRemoved(medToolBox*)));
        d->toolboxes.removeOne(toolbox);
        emit toolboxRemoved(toolbox);
    }
}

QList<medToolBox*> medViewerConfiguration::toolBoxes(void) const
{
    return d->toolboxes;
}

void medViewerConfiguration::setLayoutType(medViewerConfiguration::LayoutType type)
{
    d->layoutType = type;
}

int medViewerConfiguration::layoutType(void) const
{
    return d->layoutType;
}

void medViewerConfiguration::setViewLayoutType(int type)
{
    d->viewLayoutType = type;
}

int medViewerConfiguration::viewLayoutType(void) const
{
    return d->viewLayoutType;
}

void medViewerConfiguration::setCustomLayoutType(int type)
{
    d->customLayoutType = type;
}

int medViewerConfiguration::customLayoutType(void) const
{
    return d->customLayoutType;
}

void medViewerConfiguration::hideDatabase(void)
{
    d->databaseVisibility = 0;
}

void medViewerConfiguration::showDatabase(void)
{
    d->databaseVisibility = 1;
}

int medViewerConfiguration::databaseVisibility(void) const
{
    return d->databaseVisibility;
}