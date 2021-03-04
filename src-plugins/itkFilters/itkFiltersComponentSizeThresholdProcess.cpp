/*=========================================================================

 medInria

 Copyright (c) INRIA 2013. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include "itkFiltersComponentSizeThresholdProcess.h"

#include <dtkCore/dtkAbstractProcessFactory.h>

#include <itkBinaryThresholdImageFilter.h>
#include <itkCastImageFilter.h>
#include <itkConnectedComponentImageFilter.h>
#include <itkImage.h>
#include <itkRelabelComponentImageFilter.h>

#include <medAbstractDataFactory.h>
#include <medUtilitiesITK.h>

class itkFiltersComponentSizeThresholdProcessPrivate
{
public:
    double minimumSize;
    double binarize;
};

const double itkFiltersComponentSizeThresholdProcess::defaultMinimumSize = 50.0;
//-------------------------------------------------------------------------------------------

itkFiltersComponentSizeThresholdProcess::itkFiltersComponentSizeThresholdProcess(itkFiltersComponentSizeThresholdProcess *parent) 
    : itkFiltersProcessBase(parent), d(new itkFiltersComponentSizeThresholdProcessPrivate)
{  
    d->minimumSize = defaultMinimumSize;
    double binarize = 0;
}

itkFiltersComponentSizeThresholdProcess::itkFiltersComponentSizeThresholdProcess(const itkFiltersComponentSizeThresholdProcess& other)
     : itkFiltersProcessBase(other), d(other.d)
{
}

//-------------------------------------------------------------------------------------------

itkFiltersComponentSizeThresholdProcess::~itkFiltersComponentSizeThresholdProcess( void )
{
    delete d;
}

//-------------------------------------------------------------------------------------------

bool itkFiltersComponentSizeThresholdProcess::registered( void )
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("itkComponentSizeThresholdProcess", createitkFiltersComponentSizeThresholdProcess);
}

QString itkFiltersComponentSizeThresholdProcess::description() const
{
    return tr("Size Threshold filter");
}

//-------------------------------------------------------------------------------------------

void itkFiltersComponentSizeThresholdProcess::setParameter(int data, int channel)
{
    /*if (channel != 0)
        return;*/
     
    if (channel == 0)
    {
       d->minimumSize = data;
    }
    else if (channel == 1)
    {
       d->binarize = data;	
    }
    else
    {
      return;
    }
}

//-------------------------------------------------------------------------------------------

int itkFiltersComponentSizeThresholdProcess::tryUpdate()
{  
    int res = DTK_FAILURE;

    if ( getInputData() )
    {
        res = DISPATCH_ON_3D_PIXEL_TYPE(&itkFiltersComponentSizeThresholdProcess::updateProcess, this, getInputData());
    }

    return res;
}

template <class InputImageType>
dtkSmartPointer<medAbstractData> itkFiltersComponentSizeThresholdProcess::castToOutputType(medAbstractData* inputData)
{
    //we will later label the image so we don't care about precision.
    typedef itk::CastImageFilter< InputImageType, OutputImageType > CastFilterType;

    typename CastFilterType::Pointer  caster = CastFilterType::New();
    typename InputImageType::Pointer im = static_cast<InputImageType*>(inputData->data());
    caster->SetInput(im);
    caster->Update();

    dtkSmartPointer<medAbstractData> outputData = medAbstractDataFactory::instance()->createSmartPointer(medUtilitiesITK::itkDataImageId<OutputImageType>());
    outputData->setData(caster->GetOutput());

    return outputData;
}

template <class InputImageType>
int itkFiltersComponentSizeThresholdProcess::updateProcess(medAbstractData* inputData)
{
    dtkSmartPointer<medAbstractData> adjustedInputData = inputData;

    if (std::is_floating_point<typename InputImageType::PixelType>::value)
    {
        adjustedInputData = castToOutputType<InputImageType>(inputData);;
    }

    typename InputImageType::Pointer inputImage = static_cast<InputImageType*>(inputData->data());

    typedef itk::ConnectedComponentImageFilter <InputImageType, OutputImageType> ConnectedComponentFilterType;
    typename ConnectedComponentFilterType::Pointer connectedComponentFilter = ConnectedComponentFilterType::New();
    connectedComponentFilter->SetInput(inputImage);
    connectedComponentFilter->Update();

    // RELABEL COMPONENTS according to their sizes (0:largest(background))
    typedef itk::RelabelComponentImageFilter<OutputImageType, OutputImageType> FilterType;
    typename FilterType::Pointer relabelFilter = FilterType::New();
    relabelFilter->SetInput(connectedComponentFilter->GetOutput());
    relabelFilter->SetMinimumObjectSize(d->minimumSize);
    relabelFilter->Update();

    itk::CStyleCommand::Pointer callback = itk::CStyleCommand::New();
    callback->SetClientData ( ( void * ) this );
    callback->SetCallback ( itkFiltersProcessBase::eventCallback );
    connectedComponentFilter->AddObserver ( itk::ProgressEvent(), callback );

    setOutputData(medAbstractDataFactory::instance()->createSmartPointer(medUtilitiesITK::itkDataImageId<OutputImageType>()));


    std::cout << "d->binarize = " << d->binarize << std::endl;
    if (d->binarize == 1.0)
    { 
    // BINARY FILTER
    typedef itk::BinaryThresholdImageFilter <OutputImageType, OutputImageType> BinaryThresholdImageFilterType;
    typename BinaryThresholdImageFilterType::Pointer thresholdFilter
            = BinaryThresholdImageFilterType::New();
    thresholdFilter->SetInput(relabelFilter->GetOutput());
    thresholdFilter->SetUpperThreshold(0);
    thresholdFilter->SetInsideValue(0);
    thresholdFilter->SetOutsideValue(1);

    thresholdFilter->Update();

    getOutputData()->setData ( thresholdFilter->GetOutput() );
    }
    else
    {
    getOutputData()->setData ( relabelFilter->GetOutput());
    }
    

    QString newSeriesDescription = "connectedComponent " + QString::number(d->minimumSize);
    medUtilities::setDerivedMetaData(getOutputData(), inputData, newSeriesDescription);

    return DTK_SUCCEED;
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess * createitkFiltersComponentSizeThresholdProcess ( void )
{
    return new itkFiltersComponentSizeThresholdProcess;
}
