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

const char vtkDataMeshWriter::ID[] = "vtkDataMeshWriter";

class vtkDataMeshWriterPrivate
{
public:
     bool binary;
     bool dialogSuccess;

     vtkMetaDataSet * meshbis;

};

vtkDataMeshWriter::vtkDataMeshWriter()
    : vtkDataMeshWriterBase(),
    d(new vtkDataMeshWriterPrivate())
{
    d->binary = false;
    d->dialogSuccess = false;
    d->meshbis = nullptr;
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
   // medAbstractData * medDataCopy = medData->clone();

    if(medData->identifier() != "vtkDataMesh")
    {
        return false;
    }

    d->meshbis = dynamic_cast< vtkMetaDataSet*>( (vtkObject*)(this->data()->data()));
    //vtkMetaDataSet* meshTemp = d->meshbis->Clone();

    if (!d->meshbis)
    {
         qDebug() << "---------------------DataMeshWriter: mesh test = nullptr----------------------";
        return false;
    }
    addMetaDataAsFieldData(d->meshbis);

    try
    {
        setlocale(LC_NUMERIC, "C");
        QLocale::setDefault(QLocale("C"));

        this->moveToThread(qApp->thread());
        connect(this, SIGNAL(needMoreParameters()),
                this, SLOT(showInfoDialog()),
                Qt::BlockingQueuedConnection);
        emit needMoreParameters();

        // reached only when slot showInfoDialog has returned
        if (d->dialogSuccess)
        {
            if(d->binary)
            {
                qDebug() << "---------------------DataMeshWriter: binaire----------------------";
            }

            d->meshbis->Write(path.toLocal8Bit().constData(), d->binary);
            clearMetaDataFieldData(d->meshbis);
        }
        else
        {
            qDebug() << "---------------------Dialog false ----------------------";
            if(!d->meshbis)
            {
                qDebug() << "---------------------Bad bad bad----------------------";
                return false;
            }
            if(!d->meshbis->GetDataSet())
            {
                qDebug() << "---------------------Bad really really bad bad----------------------";
                return false;
            }
            qDebug() << "---------------------Not so bad ----------------------";

           // d->meshbis->SetDataSet(mesh->GetDataSet());
            //d->meshbis = meshTemp->Clone();

            qDebug() << "Nb arrays" << d->meshbis->GetDataSet()->GetPointData()->GetNumberOfArrays();
        }
    }
    catch (...)
    {
        qDebug() << metaObject()->className() << ": error writing to " << path;
        clearMetaDataFieldData(d->meshbis);
        return false;
    }

    return true;
}

void vtkDataMeshWriter::showInfoDialog()
{
    // Open a dialog: users must choose what cell and point data
    // to save.
    vtkMetaDataSet * meshTemp = d->meshbis->Clone();
    vtkMetaDataSet * meshTemp2 = meshTemp->Clone();
    vtkInfoDialog editDialog(meshTemp, nullptr);

    d->dialogSuccess = false;
    if (editDialog.exec() == QDialog::Accepted)
    {
        d->binary = editDialog.fileFormatType();
        d->meshbis = editDialog.getMetaDataSet();

        if (!d->meshbis)
        {
            return;
        }

        d->dialogSuccess = true;
    }
    else
    {
       d->meshbis = meshTemp2->Clone();
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
    return QStringList() << ".vtk" << ".vtp";
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


