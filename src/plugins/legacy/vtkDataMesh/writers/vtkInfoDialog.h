#pragma once

#include "vtkDataMeshPluginExport.h"

#include <medDataIndex.h>
#include <vtkMetaDataSet.h>

#include <vtkSmartPointer.h>

#include <QDialog>

class vtkInfoDialogPrivate;

class VTKDATAMESHPLUGIN_EXPORT vtkInfoDialog: public QDialog
{
    Q_OBJECT

public:

    vtkInfoDialog(vtkSmartPointer<vtkMetaDataSet> mesh, bool binaryFormat, QWidget *parent);

    virtual ~vtkInfoDialog();

    bool fileFormatType();
    vtkMetaDataSet* getMetaDataSet();


protected slots:
    void getArrayId(int id);
    void showWidget(bool show);

public slots:
    void cancel();
    void validate();

private:
    vtkInfoDialogPrivate *d;
};

