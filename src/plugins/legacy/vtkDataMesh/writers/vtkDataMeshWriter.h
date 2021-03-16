#pragma once
/*=========================================================================

medInria

Copyright (c) INRIA 2013 - 2020. All rights reserved.
See LICENSE.txt for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.

=========================================================================*/

#include "vtkDataMeshPluginExport.h"
#include "vtkDataMeshWriterBase.h"

class vtkDataSetWriter;
class vtkDataMeshWriterPrivate;

class VTKDATAMESHPLUGIN_EXPORT vtkDataMeshWriter : public vtkDataMeshWriterBase
{
    Q_OBJECT

public:
    vtkDataMeshWriter();
    ~vtkDataMeshWriter() override;

    QStringList handled() const override;
    static  QStringList s_handled();

    QString description() const override;
    QString identifier() const override;

    QStringList supportedFileExtensions() const override;

    static bool registered();

public slots:
    bool write (const QString& path) override;
    void showInfoDialog();

signals:
    void needMoreParameters();

private:
    static const char ID[];
    vtkDataMeshWriterPrivate* d;
};

dtkAbstractDataWriter *createVtkDataMeshWriter();
