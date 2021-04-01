/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2020. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "vtkConfigurableMeshWriter.h"
#include "vtkInfoDialog.h"

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <vtkPointData.h>
#include <vtksys/SystemTools.hxx>

const char vtkConfigurableMeshWriter::ID[] = "vtkConfigurableMeshWriter";

class vtkConfigurableMeshWriterPrivate
{
public:
    bool isVtpExtension(const char* ext);
    bool isVtuExtension(const char* ext);

    bool binary;
    bool binaryFomatType;
    bool dialogSuccess;

    vtkSmartPointer<vtkMetaDataSet> mesh;

};

bool vtkConfigurableMeshWriterPrivate::isVtpExtension(const char* ext)
{
    if (strcmp (ext, ".vtp") == 0)
    {
        return true;
    }
    return false;
}

bool vtkConfigurableMeshWriterPrivate::isVtuExtension(const char* ext)
{
    if (strcmp (ext, ".vtu") == 0)
    {
        return true;
    }
    return false;
}

vtkConfigurableMeshWriter::vtkConfigurableMeshWriter()
    : vtkDataMeshWriterBase(),
      d(new vtkConfigurableMeshWriterPrivate())
{
    d->binary = false;
    d->binaryFomatType = false;
    d->dialogSuccess = false;
    d->mesh = nullptr;
}

vtkConfigurableMeshWriter::~vtkConfigurableMeshWriter()
{
    delete d;
}

QStringList vtkConfigurableMeshWriter::handled() const
{
    return QStringList() << "vtkDataMesh";
}

QStringList vtkConfigurableMeshWriter::s_handled()
{
    return QStringList() << "vtkDataMesh";
}

bool vtkConfigurableMeshWriter::write(const QString& path)
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
            return true;
        }
    }
    catch (...)
    {
        qDebug() << metaObject()->className() << ": error writing to " << path;
        clearMetaDataFieldData(d->mesh);
        return false;
    }

    return false;
}

void vtkConfigurableMeshWriter::showInfoDialog()
{
    // Open a dialog: users must choose what cell and point data
    // to save.
    vtkSmartPointer<vtkMetaDataSet> meshTemp = d->mesh->Clone();
    vtkSmartPointer<vtkMetaDataSet> meshTemp2 = meshTemp->Clone();
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

QString vtkConfigurableMeshWriter::description() const
{
    return tr( "VTK ascii/binary file Writer" );
}

QString vtkConfigurableMeshWriter::identifier() const
{
    return ID;
}

QStringList vtkConfigurableMeshWriter::supportedFileExtensions() const
{
    return QStringList() << ".vtk" << ".vtp" << ".vtu";
}

bool vtkConfigurableMeshWriter::registered()
{
    return medAbstractDataFactory::instance()->registerDataWriterType("vtkConfigurableMeshWriter", vtkConfigurableMeshWriter::s_handled(), createvtkConfigurableMeshWriter);
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataWriter *createvtkConfigurableMeshWriter()
{
    return new vtkConfigurableMeshWriter;
}


