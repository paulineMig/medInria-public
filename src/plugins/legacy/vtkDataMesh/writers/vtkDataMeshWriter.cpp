/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2020. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "vtkDataMeshWriter.h"
#include "vtkInfoDialog.h"

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <vtkPointData.h>
#include <vtksys/SystemTools.hxx>

const char vtkDataMeshWriter::ID[] = "vtkDataMeshWriter";

class vtkDataMeshWriterPrivate
{
public:
    bool isVtpExtension(const char* ext);
    bool isVtuExtension(const char* ext);

    bool binary;
    bool binaryFomatType;
    bool dialogSuccess;

    vtkMetaDataSet * mesh;

};

bool vtkDataMeshWriterPrivate::isVtpExtension(const char* ext)
{
    if (strcmp (ext, ".vtp") == 0)
    {
        return true;
    }
    return false;
}

bool vtkDataMeshWriterPrivate::isVtuExtension(const char* ext)
{
    if (strcmp (ext, ".vtu") == 0)
    {
        return true;
    }
    return false;
}

vtkDataMeshWriter::vtkDataMeshWriter()
    : vtkDataMeshWriterBase(),
      d(new vtkDataMeshWriterPrivate())
{
    d->binary = false;
    d->binaryFomatType = false;
    d->dialogSuccess = false;
    d->mesh = nullptr;
}

vtkDataMeshWriter::~vtkDataMeshWriter()
{
    delete d;
}

QStringList vtkDataMeshWriter::handled() const
{
    return QStringList() << "vtkDataMesh";
}

QStringList vtkDataMeshWriter::s_handled()
{
    return QStringList() << "vtkDataMesh";
}

bool vtkDataMeshWriter::write(const QString& path)
{
    if (!this->data())
    {
        return false;
    }

    qDebug().noquote() << "Can write with: " << this->identifier();

    medAbstractData * medData = dynamic_cast<medAbstractData*>(this->data());

    if(medData->identifier() != "vtkDataMesh")
    {
        return false;
    }

    d->mesh = dynamic_cast< vtkMetaDataSet*>( (vtkObject*)(this->data()->data()));

    if (!d->mesh)
    {
        return false;
    }
    addMetaDataAsFieldData(d->mesh);

    try
    {
        setlocale(LC_NUMERIC, "C");
        QLocale::setDefault(QLocale("C"));

        if(d->isVtpExtension(vtksys::SystemTools::GetFilenameLastExtension(path.toLocal8Bit().constData()).c_str())
                ||d->isVtuExtension(vtksys::SystemTools::GetFilenameLastExtension(path.toLocal8Bit().constData()).c_str()))
        {
            d->binaryFomatType = true;
        }

        this->moveToThread(qApp->thread());
        connect(this, SIGNAL(needMoreParameters()),
                this, SLOT(showInfoDialog()),
                Qt::BlockingQueuedConnection);
        emit needMoreParameters();

        // reached only when slot showInfoDialog has returned
        if (d->dialogSuccess)
        {
            d->mesh->Write(path.toLocal8Bit().constData(), d->binary);
            clearMetaDataFieldData(d->mesh);
        }
    }
    catch (...)
    {
        qDebug() << metaObject()->className() << ": error writing to " << path;
        clearMetaDataFieldData(d->mesh);
        return false;
    }

    return true;
}

void vtkDataMeshWriter::showInfoDialog()
{
    // Open a dialog: users must choose what cell and point data
    // to save.
    vtkMetaDataSet * meshTemp = d->mesh->Clone();
    vtkMetaDataSet * meshTemp2 = meshTemp->Clone();
    vtkInfoDialog editDialog(meshTemp, d->binaryFomatType, nullptr);

    d->dialogSuccess = false;
    if (editDialog.exec() == QDialog::Accepted)
    {
        d->binary = editDialog.fileFormatType();
        d->mesh = editDialog.getMetaDataSet();

        if (!d->mesh)
        {
            return;
        }

        d->dialogSuccess = true;
    }
    else
    {
        d->mesh = meshTemp2->Clone();
    }
}

QString vtkDataMeshWriter::description() const
{
    return tr( "VTK with metadata Mesh Writer" );
}

QString vtkDataMeshWriter::identifier() const
{
    return ID;
}

QStringList vtkDataMeshWriter::supportedFileExtensions() const
{
    return QStringList() << ".vtk" << ".vtp" << ".vtu";
}

bool vtkDataMeshWriter::registered()
{
    return medAbstractDataFactory::instance()->registerDataWriterType("vtkDataMeshWriter", vtkDataMeshWriter::s_handled(), createVtkDataMeshWriter);
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataWriter *createVtkDataMeshWriter()
{
    return new vtkDataMeshWriter;
}


