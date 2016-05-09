/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medSegmentationWorkspace.h>

#include <medAbstractSelectableToolBox.h>
#include <medDataManager.h>
#include <medLayerParameterGroup.h>
#include <medSelectorToolBox.h>
#include <medTabbedViewContainers.h>
#include <medToolBoxFactory.h>
#include <medViewParameterGroup.h>

#include <stdexcept>

class medSegmentationWorkspacePrivate
{
public:
    // Give values to items without a constructor.
    medSegmentationWorkspacePrivate() :
       selectorToolBox(NULL)
    {}

    medSelectorToolBox *selectorToolBox;
    medToolBox * roiManagementToolBox;
};


medSegmentationWorkspace::medSegmentationWorkspace(QWidget * parent /* = NULL */ ) :
medAbstractWorkspace(parent), d(new medSegmentationWorkspacePrivate)
{
    d->selectorToolBox = new medSelectorToolBox(parent, "segmentation");

    connect(d->selectorToolBox,SIGNAL(success()),this,SLOT(onSuccess()));
    connect(d->selectorToolBox,SIGNAL(currentToolBoxChanged()),this,SLOT(onCurrentToolBoxChanged()));

    // Always have a parent.
    if (!parent)
        throw (std::runtime_error ("Must have a parent widget"));
    
    this->addToolBox(d->selectorToolBox);
    d->selectorToolBox->setTitle(this->name()); // get workspace name

    if(medToolBoxFactory::instance()->createToolBox("medRoiManagementToolBox"))
	{
		d->roiManagementToolBox= medToolBoxFactory::instance()->createToolBox("medRoiManagementToolBox");
		d->roiManagementToolBox->setWorkspace(this);
		this->addToolBox(d->roiManagementToolBox);
	}

    setInitialGroups();

    connect(this->stackedViewContainers(), SIGNAL(containersSelectedChanged()),
            d->selectorToolBox, SIGNAL(inputChanged()));
}

medSegmentationWorkspace::~medSegmentationWorkspace(void)
{
    delete d;
    d = NULL;
}

medSelectorToolBox * medSegmentationWorkspace::segmentationToobox()
{
    return d->selectorToolBox;
}

bool medSegmentationWorkspace::isUsable()
{
    medToolBoxFactory * tbFactory = medToolBoxFactory::instance();
    return (tbFactory->toolBoxesFromCategory("segmentation").size()!=0); 
}

void medSegmentationWorkspace::onSuccess()
{
    medAbstractData * output = d->selectorToolBox->currentToolBox()->processOutput();
    medDataManager::instance()->importData(output);
}

void medSegmentationWorkspace::onCurrentToolBoxChanged()
{
    medAbstractSelectableToolBox* currentToolBox = d->selectorToolBox->currentToolBox();

    // Remove interactor on previous tlbx
    if (currentToolBox->findChild<QPushButton*>("closedPolygonButton"))
    {
        currentToolBox->findChild<QPushButton*>("closedPolygonButton")->setChecked(false);
    }
    else if (currentToolBox->findChild<QPushButton*>("paintButton"))
    {
        if (currentToolBox->findChild<QPushButton*>("paintButton")->isChecked())
        {
            currentToolBox->findChild<QPushButton*>("paintButton")->click();
        }
        if (currentToolBox->findChild<QPushButton*>("Magic Wand")->isChecked())
        {
            currentToolBox->findChild<QPushButton*>("Magic Wand")->click();
        }
    }
}
