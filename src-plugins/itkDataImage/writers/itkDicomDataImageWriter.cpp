/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <itkDicomDataImageWriter.h>

#include <medAbstractData.h>
#include <medAbstractDataFactory.h>

#include <itkGDCMImageIO.h>

static QString s_identifier() {
    return "itkDicomDataImageWriter";
}

static QStringList s_handled() {
    return QStringList()  << "itkDataImageChar3" << "itkDataImageChar4"
                          << "itkDataImageUChar3" << "itkDataImageUChar4"
                          << "itkDataImageShort3" << "itkDataImageShort4"
                          << "itkDataImageUShort3" << "itkDataImageUShort4"
                          << "itkDataImageInt3" << "itkDataImageInt4"
                          << "itkDataImageUInt3" << "itkDataImageUInt4"
                          << "itkDataImageLong3" << "itkDataImageLong4"
                          << "itkDataImageULong3" << "itkDataImageULong4"
                          << "itkDataImageFloat3" << "itkDataImageFloat4"
                          << "itkDataImageDouble3" << "itkDataImageDouble4";
}

itkDicomDataImageWriter::itkDicomDataImageWriter(): itkDataImageWriterBase() {
    this->io = itk::GDCMImageIO::New();
}

itkDicomDataImageWriter::~itkDicomDataImageWriter()
{
}

QStringList itkDicomDataImageWriter::handled() const
{
    return s_handled();
}

QStringList itkDicomDataImageWriter::supportedFileExtensions() const
{
    return QStringList() << ".dcm";
}

bool itkDicomDataImageWriter::registered()
{
    return medAbstractDataFactory::instance()->registerDataWriterType(s_identifier(), s_handled(), create);
}

QString itkDicomDataImageWriter::identifier() const
{
    return s_identifier();
}

QString itkDicomDataImageWriter::description() const
{
    return "Dicom image exporter";
}

// /////////////////////////////////////////////////////////////////
// Type instantiation
// /////////////////////////////////////////////////////////////////

dtkAbstractDataWriter * itkDicomDataImageWriter::create()
{
    return new itkDicomDataImageWriter;
}

