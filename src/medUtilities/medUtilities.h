#pragma once

#include <QHash>
#include <medUtilitiesExport.h>

class medAbstractData;
class medAbstractView;

class MEDUTILITIES_EXPORT medUtilities
{
public:

    enum Mode3DType
    {
        VR,
        MIP_MAXIMUM,
        MIP_MINIMUM,
        MSR
    };

    static void setDerivedMetaData(medAbstractData* derived, medAbstractData* original,
                                   QString derivationDescription, bool queryForDescription = false);

    static void copyMetaDataIfEmpty(medAbstractData* derived, medAbstractData* original, QList<QString> metaDataKeys);
    static void copyMetaDataIfEmpty(medAbstractData* derived, medAbstractData* original, QString metaDataKey);

    static QStringList metaDataKeysToCopyForDerivedData(medAbstractData* derived);

    static void generateSeriesAndSOPInstanceId(medAbstractData* data);

    static void querySeriesDescription(medAbstractData* data);

    static void applyOrientationMatrix(medAbstractView* view, double* inPoint, double* outPoint, bool withTranslation = true);

    static void applyInverseOrientationMatrix(medAbstractView* view, double* inPoint, double* outPoint, bool withTranslation = true);

    static void switchTo3D(medAbstractView *view, Mode3DType mode3D = VR); // Display mesh in 3D orientation

    static medAbstractData *changeMaxNumberOfMeshTriangles(medAbstractData *mesh, int value);
};
