#ifndef _med_ITKProcessObjectObserver_h_
#define _med_ITKProcessObjectObserver_h_

#include <QObject>
#include <itkCommand.h>

#include "medItk/medItkExport.h"

namespace itk
{

  class QtSignalAdaptor;


  class MEDITK_EXPORT medProcessObjectObserver : public Command
  {
  public:
    typedef medProcessObjectObserver       Self;
    typedef itk::Command                   Superclass;
    typedef itk::SmartPointer<Self>        Pointer;
    typedef itk::SmartPointer<const Self>  ConstPointer;
    
    itkTypeMacro(medProcessObjectObserver, Command);
    itkNewMacro (Self);
    
    void Execute(itk::Object *caller, const itk::EventObject &event);
    void Execute(const itk::Object *caller, const itk::EventObject &event);
    
    void SetQtSignalAdaptor (QtSignalAdaptor *adaptor)
    { this->adaptor = adaptor; }
    QtSignalAdaptor *GetQtSignalAdaptor (void) const
    { return this->adaptor; }
    
  protected:
    medProcessObjectObserver();
    ~medProcessObjectObserver();
    
  private:
    QtSignalAdaptor* adaptor;
    
  };

  
  /** Helper class that interface Observers with Qt Signals */
  class MEDITK_EXPORT QtSignalAdaptor : public QObject
  {
    Q_OBJECT

  public:

    typedef medProcessObjectObserver CommandType;
    
    QtSignalAdaptor();
    virtual ~QtSignalAdaptor();

    CommandType *GetCommand(void)
    { return this->command; }
    
    void EmitSignal(int value)
    {
      emit Signal(value);
    }
    
  signals:
      void Signal(int);
    
  private:
      CommandType::Pointer command;
    
  };
  
  
} // end of namespace

#endif