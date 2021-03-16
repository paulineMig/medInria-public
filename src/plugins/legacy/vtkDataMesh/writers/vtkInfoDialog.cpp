#include "vtkInfoDialog.h"

#include <medComboBox.h>

#include <vtkCellData.h>
#include <vtkPointData.h>

#include <QtWidgets>

#include <algorithm>
#include <set>


// ////////////////////////////////////////////////////////////////////////////
// ///////////////////// vtkInfoDialogPrivate ///////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
class vtkInfoDialogPrivate
{
public:
    void initializeArraysMap();

    QCheckBox* arraysCheckBox;
    QCheckBox* binaryCheckBox;
    QMenu* managerMenu;
    QWidget* arraysWidget;

    QMap<int, QPair<QString, bool> > mapOfArrayToKeep;

    // maps multiple actions on one slot
    QSignalMapper* visibilityMapper;

    vtkMetaDataSet * mesh;

    int nbCellArray;
    int nbPointArray;
};

void vtkInfoDialogPrivate::initializeArraysMap()
{
    if (!mesh)
    {
        return;
    }

    nbCellArray = mesh->GetDataSet()->GetCellData()->GetNumberOfArrays();
    nbPointArray = mesh->GetDataSet()->GetPointData()->GetNumberOfArrays();

    for(int i = 0; i< nbPointArray + nbCellArray; i++)
    {
        if (i < nbPointArray)
        {
            mapOfArrayToKeep.insert(i,
                                    qMakePair( QString::fromUtf8(mesh->GetDataSet()->
                                                                 GetPointData()->GetArrayName(i)), true));

        }
        else
        {
            mapOfArrayToKeep.insert(i,
                                    qMakePair( QString::fromUtf8(mesh->GetDataSet()->
                                                                 GetCellData()->GetArrayName(i-nbPointArray)), true));
        }
    }
}

// ////////////////////////////////////////////////////////////////////////////
// //////////////////////// vtkInfoDialog ///////////////////////////////////
// ////////////////////////////////////////////////////////////////////////////
vtkInfoDialog::vtkInfoDialog(vtkMetaDataSet *mesh, QWidget* parent)
    : QDialog(parent, Qt::Dialog | Qt::WindowCloseButtonHint),
      d(new vtkInfoDialogPrivate())
{
    d->mesh = mesh;
    d->initializeArraysMap();

    /** ------------- initialize UI --------------------- **/
    QVBoxLayout* mainLayout = new QVBoxLayout();

    d->visibilityMapper = new QSignalMapper(this);

    d->binaryCheckBox = new QCheckBox(tr("Binary Format"));
    d->binaryCheckBox->setChecked(false);

    d->arraysWidget = new QWidget(this);
    d->arraysCheckBox = new QCheckBox(tr("Choose arrays to keep"));
    d->arraysCheckBox->setChecked(false);
    connect(d->arraysCheckBox,SIGNAL(clicked(bool)), this, SLOT(showWidget(bool)));


    QWidget* menuArrayWidget = new QWidget(this);
    QVBoxLayout* menuArrayLayout = new QVBoxLayout();
    menuArrayLayout->setContentsMargins(0,0,0,0);
    menuArrayWidget->setLayout(menuArrayLayout);
    menuArrayLayout->addWidget(d->arraysCheckBox);

    QVBoxLayout* arrayLayout = new QVBoxLayout();
    d->arraysWidget->setLayout(arrayLayout);

    d->visibilityMapper->disconnect();
    QIcon cellIcon(":/icons/dataTypeCell.png");
    QIcon pointIcon(":/icons/dataTypePoint.png");

    for (int i = 0; i < d->nbPointArray + d->nbCellArray; ++i)
    {
        QCheckBox* checkBox = new QCheckBox(d->mapOfArrayToKeep.value(i).first, d->arraysWidget);
        checkBox->setChecked(true);
        if (i < d->nbPointArray)
        {
            checkBox->setIcon(pointIcon);
        }
        else
        {
            checkBox->setIcon(cellIcon);
        }
        checkBox->show();
        arrayLayout->addWidget(checkBox);

        connect(checkBox, SIGNAL(clicked(bool)),
                d->visibilityMapper, SLOT(map()));
        d->visibilityMapper->setMapping(checkBox, i);

    }
    // connect the signal mapper to the correct slot
    connect(d->visibilityMapper, SIGNAL(mapped(int)),
            this, SLOT(getArrayId(int)));

    d->arraysWidget->hide();

    mainLayout->addWidget(d->binaryCheckBox);
    mainLayout->addWidget(menuArrayWidget);
    mainLayout->addWidget(d->arraysWidget);


    // buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton(tr("OK"));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(validate()));
    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(cancel()));

    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);
    setModal(true);
}

vtkInfoDialog::~vtkInfoDialog()
{ 
    delete d->visibilityMapper;
    //d->mesh = nullptr;

    delete d;
}

vtkMetaDataSet* vtkInfoDialog::getMetaDataSet()
{
   std::vector<int> idToRemove;

   QMap<int, QPair<QString, bool>>::iterator i;
   for (i = d->mapOfArrayToKeep.begin(); i != d->mapOfArrayToKeep.end(); ++i)
   {
       if (!i.value().second)
       {
           idToRemove.push_back(i.key());
       }
   }

   std::sort(idToRemove.rbegin(), idToRemove.rend());

   for (unsigned long it = 0; it < idToRemove.size(); it++)
   {
       int id = idToRemove[it];

       if(id < d->nbPointArray)
       {
           d->mesh->GetDataSet()->GetPointData()->RemoveArray(id);
       }
       else
       {
           id = id - d->nbPointArray;
           d->mesh->GetDataSet()->GetCellData()->RemoveArray(id);
       }
   }

   return d->mesh;
}

bool vtkInfoDialog::fileFormatType()
{
    return d->binaryCheckBox->isChecked();
}

void vtkInfoDialog::getArrayId(int id)
{
    bool keep = d->mapOfArrayToKeep.value(id).second;
    QString arrayName = d->mapOfArrayToKeep.value(id).first;
    d->mapOfArrayToKeep.insert(id, qMakePair(arrayName, !keep));
}

void vtkInfoDialog::showWidget(bool show)
{
    d->arraysWidget->setVisible(show);
}

void vtkInfoDialog::cancel()
{
    this->reject();
}

void vtkInfoDialog::validate()
{
    this->accept();
}

