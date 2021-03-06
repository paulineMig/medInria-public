/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2014. All rights reserved.
 See LICENSE.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medAbstractInteractor.h>

#include <medAbstractView.h>


/**
* @fn QWidget* medAbstractInteractor::buildToolBoxWidget()
* @brief buildToolBoxWidget reimplement it to construct and return the widget displayed in the
* view settings toolBox when the container of the parent view is single selected.
*/

/**
* @fn QWidget* medAbstractInteractor::buildToolBarWidget()
* @brief buildToolBoxWidget reimplement it to construct and return the widget displayed in the
* toolbar of the container where the parent view is displayed.
*/

/**
* @fn QWidget* medAbstractInteractor::buildLayerWidget()
* @brief buildToolBoxWidget reimplement it to construct and return the widget displayed in the
* layer toolbox when the container of the parent view is selected.
*/

/**
* @fn QList<medAbstractParameter*> linkableParameters()
* @brief linkableParameters reimplement it to return the parameters that you want to be linkable
*/

class medAbstractInteractorPrivate
{
public:
    medAbstractData* data;

    QPointer<QWidget> toolBoxWidget;
    QPointer<QWidget> toolBarWidget;
    QPointer<QWidget> layerWidget;
};

medAbstractInteractor::medAbstractInteractor(medAbstractView *parent):
    d(new medAbstractInteractorPrivate)
{
    setParent(parent);
    d->toolBarWidget = NULL;
    d->toolBoxWidget = NULL;
    d->layerWidget = NULL;
}

medAbstractInteractor::~medAbstractInteractor()
{
    delete d;
}

void medAbstractInteractor::setInputData(medAbstractData* data)
{
    d->data = data;
}

medAbstractData* medAbstractInteractor::inputData() const
{
    return d->data;
}

QWidget* medAbstractInteractor::toolBoxWidget()
{
    if(d->toolBoxWidget.isNull())
    {
        d->toolBoxWidget = this->buildToolBoxWidget();
    }

    return d->toolBoxWidget;
}

QWidget* medAbstractInteractor::toolBarWidget()
{
    if(d->toolBarWidget.isNull())
    {
        d->toolBarWidget = this->buildToolBarWidget();
    }

    return d->toolBarWidget;
}

QWidget* medAbstractInteractor::layerWidget()
{
    if(d->layerWidget.isNull())
    {
        d->layerWidget = this->buildLayerWidget();
    }

    return d->layerWidget;
}

/**
 * @brief updateWidgets Reimplement this methode to change the widget that you expose when the
 * state of the view changes. (i.e. Orientation, new data added)
 */
void medAbstractInteractor::updateWidgets()
{
}

void medAbstractInteractor::toXMLNode(QDomDocument* doc,QDomElement* currentNode)
{
	currentNode->setAttribute("name",name());
	currentNode->setAttribute("version",version());
	QDomElement elmt=doc->createElement("parameters");
	elmt.setAttribute("number",this->linkableParameters().size());
	for(int i=0;i<linkableParameters().size();i++)
	{
		QDomElement paramNode=doc->createElement("parameter");
		linkableParameters()[i]->toXMLNode(doc,&paramNode);
		elmt.appendChild(paramNode);
	}
	currentNode->appendChild(elmt);
}

void medAbstractInteractor::fromXMLNode(QDomElement* element)
{
	if(element->nodeName()!="interactor")
	{
		qWarning()<<"Unable to parse "<<element->nodeName();
		return;
	}
	QDomNodeList parameterList=element->elementsByTagName("parameter");
	qDebug()<<element->elementsByTagName("parameter").size();
	QHash<QString,QString> parameters;
	for(int i=0;i<parameterList.size();i++)
	{
		if(!(parameterList.at(i).isElement()))
		{
			qWarning()<<"failed to read a parameter";
		}
		QDomElement currentParameterElement =parameterList.at(i).toElement();
		QDomNodeList currentParametersValues=currentParameterElement.childNodes();
		QString name,type,value;
		for(int j=0;j<currentParametersValues.size();j++)
		{
			QString nodeName=currentParametersValues.at(j).nodeName();
			if(nodeName=="name")
				name=currentParametersValues.at(j).firstChild().toText().nodeValue();
			else if(nodeName=="type")
				type=currentParametersValues.at(j).firstChild().toText().nodeValue();
			else if(nodeName=="value")
				value=currentParametersValues.at(j).firstChild().toText().nodeValue(); 
		}
		parameters[name]=value;
	}
	
	restoreParameters(parameters);
}

void medAbstractInteractor::restoreParameters(QHash<QString,QString> parameters)
{//default implementation: do nothing
		
}

QString medAbstractInteractor::version() const
{
	return "0.0.1";
}

QString medAbstractInteractor::name() const
{
	return "undefined interactor";
}
